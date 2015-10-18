#include "UIElement.hpp"

#include <Dusk/Program.hpp>
#include <Dusk/Graphics/GraphicsContext.hpp>
#include <Dusk/Logging/Logging.hpp>

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
        pRelativeTo->RemoveEventListener(EvtLayoutChanged, this, &UIElement::OnRelativeToLayoutChanged);
}

void UIElement::Inherit(const UIElement* pInheritFrom)
{
    m_Active = pInheritFrom->m_Active;
    m_Visible = pInheritFrom->m_Visible;
    m_TargetSize = pInheritFrom->m_TargetSize;
    m_RelativeTo = pInheritFrom->m_RelativeTo;
    m_RelativePoint = pInheritFrom->m_RelativePoint;
    m_Offset = pInheritFrom->m_Offset;
    m_BorderSize = pInheritFrom->m_BorderSize;
    m_BorderColor = pInheritFrom->m_BorderColor;
    m_Font = pInheritFrom->m_Font;
    m_TextBuffer = pInheritFrom->m_TextBuffer;

    UpdateLayout();
}

void UIElement::OnUpdate(const Event& evt)
{
    if (!m_Active)
        return;

    for (auto& child : m_Children)
        child->OnUpdate(evt);
}

void UIElement::OnRender(const Event& evt)
{
    if (!m_Visible)
        return;

    RenderEventData* pData = evt.GetDataAs<RenderEventData>();

    sf::RectangleShape rect(m_Size);
    rect.setPosition(m_Pos);
    rect.setFillColor(Color::White);
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

void UIElement::OnRelativeToLayoutChanged(const Event& evt)
{
    UpdateLayout();
    Dispatch(evt);
}

void UIElement::SetSize(const Vector2f& size)
{
    m_TargetSize = size;

    UpdateLayout();
    Dispatch(Event(EvtLayoutChanged));
}

void UIElement::SetParent(weak_ptr<UIElement> pParent)
{
    mp_Parent = pParent;

    UpdateLayout();
    Dispatch(Event(EvtLayoutChanged));
}

void UIElement::SetRelativeTo(weak_ptr<UIElement> pRelativeTo)
{
    if (auto pOldRelativeTo = m_RelativeTo.lock())
        pOldRelativeTo->RemoveEventListener(EvtLayoutChanged, this, &UIElement::OnRelativeToLayoutChanged);

    m_RelativeTo = pRelativeTo;

    if (auto pNewRelativeTo = m_RelativeTo.lock())
        pNewRelativeTo->AddEventListener(EvtLayoutChanged, this, &UIElement::OnRelativeToLayoutChanged);

    UpdateLayout();
    Dispatch(Event(EvtLayoutChanged));
}

void UIElement::SetRelativePoint(UIRelPoint relPoint)
{
    m_RelativePoint = relPoint;

    UpdateLayout();
    Dispatch(Event(EvtLayoutChanged));
}

void UIElement::SetOffset(const Vector2f& offset)
{
    m_Offset = offset;

    UpdateLayout();
    Dispatch(Event(EvtLayoutChanged));
}

void UIElement::SetFont(UIFont* pFont, const UIState& state /*= UIState::StateDefault*/)
{
    m_Font.SetValue(state, pFont);
    UpdateState();
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

void UIElement::UpdateState()
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
}

} // namespace dusk
