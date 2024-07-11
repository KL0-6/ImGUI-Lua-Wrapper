#include "api.h"
#include <Luau/Compiler.h>

int window_new(lua_State* L)
{
    const char* window_title = luaL_checklstring(L, 1, NULL);

    window::window* win = reinterpret_cast<window::window*>(lua_newuserdata(L, sizeof(window::window)));

    win->title = window_title;

    window::windows.push_back(win);

    return 1;
}

int add_label(lua_State* L)
{
    window::window* win = reinterpret_cast<window::window*>(lua_touserdata(L, 1));

    const char* text = luaL_checklstring(L, 2, NULL);

    window::label* label = reinterpret_cast<window::label*>(lua_newuserdata(L, sizeof(window::label)));
	new(label)window::label;

    label->text = text;

    win->children.push_back(label);

    return 1;
}

lua_State* api::initialize()
{
    lua_State* L = luaL_newstate(); // Create a new lua_State for our scripting environment 

    if(L == nullptr) 
    {
        std::printf("[FATAL ERROR]: Failed to create lua_State!");

        return L;
    }

    luaL_openlibs(L); // Registers the default Luau libraries!

    lua_pushcfunction(L, window_new, "window_new");
    lua_setglobal(L, "window_new");

    lua_pushcfunction(L, add_label, "add_label");
    lua_setglobal(L, "add_label");

    std::string bytecode = Luau::compile(R"(
        local window = window_new('Hello!');

        local label = add_label(window, "this is text");
    )");

    luau_load(L, "", bytecode.c_str(), bytecode.size(), 0);
    lua_pcall(L, 0, 0, 0);

    return L; // Returns the lua_State for future use!
}