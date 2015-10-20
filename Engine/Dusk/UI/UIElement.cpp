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
        if (m_State == StateDefault)
        {
            ChangeState(StateHover);
            MouseEnter();
        }
    }
    else
    {
        if (m_State == StateHover)
        {
            ChangeState(StateDefault);
            MouseLeave();
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

    if (m_State == StateHover)
    {
        ChangeState(StateActive);
        MouseDown();
        Focus();
    }

    for (auto& child : m_Children)
        child->OnMouseButtonPress(evt);
}

void UIElement::OnMouseButtonRelease(const Event& evt)
{
    auto pData = evt.GetDataAs<MouseButtonEventData>();
    
    if (m_State == StateDisabled)
        return;

    if (m_State == StateActive)
    {
        MouseUp();
        Click();
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
    UIElement* pFocusedElement = mp_UIManager->GetFocusedElement();
    if (pFocusedElement)
        pFocusedElement->Blur();
    mp_UIManager->SetFocusedElement(this);
    Dispatch(Event(UIElement::EvtFocus));
}

void UIElement::SetActive(bool active)
{
    m_Active = active;
    if (m_Active)
        Dispatch(Event(UIElement::EvtActivate));
    else
    {
        ChangeState(UIState::StateDisabled);
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

void UIElement::ChangeState(const UIState& newState)
{
    m_State = newState;
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
    }

    UpdateLayout();
}

void UIElement::UpdateLayout()
{
    if (auto pRelativeTo = m_RelativeTo.lock())
    {
        Vector2f relPos = pRelativeTo->GetPos();
        switch (m_RelativePoint)
        {
        case TopLeft:

            m_Pos.x = relPos.x + m_Offset.x;
            m_Pos.y = relPos.y + m_Offset.y;

            break;
        case TopRight:

            m_Pos.x = relPos.x + m_Size.x + m_Offset.x;
            m_Pos.y = relPos.y + m_Offset.y;

            break;
        case BottomLeft:

            m_Pos.x = relPos.x + m_Offset.x;
            m_Pos.y = relPos.y + m_Size.y + m_Offset.y;

            break;
        case BottomRight:

            m_Pos.x = relPos.x + m_Size.x + m_Offset.x;
            m_Pos.y = relPos.y + m_Size.y + m_Offset.y;

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

int StateChangeData::PushDataToLua(lua_State* L) const
{
    lua_pushinteger(L, m_OldState);
    lua_pushinteger(L, m_NewState);
    return 2;
}

} // namespace dusk
