#ifndef SIGNINRESPONSE_H
#define SIGNINRESPONSE_H

#include <godot_cpp/classes/ref_counted.hpp>
#include "IDictionaryConvertible.h"
#include "User.h"

namespace godot
{
    class SignInResponse : public RefCounted, public IDictionaryConvertible
    {
        GDCLASS(SignInResponse, RefCounted)

    protected:
        static void _bind_methods();

    public:
        SignInResponse();

        int expires_in;
        String id_token;
        String session_token;
        String last_notification_date;
        Ref<User> user;
        String user_id;

        Dictionary to_dict() const override;
        void from_dict(const Dictionary &dict) override;
    };
}

#endif
