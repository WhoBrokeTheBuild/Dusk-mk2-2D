#ifndef DUSK_SCRIPTING_SCRIPT_HOST_HPP
#define DUSK_SCRIPTING_SCRIPT_HOST_HPP

#include <Utility/Types.hpp>
#include <Tracking/ITrackedObject.hpp>

#include <lua.hpp>

namespace dusk
{

class ScriptHost :
	public ITrackedObject
{
public:

	ScriptHost( void ) :
		mp_LuaState(nullptr)
	{ }

	~ScriptHost( void ) { Term(); }

	virtual inline string GetClassName( void ) const { return "Script Host"; }

	bool Init( void );
	void Term( void );

	bool RunFile( const string& filename );
	bool RegisterFunction( const string& funcName, LuaCallback callback );

	inline lua_State* GetState( void ) { return mp_LuaState; }

private:

	lua_State*		mp_LuaState;

}; // class ScriptHost

} // namespace dusk

#endif // DUSK_SCRIPTING_SCRIPT_HOST_HPP