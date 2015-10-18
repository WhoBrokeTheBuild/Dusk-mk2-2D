#ifndef DUSK_UI_UI_LABEL_HPP
#define DUSK_UI_UI_LABEL_HPP

#include <Dusk/UI/UIElement.hpp>

namespace dusk
{

class UILabel :
    public UIElement
{
public:

    UILabel();
    virtual ~UILabel();

    virtual inline string GetClassName() const { return "UI Label"; }

    virtual void Inherit(const UIElement* pInheritFrom);
};

} // namespace dusk

#endif // DUSK_UI_UI_LABEL_HPP