// imgui_bridge.cpp
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

extern "C" {

void ImGui_ImplSDL2_InitBridge(void* window, void* gl_context) {
    ImGui_ImplSDL2_InitForOpenGL((SDL_Window*)window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void ImGui_ImplSDL2_NewFrameBridge(void* window) {
    ImGui_ImplSDL2_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
}

void ImGui_ImplSDL2_ProcessEventBridge(void* event) {
    ImGui_ImplSDL2_ProcessEvent((SDL_Event*)event);
}

void ImGui_ImplSDL2_RenderBridge(ImDrawData* draw_data) {
    ImGui_ImplOpenGL3_RenderDrawData(draw_data);
}

void ImGui_ImplSDL2_ShutdownBridge() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
}

}