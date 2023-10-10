#include "TextReader.h"

namespace r8ge {
    namespace Reader {
        Text::~Text() = default;

        void Text::save() const {

        }

        void Text::load() const {

        }

        FileType Text::getType() {
            return FileType::TEXT;
        }

        std::string Text::readFile() const {
            //return std::string();
            return "whole_file";
        }
    }
}