#ifndef DUSK_SCRIPTING_SCRIPT_HOST_HPP
#define DUSK_SCRIPTING_SCRIPT_HOST_HPP

#include <Dusk/Utility/Types.hpp>
#include <Dusk/Tracking/TrackedObject.hpp>

#include <lua.hpp>

namespace dusk
{

class ScriptHost :
    public TrackedObject
{
public:

    ScriptHost();
    ScriptHost(const ScriptHost&) = delete;
    ScriptHost& operator=(const ScriptHost&) = delete;
    virtual ~ScriptHost();

    virtual inline string GetClassName() const override { return "Script Host"; }

    bool RunFile(const string& filename);
    bool RegisterFunction(const string& funcName, LuaCallback callback);

    inline lua_State* GetState() { return mp_LuaState; }

private:

    lua_State*        mp_LuaState;

}; // class ScriptHost

} // namespace dusk

#endif // DUSK_SCRIPTING_SCRIPT_HOST_HPP
