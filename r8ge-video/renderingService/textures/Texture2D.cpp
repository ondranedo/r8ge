//
// Created by karnatour on 4.1.24.
//

#include "Texture2D.h"


namespace r8ge {
    namespace video {

        uint16_t Texture2D::getWidth() {
            return 0;
        }

        uint16_t Texture2D::getHeight() {
            return 0;
        }

        uint16_t Texture2D::getChannelsCount() {
            return 0;
        }

        uint8_t Texture2D::getImageData() {
            return 0;
        }

        void Texture2D::loadTextureFromFile(std::string pathToFile, bool flipTexture) {
            if (flipTexture) {
                stbi_set_flip_vertically_on_load(true);
            }
            stbi_load(pathToFile.c_str(), &m_width, &m_height, &m_channelsCount, 0);
        }
    }
}