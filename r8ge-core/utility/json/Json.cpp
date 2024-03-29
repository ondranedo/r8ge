#include "Json.h"

#include "../../Logger.h"

#include "Object.h"
#include "Array.h"

#include <algorithm>

namespace r8ge {
    namespace utility {
        Json::Json() : m_type(Type::null) {}

        Json::Json(const object &o) : m_type(Type::object) {
            m_data.o = new object(o);
        }

        Json::Json(const std::initializer_list<std::pair<StringKey, Json>> &list) : m_type(Type::object) {
            m_data.o = new object(list);
        }

        Json::Json(const array &a) : m_type(Type::array) {
            m_data.a = new array(a);
        }

        Json::Json(const std::initializer_list<Json> &list) {
            m_type = Type::array;
            m_data.a = new array(list);
        }

        Json::~Json() {
            if (is_object()) delete m_data.o;
            if (is_array()) delete m_data.a;
            if (is_string()) delete m_data.s;
        }

        Json::Json(Json &&other) noexcept {
            m_data = other.m_data;
            m_type = other.m_type;
            other.m_data = {};
        }

        Json &Json::operator=(Json &&other) noexcept {
            if (this == &other)
                return *this;

            m_data = other.m_data;
            m_type = other.m_type;
            other.m_data = {};
            return *this;
        }


        Json::Json(const Json &other) {
            copy(other);
        }

        Json &Json::operator=(const Json &other) {
            copy(other);
            return *this;
        }

        void Json::copy(const Json &other) {
            if (this == &other) return;
            m_type = other.m_type;
            if (is_object()) m_data.o = new object(*other.m_data.o);
            else if (is_array()) m_data.a = new array(*other.m_data.a);
            else if (is_string()) m_data.s = new string(*other.m_data.s);
            else
                m_data = other.m_data;
        }

        std::string Json::to_string(bool format, size_t _tab_spaces, size_t _count_of_indent, bool _should_format) const {
            std::string str;

            if(_should_format)
                for (size_t c = 0; c < _count_of_indent * _tab_spaces; c++)
                    str += format ? " " : "";

            if (is_object()) str += m_data.o->to_string(format, _tab_spaces, _count_of_indent+1);
            if (is_array()) str += m_data.a->to_string(format, _tab_spaces, _count_of_indent+1);
            if (is_string()) str += "\"" + *m_data.s + "\"";
            if (is_boolean()) str += m_data.b ? "true" : "false";
            if (is_integral())str += std::to_string(m_data.i);
            if (is_decimal()) str += std::to_string(m_data.d);
            if (is_null()) str += "null";

            return str;
        }

        Type Json::type() const { return m_type; }

        bool Json::is_integral() const { return m_type == Type::integral; }

        bool Json::is_decimal() const { return m_type == Type::decimal; }

        bool Json::is_boolean() const { return m_type == Type::boolean; }

        bool Json::is_string() const { return m_type == Type::string; }

        bool Json::is_object() const { return m_type == Type::object; }

        bool Json::is_array() const { return m_type == Type::array; }

        bool Json::is_null() const { return m_type == Type::null; }

        Json &Json::operator[](const StringKey &key) {
            if (!is_object()) {
                if (is_null()) {
                    m_type = Type::object;
                    m_data.o = new object;
                } else {
                    R8GE_LOG_ERROR("Cannot use operator[StringKey:key] on non-object value");
                    return *this;
                }
            }
            return (*m_data.o)[key];
        }

        Json &Json::operator[](size_t index) {
            if (!is_array()) {
                if (is_null()) {
                    m_type = Type::array;
                    m_data.a = new array;
                } else {
                    R8GE_LOG_ERROR("Cannot use operator[size_t:index] on non-array value");
                    return *this;
                }
            }

            return (*m_data.a)[index];
        }

        Json &Json::operator+=(const Json &other) {
            if (is_array()) {
                m_data.a->add(other);
            }
            return *this;
        }

        Json &Json::operator+=(const std::pair<StringKey, Json> &p) {
            if (!is_object()) {
                if (is_null()) {
                    m_type = Type::object;
                    m_data.o = new object;
                } else {
                    R8GE_LOG_ERROR("Cannot use operator[std::pair<StringKey, Value>] on non-object value");
                    return *this;
                }
            } else
                (*m_data.o)[p.first] = p.second;

            return *this;
        }

