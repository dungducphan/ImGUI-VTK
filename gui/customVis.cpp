#include "customVis.h"

namespace gui {
    vtkSmartPointer<vtkActor> actor;
    VtkViewer vtkViewer1;
    VtkViewer vtkViewer2;
}

void gui::GenerateData() {
    actor = SetupDemoPipeline();
}

void gui::SetupViewers() {
    vtkViewer1.addActor(actor);
    vtkViewer2.getRenderer()->SetBackground(0, 0, 0); // Black background
    vtkViewer2.addActor(actor);
}

void gui::RenderViewer(bool& vtk_2_open) {
    ImGui::SetNextWindowSize(ImVec2(360, 240), ImGuiCond_FirstUseEver);
    ImGui::Begin("Vtk Viewer 1", nullptr, VtkViewer::NoScrollFlags());
    ImGui::Text("Render %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    vtkViewer1.render();
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(720, 480), ImGuiCond_FirstUseEver);
    if (vtk_2_open) {
        ImGui::Begin("Vtk Viewer 2", &vtk_2_open, VtkViewer::NoScrollFlags());

        auto renderer = vtkViewer2.getRenderer();
        if (ImGui::Button("VTK Background: Black")) renderer->SetBackground(0, 0, 0);
        ImGui::SameLine();
        if (ImGui::Button("VTK Background: Red")) renderer->SetBackground(1, 0, 0);
        ImGui::SameLine();
        if (ImGui::Button("VTK Background: Green")) renderer->SetBackground(0, 1, 0);
        ImGui::SameLine();
        if (ImGui::Button("VTK Background: Blue")) renderer->SetBackground(0, 0, 1);

        static float vtk2BkgAlpha = 0.2f;
        ImGui::SliderFloat("Background Alpha", &vtk2BkgAlpha, 0.0f, 1.0f);
        renderer->SetBackgroundAlpha(vtk2BkgAlpha);

        vtkViewer2.render();
        ImGui::End();
    }
}