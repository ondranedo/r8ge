#ifndef R8GE_VERTEX_H
#define R8GE_VERTEX_H

#include "../renderer/Types.h"

#include <vector>

namespace r8ge {
    struct Vertex {
        Vertex(coord_float x, coord_float y) : x(x), y(y) {}

        coord_float x, y;
    };
}

#endif//!R8GE_VERTEX_H
