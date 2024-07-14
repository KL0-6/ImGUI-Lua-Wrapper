#include "api.h"
#include <Luau/Compiler.h>

int window_new(lua_State* L)
{
    luaL_checktype(L, 1, LUA_TSTRING);

    const char* window_title = lua_tostring(L, 1);

    window::window* win = metatable::allocate_userdata<window::window>(L, "window_metatable");
	new(win)window::window;

    win->title = window_title;
    win->lua_ref = lua_ref(L, -1);

    window::windows.push_back(win);

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
    metatable::initialize(L); // Register our metatables

    lua_createtable(L, 0, 0);
    {
        lua_pushcfunction(L, window_new, "window_new");   
        lua_setfield(L, -2, "new");
    }
    lua_setglobal(L, "Window");

    std::string bytecode = Luau::compile(R"(
        local window = Window.new("Hello!");
        local x = "E"
        window:Button("H", function()
            print(x)
        end);
        
        window:Separator("Section 1")

        window:Button("Y", function()
            x = "Y"
        end);
    )");

    lua_State* T = lua_newthread(L);

    luau_load(T, "", bytecode.c_str(), bytecode.size(), 0);
    int status = lua_resume(T, NULL, 0);
    if(status == LUA_ERRRUN)
    {
        std::printf("Running error %s\n", lua_tostring(T, -1));
    }

    return L; // Returns the lua_State for future use!
}