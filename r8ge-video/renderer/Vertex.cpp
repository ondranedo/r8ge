#include "Vertex.h"

r8ge::Vertex2D::Vertex2D(float _x, float _y) : x(_x), y(_y){}

bool r8ge::Vertex2D::operator==(const r8ge::Vertex2D &other) const  {
    return x == other.x && y == other.y;
}
