#include "ScriptingSystem.hpp"

#include <Utility/Benchmark.hpp>
#include <Logging/LoggingSystem.hpp>
#include <Scripting/ScriptHost.hpp>

namespace dusk
{
	
Map<string, LuaCallback> dusk::ScriptingSystem::s_Functions;
ArrayList<ScriptHost*> dusk::ScriptingSystem::s_ScriptHosts;

void dusk::ScriptingSystem::AddScriptHost(ScriptHost* pHost)
{
	s_ScriptHosts.add(pHost);

	for (auto it : s_Functions) {
		pHost->RegisterFunction(it.first, it.second);
	}
}

ScriptHost* dusk::ScriptingSystem::GetScriptHost(lua_State* L)
{
	for (auto it : s_ScriptHosts)
	{
		if (it->GetState() == L)
			return it;
	}

	return nullptr;
}

void dusk::ScriptingSystem::RemoveScriptHost(ScriptHost* pHost)
{
	s_ScriptHosts.erase_all(pHost);
}

bool dusk::ScriptingSystem::RegisterFunction(const string& funcName, LuaCallback callback)
{
	if (funcName.empty())
	{
		DuskLog("error", "Cannot register a function with no name");
		return false;
	}

	if (callback == nullptr)
	{
		DuskLog("error", "Cannot register a fucntion with no callback");
	}

	if (s_Functions.contains_key(funcName))
	{
		DuskLog("error", "Cannot register a function twice");
		return false;
	}

	s_Functions.add(funcName, callback);

	for (auto it : s_ScriptHosts)
	{
		it->RegisterFunction(funcName, callback);
	}

	return true;
}

} // namespace dusk
