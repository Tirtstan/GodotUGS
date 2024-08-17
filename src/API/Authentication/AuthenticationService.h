#ifndef AUTHENTICATIONSERVICE_H
#define AUTHENTICATIONSERVICE_H

#include <godot_cpp/classes/object.hpp>

namespace godot
{
    class AuthenticationService : public Object
    {
        GDCLASS(AuthenticationService, Object)

    protected:
        static void _bind_methods();

    public:
        AuthenticationService();
        ~AuthenticationService();
    };
}

#endif