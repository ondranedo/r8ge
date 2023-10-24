#ifndef R8GE_MESH_H
#define R8GE_MESH_H

#include "MeshTrinagle.h"
#include <vector>

namespace r8ge {/*
    class Mesh2D {
    public:
        Mesh2D();
        Mesh2D(std::initializer_list<MeshTrinagle> triangles);
        virtual ~Mesh2D() = default;

        void addTriangle(const MeshTrinagle& triangle);

        void setData(const std::vector<Vertex2D>& vertex, const std::vector<size_t>& indices);

        [[nodiscard]] const std::vector<Vertex2D>& getVertices() const;
        [[nodiscard]] const std::vector<size_t>& getIndices() const;
    private:
        std::vector<Vertex2D> m_vertices;
        std::vector<size_t> m_indices;
        size_t m_indexCount;
    };*/
}

#endif//!R8GE_MESH_H
