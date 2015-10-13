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
    virtual ~UIFrame() { Term(); }

    virtual inline string GetClassName() const { return "UI Frame"; }

    bool Init(shared_ptr<UIElement> inheritFrom);
    bool Init();
    void Term();

};

} // namespace dusk

#endif // DUSK_UI_UI_FRAME_HPP