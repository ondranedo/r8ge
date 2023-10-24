#ifndef R8GE_JSON_H
#define R8GE_JSON_H

#include "StringKey.h"

#include <vector>

namespace r8ge {
    namespace utility {
        class Object;
        class Array;

        using boolean = bool;
        using integral = long long int;
        using decimal = long double;
        using string = std::string;
        using array = ::r8ge::utility::Array;
        using object = ::r8ge::utility::Object;

        template<class T> concept Boolean = std::is_same_v<T, boolean>;
        template<class T> concept Integral = std::integral<T> && std::is_convertible_v<T, integral> && !Boolean<T>;
        template<class T> concept Decimal = std::floating_point<T> && std::is_convertible_v<T, decimal>;
        template<class T> concept String = std::is_convertible_v<T, string>;

        union Data {
            integral i;
            decimal d;
            boolean b;
            string *s;
            object *o;
            array *a;
        };

        enum class Type {
            integral,
            decimal,
            boolean,
            string,
            object,
            array,
            null
        };

        class Json {
        public:
            Json();
            ~Json();

            size_t from_string(std::string_view str, size_t _index = 0);

            template<Integral T> Json(T i) : m_type(Type::integral) { m_data.i = i; }
            template<Decimal T> Json(T d) : m_type(Type::decimal) { m_data.d = d; }
            template<Boolean T> Json(T b) : m_type(Type::boolean) { m_data.b = b; }
            template<String T> Json(T s) : m_type(Type::string) { m_data.s = new string(s); }

            Json(const object &o);
            Json(const std::initializer_list<std::pair<StringKey, Json>> &list);
            Json(const array &a);
            Json(const std::initializer_list<Json> &list);

            Json(const Json &other);
            Json(Json &&other) noexcept;
            Json &operator=(const Json &other);
            Json &operator=(Json &&other) noexcept;

        public:
            Json &operator[](const StringKey &key);
            Json &operator[](size_t index);
            Json &operator+=(const Json &other);
            Json &operator+=(const std::pair<StringKey, Json> &p);

        private:
            void copy(const Json &other);

        public:
            [[nodiscard]] std::string to_string(bool format, size_t _tab_spaces=4, size_t _count_of_indent = 0, bool _should_format = 1) const;
            [[nodiscard]] std::string to_string(Type t) const;
            [[nodiscard]] Type type() const;
            [[nodiscard]] bool is_integral() const;
            [[nodiscard]] bool is_decimal() const;
            [[nodiscard]] bool is_boolean() const;
            [[nodiscard]] bool is_string() const;
            [[nodiscard]] bool is_object() const;
            [[nodiscard]] bool is_array() const;
            [[nodiscard]] bool is_null() const;

        private:
            struct Convertor {
                Convertor(const Json &value);
                operator int() const;
                operator long() const;
                operator long long() const;
                operator float() const;
                operator double() const;
                operator long double() const;
                operator bool() const;
                operator std::string() const;
            private:
                const Json &m_value;
            };

        public:
            [[nodiscard]] Convertor operator()() const;
            [[nodiscard]] integral as_integral() const;
            [[nodiscard]] decimal as_decimal() const;
            [[nodiscard]] boolean as_boolean() const;
            [[nodiscard]] string as_string(bool format) const;
            [[nodiscard]] std::vector<Json> as_vector() const;

        private:
            Data m_data{};
            Type m_type;
        };
    }
}

#endif//!R8GE_JSON_H
