#ifndef _metatable_h_
#define _metatable_h_

#include <lualib.h>
#include <iostream>

namespace metatable
{
    // Creates a userdata with size T and casts void* to T
    template <typename T> T* create_userdata(lua_State* L)
    {
        return reinterpret_cast<T*>(lua_newuserdata(L, sizeof(T)));
    }

    // Similar to create_userdata however this function attaches an existing metatable 
    template <typename T> T* allocate_userdata(lua_State* L, const char* method_name)
    {
        void* ud = lua_newuserdata(L, sizeof(T)); // Allocate the user data
        lua_getfield(L, LUA_REGISTRYINDEX, method_name); // Search up the metatable within the registery index
        lua_setmetatable(L, -2); // Assign the metatables to the user data

        return reinterpret_cast<T*>(ud); // Return the userdata
    }

    // Creates a metatable and saves it in the registry for future reuse
    void create_metatable(lua_State*, const char*);

    // Push our metatables into the environment 
    void initialize(lua_State *L);
}

#endif