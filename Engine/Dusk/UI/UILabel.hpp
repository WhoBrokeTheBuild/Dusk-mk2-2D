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
    virtual ~UILabel() { Term(); }

    virtual inline string GetClassName() const { return "UI Label"; }

    bool Init(shared_ptr<UIElement> inheritFrom);
    bool Init();
    void Term();

};

} // namespace dusk

#endif // DUSK_UI_UI_LABEL_HPP