#include "UIElement.hpp"

#include <Dusk/Program.hpp>
#include <Dusk/Graphics/GraphicsContext.hpp>
#include <Dusk/Logging/Logging.hpp>
#include <Dusk/UI/UIManager.hpp>

#include <cfloat>
#include <SFML/Graphics/RectangleShape.hpp>

namespace dusk
{

UIElement::UIElement()
{
    UpdateLayout();
}

UIElement::~UIElement()
{
    if (auto pRelativeTo = m_RelativeTo.lock())
        pRelativeTo->RemoveEventListener(EvtLayoutChange, this, &UIElement::OnRelativeToLayoutChange);
}

void UIElement::Inherit(const UIElement* pInheritFrom)
{
    m_Active = pInheritFrom->m_Active;
    m_Visible = pInheritFrom->m_Visible;
    m_TargetSize = pInheritFrom->m_TargetSize;
    m_RelativeTo = pInheritFrom->m_RelativeTo;
    m_RelativePoint = pInheritFrom->m_RelativePoint;
    m_Offset = pInheritFrom->m_Offset;
    m_BackgroundColor = pInheritFrom->m_BackgroundColor;
    m_BorderSize = pInheritFrom->m_BorderSize;
    m_BorderColor = pInheritFrom->m_BorderColor;
    m_Font = pInheritFrom->m_Font;
    m_TextBuffer = pInheritFrom->m_TextBuffer;

    UpdateLayout();
}

void UIElement::SetUIManager(UIManager* pUIManager)
{
    mp_UIManager = pUIManager;
}

void UIElement::OnUpdate(const Event& evt)
{
    if (!m_Active)
        return;

    Dispatch(Event(UIElement::EvtUpdate, *evt.GetData()));

    for (auto& child : m_Children)
        child->OnUpdate(evt);
}

void UIElement::OnRender(const Event& evt)
{
    auto pData = evt.GetDataAs<RenderEventData>();

    if (!m_Visible)
        return;

    Dispatch(Event(UIElement::EvtRender, *evt.GetData()));

    sf::RectangleShape rect(m_Size);
    rect.setPosition(m_Pos);
    rect.setFillColor(m_BackgroundColor.GetValue(m_State));
    pData->GetContext()->Draw(rect);

    float borderSize = m_BorderSize.GetValue(m_State);
    if (borderSize > 0)
    {
        sf::RectangleShape borderRect(m_Size);
        borderRect.setPosition(m_Pos);
        borderRect.setFillColor(Color::Transparent);
        borderRect.setOutlineThickness(borderSize);
        borderRect.setOutlineColor(m_BorderColor.GetValue(m_State));
        pData->GetContext()->Draw(borderRect);
    }

    m_TextBuffer.SetPos(m_Pos);
    pData->GetContext()->Draw(&m_TextBuffer);

    for (auto& child : m_Children)
        child->OnRender(evt);
}

void UIElement::OnMouseMove(const Event& evt)
{
    auto pData = evt.GetDataAs<MouseMoveEventData>();

    if (m_State == StateDisabled)
        return;

    if (GetBounds().contains(pData->GetPos()))
    {
        if (!m_MouseOver)
        {
            m_MouseOver = true;
            MouseEnter();
            UpdateState();
        }
    }
    else
    {
        if (m_MouseOver) 
        {
            m_MouseOver = false;
            MouseLeave();
            UpdateState();
        }
    }

    for (auto& child : m_Children)
        child->OnMouseMove(evt);
}

void UIElement::OnMouseButtonPress(const Event& evt)
{
    auto pData = evt.GetDataAs<MouseButtonEventData>();

    if (m_State == StateDisabled)
        return;

    if (m_MouseOver)
    {
        m_MouseDown = true;
        MouseDown();
        Focus();
        UpdateState();
    }

    for (auto& child : m_Children)
        child->OnMouseButtonPress(evt);
}

void UIElement::OnMouseButtonRelease(const Event& evt)
{
    auto pData = evt.GetDataAs<MouseButtonEventData>();
    
    if (m_State == StateDisabled)
        return;

    if (m_MouseDown)
    {
        m_MouseDown = false;
        MouseUp();
        UpdateState();
    }

    for (auto& child : m_Children)
        child->OnMouseButtonRelease(evt);
}

void UIElement::OnRelativeToLayoutChange(const Event& evt)
{
    UpdateLayout();
    Dispatch(evt);
}

void UIElement::Focus()
{
    if (!m_Focusable) return;

    UIElement* pFocusedElement = mp_UIManager->GetFocusedElement();
    mp_UIManager->SetFocusedElement(this);
    if (pFocusedElement)
    {
        pFocusedElement->Blur();
    }

    m_HasFocus = true;
    UpdateState();
    Dispatch(Event(UIElement::EvtFocus));
}

void UIElement::Blur()
{
    m_HasFocus = false;
    UpdateState();
    Dispatch(Event(UIElement::EvtBlur));
}

void UIElement::SetFocusable(bool focusable)
{
    m_Focusable = focusable;
    if (!m_Focusable && m_HasFocus)
    {
        Blur();
    }
}

void UIElement::SetActive(bool active)
{
    m_Active = active;
    UpdateState();
    if (m_Active)
    {
        Dispatch(Event(UIElement::EvtActivate));
    }
    else
    {
        Dispatch(Event(UIElement::EvtDeactivate));
    }
}

void UIElement::SetVisible(bool visible)
{
    m_Visible = visible;
    if (m_Visible)
        Dispatch(Event(UIElement::EvtShow));
    else
        Dispatch(Event(UIElement::EvtHide));
}

void UIElement::UpdateState()
{
    if (!m_Active)
    {
        m_State = StateDisabled;
    }
    else if (m_MouseOver)
    {
        m_State = StateHover;
    }
    else if (m_MouseDown || m_HasFocus)
    {
        m_State = StateActive;
    }
    else
    {
        m_State = StateDefault;
    }

    UpdateStateData();
}

void UIElement::SetSize(const Vector2f& size)
{
    m_TargetSize = size;

    UpdateLayout();
    Dispatch(Event(EvtLayoutChange));
}

void UIElement::SetParent(weak_ptr<UIElement> pParent)
{
    mp_Parent = pParent;

    UpdateLayout();
    Dispatch(Event(EvtLayoutChange));
}

void UIElement::SetRelativeTo(weak_ptr<UIElement> pRelativeTo)
{
    if (auto pOldRelativeTo = m_RelativeTo.lock())
        pOldRelativeTo->RemoveEventListener(EvtLayoutChange, this, &UIElement::OnRelativeToLayoutChange);

    m_RelativeTo = pRelativeTo;

    if (auto pNewRelativeTo = m_RelativeTo.lock())
        pNewRelativeTo->AddEventListener(EvtLayoutChange, this, &UIElement::OnRelativeToLayoutChange);

    UpdateLayout();
    Dispatch(Event(EvtLayoutChange));
}

void UIElement::SetRelativePoint(UIRelPoint relPoint)
{
    m_RelativePoint = relPoint;

    UpdateLayout();
    Dispatch(Event(EvtLayoutChange));
}

void UIElement::SetOffset(const Vector2f& offset)
{
    m_Offset = offset;

    UpdateLayout();
    Dispatch(Event(EvtLayoutChange));
}

void UIElement::SetFont(UIFont* pFont, const UIState& state /*= UIState::StateDefault*/)
{
    m_Font.SetValue(state, pFont);
    UpdateStateData();
}

void UIElement::SetText(const string& text)
{
    m_TextBuffer.SetText(text);
    UpdateLayout();
}

void UIElement::AddChild(shared_ptr<UIElement>& pChild)
{
    m_Children.add(pChild);
}

void UIElement::UpdateStateData()
{
    UIFont* pUIFont = m_Font.GetValue(m_State);
    if (pUIFont)
    {
        m_TextBuffer.SetFont(pUIFont->GetFont());
        m_TextBuffer.SetFontSize(pUIFont->GetFontSize());
        m_TextBuffer.SetColor(pUIFont->GetColor());
        UpdateLayout();
    }
}

void UIElement::UpdateLayout()
{
    if (auto pRelativeTo = m_RelativeTo.lock())
    {
        Vector2f relPos = pRelativeTo->GetPos();
        Vector2f relSize = pRelativeTo->GetSize();
        switch (m_RelativePoint)
        {
        case TopLeft:

            m_Pos.x = relPos.x + m_Offset.x;
            m_Pos.y = relPos.y + m_Offset.y;

            break;
        case TopRight:

            m_Pos.x = relPos.x + relSize.x + m_Offset.x;
            m_Pos.y = relPos.y + m_Offset.y;

            break;
        case BottomLeft:

            m_Pos.x = relPos.x + m_Offset.x;
            m_Pos.y = relPos.y + m_Size.y + m_Offset.y;

            break;
        case BottomRight:

            m_Pos.x = relPos.x + relSize.x + m_Offset.x;
            m_Pos.y = relPos.y + relSize.y + m_Offset.y;

            break;
        }
    }
    else
    {
        m_Pos = m_Offset;
    }

    Vector2f parentSize;
    if (auto pParent = mp_Parent.lock())
        parentSize = pParent->GetSize();

    Vector2f textSize = m_TextBuffer.GetSize();

    if (m_TargetSize.x == FLT_MIN)
    {
        m_Size.x = textSize.x;
    }
    else if (m_TargetSize.x == FLT_MAX)
    {
        m_Size.x = parentSize.x - m_Pos.x;
    }
    else
    {
        m_Size.x = m_TargetSize.x;
    }

    if (m_TargetSize.y == FLT_MIN)
    {
        m_Size.y = textSize.y;
    }
    else if (m_TargetSize.y == FLT_MAX)
    {
        m_Size.y = parentSize.y - m_Pos.y;
    }
    else
    {
        m_Size.y = m_TargetSize.y;
    }
}

void UIElement::Script_RegisterFunctions()
{
    Scripting::RegisterFunction("dusk_ui_element_is_mouse_over", &UIElement::Script_IsMouseOver);
    Scripting::RegisterFunction("dusk_ui_element_is_mouse_down", &UIElement::Script_IsMouseDown);
    Scripting::RegisterFunction("dusk_ui_element_has_focus", &UIElement::Script_HasFocus);

    Scripting::RegisterFunction("dusk_ui_element_is_focusable", &UIElement::Script_IsFocusable);
    Scripting::RegisterFunction("dusk_ui_element_set_focusable", &UIElement::Script_SetFocusable);

    Scripting::RegisterFunction("dusk_ui_element_is_active", &UIElement::Script_IsActive);
    Scripting::RegisterFunction("dusk_ui_element_set_active", &UIElement::Script_SetActive);

    Scripting::RegisterFunction("dusk_ui_element_is_visible", &UIElement::Script_IsVisible);
    Scripting::RegisterFunction("dusk_ui_element_set_visible", &UIElement::Script_SetVisible);

    Scripting::RegisterFunction("dusk_ui_element_get_name", &UIElement::Script_GetValue);

    Scripting::RegisterFunction("dusk_ui_element_get_state", &UIElement::Script_GetState);

    Scripting::RegisterFunction("dusk_ui_element_get_pos", &UIElement::Script_GetPos);

    Scripting::RegisterFunction("dusk_ui_element_get_size", &UIElement::Script_GetSize);
    Scripting::RegisterFunction("dusk_ui_element_set_size", &UIElement::Script_SetSize);
}

int UIElement::Script_IsMouseOver(lua_State* L)
{
    UIElement* pElement = (UIElement*)lua_tointeger(L, 1);
    const bool& value = pElement->IsMouseOver();
    lua_pushboolean(L, (int)value);
    return 1;
}

int UIElement::Script_IsMouseDown(lua_State* L)
{
    UIElement* pElement = (UIElement*)lua_tointeger(L, 1);
    const bool& value = pElement->IsMouseDown();
    lua_pushboolean(L, (int)value);
    return 1;
}

int UIElement::Script_HasFocus(lua_State* L)
{
    UIElement* pElement = (UIElement*)lua_tointeger(L, 1);
    const bool& value = pElement->HasFocus();
    lua_pushboolean(L, (int)value);
    return 1;
}

int UIElement::Script_IsFocusable(lua_State* L)
{
    UIElement* pElement = (UIElement*)lua_tointeger(L, 1);
    const bool& value = pElement->IsFocusable();
    lua_pushboolean(L, (int)value);
    return 1;
}

int UIElement::Script_SetFocusable(lua_State* L)
{
    return 0;
}

int UIElement::Script_IsActive(lua_State* L)
{
    UIElement* pElement = (UIElement*)lua_tointeger(L, 1);
    const bool& value = pElement->IsActive();
    lua_pushboolean(L, (int)value);
    return 1;
}

int UIElement::Script_SetActive(lua_State* L)
{
    return 0;
}

int UIElement::Script_IsVisible(lua_State* L)
{
    UIElement* pElement = (UIElement*)lua_tointeger(L, 1);
    const bool& value = pElement->IsVisible();
    lua_pushboolean(L, (int)value);
    return 1;
}

int UIElement::Script_SetVisible(lua_State* L)
{
    return 0;
}

int UIElement::Script_GetValue(lua_State* L)
{
    UIElement* pElement = (UIElement*)lua_tointeger(L, 1);
    const string& name = pElement->GetName();
    lua_pushstring(L, name.c_str());
    return 1;
}

int UIElement::Script_GetState(lua_State* L)
{
    UIElement* pElement = (UIElement*)lua_tointeger(L, 1);
    const UIState& state = pElement->GetState();
    lua_pushinteger(L, state);
    return 1;
}

int UIElement::Script_GetPos(lua_State* L)
{
    UIElement* pElement = (UIElement*)lua_tointeger(L, 1);
    const Vector2f& pos = pElement->GetPos();
    lua_pushnumber(L, pos.x);
    lua_pushnumber(L, pos.y);
    return 2;
}

int UIElement::Script_GetSize(lua_State* L)
{
    UIElement* pElement = (UIElement*)lua_tointeger(L, 1);
    const Vector2f& size = pElement->GetSize();
    lua_pushnumber(L, size.x);
    lua_pushnumber(L, size.y);
    return 2;
}

int UIElement::Script_SetSize(lua_State* L)
{
    UIElement* pElement = (UIElement*)lua_tointeger(L, 1);
    Vector2f size;

    if (lua_isstring(L, 2)) 
    {
        const string& xStr = lua_tostring(L, 2);
        if (xStr == "min")
        {
            size.x = FLT_MIN;
        }
        else if (xStr == "max")
        {
            size.x = FLT_MAX;
        }
    }
    else
    {
        size.x = (float)lua_tonumber(L, 2);
    }

    float y = 0.0f;
    if (lua_isstring(L, 3))
    {
        const string& yStr = lua_tostring(L, 3);
        if (yStr == "min")
        {
            size.y = FLT_MIN;
        }
        else if (yStr == "max")
        {
            size.y = FLT_MAX;
        }
    }
    else
    {
        size.y = (float)lua_tonumber(L, 3);
    }

    pElement->SetSize(size);
    return 0;
}

int StateChangeData::PushDataToLua(lua_State* L) const
{
    lua_pushinteger(L, m_OldState);
    lua_pushinteger(L, m_NewState);
    return 2;
}

} // namespace dusk
