#include "window.h"
#include <lstate.h>
#include <ldo.h>

void window::button::render()
{
    if (ImGui::Button(text.c_str()))
    {
        lua_rawgeti(L, LUA_REGISTRYINDEX, callback_ref);
        lua_call(L, 0, LUA_MULTRET);

        if(L->status == LUA_YIELD)
        {
            lua_resume(L, NULL, lua_gettop(L));
        }
    }
}

void window::label::render()
{
    ImGui::Text(text.c_str());
}

void window::separator::render()
{
    ImGui::SeparatorTextEx(0, text.c_str(), ImGui::FindRenderedTextEnd(text.c_str()), extra_width);
}

void window::window::render()
{
    ImGui::Begin(title.c_str());

    for (base* child : children)
        child->render();

    ImGui::End();
}

std::vector<window::window*> window::windows;