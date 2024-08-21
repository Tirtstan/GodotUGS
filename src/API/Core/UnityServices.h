#ifndef UNITYSERVICES_H
#define UNITYSERVICES_H

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/json.hpp>

#include "APIResource.h"
#include "GodotUGS.h"
#include "CoreExceptionContent.h"

namespace godot
{
    class UnityServices : public Object
    {
        GDCLASS(UnityServices, Object)

    private:
        static UnityServices *instance;

        const String UnityServicesUrl = "https://services.api.unity.com";
        String environment = "production";

    protected:
        static void _bind_methods();

    public:
        UnityServices();
        ~UnityServices();
        static UnityServices *get_singleton();

        void initialize();

        String get_environment() const;
        void set_environment(const String &environment = "production");
    };
}

#endif