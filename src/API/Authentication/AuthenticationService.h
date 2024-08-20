#ifndef AUTHENTICATIONSERVICE_H
#define AUTHENTICATIONSERVICE_H

#include <godot_cpp/classes/object.hpp>
#include "SignInResponse.h"

namespace godot
{
    class AuthenticationService : public Object
    {
        GDCLASS(AuthenticationService, Object)

    private:
        static AuthenticationService *instance;

        bool signed_in = false;
        String access_token;
        String player_id;
        String player_name;
        String profile = "DefaultProfile";
        String last_notification_date;

        String session_token;
        const String AuthURL = "https://player-auth.services.api.unity.com/v1";
        const String ProfileRegex = "^[a-zA-Z0-9_-]{1,30}$";
        const String SteamIdentityRegex = "^[a-zA-Z0-9]{5,30}$";
        const String CachePath = "user://GodotUGS_UserCache_gdextension.cfg";
        const String Persistents = "Persistents";

        void on_initialized(bool initialized);

        void sign_in_with_session_token(const String &session_token);

    protected:
        static void _bind_methods();

    public:
        AuthenticationService();
        ~AuthenticationService();
        static AuthenticationService *get_singleton();

        bool is_signed_in() const;
        String get_access_token() const;
        String get_player_id() const;
        String get_player_name() const;
        String get_profile() const;
        bool does_session_token_exists() const;

        void sign_in_anonymously();
        void delete_account();

        void sign_out(bool clear_credentials = false);
        void switch_profile(const String &profile_name);
        void clear_session_token();
    };
}

#endif