#pragma once

#include "imgui_vtk_demo.h"

#include "VtkViewer.h"

namespace gui {
    void GenerateData();
    void SetupViewers();
    void RenderViewer(bool& vtk_2_open);
}