#include "AuthenticationService.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/json.hpp>
#include <cpr/cpr.h>

using namespace godot;

AuthenticationService *AuthenticationService::instance = nullptr;

AuthenticationService::AuthenticationService()
{
    instance = this;
    UnityServices::get_singleton()->connect("on_initialized", Callable(this, "on_initialized"));
}

AuthenticationService::~AuthenticationService()
{
    if (instance == this)
        instance = nullptr;
}

AuthenticationService *AuthenticationService::get_singleton()
{
    return instance;
}

void AuthenticationService::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("_on_initialized", "initialized"), &AuthenticationService::_on_initialized);

    ClassDB::bind_method(D_METHOD("is_signed_in"), &AuthenticationService::is_signed_in);
    ClassDB::bind_method(D_METHOD("get_access_token"), &AuthenticationService::get_access_token);
    ClassDB::bind_method(D_METHOD("get_player_id"), &AuthenticationService::get_player_id);
    ClassDB::bind_method(D_METHOD("get_player_name"), &AuthenticationService::get_player_name);
    ClassDB::bind_method(D_METHOD("get_profile"), &AuthenticationService::get_profile);
    ClassDB::bind_method(D_METHOD("does_session_token_exist"), &AuthenticationService::does_session_token_exist);
    ClassDB::bind_method(D_METHOD("get_last_notification_date"), &AuthenticationService::get_last_notification_date);

    ClassDB::bind_method(D_METHOD("sign_in_anonymously"), &AuthenticationService::sign_in_anonymously);
    ClassDB::bind_method(D_METHOD("sign_in_with_username_password", "username", "password"), &AuthenticationService::sign_in_with_username_password);
    ClassDB::bind_method(D_METHOD("sign_up_with_username_password", "username", "password"), &AuthenticationService::sign_up_with_username_password);
    ClassDB::bind_method(D_METHOD("add_username_password", "username", "password"), &AuthenticationService::add_username_password);
    ClassDB::bind_method(D_METHOD("delete_account"), &AuthenticationService::delete_account);

    ClassDB::bind_method(D_METHOD("sign_out", "clear_credentials"), &AuthenticationService::sign_out);
    ClassDB::bind_method(D_METHOD("switch_profile", "profile_name"), &AuthenticationService::switch_profile);
    ClassDB::bind_method(D_METHOD("clear_session_token"), &AuthenticationService::clear_session_token);

    ADD_SIGNAL(MethodInfo("on_signed_in"));
    ADD_SIGNAL(MethodInfo("on_signed_out"));
}

void AuthenticationService::_on_initialized(bool initialized)
{
    if (!initialized)
        return;

    project_id = GodotUGS::get_singleton()->get_project_id();
    environment = UnityServices::get_singleton()->get_environment();

    sign_in_response.instantiate();
}

bool AuthenticationService::is_signed_in() const
{
    return signed_in;
}

String AuthenticationService::get_access_token() const
{
    return access_token;
}

String AuthenticationService::get_player_id() const
{
    return player_id;
}

String AuthenticationService::get_player_name() const
{
    return player_name;
}

String AuthenticationService::get_profile() const
{
    return profile;
}

bool AuthenticationService::does_session_token_exist() const
{
    return !session_token.is_empty();
}

String AuthenticationService::get_last_notification_date() const
{
    return last_notification_date;
}

void AuthenticationService::sign_in_anonymously()
{
    // String url = AUTH_URL.utf8() + "/authentication/anonymous";
    // cpr::Response response = cpr::Post(cpr::Url{url.utf8()}, cpr::Header{{"ProjectId", project_id.utf8()}, {"Content-Type", "application/json"}});

    // UtilityFunctions::print("Response: " + (String)response.text.c_str());
    // if (response.error.code == cpr::ErrorCode::OK)
    // {
    //     emit_signal("on_signed_in");
    //     signed_in = true;
    // }
    // else
    // {
    //     UtilityFunctions::print("Failed to sign in anonymously: " + (String)response.error.message.c_str());
    // }
}

void AuthenticationService::sign_in_with_session_token(const String &session_token)
{
    emit_signal("on_signed_in");
    signed_in = true;
}

void AuthenticationService::sign_in_with_username_password(const String &username, const String &password)
{
    String url = AUTH_URL.utf8() + "/authentication/usernamepassword/sign-in";
    Dictionary dict;
    dict["username"] = username;
    dict["password"] = password;
    String json_string = JSON::stringify(dict);

    cpr::Response response = cpr::Post(cpr::Url{url.utf8()},
                                       cpr::Header{
                                           {"ProjectId", (std::string)project_id.utf8()},
                                           {"UnityEnvironment", (std::string)environment.utf8()},
                                           {"Content-Type", "application/json"}},
                                       cpr::Body{json_string.utf8()});

    if (response.status_code == 200)
    {
        emit_signal("on_signed_in");
        signed_in = true;
        sign_in_response->from_dict(JSON::parse_string(response.text.c_str()));
    }
    else
    {
        Ref<CoreExceptionContent> parsed_content = memnew(CoreExceptionContent(response.text.c_str()));
        ERR_FAIL_MSG(parsed_content->get_message());
    }
}

void AuthenticationService::sign_up_with_username_password(const String &username, const String &password)
{
}

void AuthenticationService::add_username_password(const String &username, const String &password)
{
}

void AuthenticationService::delete_account()
{
}

void AuthenticationService::sign_out(bool clear_credentials)
{
    emit_signal("on_signed_out");
    signed_in = false;
}

void AuthenticationService::switch_profile(const String &profile_name)
{
}

void AuthenticationService::clear_session_token()
{
}
