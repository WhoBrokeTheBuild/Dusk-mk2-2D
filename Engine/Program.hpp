#ifndef DUSK_PROGRAM_H
#define DUSK_PROGRAM_H

#include <Events/IEventDispatcher.hpp>
#include <Tracking/ITrackedObject.hpp>

#include <lua.hpp>
#include <Events/Event.hpp>

namespace dusk
{

class GraphicsSystem;
class GraphicsContext;

class InputSystem;

class ScriptingSystem;
class ScriptHost;

class FrameTimeInfo;

class Program :
	public IEventDispatcher,
	public ITrackedObject
{
public:

	static EventID
		EVT_UPDATE,
		EVT_RENDER,
		EVT_EXIT;

	static inline Program* Inst()
	{
		static Program* pProgram = New Program();

		return pProgram;
	}

	virtual inline ~Program() { Term(); }

	void Run();

	inline void Exit() { m_Running = false; }

	double GetCurrentFPS() const { return m_CurrentFPS; }

	double GetTargetFPS() const { return m_TargetFPS; }

	void   SetTargetFPS(double fps);

	GraphicsSystem* GetGraphicsSystem();

	InputSystem* GetInputSystem();

	static void InitScripting();

	static int Script_GetProgram(lua_State* L);

	static int Script_Exit(lua_State* L);

	static int Script_GetGraphicsSystem(lua_State* L);

	static int Script_GetInputSystem(lua_State* L);

	static int Script_AddEventListener(lua_State* L);

	// Temporary

private:

    Program(  ) :
		m_Running(),
		m_TargetFPS(),
		m_CurrentFPS(),
		m_UpdateInterval(),
		mp_GraphicsSystem(nullptr),
		mp_InputSystem(nullptr),
		mp_ScriptHost(nullptr)
	{ };

	Program(Program const&);
	void operator=(Program const&);

	virtual inline string GetClassName() const { return "Program"; }

	bool Init();

	void Term();

	void Update(FrameTimeInfo& timeInfo);

	void Render();

	bool InitGraphics();

	void TermGraphics();

	bool InitInput();

	void TermInput();

	bool InitAudio();

	void TermAudio();

	bool m_Running;

	double m_TargetFPS;

	double m_CurrentFPS;

	double m_UpdateInterval;

	GraphicsSystem* mp_GraphicsSystem;

	InputSystem* mp_InputSystem;

	ScriptHost*		mp_ScriptHost;

	// Temporary


}; // class Program

class UpdateEventData :
	public EventData
{
public:

	UpdateEventData(FrameTimeInfo* timeInfo) :
		mp_TimeInfo(timeInfo)
	{ }

	virtual inline string GetClassName() const { return "Update Event Data"; }

	virtual inline EventData* Clone() const { return New UpdateEventData(mp_TimeInfo); }

	FrameTimeInfo* GetTimeInfo();

	virtual int PushDataToLua(lua_State* L) const;

private:

	FrameTimeInfo* mp_TimeInfo;

};

class RenderEventData :
	public EventData
{
public:

	RenderEventData()
	{ }

	virtual inline string GetClassName() const { return "Render Event Data"; }

	virtual inline EventData* Clone() const { return New RenderEventData(); }

	virtual int PushDataToLua(lua_State* L) const;

private:

};

} // namespace dusk

#endif // DUSK_PROGRAM_H
