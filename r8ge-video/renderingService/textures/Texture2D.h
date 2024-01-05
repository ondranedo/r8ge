//
// Created by karnatour on 4.1.24.
//

#ifndef R8GE_TEXTURE2D_H
#define R8GE_TEXTURE2D_H

#include <r8ge/r8ge.h>

namespace r8ge {
    namespace video {
        class Texture2D {
        public:
            uint16_t getWidth();

            uint16_t getHeight();

            uint16_t getChannelsCount();

            uint8_t getImageData();

            void loadTextureFromFile(std::string pathToFile, bool flipTexture);

        private:
            int32_t m_width, m_height, m_channelsCount;
            uint8_t *m_imageData;
            bool m_isFlipped = false;
        };
    }
} // r8ge

#endif //R8GE_TEXTURE2D_H
