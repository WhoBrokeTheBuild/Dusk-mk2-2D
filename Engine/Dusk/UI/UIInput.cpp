#include "UIInput.hpp"

namespace dusk
{

UIInput::UIInput()
{

}

bool UIInput::Init(shared_ptr<UIElement> inheritFrom)
{
    if (!UIElement::Init(inheritFrom))
        return false;

    return true;
}

bool UIInput::Init()
{
    if (!UIElement::Init())
        return false;

    return true;
}

void UIInput::Term()
{
    UIElement::Term();
}

}