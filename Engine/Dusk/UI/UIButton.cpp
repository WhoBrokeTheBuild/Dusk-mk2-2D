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

void UIButton::UpdateState()
{
    UIElement::UpdateState();

    sf::WindowHandle handle = Program::Inst()->GetGraphicsSystem()->GetWindowHandle();
    if (m_State == StateHover)
    {
        Cursor handCursor(Cursor::HAND);
        handCursor.set(handle);
    }
    else
    {
        Cursor handCursor(Cursor::NORMAL);
        handCursor.set(handle);
    }
}

}