#include "StringFormat.h"

#include <vector>

#include "../Logger.h"

namespace r8ge {
    namespace utility{
        enum class FormatMode {IN_BRACKETS, OUT_BRACKETS, PROTECTED};

        static std::string typeToString(const StringFormat::ValidType &type);
        static std::string formatLoop(const std::string &form, const std::vector<std::string>& list);
        static std::string format(const std::string &form, const StringFormat::ValidList &list);
        static std::string formatInBrackets(const std::string&, size_t*, const std::vector<std::string>&);

        StringFormat::StringFormat(const std::string &form, const ValidList & list) : m_str(format(form, list)){}

        StringFormat::StringFormat(const std::string &str) : m_str{str}{}

        StringFormat::StringFormat() : m_str{} {}

        std::string StringFormat::to_string() {
            return m_str;
        }

        std::string format(const std::string &form, const StringFormat::ValidList &list) {
            std::vector<std::string> vec_list{};

            for(auto& type : list)
                vec_list.emplace_back(typeToString(type));

            return formatLoop(form, vec_list);
        }

        std::string formatLoop(const std::string &form, const std::vector<std::string>& list){
            FormatMode mode = FormatMode::OUT_BRACKETS;
            std::string outstr{""},instr{""};
            size_t counter = 0;
            char prev = '\0';

            for(char c : form) {
                if(c != '\\' && c!='{' && c!='}' && prev!='\\') {
                    if(mode == FormatMode::OUT_BRACKETS)
                        outstr+=c;
                    else
                        instr+=c;
                    prev = c;
                    continue;
                }

                if(prev == '\\' && c == '{')  outstr+=c; else
                if(prev == '\\' && c == '\\') outstr+='\\'; else
                if(prev != '\\' && c == '{' && mode == FormatMode::OUT_BRACKETS)  mode = FormatMode::IN_BRACKETS; else
                if(prev != '\\' && c == '}' && mode == FormatMode::IN_BRACKETS) {
                    mode = FormatMode::OUT_BRACKETS;
                    outstr += formatInBrackets(instr, &counter, list);
                    instr = "";
                } else
                if(prev != '\\' && c == '}')
                    outstr+= '}';

                prev = c;
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

        std::string typeToString(const StringFormat::ValidType &type) {
            if(const int* p = std::get_if<int>(&type)) return std::to_string(*p);
            if(const float* p = std::get_if<float>(&type)) return std::to_string(*p);
            if(const std::string* p = std::get_if<std::string>(&type)) return *p;
            if(const char* p = std::get_if<char>(&type)) return std::to_string(*p);
            if(const unsigned long* p = std::get_if<unsigned long>(&type)) return std::to_string(*p);

            return "";
        }
    }
}


