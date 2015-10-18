#include "UIInput.hpp"

namespace dusk
{

UIInput::UIInput()
{

}


UIInput::~UIInput()
{

}

void UIInput::Inherit(const UIElement* pInheritFrom)
{
    UIElement::Inherit(pInheritFrom);
    const UIInput* pInheritFromInput = dynamic_cast<const UIInput*>(pInheritFrom);
    if (pInheritFromInput)
    {

    }
}

}