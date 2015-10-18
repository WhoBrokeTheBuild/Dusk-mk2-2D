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
    virtual ~UIInput();

    virtual inline string GetClassName() const { return "UI Input"; }

    virtual void Inherit(const UIElement* pInheritFrom);

};

} // namespace dusk

#endif // DUSK_UI_UI_INPUT_HPP