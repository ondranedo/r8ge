#ifndef R8GE_JSONF_H
#define R8GE_JSONF_H

#include "StringKey.h"

namespace r8ge {
    using boolean = bool;
    template<class T> concept Boolean = std::is_same_v<T, boolean>;
    using integral = long long int;
    template<class T> concept Integral = std::integral<T> && std::is_convertible_v<T, integral> && !Boolean<T>;
    using decimal = long double;
    template<class T> concept Decimal = std::floating_point<T> && std::is_convertible_v<T, decimal>;
    using string = std::string;
    template<class T> concept String = std::is_convertible_v<T, string>;

    class Object;
    class Array;
    using array = ::r8ge::Array;
    using object = Object;

    union Data {
        integral i;
        decimal d;
        boolean b;
        string* s;
        object* o;
        array* a;
    };

    enum class Type{
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
        template<Integral T> Json(T i) : m_type(Type::integral) { m_data.i = i; }
        template<Decimal T> Json(T d) : m_type(Type::decimal) { m_data.d = d; }
        template<Boolean T> Json(T b) : m_type(Type::boolean) { m_data.b = b; }
        template<String T> Json(T s) : m_type(Type::string) { m_data.s = new string(s); }

        Json(const object& o);
        Json(const std::initializer_list<std::pair<StringKey, Json>>& list);

        Json(const array& a);
        Json(const std::initializer_list<Json>& list);

    public:
        ~Json();
        Json(const Json& other);
        Json(Json&& other) noexcept;
        Json& operator=(const Json& other);
        Json& operator=(Json&& other) noexcept;

    public:
        Json& operator[](const StringKey& key);
        Json& operator[] (size_t index);
        Json& operator+=(const Json& other);
        Json& operator+=(const std::pair<StringKey, Json>& p);

    private:
        void copy(const Json& other);


    public:
        [[nodiscard]] std::string to_string() const;
        [[nodiscard]] std::string to_string(Type t) const;

    public:
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
            Convertor (const Json& value);
            operator int() const;
            operator long() const;
            operator long long() const;

            operator float() const;
            operator double() const;
            operator long double() const;

            operator bool() const;

            operator std::string() const;
        private:
            const Json& m_value;
        };

    public:
        [[nodiscard]] Convertor operator()() const;
        [[nodiscard]] integral as_integral() const;
        [[nodiscard]] decimal as_decimal() const;
        [[nodiscard]] boolean as_boolean() const;
        [[nodiscard]] string as_string() const;

    private:
        Data m_data{};
        Type m_type;
    };
}

#endif//!R8GE_JSONF_H
