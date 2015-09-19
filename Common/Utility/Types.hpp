#ifndef DUSK_TYPES_HPP
#define DUSK_TYPES_HPP

#include <string>
using std::string;

struct lua_State;

namespace Dusk
{

typedef unsigned int Flag;
typedef int(*LuaCallback)(lua_State* L);

} // namespace Dusk

#endif // DUSK_TYPES_HPP
