//
// Created by karnatour on 4.1.24.
//

#include "Texture2D.h"
#include <stb_image.h>

namespace r8ge {
    namespace video {

        Texture2D::Texture2D(const std::string &pathToFile, bool flipTexture) {
            loadTextureFromFile(pathToFile, flipTexture);
        }

        uint16_t Texture2D::getWidth() const {
            return m_width;
        }

        uint16_t Texture2D::getHeight() const {
            return m_height;
        }

        uint16_t Texture2D::getChannelsCount() const {
            return m_channelsCount;
        }

        void* Texture2D::getImageData() const{
            return m_imageData;
        }

        bool Texture2D::getFlipState() const {
            return m_isFlipped;
        }

        void Texture2D::loadTextureFromFile(const std::string &pathToFile, bool flipTexture) {
            if (flipTexture) {
                stbi_set_flip_vertically_on_load(true);
                m_isFlipped = true;
            }
            m_imageData = stbi_load(pathToFile.c_str(), &m_width, &m_height, &m_channelsCount, 0);
            if (m_imageData == nullptr) {
                R8GE_LOG_WARNI("Data of texture {} is null", pathToFile.c_str());
            }
        }

        Texture2D::~Texture2D() {
            stbi_image_free(m_imageData);
        }
    }
}