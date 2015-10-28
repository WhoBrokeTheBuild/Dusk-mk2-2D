#include "UILabel.hpp"

namespace dusk
{

UILabel::UILabel()
{
    SetFocusable(false);
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
        mp_Target = pInheritFromLabel->GetTarget();
    }
}

void UILabel::Focus()
{
    UIElement::Focus();
    if (auto pTarget = mp_Target.lock())
    {
        pTarget->Focus();
    }
}

void UILabel::MouseUp()
{
    UIElement::MouseUp();
    if (auto pTarget = mp_Target.lock())
    {
        pTarget->MouseUp();
    }
}

void UILabel::MouseDown()
{
    UIElement::MouseDown();
    if (auto pTarget = mp_Target.lock())
    {
        pTarget->MouseDown();
    }
}

}