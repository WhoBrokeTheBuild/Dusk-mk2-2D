#include "UIFrame.hpp"

namespace dusk
{

UIFrame::UIFrame()
{

}

bool UIFrame::Init(shared_ptr<UIElement> inheritFrom)
{
    if (!UIElement::Init(inheritFrom))
        return false;

    return true;
}

bool UIFrame::Init()
{
    if (!UIElement::Init())
        return false;

    return true;
}

void UIFrame::Term()
{
    UIElement::Term();
}

} // namespace dusk