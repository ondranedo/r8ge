#include "Vertex.h"

//TODO Untested if getRawData works for other definitions than Vertex,Vertex3D

std::vector<uint8_t> operator+=(const std::vector<uint8_t> &v1, const std::vector<uint8_t> &v2) {
    std::vector<uint8_t> result(v1.size() + v2.size());
    std::copy(v1.begin(), v1.end(), result.begin());
    std::copy(v2.begin(), v2.end(), result.begin() + v1.size());
    return result;
}

r8ge::video::VertexBufferLayout r8ge::Vertex::getLayout() const {
    return video::VertexBufferLayout({video::VertexBufferLayout::Entry::POS_XY
                                     });
}

r8ge::Vertex::Vertex(r8ge::coord_float _x, r8ge::coord_float _y) : x(_x), y(_y) {
}

std::vector<uint8_t> r8ge::Vertex::getRawData() const {
    std::vector<uint8_t> data(getSize());
    union {
        struct {
            coord_float x, y;
        };
        uint8_t _raw[2 * sizeof(coord_float)];
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
        : Vertex(x, y), z(z) {
}

std::vector<uint8_t> r8ge::Vertex3D::getRawData() const {
    auto data = Vertex::getRawData();
    union {
        struct {
            coord_float z;
        };
        uint8_t _raw[sizeof(coord_float)];
    } convertor = {z};
    data += {convertor._raw, convertor._raw + sizeof(convertor._raw)};
    return data;
}

size_t r8ge::Vertex3D::getSize() const {
    return Vertex::getSize() + sizeof(z);
}

r8ge::VertexTexture::VertexTexture(r8ge::coord_float x, r8ge::coord_float y, r8ge::texture_coord tex_x,
                                   r8ge::texture_coord tex_y) : Vertex(x, y), tex_x(tex_x), tex_y(tex_y) {
}

r8ge::video::VertexBufferLayout r8ge::VertexTexture::getLayout() const {
    return video::VertexBufferLayout(
            {video::VertexBufferLayout::Entry::POS_XY, video::VertexBufferLayout::Entry::TEXTURE_XY});
}

std::vector<uint8_t> r8ge::VertexTexture::getRawData() const {
    auto data = Vertex::getRawData();
    union {
        struct {
            texture_coord tex_x, tex_y;
        };
        uint8_t _raw[2 * sizeof(texture_coord)];
    } convertor = {tex_x, tex_y};
    data += {convertor._raw, convertor._raw + sizeof(convertor._raw)};
    return data;
}

size_t r8ge::VertexTexture::getSize() const {
    return Vertex::getSize() + sizeof(tex_x) + sizeof(tex_y);
}

r8ge::VertexTexture3D::VertexTexture3D(r8ge::coord_float x, r8ge::coord_float y, r8ge::coord_float z,
                                       r8ge::texture_coord tex_x, r8ge::texture_coord tex_y,
                                       r8ge::texture_coord tex_z) : Vertex(x, y), z(z), tex_x(tex_x), tex_y(tex_y),
                                                                    tex_z(tex_z) {

}

r8ge::video::VertexBufferLayout r8ge::VertexTexture3D::getLayout() const {
    return video::VertexBufferLayout(
            {video::VertexBufferLayout::Entry::POS_XYZ, video::VertexBufferLayout::Entry::TEXTURE_XYZ});
}

std::vector<uint8_t> r8ge::VertexTexture3D::getRawData() const {
    auto data = Vertex::getRawData();
    union {
        struct {
            coord_float z;
            texture_coord tex_x, tex_y, tex_z;
        };
        uint8_t _raw[sizeof(coord_float) + 3 * sizeof(texture_coord)];
    } convertor = {z, tex_x, tex_y, tex_z};
    data += {convertor._raw, convertor._raw + sizeof(convertor._raw)};
    return data;
}

size_t r8ge::VertexTexture3D::getSize() const {
    return Vertex::getSize() + sizeof(z) + sizeof(tex_x) + sizeof(tex_y) + sizeof(tex_z);
}

r8ge::VertexColor::VertexColor(r8ge::coord_float x, r8ge::coord_float y, r8ge::ColorRGBA rgba) : Vertex(x, y),
                                                                                                 rgba(rgba) {
}

r8ge::video::VertexBufferLayout r8ge::VertexColor::getLayout() const {
    return video::VertexBufferLayout(
            {video::VertexBufferLayout::Entry::POS_XY, video::VertexBufferLayout::Entry::COLOUR_RGBA});
}

std::vector<uint8_t> r8ge::VertexColor::getRawData() const {
    auto data = Vertex::getRawData();
    union {
        struct {
            ColorRGBA rgba;
        };
        uint8_t _raw[sizeof(ColorRGBA)];
    } convertor = {rgba};
    data += {convertor._raw, convertor._raw + sizeof(convertor._raw)};
    return data;
}

size_t r8ge::VertexColor::getSize() const {
    return Vertex::getSize() + sizeof(rgba);
}

r8ge::VertexColor3D::VertexColor3D(r8ge::coord_float x, r8ge::coord_float y, r8ge::coord_float z,
                                   r8ge::ColorRGBA rgba) : Vertex(x, y), z(z), rgba(rgba) {

}

r8ge::video::VertexBufferLayout r8ge::VertexColor3D::getLayout() const {
    return video::VertexBufferLayout(
            {video::VertexBufferLayout::Entry::POS_XYZ, video::VertexBufferLayout::Entry::COLOUR_RGBA});
}

std::vector<uint8_t> r8ge::VertexColor3D::getRawData() const {
    auto data = Vertex::getRawData();
    union {
        struct {
            coord_float z;
            ColorRGBA rgba;
        };
        uint8_t _raw[sizeof(coord_float) + sizeof(ColorRGBA)];
    } convertor = {z, rgba};
    data += {convertor._raw, convertor._raw + sizeof(convertor._raw)};
    return data;
}

size_t r8ge::VertexColor3D::getSize() const {
    return Vertex::getSize() + sizeof(z) + sizeof(rgba);
}

r8ge::VertexColorTexture::VertexColorTexture(r8ge::coord_float x, r8ge::coord_float y, r8ge::ColorRGBA rgba,
                                             r8ge::texture_coord tex_x, r8ge::texture_coord tex_y) : Vertex(x, y),
                                                                                                     rgba(rgba),
                                                                                                     tex_x(tex_x),
                                                                                                     tex_y(tex_y) {

}

r8ge::video::VertexBufferLayout r8ge::VertexColorTexture::getLayout() const {
    return video::VertexBufferLayout({video::VertexBufferLayout::POS_XY, video::VertexBufferLayout::COLOUR_RGBA,
                                      video::VertexBufferLayout::TEXTURE_XY
                                     });
}

std::vector<uint8_t> r8ge::VertexColorTexture::getRawData() const {
    auto data = Vertex::getRawData();
    union {
        struct {
            ColorRGBA rgba;
            texture_coord tex_x, tex_y;
        };
        uint8_t _raw[sizeof(ColorRGBA) + 2 * sizeof(texture_coord)];
    } convertor = {rgba, tex_x, tex_y};
    data += {convertor._raw, convertor._raw + sizeof(convertor._raw)};
    return data;
}

size_t r8ge::VertexColorTexture::getSize() const {
    return Vertex::getSize() + sizeof(rgba) + sizeof(tex_x) + sizeof(tex_y);
}

r8ge::VertexColorTexture3D::VertexColorTexture3D(r8ge::coord_float x, r8ge::coord_float y, r8ge::coord_float z,
                                                 r8ge::ColorRGBA rgba, r8ge::texture_coord tex_x,
                                                 r8ge::texture_coord tex_y, r8ge::texture_coord tex_z) : Vertex(x, y),
                                                                                                         z(z),
                                                                                                         rgba(rgba),
                                                                                                         tex_x(tex_x),
                                                                                                         tex_y(tex_y),
                                                                                                         tex_z(tex_z) {
}

r8ge::video::VertexBufferLayout r8ge::VertexColorTexture3D::getLayout() const {
    return video::VertexBufferLayout({video::VertexBufferLayout::POS_XYZ, video::VertexBufferLayout::COLOUR_RGBA,
                                      video::VertexBufferLayout::TEXTURE_XYZ
                                     });
}

std::vector<uint8_t> r8ge::VertexColorTexture3D::getRawData() const {
    auto data = Vertex::getRawData();
    union {
        struct {
            coord_float z;
            ColorRGBA rgba;
            texture_coord tex_x, tex_y, tex_z;
        };
        uint8_t _raw[sizeof(coord_float) + sizeof(ColorRGBA) + 3 * sizeof(texture_coord)];
    } convertor = {z, rgba, tex_x, tex_y, tex_z};
    data += {convertor._raw, convertor._raw + sizeof(convertor._raw)};
    return data;
}

size_t r8ge::VertexColorTexture3D::getSize() const {
    return Vertex::getSize() + sizeof(z) + sizeof(rgba) + sizeof(tex_x) + sizeof(tex_y) + sizeof(tex_z);
}
