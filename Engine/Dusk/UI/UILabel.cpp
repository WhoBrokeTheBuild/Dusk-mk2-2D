#include "UILabel.hpp"

namespace dusk
{

UILabel::UILabel()
{

}

UILabel::~UILabel()
{
}

void UILabel::Inherit(const UIElement* pInheritFrom)
{
    UIElement::Inherit(pInheritFrom);
    const UILabel* pInheritFromLabel = dynamic_cast<const UILabel*>(pInheritFrom);
    if (pInheritFromLabel)
    {

    }
}

}