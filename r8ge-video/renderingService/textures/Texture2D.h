//
// Created by karnatour on 4.1.24.
//

#ifndef R8GE_TEXTURE2D_H
#define R8GE_TEXTURE2D_H

#include <r8ge/r8ge.h>

#include "../r8ge-video/vendor/stb/stb_image.h"

namespace r8ge {
    namespace video {
        class Texture2D {
        public:
            Texture2D(const std::string &pathToFile, bool flipTexture);
            ~Texture2D();

            [[nodiscard]] uint16_t getWidth() const;

            [[nodiscard]] uint16_t getHeight() const;

            [[nodiscard]] uint16_t getChannelsCount() const;

            [[nodiscard]] void* getImageData() const;

            [[nodiscard]] bool getFlipState() const;

            void loadTextureFromFile(const std::string &pathToFile, bool flipTexture);

        private:
            int32_t m_width{}, m_height{}, m_channelsCount{};
            void *m_imageData{};
            bool m_isFlipped = false;
        };
    }
} // r8ge

#endif //R8GE_TEXTURE2D_H