        //TODO: change error function
        integral Json::as_integral() const {
            if (is_integral()) return m_data.i;
            else
                R8GE_LOG_ERROR("Cannot convert value [{}] to integral", to_string(m_type));
            return 0;
        }

        decimal Json::as_decimal() const {
            if (is_decimal()) return m_data.d;
            else
                R8GE_LOG_ERROR("Cannot convert value [{}] to decimal", to_string(m_type));
            return 0.0;
        }

        boolean Json::as_boolean() const {
            if (is_boolean()) return m_data.b;
            else
                R8GE_LOG_ERROR("Cannot convert value [{}] to boolean", to_string(m_type));
            return 0.0;
        }

        string Json::as_string(bool format) const {
            if (is_string()) return *m_data.s;
            else
                return to_string(format);
        }

        Json::Convertor Json::operator()() const {
            return {*this};
        }

        std::string Json::to_string(Type t) const {
            switch (t) {
                case Type::integral:
                    return "integral";
                case Type::decimal:
                    return "decimal";
                case Type::boolean:
                    return "boolean";
                case Type::string:
                    return "string";
                case Type::object:
                    return "object";
                case Type::array:
                    return "array";
                case Type::null:
                    return "null";
            }
            return "unknown";
        }

         size_t Json::from_string(std::string_view str, size_t _index) {
            // Remove all spaces, tabs, newlines
            std::string s{str};
            s.erase(std::remove_if(s.begin(), s.end(), [](unsigned char x) { return std::isspace(x); }), s.end());

            if (s.empty()) {
                m_type = Type::null;
                return _index;
            }

            if (s[_index] == '{') {
                m_type = Type::object;
                m_data.o = new object;
                return m_data.o->from_string(s, _index);
            } else if (s[_index] == '[') {
                m_type = Type::array;
                m_data.a = new array;
                return m_data.a->from_string(s, _index);
            } else if (s[_index] == '"') {
                m_type = Type::string;
                size_t last_index = s.find('"', _index + 1);
                auto str = s.substr(_index + 1, last_index - _index - 1);
                m_data.s = new string(str);
                return last_index + 1;
            } else if (s[_index] == 't' || s[_index] == 'f') {
                m_type = Type::boolean;
                m_data.b = s[_index] == 't';
                return _index + (s[_index] == 't' ? 5 : 6);
            } else if (s == "null") {
                m_type = Type::null;
                return _index;
            } else {
                size_t last_index_c = s.find(',', _index);
                size_t last_index_b = s.find('}', _index);
                size_t last_index_s = s.find(']', _index);
                size_t last_index = std::min(last_index_c, std::min(last_index_b, last_index_s));
                std::string num = s.substr(_index, last_index - _index);

                if (num.find('.') != std::string::npos) {
                    m_type = Type::decimal;
                    m_data.d = std::stod(num);
                } else {
                    m_type = Type::integral;
                    m_data.i = std::stoi(num);
                }

                return last_index;
            }
        }

        size_t Json::size() const {
            if (is_object()) return m_data.o->size();
            if (is_array()) return m_data.a->size();
            return 0;
        }

        std::vector<Json> Json::as_vector() const {
            if (is_array()) return m_data.a->as_vector();
            else
                R8GE_LOG_ERROR("Cannot convert value [{}] to vector", to_string(m_type));
            return {};
        }

        Json::Convertor::Convertor(const Json &value) : m_value(value) {}

        Json::Convertor::operator int() const {
            return static_cast<int>(m_value.as_integral());
        }

        Json::Convertor::operator long() const {
            return static_cast<long>(m_value.as_integral());
        }

        Json::Convertor::operator long long() const {
            return static_cast<long long>(m_value.as_integral());
        }

        Json::Convertor::operator float() const {
            return static_cast<float>(m_value.as_decimal());
        }

        Json::Convertor::operator double() const {
            return static_cast<double>(m_value.as_decimal());
        }

        Json::Convertor::operator long double() const {
            return static_cast<long double>(m_value.as_decimal());
        }

        Json::Convertor::operator bool() const {
            return m_value.as_boolean();
        }

        Json::Convertor::operator std::string() const {
            return m_value.as_string(false);
        }
    }
}