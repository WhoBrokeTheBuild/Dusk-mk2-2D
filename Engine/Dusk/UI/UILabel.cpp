#include "UILabel.hpp"

namespace dusk
{

UILabel::UILabel()
{

}

bool UILabel::Init(shared_ptr<UIElement> inheritFrom)
{
    if (!UIElement::Init(inheritFrom))
        return false;

    return true;
}

bool UILabel::Init()
{
    if (!UIElement::Init())
        return false;

    return true;
}

void UILabel::Term()
{
    UIElement::Term();
}

}