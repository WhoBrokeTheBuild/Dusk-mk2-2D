#ifndef DUSK_PROGRAM_H
#define DUSK_PROGRAM_H

#include <Dusk/Events/IEventDispatcher.hpp>
#include <Dusk/Tracking/ITrackedObject.hpp>
#include <Dusk/Events/Event.hpp>
#include <Dusk/UpdateEventData.hpp>
#include <Dusk/RenderEventData.hpp>

#include <lua.hpp>

namespace dusk
{

class GraphicsSystem;
class GraphicsContext;

class InputSystem;

class Scripting;
class ScriptHost;

class FrameTimeInfo;

class Program :
	public IEventDispatcher,
	public ITrackedObject
{
public:

	// Singleton Instance

	static inline Program* Inst() {
		return sp_Inst;
	}

	// Events

	static EventID EVT_UPDATE;
	static EventID EVT_RENDER;
	static EventID EVT_EXIT;

	Program();

	virtual inline ~Program() { Term(); }

	virtual inline string GetClassName() const { return "Program"; }

	void Run();

	double GetCurrentFPS() const { return m_CurrentFPS; }
	double GetTargetFPS() const { return m_TargetFPS; }
	void   SetTargetFPS(double fps);

	inline void Exit() { m_Running = false; }

protected:

	ScriptHost* GetScriptHost();

	virtual bool Init();
	virtual void Term();
	virtual void Update(FrameTimeInfo& timeInfo);
	virtual void PreRender(GraphicsContext* ctx);
	virtual void Render(GraphicsContext* ctx);
	virtual void PostRender(GraphicsContext* ctx);

private:

	static Program* sp_Inst;

	Program(Program const&);
	void operator=(Program const&);

	bool m_Running;

	double m_TargetFPS;
	double m_CurrentFPS;
	double m_UpdateInterval;

	ScriptHost*	mp_ScriptHost;

public:

	static void Script_RegisterFunctions();
	static int Script_GetProgram(lua_State* L);
	static int Script_Exit(lua_State* L);
	static int Script_GetGraphicsSystem(lua_State* L);
	static int Script_GetInputSystem(lua_State* L);
	static int Script_AddEventListener(lua_State* L);

}; // class Program

} // namespace dusk

#endif // DUSK_PROGRAM_H
