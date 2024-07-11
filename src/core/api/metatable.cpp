#include "metatable.h"

void metatable::create_metatable(lua_State* L, const char* method_name)
{
    lua_getfield(L, LUA_REGISTRYINDEX, method_name); // Look up method

    if(lua_type(L, -1) != LUA_TNIL) // If the type isn't nil, that means something else with the same global exists. 
        return; // Instead of overwriting, return. [[ This should be treated as an error in this context ]]

    lua_pop(L, 1);

    // Create & Save method

    lua_createtable(L, 0, 0);
    lua_pushvalue(L, -1);
    lua_setfield(L, LUA_REGISTRYINDEX, method_name);
}

void metatable::initialize(lua_State* L)
{
    create_metatable(L, "window_metatable");

    lua_pushcclosure(L, [](lua_State* L) -> int
    {
        std::printf("Window Index!\n");

        return 1;
    }, "window_metatable_index", 0);

    lua_setfield(L, -2, "__index");

    lua_pop(L, 1);
}