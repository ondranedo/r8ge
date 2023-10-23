#ifndef R8GE_VERTEX_H
#define R8GE_VERTEX_H

#include "Color.h"
#include "../renderingService/buffers/VertexBufferLayout.h"

#include <vector>

namespace r8ge {
    struct Vertex {
        Vertex(coord_float x, coord_float y);
        virtual ~Vertex() = default;

        [[nodiscard]] virtual video::VertexBufferLayout getLayout() const;
        [[nodiscard]] virtual std::vector<uint8_t> getRawData() const;
        [[nodiscard]] virtual size_t getSize() const;

        coord_float x, y;
    };

    struct Vertex3D : public Vertex {
        Vertex3D(coord_float x, coord_float y, coord_float z);
        ~Vertex3D() override = default;

        [[nodiscard]] video::VertexBufferLayout getLayout() const override;

        [[nodiscard]] std::vector<uint8_t> getRawData() const override;

        [[nodiscard]] size_t getSize() const override;

        coord_float z;
    };
}

#endif//!R8GE_VERTEX_H
