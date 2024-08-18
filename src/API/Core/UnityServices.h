#ifndef UNITYSERVICES_H
#define UNITYSERVICES_H

#include <godot_cpp/classes/object.hpp>
#include "APIResource.h"

namespace godot
{
    class UnityServices : public Object
    {
        GDCLASS(UnityServices, Object)

    private:
        const String UnityServicesUrl = "https://services.api.unity.com";
        String environment = "production";

    protected:
        static void _bind_methods();

    public:
        UnityServices();
        ~UnityServices();

        void initialize();

        String get_environment() const;
        void set_environment(const String environment);

        static String get_project_id();
    };
}

#endif