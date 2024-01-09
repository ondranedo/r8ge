//
// Created by karnatour on 4.1.24.
//

#include "Texture2D.h"

namespace r8ge {
    namespace video {

        uint16_t Texture2D::getWidth() const {
            return m_width;
        }

        uint16_t Texture2D::getHeight() const {
            return m_height;
        }

        uint16_t Texture2D::getChannelsCount() const {
            return m_channelsCount;
        }

        uint8_t Texture2D::getImageData() {
            return *m_imageData;
        }

        bool Texture2D::getFlipState() const{
            return m_isFlipped;
        }

        void Texture2D::loadTextureFromFile(std::string pathToFile, bool flipTexture) {
            if (flipTexture) {
                stbi_set_flip_vertically_on_load(true);
            }
            stbi_load(pathToFile.c_str(), &m_width, &m_height, &m_channelsCount, 0);
        }
    }
}