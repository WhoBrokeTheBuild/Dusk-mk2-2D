#ifndef DUSK_TYPES_HPP
#define DUSK_TYPES_HPP

#include <string>
using std::string;

#include <memory>
using std::weak_ptr;
using std::shared_ptr;
using std::unique_ptr;
using std::dynamic_pointer_cast;

struct lua_State;

namespace dusk
{

typedef unsigned int Flag;
typedef int(*LuaCallback)(lua_State* L);

} // namespace dusk

#endif // DUSK_TYPES_HPP
