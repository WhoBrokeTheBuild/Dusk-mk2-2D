#ifndef DUSK_PROGRAM_H
#define DUSK_PROGRAM_H

#include <Dusk/Events/EventDispatcher.hpp>
#include <Dusk/Tracking/TrackedObject.hpp>
#include <Dusk/Graphics/GraphicsSystem.hpp>
#include <Dusk/Events/Event.hpp>
#include <Dusk/Scripting/ScriptHost.hpp>
#include <Dusk/Input/InputSystem.hpp>

#include <lua.hpp>

namespace dusk
{

class GraphicsContext;

class Scripting;

class FrameTimeInfo;

class Program :
    public EventDispatcher,
    public TrackedObject
{

public:

    // Singleton Instance

    static inline Program* Inst() { return sp_Inst; }

    // Events

    static EventID EvtUpdate;
    static EventID EvtRender;
    static EventID EvtExit;

    Program();
    Program(const Program &) = delete;
    Program& operator=(const Program &) = delete;
    virtual ~Program();

    virtual inline string GetClassName() const { return "Program"; }

    Program* Run(int argc, char* argv[]);
    inline void Exit() { m_Running = false; }

    inline double GetCurrentFPS() const { return m_CurrentFPS; }

    inline double GetTargetFPS() const { return m_TargetFPS; }

    void SetTargetFPS(double fps);

    GraphicsSystem* GetGraphicsSystem() const;
    InputSystem* GetInputSystem() const;
    //AudioSystem* GetAudioSystem() const;

protected:

    ScriptHost* GetScriptHost();

    virtual void Update(FrameTimeInfo& timeInfo);
    virtual void PreRender(GraphicsContext* ctx);
    virtual void Render(GraphicsContext* ctx);
    virtual void PostRender(GraphicsContext* ctx);

private:

    static Program* sp_Inst;

    unique_ptr<GraphicsSystem> mp_GraphicsSystem;
    unique_ptr<InputSystem> mp_InputSystem;
    //AudioSystem* mp_AudioSystem;

    bool m_Running;

    double m_TargetFPS;
    double m_CurrentFPS;
    double m_UpdateInterval;

    unique_ptr<ScriptHost> mp_ScriptHost;

public:

    static void Script_RegisterFunctions();
    static int Script_GetProgram(lua_State* L);
    static int Script_Exit(lua_State* L);
    static int Script_GetGraphicsSystem(lua_State* L);
    static int Script_GetInputSystem(lua_State* L);
    static int Script_AddEventListener(lua_State* L);

}; // class Program

class UpdateEventData :
    public EventData
{
public:

    UpdateEventData(FrameTimeInfo* timeInfo) :
        mp_TimeInfo(timeInfo)
    { }

    virtual inline string GetClassName() const
    {
        return "Update Event Data";
    }

    virtual inline EventData* Clone() const
    {
        return New UpdateEventData(mp_TimeInfo);
    }

    FrameTimeInfo* GetTimeInfo();

    virtual int PushDataToLua(lua_State* L) const;

private:

    FrameTimeInfo* mp_TimeInfo;

}; // class UpdateEventData

class RenderEventData :
    public EventData
{
public:

    RenderEventData(GraphicsContext* ctx) :
        mp_Context(ctx)
    { }

    virtual inline string GetClassName() const
    {
        return "Render Event Data";
    }

    virtual inline EventData* Clone() const
    {
        return New RenderEventData(mp_Context);
    }

    virtual int PushDataToLua(lua_State* L) const;

    virtual GraphicsContext* GetContext();

private:

    GraphicsContext* mp_Context;

}; // class RenderEventData

} // namespace dusk

#endif // DUSK_PROGRAM_H
