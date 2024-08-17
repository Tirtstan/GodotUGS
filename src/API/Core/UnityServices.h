#ifndef UNITYSERVICES_H
#define UNITYSERVICES_H

#include <godot_cpp/classes/object.hpp>
#include "APIResource.h"

namespace godot
{
    class UnityServices : public Object
    {
        GDCLASS(UnityServices, Object)

    protected:
        static void _bind_methods();

    public:
        UnityServices();
        ~UnityServices();

        static String get_project_id();
    };
}

#endif