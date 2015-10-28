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
    }

    virtual void OnMouseMove(const Event& evt) override
    {
        UIRenderFrame::OnMouseMove(evt);

        auto pData = evt.GetDataAs<MouseMoveEventData>();

        if (m_MouseDown && GetBounds().contains(pData->GetPos()))
        {
            DuskLog("info", "Custom Render Frame Mouse Dragged");
        }
    }

    virtual inline void MouseUp() override
    {
        UIRenderFrame::MouseUp();
        m_MouseDown = false;
    }

    virtual inline void MouseDown() override
    {
        UIRenderFrame::MouseDown();
        m_MouseDown = true;
    }

private:

    bool m_MouseDown = false;

};

#endif // CUSTOM_RENDER_FRAME_H