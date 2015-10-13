#ifndef DUSK_UI_UI_INPUT_HPP
#define DUSK_UI_UI_INPUT_HPP

#include <Dusk/UI/UIElement.hpp>

namespace dusk
{

class UIInput :
    public UIElement
{
public:

    UIInput();
    virtual ~UIInput() { Term(); }

    virtual inline string GetClassName() const { return "UI Input"; }

    bool Init(shared_ptr<UIElement> inheritFrom);
    bool Init();
    void Term();

};

} // namespace dusk

#endif // DUSK_UI_UI_INPUT_HPP