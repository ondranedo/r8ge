#ifndef R8GE_VERTEXBUFFER_H
#define R8GE_VERTEXBUFFER_H

#include "Buffer.h"
#include <vector>

#include "VertexBufferLayout.h"

namespace r8ge {
    namespace video {
        // Vertex buffer is a buffer that stores vertex data
        // It is used to store data that is used to draw objects
        // data is transferred to GPU memory. Very important thing
        // is that vertex buffer holds layout of data that is stored
        // in it. Layout is used to tell GPU (shaders) how to interpret data
        // that is stored in vertex buffer.
        class VertexBuffer final : public Buffer
        {
        public:
            template<typename T>
            VertexBuffer(const std::vector<T>& data, const VertexBufferLayout& layout)
            {
                auto first = reinterpret_cast<const uint8_t*>(data.data());
                m_data = std::vector<uint8_t>(first, first + data.size() * sizeof(T));
            }

            VertexBuffer(const std::vector<uint8_t>& data, const VertexBufferLayout& layout);
            ~VertexBuffer() override;

            // Sets data to vertex buffer
            void setData(const std::vector<uint8_t>& data);

            // Sets layout of data that is stored in vertex buffer
            // very important thing is that layout must be set
            void setLayout(const VertexBufferLayout &layout);

            // Returns layout of data that is stored in vertex buffer
            [[nodiscard]] const VertexBufferLayout& getLayout() const;

            template<typename T>
            [[nodiscard]] std::vector<T> getData() {
                std::vector<T> data;

                for(size_t i = 0; i < m_data.size()/sizeof(T); ++i) {
                    data.push_back(*reinterpret_cast<T*>(&m_data[i*sizeof(T)]));
                }

                return data;
            }

        protected:
            VertexBufferLayout m_layout;
        };
    }
}

#endif//!R8GE_VERTEXBUFFER_H
