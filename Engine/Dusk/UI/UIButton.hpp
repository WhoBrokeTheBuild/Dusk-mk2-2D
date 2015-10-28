#ifndef DUSK_UI_UI_BUTTON_HPP
#define DUSK_UI_UI_BUTTON_HPP

#include <Dusk/UI/UIElement.hpp>

namespace dusk
{

class UIButton :
    public UIElement
{
public:

    enum : EventID 
    {
        EvtClick = 100,
    };

    UIButton();
    virtual ~UIButton();

    virtual inline string GetClassName() const { return "UI Button"; }

    virtual void Inherit(const UIElement* pInheritFrom);

    virtual void OnMouseButtonRelease(const Event& evt) override;

    virtual inline void Click() { Dispatch(Event(UIButton::EvtClick)); }

protected:

    virtual void UpdateState() override;

};

} // namespace dusk

#endif // DUSK_UI_UI_BUTTON_HPP