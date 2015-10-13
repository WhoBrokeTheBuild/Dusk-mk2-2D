#ifndef TEST_APP_H
#define TEST_APP_H

#include <Dusk/Program.hpp>
#include <Dusk/Timing/FrameTimeInfo.hpp>
#include <Dusk/Graphics/GraphicsContext.hpp>
#include <Dusk/Graphics/Font.hpp>
#include <Dusk/Graphics/TextBuffer.hpp>
#include <Dusk/UI/UIManager.hpp>

class TestApp :
    public dusk::Program
{
public:

    TestApp();
    virtual inline ~TestApp() { Term(); }

    virtual inline string GetClassName() const { return "Test App"; }

protected:

    virtual bool Init() override;

    virtual void Term() override;

    virtual void Update(dusk::FrameTimeInfo& timeInfo) override;

    virtual void Render(dusk::GraphicsContext* ctx) override;

private:

    dusk::UIManager m_UIManager;

};

#endif // TEST_APP_H