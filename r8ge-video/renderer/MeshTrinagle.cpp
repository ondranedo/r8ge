#include "MeshTrinagle.h"

namespace r8ge {

    MeshTrinagle::MeshTrinagle(const std::array<Vertex2D, 3> &vertices, bool direction) : m_vertices(vertices),
                                                                                         m_directionClockwise(
                                                                                                 direction) {}

    const std::array<Vertex2D, 3> &MeshTrinagle::getVertices() const {
        return m_vertices;
    }

    bool MeshTrinagle::isClockWise() const {
        return m_directionClockwise;
    }
}