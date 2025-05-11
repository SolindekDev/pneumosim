// imgui_bridge.h
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void ImGui_ImplSDL2_InitBridge(void* window, void* gl_context);
void ImGui_ImplSDL2_NewFrameBridge(void* window);
void ImGui_ImplSDL2_ProcessEventBridge(void* event);
void ImGui_ImplSDL2_RenderBridge(struct ImDrawData* draw_data);
void ImGui_ImplSDL2_ShutdownBridge(void);

#ifdef __cplusplus
}
#endif
