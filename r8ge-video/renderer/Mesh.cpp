#include "Mesh.h"

#include <utility>
#include <algorithm>

namespace r8ge {

    Mesh2D::Mesh2D(std::initializer_list<MeshTrinagle> triangles) : m_indices(0), m_indexCount(0) {
        for (auto& triangle : triangles) {
            addTriangle(triangle);
        }
    }

    void Mesh2D::addTriangle(const MeshTrinagle &triangle) {
        auto vertices = triangle.getVertices();
        size_t matches = 0;
        for(auto vertex : vertices) {
            auto it = std::find(m_vertices.begin(), m_vertices.end(), vertex);
            if(it == m_vertices.end()) {
                m_vertices.push_back(vertex);
                m_indices.push_back(m_indexCount);
                m_indexCount++;
            } else
            {
                m_indices.push_back(std::distance(m_vertices.begin(), it));
                matches++;
            }
        }

        // Same triangle - remove it
        if(matches == 3) {
            m_indices.pop_back();
            m_indices.pop_back();
            m_indices.pop_back();
        }
    }

    Mesh2D::Mesh2D() : m_indices(0), m_indexCount(0) {}
}