#include "Vertex.h"

std::vector<uint8_t> operator+=(const std::vector<uint8_t>& v1, const std::vector<uint8_t>& v2) {
    std::vector<uint8_t> result(v1.size() + v2.size());
    std::copy(v1.begin(), v1.end(), result.begin());
    std::copy(v2.begin(), v2.end(), result.begin() + v1.size());
    return result;
}

r8ge::video::VertexBufferLayout r8ge::Vertex::getLayout() const {
    return video::VertexBufferLayout({
        video::VertexBufferLayout::Entry::POS_XY});
}

r8ge::Vertex::Vertex(r8ge::coord_float _x, r8ge::coord_float _y) : x(_x), y(_y) {}

std::vector<uint8_t> r8ge::Vertex::getRawData() const {
    std::vector<uint8_t> data(getSize());
    union {
        struct { coord_float x, y;};
        uint8_t _raw[2*sizeof(coord_float)];
    } convertor = {x, y};
    return {convertor._raw, convertor._raw + sizeof(convertor._raw)};
}

size_t r8ge::Vertex::getSize() const {
    return sizeof(x) + sizeof(y);
}

r8ge::video::VertexBufferLayout r8ge::Vertex3D::getLayout() const {
    return video::VertexBufferLayout({video::VertexBufferLayout::Entry::POS_XYZ});
}

r8ge::Vertex3D::Vertex3D(r8ge::coord_float x, r8ge::coord_float y, r8ge::coord_float z)
: Vertex(x, y), z(z)
{}

std::vector<uint8_t> r8ge::Vertex3D::getRawData() const {
    auto data = Vertex::getRawData();
    union {
        struct { coord_float z;};
        uint8_t _raw[sizeof(coord_float)];
    } convertor = {z};
    data += {convertor._raw, convertor._raw + sizeof(convertor._raw)};
    return data;
}

size_t r8ge::Vertex3D::getSize() const {
    return Vertex::getSize() + sizeof(z);
}
