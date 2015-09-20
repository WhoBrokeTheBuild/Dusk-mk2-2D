#ifndef DUSK_TYPES_HPP
#define DUSK_TYPES_HPP

#include <string>
using std::string;

struct lua_State;

namespace dusk
{

typedef unsigned int Flag;
typedef int(*LuaCallback)(lua_State* L);

} // namespace dusk

#endif // DUSK_TYPES_HPP
