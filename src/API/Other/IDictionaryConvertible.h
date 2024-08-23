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

String json_string = JSON::stringify(class->to_dict());

----------------------------------------------------

// How to deserialize the JSON string back to the classes

Ref<Class> parsed_class = memnew(Class);
parsed_class->from_dict(JSON::parse_string(json_string));

*/