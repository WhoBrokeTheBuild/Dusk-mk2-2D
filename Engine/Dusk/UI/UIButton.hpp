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
    virtual ~UIButton() { Term(); }

    virtual inline string GetClassName() const { return "UI Button"; }

    bool Init(shared_ptr<UIElement> inheritFrom);
    bool Init();
    void Term();

};

} // namespace dusk

#endif // DUSK_UI_UI_BUTTON_HPP