#include "Text.h"

#include "../FileIO.h"

namespace r8ge {
    namespace Reader {
        Text::Text(const std::string &path) : FileReader(path) {
            global::fileIO->add(m_path, FileType::TEXT);
        }

        Text::~Text() {
            global::fileIO->remove(m_path);
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

        size_t Text::lineNumber() const {
            return readLines().size()-1;
        }

        void Text::write(const std::string &buffer) {
            global::fileIO->setTextData(m_path, buffer);
        }

        void Text::write(const std::vector<std::string> &buffer) {
            std::string retliner{""};

            for(auto &c : buffer) {
                retliner += c + '\n';
            }

            global::fileIO->setTextData(m_path, retliner);
        }

        void Text::append(const std::string &buffer) {
            global::fileIO->appendTextData(m_path, buffer);
        }

        void Text::append(const std::vector<std::string> &buffer) {
            std::string retliner{""};

            for(auto &c : buffer) {
                retliner += c + '\n';
            }

            global::fileIO->appendTextData(m_path, retliner);
        }

        void Text::append(const char c) {
            global::fileIO->appendTextData(m_path, {c});
        }

        void Text::appendNewLine() {
            global::fileIO->appendTextData(m_path, {'\n'});
        }

        void Text::appendNewLine(const std::string &buffer) {
            appendNewLine();
            append(buffer);
        }

        void Text::appendNewLine(const std::vector<std::string> &buffer) {
            appendNewLine();
            append(buffer);
        }

        void Text::appendNewLine(char c) {
            appendNewLine();
            append(c);
        }
    }
}