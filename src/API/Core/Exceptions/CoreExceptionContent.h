#ifndef COREEXCEPTIONCONTENT_H
#define COREEXCEPTIONCONTENT_H

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/json.hpp>
#include "IDictionaryConvertible.h"

namespace godot
{
    class CoreExceptionContent : public RefCounted, public IDictionaryConvertible
    {
        GDCLASS(CoreExceptionContent, RefCounted)

    protected:
        static void _bind_methods();

    public:
        CoreExceptionContent();
        CoreExceptionContent(const String &text);

        String title;
        int status;
        String detail;
        String detail2;

        String get_message() const;

        Dictionary to_dict() const override;
        void from_dict(const Dictionary &dict) override;
    };
}

#endif
