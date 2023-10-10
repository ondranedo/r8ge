#include "TextReader.h"

namespace r8ge {
    namespace Reader {
        Text::~Text() = default;

        void Text::save() const {

        }

        void Text::load() {

        }

        FileType Text::getType() {
            return FileType::TEXT;
        }

        std::string Text::readFile() const {
            //return std::string();
            return "whole_file";
        }

        std::vector<std::string> Text::readLines() const {
            //return std::vector<std::string>();
            return {"line1", "line2"};
        }
    }
}