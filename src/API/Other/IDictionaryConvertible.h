#ifndef IDICTIONARYCONVERTIBLE_H
#define IDICTIONARYCONVERTIBLE_H

#include <godot_cpp/variant/dictionary.hpp>

namespace godot
{
    class IDictionaryConvertible
    {
    public:
        virtual ~IDictionaryConvertible() = default;
        virtual Dictionary to_dict() const = 0;
        virtual void from_dict(const Dictionary &dict) = 0;
    };
}

#endif

/* Rememeber:

// How to serialize the classes to a JSON string

Dictionary dict = class->to_dict();
String json_string = JSON::stringify(dict);

----------------------------------------------------

// How to deserialize the JSON string back to the classes

Dictionary parsed_dict = JSON::parse_string(json_string);
Ref<Class> parsed_sign_in_response = memnew(Class);
parsed_class->from_dict(parsed_dict);

*/