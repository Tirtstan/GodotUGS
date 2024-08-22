#ifndef AUTHENTICATIONSERVICE_H
#define AUTHENTICATIONSERVICE_H

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/config_file.hpp>
#include "GodotUGS.h"
#include "UnityServices.h"
#include "SignInResponse.h"

namespace godot
{
    class AuthenticationService : public Object
    {
        GDCLASS(AuthenticationService, Object)

    private:
        static AuthenticationService *instance;

        String project_id;
        String environment;

        bool signed_in = false;
        String profile = "DefaultProfile";

        Ref<SignInResponse> sign_in_response;
        Ref<ConfigFile> config;
        const String AUTH_URL = "https://player-auth.services.api.unity.com";
        const String PROFILE_REGEX = "^[a-zA-Z0-9_-]{1,30}$";
        const String STEAM_IDENTITY_REGEX = "^[a-zA-Z0-9]{5,30}$";
        const String CACHE_PATH = "user://GodotUGS_UserCache_gdextension.cfg";
        const String PERSISTENTS = "Persistents";

        void _on_initialized(bool initialized);

        void sign_in_with_session_token(const String &session_token);
        void clear_access_token();

        void save_cache();
        void save_persistents();
        void load_cache();
        void load_persistents();

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
        bool does_session_token_exist() const;
        String get_last_notification_date() const;

        void sign_in_anonymously();
        void sign_in_with_username_password(const String &username, const String &password);
        void sign_up_with_username_password(const String &username, const String &password);
        void add_username_password(const String &username, const String &password);
        void update_password(const String &current_password, const String &new_password);
        void delete_account();

        void sign_out(bool clear_credentials = false);
        void set_profile(const String &profile_name);
        void clear_session_token();
    };
}

#endif