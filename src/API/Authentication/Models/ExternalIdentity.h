#ifndef EXTERNALIDENTITY_H
#define EXTERNALIDENTITY_H

#include <godot_cpp/classes/ref_counted.hpp>
#include "IDictionaryConvertible.h"

namespace godot
{
    class ExternalIdentity : public RefCounted, public IDictionaryConvertible
    {
        GDCLASS(ExternalIdentity, RefCounted)

    protected:
        static void _bind_methods();

    public:
        ExternalIdentity();

        String external_id;
        String provider_id;

        Dictionary to_dict() const override;
        void from_dict(const Dictionary &dict) override;
    };
}

#endif