#include "window.h"

void window::button::render()
{
    if (ImGui::Button(text.c_str()))
        callback();
}

void window::label::render()
{
    ImGui::Text(text.c_str());
}

void window::window::render()
{
    ImGui::Begin(title.c_str());

    for (auto child : children)
        child->render();

    ImGui::End();
}

std::vector<window::window*> window::windows;