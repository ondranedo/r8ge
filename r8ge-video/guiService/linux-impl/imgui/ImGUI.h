//
// Created by karnatour on 15.1.24.
//

#ifndef R8GE_IMGUI_H
#define R8GE_IMGUI_H

#include "../../GUIService.h"
#include <imgui.h>
#include <imgui_internal.h>
#include <ImGuizmo.h>


namespace r8ge {
    namespace video {
        class ImGUI : public GUIService {
        public:
            ~ImGUI() override;

            void init(WindowingService &service) override;

            void exit() override;

            void beginFrame() override;

            void render() override;

            void endFrame(WindowingService &service) override;

            void showDemoWindow() override;
        private:
        };

    } // r8ge
} // video

#endif //R8GE_IMGUI_H
