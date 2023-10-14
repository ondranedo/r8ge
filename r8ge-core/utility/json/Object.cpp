#include "Object.h"

#include "../../Logger.h"

namespace r8ge {
    namespace utility {
        void Object::add(const StringKey &key, const Json &value) {
            if(m_map.find(key.get()) != m_map.end())
                return;

            m_map.emplace(key.get(), value);
        }

        Object::Object(const StringKey &key, const Json &value) {
            add(key, value);
        }

        Object::Object(const std::initializer_list<std::pair<StringKey, Json>> &list) {
            for(auto& pair : list)
                add(pair.first, pair.second);
        }


        std::string Object::to_string(bool format, size_t _tab_spaces, size_t _count_of_indent) const {
            std::string str = "{";
            str += format ? "\n" : "";

            size_t i = 0;
            for(auto&[key, value]: m_map) {
                for(size_t c = 0; c < _count_of_indent*_tab_spaces; c++)
                    str += format ? " " : "";

                str += "\"" + key + "\":" + (format?" ":"") + value.to_string(format, _tab_spaces, _count_of_indent, false);
                if(i++ < m_map.size()-1)
                    str += ",";
                str+=format?"\n":"";
            }
            for(size_t c = 0; c < (_count_of_indent-1)*_tab_spaces; c++)
                str += format ? " " : "";
            return str + "}";
        }

        Object::Object() {
            m_map = {};
        }

        Json &Object::operator[](const StringKey &key) {
            return m_map[key.get()];
        }

        static std::pair<string, Json> generateEntry(const string &str, const string& key, size_t& index) {
            Json j;
            index = j.from_string(str, index);
            char c = str[index];
            return {key, j};
        }

        static string getKey(const string &str, size_t& index)
        {
            if(str[index] == ',') index++;

            string key;
            size_t last = str.find(':', index);
            char c = str[index];
            key = str.substr(index+1, last - index-2);

            index = last + 1; // +1 for ':'

            return key;
        }

        size_t Object::from_string(const string &str, size_t _index) {
            size_t i = _index + 1;    // 1 for '{'
            size_t bracket_count = 1; // 1 for '{'

            while(bracket_count) {
                m_map.emplace(generateEntry(str, getKey(str, i), i));

                if(str[i] == '}') bracket_count--;
            }

            return i+1;
        }
    }
}