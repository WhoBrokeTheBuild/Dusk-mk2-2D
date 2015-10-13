#include "UIButton.hpp"

namespace dusk
{

UIButton::UIButton()
{

}

bool UIButton::Init(shared_ptr<UIElement> inheritFrom)
{
    if (!UIElement::Init(inheritFrom))
        return false;

    return true;
}

bool UIButton::Init()
{
    if (!UIElement::Init())
        return false;

    return true;
}

void UIButton::Term()
{
    UIElement::Term();
}

}