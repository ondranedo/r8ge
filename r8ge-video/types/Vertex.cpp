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
    std::vector<uint8_t> data = Vertex::getRawData();

    const auto* zCoordRawData = reinterpret_cast<const uint8_t*>(&z);
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

    const auto* texXRawData = reinterpret_cast<const uint8_t*>(&tex_x);
    data.insert(data.end(), texXRawData, texXRawData + sizeof(texture_coord));

    const auto* texYRawData = reinterpret_cast<const uint8_t*>(&tex_y);
    data.insert(data.end(), texYRawData, texYRawData + sizeof(texture_coord));

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
    std::vector<uint8_t> data = Vertex::getRawData();

    const auto* zCoordRawData = reinterpret_cast<const uint8_t*>(&z);
    data.insert(data.end(), zCoordRawData, zCoordRawData + sizeof(coord_float));

    const auto* texXRawData = reinterpret_cast<const uint8_t*>(&tex_x);
    data.insert(data.end(), texXRawData, texXRawData + sizeof(texture_coord));

    const auto* texYRawData = reinterpret_cast<const uint8_t*>(&tex_y);
    data.insert(data.end(), texYRawData, texYRawData + sizeof(texture_coord));

    return data;
}

size_t r8ge::VertexTexture3D::getSize() const {
    return Vertex::getSize() + sizeof(z) + sizeof(tex_x) + sizeof(tex_y) + sizeof(tex_z);
}

r8ge::VertexColor::VertexColor(r8ge::coord_float x, r8ge::coord_float y, r8ge::ColorRGB rgb) : Vertex(x, y),
                                                                                                 rgb(rgb) {
}

r8ge::video::VertexBufferLayout r8ge::VertexColor::getLayout() const {
    return video::VertexBufferLayout(
            {video::VertexBufferLayout::Entry::POS_XY, video::VertexBufferLayout::Entry::COLOUR_RGB});
}

std::vector<uint8_t> r8ge::VertexColor::getRawData() const {
    std::vector<uint8_t> data = Vertex::getRawData();

    const auto* colorRawData = reinterpret_cast<const uint8_t*>(&rgb);
    data.insert(data.end(), colorRawData, colorRawData + sizeof(ColorRGB));

    return data;
}

size_t r8ge::VertexColor::getSize() const {
    return Vertex::getSize() + sizeof(rgb);
}

r8ge::VertexColor3D::VertexColor3D(r8ge::coord_float x, r8ge::coord_float y, r8ge::coord_float z,
                                   r8ge::ColorRGB rgb) : Vertex(x, y), z(z), rgb(rgb) {

}

r8ge::video::VertexBufferLayout r8ge::VertexColor3D::getLayout() const {
    return video::VertexBufferLayout(
            {video::VertexBufferLayout::Entry::POS_XYZ, video::VertexBufferLayout::Entry::COLOUR_RGB});
}

std::vector<uint8_t> r8ge::VertexColor3D::getRawData() const {
    std::vector<uint8_t> data = Vertex::getRawData();

    const auto* colorRawData = reinterpret_cast<const uint8_t*>(&rgb);
    data.insert(data.end(), colorRawData, colorRawData + sizeof(ColorRGB));

    const auto* zCoordRawData = reinterpret_cast<const uint8_t*>(&z);
    data.insert(data.end(), zCoordRawData, zCoordRawData + sizeof(coord_float));

    return data;
}


size_t r8ge::VertexColor3D::getSize() const {
    return Vertex::getSize() + sizeof(z) + sizeof(rgb);
}

r8ge::VertexColorTexture::VertexColorTexture(r8ge::coord_float x, r8ge::coord_float y, r8ge::ColorRGB rgb,
                                             r8ge::texture_coord tex_x, r8ge::texture_coord tex_y) : Vertex(x, y),
                                                                                                     rgb(rgb),
                                                                                                     tex_x(tex_x),
                                                                                                     tex_y(tex_y) {

}

r8ge::video::VertexBufferLayout r8ge::VertexColorTexture::getLayout() const {
    return video::VertexBufferLayout({video::VertexBufferLayout::POS_XY, video::VertexBufferLayout::COLOUR_RGB,
                                      video::VertexBufferLayout::TEXTURE_XY
                                     });
}

std::vector<uint8_t> r8ge::VertexColorTexture::getRawData() const {
    std::vector<uint8_t> data = Vertex::getRawData();

    const auto* colorRawData = reinterpret_cast<const uint8_t*>(&rgb);
    data.insert(data.end(), colorRawData, colorRawData + sizeof(ColorRGB));

    const auto* texXRawData = reinterpret_cast<const uint8_t*>(&tex_x);
    data.insert(data.end(), texXRawData, texXRawData + sizeof(texture_coord));

    const auto* texYRawData = reinterpret_cast<const uint8_t*>(&tex_y);
    data.insert(data.end(), texYRawData, texYRawData + sizeof(texture_coord));

    return data;
}

size_t r8ge::VertexColorTexture::getSize() const {
    return Vertex::getSize() + sizeof(rgb) + sizeof(tex_x) + sizeof(tex_y);
}

r8ge::VertexColorTexture3D::VertexColorTexture3D(r8ge::coord_float x, r8ge::coord_float y, r8ge::coord_float z,
                                                 r8ge::ColorRGB rgb, r8ge::texture_coord tex_x,
                                                 r8ge::texture_coord tex_y, r8ge::texture_coord tex_z) : Vertex(x, y),
                                                                                                         z(z),
                                                                                                         rgb(rgb),
                                                                                                         tex_x(tex_x),
                                                                                                         tex_y(tex_y),
                                                                                                         tex_z(tex_z) {
}

r8ge::video::VertexBufferLayout r8ge::VertexColorTexture3D::getLayout() const {
    return video::VertexBufferLayout({video::VertexBufferLayout::POS_XYZ, video::VertexBufferLayout::COLOUR_RGB,
                                      video::VertexBufferLayout::TEXTURE_XYZ
                                     });
}

std::vector<uint8_t> r8ge::VertexColorTexture3D::getRawData() const {
    std::vector<uint8_t> data = Vertex::getRawData();

    const auto* colorRawData = reinterpret_cast<const uint8_t*>(&rgb);
    data.insert(data.end(), colorRawData, colorRawData + sizeof(ColorRGB));

    const auto* zCoordRawData = reinterpret_cast<const uint8_t*>(&z);
    data.insert(data.end(), zCoordRawData, zCoordRawData + sizeof(coord_float));

    const auto* texXRawData = reinterpret_cast<const uint8_t*>(&tex_x);
    data.insert(data.end(), texXRawData, texXRawData + sizeof(texture_coord));

    const auto* texYRawData = reinterpret_cast<const uint8_t*>(&tex_y);
    data.insert(data.end(), texYRawData, texYRawData + sizeof(texture_coord));

    return data;
}

size_t r8ge::VertexColorTexture3D::getSize() const {
    return Vertex::getSize() + sizeof(z) + sizeof(rgb) + sizeof(tex_x) + sizeof(tex_y) + sizeof(tex_z);
}
