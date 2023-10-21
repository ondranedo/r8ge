#ifndef R8GE_GLSERVICE_H
#define R8GE_GLSERVICE_H

#include "../RenderingService.h"

namespace r8ge {
    namespace video {
        class GLService : public RenderingService {
        public:
            GLService();
            ~GLService() override;

            void init() override;
            void exit() override;
        };
    }
}

#endif//!R8GE_GLSERVICE_H
