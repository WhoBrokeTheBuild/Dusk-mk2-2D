#ifndef DUSK_UI_UI_FRAME_HPP
#define DUSK_UI_UI_FRAME_HPP

#include <Dusk/UI/UIElement.hpp>

namespace dusk
{

class UIFrame :
    public UIElement
{
public:

    UIFrame();
    virtual ~UIFrame();

    virtual inline string GetClassName() const { return "UI Frame"; }

    virtual void Inherit(const UIElement* pInheritFrom);

};

} // namespace dusk

#endif // DUSK_UI_UI_FRAME_HPP