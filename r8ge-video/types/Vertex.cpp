#include "Vertex.h"

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
    std::vector<uint8_t> data = Vertex::getRawData();

    const auto *zCoordRawData = reinterpret_cast<const uint8_t *>(&z);
    data.insert(data.end(), zCoordRawData, zCoordRawData + sizeof(coord_float));

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
    std::vector<uint8_t> data = Vertex::getRawData();

    const auto *texXRawData = reinterpret_cast<const uint8_t *>(&tex_x);
    data.insert(data.end(), texXRawData, texXRawData + sizeof(texture_coord));

    const auto *texYRawData = reinterpret_cast<const uint8_t *>(&tex_y);
    data.insert(data.end(), texYRawData, texYRawData + sizeof(texture_coord));

    return data;
}

size_t r8ge::VertexTexture::getSize() const {
    return Vertex::getSize() + sizeof(tex_x) + sizeof(tex_y);
}

r8ge::VertexTexture3D::VertexTexture3D(r8ge::coord_float x, r8ge::coord_float y, r8ge::coord_float z,
                                       r8ge::texture_coord tex_x, r8ge::texture_coord tex_y) : Vertex(x, y), z(z),
                                                                                               tex_x(tex_x),
                                                                                               tex_y(tex_y) {
}

r8ge::video::VertexBufferLayout r8ge::VertexTexture3D::getLayout() const {
    return video::VertexBufferLayout(
            {video::VertexBufferLayout::Entry::POS_XYZ, video::VertexBufferLayout::Entry::TEXTURE_XY});
}

std::vector<uint8_t> r8ge::VertexTexture3D::getRawData() const {
    std::vector<uint8_t> data = Vertex::getRawData();

    const auto *zCoordRawData = reinterpret_cast<const uint8_t *>(&z);
    data.insert(data.end(), zCoordRawData, zCoordRawData + sizeof(coord_float));

    const auto *texXRawData = reinterpret_cast<const uint8_t *>(&tex_x);
    data.insert(data.end(), texXRawData, texXRawData + sizeof(texture_coord));

    const auto *texYRawData = reinterpret_cast<const uint8_t *>(&tex_y);
    data.insert(data.end(), texYRawData, texYRawData + sizeof(texture_coord));
    return data;
}

size_t r8ge::VertexTexture3D::getSize() const {
    return Vertex::getSize() + sizeof(z) + sizeof(tex_x) + sizeof(tex_y);
}

r8ge::VertexColor::VertexColor(r8ge::coord_float x, r8ge::coord_float y, r8ge::ColorRGBA rgba) : Vertex(x, y),
                                                                                                 rgba(rgba) {
}

r8ge::video::VertexBufferLayout r8ge::VertexColor::getLayout() const {
    return video::VertexBufferLayout(
            {video::VertexBufferLayout::Entry::POS_XY, video::VertexBufferLayout::Entry::COLOUR_RGBA});
}

std::vector<uint8_t> r8ge::VertexColor::getRawData() const {
    std::vector<uint8_t> data = Vertex::getRawData();

    const auto *colorRawData = reinterpret_cast<const uint8_t *>(&rgba);
    data.insert(data.end(), colorRawData, colorRawData + sizeof(ColorRGBA));

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
    std::vector<uint8_t> data = Vertex::getRawData();

    const auto *zCoordRawData = reinterpret_cast<const uint8_t *>(&z);
    data.insert(data.end(), zCoordRawData, zCoordRawData + sizeof(coord_float));

    const auto *colorRawData = reinterpret_cast<const uint8_t *>(&rgba);
    data.insert(data.end(), colorRawData, colorRawData + sizeof(ColorRGBA));

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
    std::vector<uint8_t> data = Vertex::getRawData();

    const auto *colorRawData = reinterpret_cast<const uint8_t *>(&rgba);
    data.insert(data.end(), colorRawData, colorRawData + sizeof(ColorRGBA));

    const auto *texXRawData = reinterpret_cast<const uint8_t *>(&tex_x);
    data.insert(data.end(), texXRawData, texXRawData + sizeof(texture_coord));

    const auto *texYRawData = reinterpret_cast<const uint8_t *>(&tex_y);
    data.insert(data.end(), texYRawData, texYRawData + sizeof(texture_coord));

    return data;
}

size_t r8ge::VertexColorTexture::getSize() const {
    return Vertex::getSize() + sizeof(rgba) + sizeof(tex_x) + sizeof(tex_y);
}

r8ge::VertexColorTexture3D::VertexColorTexture3D(r8ge::coord_float x, r8ge::coord_float y, r8ge::coord_float z,
                                                 r8ge::ColorRGBA rgba, r8ge::texture_coord tex_x,
                                                 r8ge::texture_coord tex_y, normal_float normal_x,
                                                 normal_float normal_y,
                                                 normal_float normal_z) : Vertex(x, y),
                                                                          z(z),
                                                                          rgba(rgba),
                                                                          tex_x(tex_x),
                                                                          tex_y(tex_y),
                                                                          normal_x(normal_x),
                                                                          normal_y(normal_y),
                                                                          normal_z(normal_z) {
}

r8ge::video::VertexBufferLayout r8ge::VertexColorTexture3D::getLayout() const {
    return video::VertexBufferLayout({video::VertexBufferLayout::POS_XYZ, video::VertexBufferLayout::COLOUR_RGBA,
                                      video::VertexBufferLayout::TEXTURE_XY, video::VertexBufferLayout::NORMAL_XYZ
                                     });
}

std::vector<uint8_t> r8ge::VertexColorTexture3D::getRawData() const {
    std::vector<uint8_t> data = Vertex::getRawData();

    const auto *zCoordRawData = reinterpret_cast<const uint8_t *>(&z);
    data.insert(data.end(), zCoordRawData, zCoordRawData + sizeof(coord_float));

    const auto *colorRawData = reinterpret_cast<const uint8_t *>(&rgba);
    data.insert(data.end(), colorRawData, colorRawData + sizeof(ColorRGBA));

    const auto *texXRawData = reinterpret_cast<const uint8_t *>(&tex_x);
    data.insert(data.end(), texXRawData, texXRawData + sizeof(texture_coord));

    const auto *texYRawData = reinterpret_cast<const uint8_t *>(&tex_y);
    data.insert(data.end(), texYRawData, texYRawData + sizeof(texture_coord));

    const auto *normalXRawData = reinterpret_cast<const uint8_t *>(&normal_x);
    data.insert(data.end(), normalXRawData, normalXRawData + sizeof(normal_float));

    const auto *normalYRawData = reinterpret_cast<const uint8_t *>(&normal_y);
    data.insert(data.end(), normalYRawData, normalYRawData + sizeof(normal_float));

    const auto *normalZRawData = reinterpret_cast<const uint8_t *>(&normal_z);
    data.insert(data.end(), normalZRawData, normalZRawData + sizeof(normal_float));


    return data;
}

size_t r8ge::VertexColorTexture3D::getSize() const {
    return Vertex::getSize() + sizeof(z) + sizeof(rgba) + sizeof(tex_x) + sizeof(tex_y) + sizeof(normal_x) +
           sizeof(normal_y) + sizeof(normal_z);
}
