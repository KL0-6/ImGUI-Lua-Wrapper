#include "metatable.h"
#include <lobject.h>
#include <lstate.h>

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

int add_button(lua_State* L)
{
    luaL_checktype(L, 1, LUA_TUSERDATA);
    luaL_checktype(L, 2, LUA_TSTRING);

    window::window* win = reinterpret_cast<window::window*>(lua_touserdata(L, 1));
    const char* text = lua_tostring(L, 2);

    window::button* button = metatable::create_userdata<window::button>(L);
	new(button)window::button;

    button->text = text;
    button->lua_ref = lua_ref(L, -1);
    button->L = L;

    if(lua_type(L, 3) == LUA_TFUNCTION) // Callback was provided
    {
        button->callback_ref = lua_ref(L, 3);
    }

    win->children.push_back(button);

    return 1;
}

int add_label(lua_State* L)
{
    luaL_checktype(L, 1, LUA_TUSERDATA);
    luaL_checktype(L, 2, LUA_TSTRING);

    window::window* win = reinterpret_cast<window::window*>(lua_touserdata(L, 1));
    const char* text = lua_tostring(L, 2);

    window::label* label = metatable::create_userdata<window::label>(L);
	new(label)window::label;

    label->text = text;
    label->lua_ref = lua_ref(L, -1);

    win->children.push_back(label);

    return 1;
}

int add_separator(lua_State* L)
{
    luaL_checktype(L, 1, LUA_TUSERDATA);

    window::window* win = reinterpret_cast<window::window*>(lua_touserdata(L, 1));

    window::separator* separator = metatable::create_userdata<window::separator>(L);
	new(separator)window::separator;

    separator->lua_ref = lua_ref(L, -1);

    if(lua_type(L, 2) == LUA_TSTRING)
        separator->text = lua_tostring(L, 2);
    else if(lua_type(L, 2) == LUA_TNUMBER)
        separator->extra_width = lua_tonumber(L, 2);
    else if(lua_type(L, 3) == LUA_TNUMBER) // If there is a second argument, text is already set
        separator->extra_width = lua_tonumber(L, 3);

    win->children.push_back(separator);

    return 1;
}

void metatable::initialize(lua_State* L)
{
    create_metatable(L, "window_metatable");

    lua_pushcclosure(L, [](lua_State* L) -> int
    {
        luaL_checktype(L, 1, LUA_TUSERDATA);
        luaL_checktype(L, 2, LUA_TSTRING);

        void* ud = lua_touserdata(L, 1);
        const char* object = lua_tostring(L, 2);

        // Ensure the userdata is a window object
        if(std::find(window::windows.begin(), window::windows.end(), ud) == window::windows.end())
            luaL_error(L, "window->__newindex error - argument #1 is not a valid window");

        if(std::strstr(object, "Button"))
            lua_pushcfunction(L, add_button, "Window->Button");   
        else if(std::strstr(object, "Label"))
            lua_pushcfunction(L, add_label, "Window->Label");  
        else if(std::strstr(object, "Separator"))
            lua_pushcfunction(L, add_separator, "Window->Separator");      
        else
            return 0; // Nothing to return, object isn't a valid member of window

        return 1; // Return the function
    }, "window_metatable_index", 0);
    lua_setfield(L, -2, "__index");

    // table[value] = new
    lua_pushcclosure(L, [](lua_State* L) -> int
    {
        luaL_checktype(L, 1, LUA_TUSERDATA); // table
        luaL_checktype(L, 2, LUA_TSTRING); // value
        luaL_checkany(L, 3); // new 

        return 1;
    }, "window_metatable_newindex", 0);
    lua_setfield(L, -2, "__newindex");

    lua_pop(L, 1);
}