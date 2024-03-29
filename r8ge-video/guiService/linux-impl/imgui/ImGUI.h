//
// Created by karnatour on 15.1.24.
//

#ifndef R8GE_IMGUI_H
#define R8GE_IMGUI_H

#include "../../GUIService.h"
#include "../../../renderingService/RenderingService.h"
#include <imgui.h>
#include <imgui_internal.h>


namespace r8ge {
    namespace video {
        class ImGUI : public GUIService {
        public:
            ~ImGUI() override;

            void init(WindowingService &service) override;

            void exit() override;

            void beginFrame() override;

            void render(r8ge::video::GLFrameBuffer &frameBuffer) override;

            void endFrame(WindowingService &service) override;

            void renderR8GELayout();

            void setColors();

            void showDemoWindow() override;
        private:
            ImGuiWindowFlags windowFlags = 0;

        };

    } // r8ge
} // video

#endif //R8GE_IMGUI_H
