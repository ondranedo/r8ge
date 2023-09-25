#include "StringFormat.h"

#include <vector>

namespace r8ge {
    namespace utility{
        enum class FormatMode {IN_BRACKETS, OUT_BRACKETS, PROTECTED};

        static std::string typeToString(const StringFormat::ValidType &type);
        static std::string formatLoop(const std::string &form, const std::vector<std::string>& list);
        static std::string format(const std::string &form, const StringFormat::ValidList &list);
        static FormatMode formatModeFromChar(FormatMode fm, char c);
        static std::string formatInBrackets(const std::string&, size_t*, const std::vector<std::string>&);

        StringFormat::StringFormat(const std::string &form, const ValidList & list) : m_str(format(form, list)){}

        StringFormat::StringFormat(const std::string &str) : m_str{str}{}

        StringFormat::StringFormat() : m_str{} {}

        std::string StringFormat::to_string() {
            return m_str;
        }

        StringFormat::operator std::string() {
            return to_string();
        }

        std::string format(const std::string &form, const StringFormat::ValidList &list) {
            std::vector<std::string> vec_list{};

            for(auto& type : list)
                vec_list.emplace_back(typeToString(type));

            return formatLoop(form, vec_list);
        }

        std::string formatLoop(const std::string &form, const std::vector<std::string>& list){
            FormatMode mode = FormatMode::OUT_BRACKETS;
            std::string outstr = "";
            std::string instr = "";
            size_t counter = 0;

            for(char c : form) {
                FormatMode new_mode = mode != FormatMode::PROTECTED ? formatModeFromChar(mode, c) : FormatMode::OUT_BRACKETS;

                if(new_mode == FormatMode::OUT_BRACKETS
                   && mode != FormatMode::IN_BRACKETS) outstr += c;

                if(new_mode == FormatMode::IN_BRACKETS
                   && mode != FormatMode::OUT_BRACKETS) instr += c;

                if(new_mode == FormatMode::PROTECTED
                   && c != '\\') outstr += c;

                if(mode == FormatMode::IN_BRACKETS &&
                   new_mode == FormatMode::OUT_BRACKETS) {
                    outstr += formatInBrackets(instr, &counter, list);
                    instr = "";
                }
                mode = new_mode;
            }

            return outstr;
        }

        std::string formatInBrackets(const std::string& str, size_t* counter, const std::vector<std::string>& list) {
            if(list.empty()) return "{missing_value}";
            if(!str.empty()) {
                size_t index = std::stoi(str);
                if(index >= list.size()) return "{missing_value}";
                return list[index];
            }

            size_t index = *counter >= list.size() ? list.size()-1 : *counter;
            (*counter)++;
            return list[index];
        }

        FormatMode formatModeFromChar(FormatMode fm, char c) {
            if(c == '}') return FormatMode::OUT_BRACKETS;
            if(c == '{') return FormatMode::IN_BRACKETS;
            if(c == '\\') return FormatMode::PROTECTED;

            return fm == FormatMode::OUT_BRACKETS?
            FormatMode::OUT_BRACKETS:
            FormatMode::IN_BRACKETS;
        }

        std::string typeToString(const StringFormat::ValidType &type) {
            if(const int* p = std::get_if<int>(&type)) return std::to_string(*p);
            if(const float* p = std::get_if<float>(&type)) return std::to_string(*p);
            if(const std::string* p = std::get_if<std::string>(&type)) return *p;
            if(const char* p = std::get_if<char>(&type)) return std::to_string(*p);

            // TODO: Error or something
            return "";
        }
    }
}


