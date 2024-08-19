#include "AuthenticationService.h"
#include "UnityServices.h"

#include <godot_cpp/variant/utility_functions.hpp>

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
    ClassDB::bind_method(D_METHOD("on_initialized", "initialized"), &AuthenticationService::on_initialized);

    ClassDB::bind_method(D_METHOD("is_signed_in"), &AuthenticationService::is_signed_in);
    ClassDB::bind_method(D_METHOD("get_access_token"), &AuthenticationService::get_access_token);
    ClassDB::bind_method(D_METHOD("get_player_id"), &AuthenticationService::get_player_id);
    ClassDB::bind_method(D_METHOD("get_player_name"), &AuthenticationService::get_player_name);
    ClassDB::bind_method(D_METHOD("get_profile"), &AuthenticationService::get_profile);
    ClassDB::bind_method(D_METHOD("does_session_token_exists"), &AuthenticationService::does_session_token_exists);

    ClassDB::bind_method(D_METHOD("sign_in_anonymously"), &AuthenticationService::sign_in_anonymously);
    ClassDB::bind_method(D_METHOD("delete_account"), &AuthenticationService::delete_account);

    ClassDB::bind_method(D_METHOD("sign_out", "clear_credentials"), &AuthenticationService::sign_out);
    ClassDB::bind_method(D_METHOD("switch_profile", "profile_name"), &AuthenticationService::switch_profile);
    ClassDB::bind_method(D_METHOD("clear_session_token"), &AuthenticationService::clear_session_token);

    ADD_SIGNAL(MethodInfo("on_signed_in"));
    ADD_SIGNAL(MethodInfo("on_signed_out"));
}

void AuthenticationService::on_initialized(bool initialized)
{
    UtilityFunctions::print("Unity Services initialized from auth!");
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

bool AuthenticationService::does_session_token_exists() const
{
    return session_token_exists;
}

void AuthenticationService::sign_in_anonymously()
{
    emit_signal("on_signed_in");
    signed_in = true;
}

void AuthenticationService::sign_in_with_session_token(const String &session_token)
{
    emit_signal("on_signed_in");
    signed_in = true;
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
