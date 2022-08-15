#include "myApp.h"
#include "imgui.h"

namespace myApp {

    static void ShowExampleAppFullscreen(bool* p_open)
    {
        static bool use_work_area = true;
        static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBackground;
        static int num = 0;
        static int cnt = 0;


        // We demonstrate using the full viewport area or the work area (without menu-bars, task-bars etc.)
        // Based on your use case you may want one of the other.
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
        ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);

        if (ImGui::Begin("Example: Fullscreen window", p_open, flags))
        {
            ImGui::Checkbox("Use work area instead of main area", &use_work_area);
            //ImGui::SameLine();

            //ImGui::ShowStyleEditor();

            float py = ImGui::GetCursorPosY();
            float px = 10.0f;

            ImVec2 coords;

            coords = { px, py };
            ImGui::SetCursorPos(coords);
            if (ImGui::Button("Value UP", { 80, 50 })) {
                num++;
            }

            coords = { px + 100, py + 10 };
            ImGui::SetCursorPos(coords);
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(200, 0, 100, 255));
            ImGui::Text("NUM %d", num);
            ImGui::PopStyleColor();
            

            coords = { px + 200, py };
            ImGui::SetCursorPos(coords);
            if (ImGui::Button("Value DN", { 80, 50 })) {
                num--;
            }

            coords = { px, py + 60 };
            ImGui::SetCursorPos(coords);
            static float value = 0.0f;
            ImGui::DragFloat("Value", &value);
            ImGui::Text("NUM %d", num);
            ImGui::Text("COUNT %d", cnt++);
            ImGui::SetCursorPosX(200.0f);
            ImGui::Text("NUM %d", num);

        }
        ImGui::End();
    }

    void RenderUI() {

        static bool bb;
        ShowExampleAppFullscreen(&bb);
        /*
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
        ImGui::Begin("Settings");
        ImGui::Button("Test button");
        static float value = 0.0f;
        ImGui::DragFloat("Value", &value);
        ImGui::End();
        */
    }

    
}
