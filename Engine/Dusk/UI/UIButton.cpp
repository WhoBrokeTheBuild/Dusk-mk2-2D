#include "UIButton.hpp"

#include <Dusk/Graphics/Cursor.hpp>

namespace dusk
{

UIButton::UIButton()
{

}

UIButton::~UIButton()
{

}

void UIButton::Inherit(const UIElement* pInheritFrom)
{
    UIElement::Inherit(pInheritFrom);
    const UIButton* pInheritFromButton = dynamic_cast<const UIButton*>(pInheritFrom);
    if (pInheritFromButton)
    {

    }
}

void UIButton::OnMouseButtonRelease(const Event& evt)
{
    auto pData = evt.GetDataAs<MouseButtonEventData>();

    UIElement::OnMouseButtonRelease(evt);

    if (m_State == StateActive)
        ChangeState(StateHover);
}

void UIButton::ChangeState(const UIState& newState)
{
    sf::WindowHandle handle = Program::Inst()->GetGraphicsSystem()->GetWindowHandle();
    if (newState == StateHover || newState == StateActive)
    {
        Cursor handCursor(Cursor::HAND);
        handCursor.set(handle);
    }
    else
    {
        Cursor handCursor(Cursor::NORMAL);
        handCursor.set(handle);
    }

    UIElement::ChangeState(newState);
}

}