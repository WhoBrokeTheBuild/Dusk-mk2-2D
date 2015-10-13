#include "UIElement.hpp"

#include <Dusk/Program.hpp>
#include <Dusk/Graphics/GraphicsContext.hpp>
#include <Dusk/Logging/Logging.hpp>

#include <SFML/Graphics/RectangleShape.hpp>

namespace dusk
{

EventID UIElement::EvtLayoutChanged = 1;

UIElement::UIElement() :
    m_Active(false),
    m_Visible(false),
    m_Pos(),
    m_TargetSize(),
    m_Size(),
    m_RelativeTo(nullptr),
    m_RelativePoint(TopLeft),
    m_BorderSize(),
    m_BorderColor(),
    m_Font(),
    m_Parent(nullptr),
    m_Children()
{

}

bool UIElement::Init(shared_ptr<UIElement> inheritFrom)
{
    m_RelativeTo = inheritFrom->m_RelativeTo;
    m_RelativePoint = inheritFrom->m_RelativePoint;
    m_Offset = inheritFrom->m_Offset;
    m_BorderSize = inheritFrom->m_BorderSize;
    m_BorderColor = inheritFrom->m_BorderColor;
    m_Font = inheritFrom->m_Font;
    m_TargetSize = inheritFrom->m_TargetSize;

    m_Active = true;
    m_Visible = true;

    UpdateLayout();

    return true;
}

bool UIElement::Init()
{
    m_RelativeTo = nullptr;
    m_RelativePoint = TopLeft;
    m_Offset = Vector2f();
    m_TargetSize = Vector2f();

    m_Active = true;
    m_Visible = true;

    UpdateLayout();

    return true;
}

void UIElement::Term()
{
    if (m_RelativeTo)
        m_RelativeTo->RemoveEventListener(EvtLayoutChanged, this, &UIElement::OnRelativeToLayoutChanged);

    m_Active = false;
    m_Visible = false;
    m_RelativeTo = nullptr;
    m_Parent = nullptr;
    m_Children.clear();

    RemoveAllListeners();
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
    rect.setOutlineColor(Color::Black);
    rect.setOutlineThickness(1.0f);

    DuskExtLog("info", "%s (%f %f) (%f %f)", m_Name.c_str(), m_Pos.x, m_Pos.y, m_Size.x, m_Size.y);
    pData->GetContext()->Draw(rect);
    
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

void UIElement::SetParent(shared_ptr<UIElement> parent)
{
    m_Parent = parent;

    UpdateLayout();
    Dispatch(Event(EvtLayoutChanged));
}

void UIElement::SetRelativeTo(shared_ptr<UIElement> relTo)
{
    if (m_RelativeTo)
        m_RelativeTo->RemoveEventListener(EvtLayoutChanged, this, &UIElement::OnRelativeToLayoutChanged);

    m_RelativeTo = relTo;
    m_RelativeTo->AddEventListener(EvtLayoutChanged, this, &UIElement::OnRelativeToLayoutChanged);

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

void UIElement::AddChild(shared_ptr<UIElement>& pChild)
{
    m_Children.add(pChild);
}

void UIElement::UpdateLayout()
{
    Vector2f parentSize;
    if (m_Parent)
        parentSize = m_Parent->GetSize();

    if (m_TargetSize.x == FLT_MIN)
    {
        m_Size.x = 10.0f;
        // TODO
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
        m_Size.y = 10.0f;
        // TODO
    }
    else if (m_TargetSize.y == FLT_MAX)
    {
        m_Size.y = parentSize.y - m_Pos.y;
    }
    else
    {
        m_Size.y = m_TargetSize.y;
    }

    if (m_RelativeTo == nullptr)
    {
        m_Pos = m_Offset;
        return;
    }

    Vector2f relPos = m_RelativeTo->GetPos();
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

} // namespace dusk