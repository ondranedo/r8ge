#ifndef R8GE_GLSERVICE_H
#define R8GE_GLSERVICE_H

#include "../RenderingService.h"

#include <vector>

namespace r8ge {
    namespace video {
        class GLService : public RenderingService {
        public:
            GLService();
            ~GLService() override;

            void init() override;
            void exit() override;

            void clear() const override;

            void render(const std::vector<size_t>& index_data, const std::vector<float>& vertex_data) const override;
        };
    }
}

#endif//!R8GE_GLSERVICE_H
