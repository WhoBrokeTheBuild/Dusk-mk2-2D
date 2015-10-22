#ifndef CUSTOM_RENDER_FRAME_H
#define CUSTOM_RENDER_FRAME_H

#include <Dusk/UI/UIRenderFrame.hpp>
#include <Dusk/Logging/Logging.hpp>

using namespace dusk;

class CustomRenderFrame :
    public UIRenderFrame
{
public:

    virtual inline string GetClassName() const override { return "Custom Render Frame"; }

    virtual void OnUpdate(const Event& evt) override
    {
        UIRenderFrame::OnUpdate(evt);
        DuskLog("info", "Render Frame Updated");
    }

    virtual inline void Click() override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

};

#endif // CUSTOM_RENDER_FRAME_H