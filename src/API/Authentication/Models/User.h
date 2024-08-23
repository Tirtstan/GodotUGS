#ifndef USER_H
#define USER_H

#include <godot_cpp/classes/ref_counted.hpp>
#include "IDictionaryConvertible.h"
#include "ExternalIdentity.h"

namespace godot
{
    class User : public RefCounted, public IDictionaryConvertible
    {
        GDCLASS(User, RefCounted)

    protected:
        static void _bind_methods();

    public:
        User();

        bool disabled;
        String id;
        Vector<Ref<ExternalIdentity>> external_ids;
        String username;

        Dictionary to_dict() const override;
        void from_dict(const Dictionary &dict) override;
    };
}

#endif