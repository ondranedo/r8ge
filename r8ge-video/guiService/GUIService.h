//
// Created by karnatour on 15.1.24.
//

#ifndef R8GE_GUISERVICE_H
#define R8GE_GUISERVICE_H

#include <memory>
#include "../../../windowingService/WindowingService.h"

namespace r8ge {
    namespace video {
        class GUIService {
        public:
            GUIService();

            virtual ~GUIService() = 0;

            virtual void init(WindowingService &service) = 0;

            virtual void exit() = 0;

            virtual void beginFrame() = 0;

            virtual void render() = 0;

            virtual void endFrame(WindowingService &service) = 0;

            virtual void showDemoWindow() = 0;


            static std::shared_ptr<GUIService> create();

        protected:
            bool m_isInitialized;

        };

    } // r8ge
} // video

#endif //R8GE_GUISERVICE_H