#include "TextReader.h"

#include "../FileIO.h"

namespace r8ge {
    namespace Reader {
        Text::Text(const std::string &path) : FileReader(path) {
            global::fileIO->add(m_path, FileType::TEXT);
        }

        Text::~Text() {
            global::fileIO->remove(m_path);
        }

        void Text::save() const {
            global::fileIO->save(m_path);
        }

        void Text::load() {
            global::fileIO->load(m_path);
        }

        FileType Text::getType() {
            return FileType::TEXT;
        }

        std::string Text::readFile() const {
            return global::fileIO->getTextData(m_path);
        }

        std::vector<std::string> Text::readLines() const {
            std::vector<std::string> retliner = {""};
            std::size_t line_count = 0;

            for(auto &c : global::fileIO->getTextData(m_path)) {
                if(c == '\n') {
                    line_count++;
                    retliner.push_back("");
                }
                else {
                    retliner[line_count] += c;
                }
            }

            return retliner;
        }
    }
}