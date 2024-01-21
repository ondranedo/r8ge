//
// Created by karnatour on 21.1.24.
//

#include "Gltf.h"
#include "../../Logger.h"

namespace r8ge {
    namespace reader {

        Gltf::Gltf(std::string_view path) : Text(path) {
            write("");
        }

        Gltf::~Gltf() {

        }

        utility::Json &Gltf::gltf() {
            return m_gltf;
        }

        void Gltf::load_gltf() {
            load();
            m_gltf.from_string(readFile());
            write("");
            m_materials = m_gltf["materials"];
            m_meshes = m_gltf["meshes"];

        }

        FileType Gltf::getType() {
            return FileType::GLTF;
        }

        void Gltf::save_gltf() {
            write(m_gltf.to_string(true));
            save();
            write("");
        }

        std::vector<GltfObject> Gltf::parse() {
            return std::vector<GltfObject>();
        }


    }

} // r8ge
} // reader