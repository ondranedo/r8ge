//
// Created by karnatour on 4.1.24.
//

#ifndef R8GE_GLTEXTURE_H
#define R8GE_GLTEXTURE_H

#include <r8ge/r8ge.h>
#include <../r8ge-video/renderingService/textures/Texture2D.h>

namespace r8ge {
    namespace video {
        class GLTexture {
        public:
            GLTexture(const Texture2D& texture2D);

            ~GLTexture();

            void updateData(void *data);

            void bindTexture() const;

        private:
            uint32_t m_texture{};


        };
    }
} // r8ge

#endif //R8GE_GLTEXTURE_H
