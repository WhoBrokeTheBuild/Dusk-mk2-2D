#include "UIFrame.hpp"

namespace dusk
{

UIFrame::UIFrame()
{
    SetFocusable(false);
}

UIFrame::~UIFrame()
{

}

void UIFrame::Inherit(const UIElement* pInheritFrom)
{
    UIElement::Inherit(pInheritFrom);
    const UIFrame* pInheritFromFrame = dynamic_cast<const UIFrame*>(pInheritFrom);
    if (pInheritFromFrame)
    {

    }
}

} // namespace dusk