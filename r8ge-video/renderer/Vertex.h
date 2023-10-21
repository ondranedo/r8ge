#ifndef R8GE_VERTEX_H
#define R8GE_VERTEX_H

namespace r8ge {
    struct Vertex2D {
        Vertex2D(float _x, float _y);

        bool operator==(const Vertex2D& other) const;

        float x, y;
    };
}

#endif//!R8GE_VERTEX_H
