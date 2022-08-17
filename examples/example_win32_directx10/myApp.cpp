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

            ImGuiIO& io = ImGui::GetIO();
            ImGuiStyle& style = ImGui::GetStyle();
            ImDrawList* draw_list = ImGui::GetWindowDrawList();
            static float x = 0;
            x = x + 1;
            const ImU32 color = 0x80ffffff;
            draw_list->AddTriangleFilled(ImVec2(100 + x, 100),
                ImVec2(100 + x, 200),
                ImVec2(200 + x, 100),
                color);
            ImGui::ShowMetricsWindow();
            ImGui::TextWrapped(
                "Below we are displaying the font texture (which is the only texture we have access to in this demo). "
                "Use the 'ImTextureID' type as storage to pass pointers or identifier to your own texture data. "
                "Hover the texture for a zoomed view!");
            ImTextureID my_tex_id = io.Fonts->TexID;
            float my_tex_w = (float)io.Fonts->TexWidth;
            float my_tex_h = (float)io.Fonts->TexHeight;
            {
                ImGui::Text("%.0fx%.0f", my_tex_w, my_tex_h);
                ImVec2 pos = ImGui::GetCursorScreenPos();
                ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
                ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
                ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
                ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white
                ImGui::Image(my_tex_id, ImVec2(my_tex_w, my_tex_h), uv_min, uv_max, tint_col);// , border_col);
                if (ImGui::IsItemHovered())
                {
                    ImGui::BeginTooltip();
                    float region_sz = 32.0f;
                    float region_x = io.MousePos.x - pos.x - region_sz * 0.5f;
                    float region_y = io.MousePos.y - pos.y - region_sz * 0.5f;
                    float zoom = 4.0f;
                    if (region_x < 0.0f) { region_x = 0.0f; }
                    else if (region_x > my_tex_w - region_sz) { region_x = my_tex_w - region_sz; }
                    if (region_y < 0.0f) { region_y = 0.0f; }
                    else if (region_y > my_tex_h - region_sz) { region_y = my_tex_h - region_sz; }
                    ImGui::Text("Min: (%.2f, %.2f)", region_x, region_y);
                    ImGui::Text("Max: (%.2f, %.2f)", region_x + region_sz, region_y + region_sz);
                    ImVec2 uv0 = ImVec2((region_x) / my_tex_w, (region_y) / my_tex_h);
                    ImVec2 uv1 = ImVec2((region_x + region_sz) / my_tex_w, (region_y + region_sz) / my_tex_h);
                    ImGui::Image(my_tex_id, ImVec2(region_sz * zoom, region_sz * zoom), uv0, uv1, tint_col, border_col);
                    ImGui::EndTooltip();
                }
            }

            
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
