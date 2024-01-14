//
// Created by karnatour on 4.1.24.
//

#include "GLTexture.h"
#include "../r8ge-video/renderingService/openGL/GLConvertor.h"
#include <GL/glew.h>


namespace r8ge {
    namespace video {

        GLTexture::GLTexture(const Texture2D &texture2D) {
            glCreateTextures(GL_TEXTURE_2D, 1, &m_texture);

            auto getInternalFormat = [](int channels) {
                switch (channels) {
                    case 3:
                        return GLConvertor::convertImageFormatToGLInternalFormat(ImageFormat::RGB8);
                    case 4:
                        return GLConvertor::convertImageFormatToGLInternalFormat(ImageFormat::RGBA8);
                }
            };

            auto getFormat = [](int channels) {
                switch (channels) {
                    case 3:
                        return GLConvertor::convertImageFormatToGLFormat(Format::RGB);
                    case 4:
                        return GLConvertor::convertImageFormatToGLFormat(Format::RGBA);
                }
            };

            glTextureStorage2D(m_texture, 1, getInternalFormat(texture2D.getChannelsCount()), texture2D.getWidth(),
                               texture2D.getHeight());

            glTextureParameteri(m_texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTextureParameteri(m_texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTextureParameteri(m_texture, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTextureParameteri(m_texture, GL_TEXTURE_WRAP_T, GL_REPEAT);

            glTextureSubImage2D(m_texture, 0, 0, 0, texture2D.getWidth(), texture2D.getHeight(), getFormat(texture2D.getChannelsCount()),
                                GL_UNSIGNED_BYTE, texture2D.getImageData());

        }

        GLTexture::~GLTexture() {

        }

        void GLTexture::updateData(void *data) {

        }

        void GLTexture::bindTexture(int unit) const {
            glBindTextureUnit(unit, m_texture);
        }
    }
} // r8ge