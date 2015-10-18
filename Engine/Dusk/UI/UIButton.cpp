#include "UIButton.hpp"

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

}