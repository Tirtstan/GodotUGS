#ifndef AUTHENTICATIONSERVICE_H
#define AUTHENTICATIONSERVICE_H

#include <godot_cpp/classes/object.hpp>

namespace godot
{
    class AuthenticationService : public Object
    {
        GDCLASS(AuthenticationService, Object)

    private:
        static AuthenticationService *instance;

    protected:
        static void _bind_methods();

    public:
        AuthenticationService();
        ~AuthenticationService();
        static AuthenticationService *get_singleton();

        void test();
    };
}

#endif