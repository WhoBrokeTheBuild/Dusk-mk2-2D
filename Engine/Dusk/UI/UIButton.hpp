#ifndef DUSK_UI_UI_BUTTON_HPP
#define DUSK_UI_UI_BUTTON_HPP

#include <Dusk/UI/UIElement.hpp>

namespace dusk
{

class UIButton :
    public UIElement
{
public:

    UIButton();
    virtual ~UIButton();

    virtual inline string GetClassName() const { return "UI Button"; }

    virtual void Inherit(const UIElement* pInheritFrom);

protected:

    virtual void UpdateState() override;

};

} // namespace dusk

#endif // DUSK_UI_UI_BUTTON_HPP