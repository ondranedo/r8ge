//
// Created by karnatour on 4.1.24.
//

#ifndef R8GE_TEXTURE2D_H
#define R8GE_TEXTURE2D_H

#include <r8ge/r8ge.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../r8ge-video/vendor/stb/stb_image.h"

namespace r8ge {
    namespace video {
        class Texture2D {
        public:
            [[nodiscard]] uint16_t getWidth() const;

            [[nodiscard]] uint16_t getHeight() const;

            [[nodiscard]] uint16_t getChannelsCount() const;

            uint8_t getImageData();

            [[nodiscard]] bool getFlipState() const;

            void loadTextureFromFile(std::string pathToFile, bool flipTexture);

        private:
            int32_t m_width, m_height, m_channelsCount;
            uint8_t *m_imageData;
            bool m_isFlipped = false;
        };
    }
} // r8ge

#endif //R8GE_TEXTURE2D_H
