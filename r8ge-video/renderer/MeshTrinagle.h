#ifndef R8GE_MESHTRINAGLE_H
#define R8GE_MESHTRINAGLE_H

#include "Vertex.h"

#include <initializer_list>
#include <array>

namespace r8ge {
    class MeshTrinagle final {
    public:
        MeshTrinagle(const std::array<Vertex2D, 3>& vertices, bool direction = true);

        [[nodiscard]] const std::array<Vertex2D, 3>& getVertices() const;
        [[nodiscard]] bool isClockWise() const;

    private:
        std::array<Vertex2D, 3> m_vertices;
        bool m_directionClockwise;
    };
}

#endif//!R8GE_MESHTRINAGLE_H
