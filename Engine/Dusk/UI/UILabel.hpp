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

    weak_ptr<UIElement> GetTarget() const { return mp_Target; }
    void SetTarget(weak_ptr<UIElement> pTarget) { mp_Target = pTarget; }

    virtual void Focus() override;
    virtual void MouseUp() override;
    virtual void MouseDown() override;

protected:

    weak_ptr<UIElement> mp_Target;
};

} // namespace dusk

#endif // DUSK_UI_UI_LABEL_HPP