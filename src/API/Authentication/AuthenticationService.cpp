#include "AuthenticationService.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/json.hpp>
#include <godot_cpp/classes/reg_ex.hpp>
#include <godot_cpp/classes/http_client.hpp>
#include <godot_cpp/classes/os.hpp>
#include <cpr/cpr.h>

using namespace godot;

AuthenticationService *AuthenticationService::instance = nullptr;

AuthenticationService::AuthenticationService()
{
    instance = this;
    UnityServices::get_singleton()->connect("on_initialized", Callable(this, "_on_initialized"));
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
    ClassDB::bind_method(D_METHOD("update_password", "current_password", "new_password"), &AuthenticationService::update_password);
    ClassDB::bind_method(D_METHOD("delete_account"), &AuthenticationService::delete_account);

    ClassDB::bind_method(D_METHOD("sign_out", "clear_credentials"), &AuthenticationService::sign_out);
    ClassDB::bind_method(D_METHOD("set_profile", "profile_name"), &AuthenticationService::set_profile);
    ClassDB::bind_method(D_METHOD("clear_session_token"), &AuthenticationService::clear_session_token);

    ADD_PROPERTY(PropertyInfo(Variant::STRING, "profile"), "set_profile", "get_profile");

    ADD_SIGNAL(MethodInfo("on_signed_in"));
    ADD_SIGNAL(MethodInfo("on_signed_out"));
}

void AuthenticationService::_on_initialized(bool initialized)
{
    if (!initialized)
        return;

    UtilityFunctions::print("init from auth!");

    project_id = GodotUGS::get_singleton()->get_project_id();
    environment = UnityServices::get_singleton()->get_environment();

    sign_in_response.instantiate();
    config.instantiate();

    load_persistents();
    load_cache();
}

bool AuthenticationService::is_signed_in() const
{
    return signed_in;
}

String AuthenticationService::get_access_token() const
{
    return sign_in_response->id_token;
}

String AuthenticationService::get_player_id() const
{
    return sign_in_response->user->id;
}

String AuthenticationService::get_player_name() const
{
    return sign_in_response->user->username;
}

String AuthenticationService::get_profile() const
{
    return profile;
}

bool AuthenticationService::does_session_token_exist() const
{
    return !sign_in_response->session_token.is_empty();
}

String AuthenticationService::get_last_notification_date() const
{
    return sign_in_response->last_notification_date;
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

    // auto future_text = cpr::PostCallback([](cpr::Response r)
    //                                      {
    //                                         AuthenticationService::get_singleton()->auth_test((String)r.text.c_str());
    //                                         return r.text; },
    //                                      cpr::Url{url.utf8()},
    //                                      cpr::Header{
    //                                          {"ProjectId", (std::string)project_id.utf8()},
    //                                          {"UnityEnvironment", (std::string)environment.utf8()},
    //                                          {"Content-Type", "application/json"}},
    //                                      cpr::Body{json_string.utf8()});

    Ref<HTTPClient> http = memnew(HTTPClient);
    Error err = http->connect_to_host(AUTH_URL);
    if (err != Error::OK)
        ERR_FAIL_MSG("Failed to connect to host: " + String::num(err));

    while (http->get_status() == HTTPClient::Status::STATUS_CONNECTING || http->get_status() == HTTPClient::Status::STATUS_RESOLVING)
    {
        http->poll();
        UtilityFunctions::print("connecting...");
        OS::get_singleton()->delay_usec(1000);
    }

    if (http->get_status() != HTTPClient::Status::STATUS_CONNECTED)
        ERR_FAIL_MSG("Failed to connect to host: " + String::num(http->get_status()));

    PackedStringArray headers = {"ProjectId: " + project_id, "UnityEnvironment: " + environment, "Content-Type: application/json"};
    err = http->request(HTTPClient::Method::METHOD_POST, "/v1/authentication/usernamepassword/sign-in", headers, json_string);
    if (err != Error::OK)
        ERR_FAIL_MSG("Failed to request: " + String::num(err));

    while (http->get_status() == HTTPClient::Status::STATUS_REQUESTING)
    {
        http->poll();
        UtilityFunctions::print("requesting...");
        OS::get_singleton()->delay_usec(1000);
    }

    if (http->get_status() != HTTPClient::STATUS_BODY && http->get_status() != HTTPClient::STATUS_CONNECTED)
        ERR_FAIL_MSG("Failed to get body: " + String::num(http->get_status()));

    String text;
    if (http->has_response())
    {
        PackedByteArray rb = PackedByteArray();

        while (http->get_status() == HTTPClient::STATUS_BODY)
        {
            http->poll();
            PackedByteArray chunk = http->read_response_body_chunk();
            if (chunk.size() == 0)
                OS::get_singleton()->delay_usec(1000);
            else
                rb = rb + chunk;
        }

        text = rb.get_string_from_ascii();
    }

    if (http->get_response_code() == 200)
    {
        sign_in_response->from_dict(JSON::parse_string(text));
        save_cache();
        emit_signal("on_signed_in");
        signed_in = true;
    }
    else
    {
        Ref<CoreExceptionContent> parsed_content = memnew(CoreExceptionContent(text));
        ERR_FAIL_MSG(parsed_content->get_message());
    }
}

void AuthenticationService::sign_up_with_username_password(const String &username, const String &password)
{
}

void AuthenticationService::add_username_password(const String &username, const String &password)
{
}

void AuthenticationService::update_password(const String &current_password, const String &new_password)
{
}

void AuthenticationService::delete_account()
{
}

void AuthenticationService::sign_out(bool clear_credentials)
{
    if (clear_credentials)
    {
        clear_access_token();
        clear_session_token();
    }

    sign_in_response.instantiate();
    emit_signal("on_signed_out");
    signed_in = false;
}

void AuthenticationService::set_profile(const String &profile_name)
{
    // RegEx regex;
    // regex.compile(PROFILE_REGEX);
    // Ref<RegExMatch> result = regex.search(profile_name);
    // result->get_string();

    if (!profile_name.is_empty())
        profile = profile_name;
    else
        profile = "DefaultProfile";

    save_persistents();
    load_cache();
}

void AuthenticationService::clear_session_token()
{
    Error error = config->load(CACHE_PATH);
    if (error != Error::OK)
        return;

    config->erase_section_key(profile, "sessionToken");
    config->save(CACHE_PATH);

    sign_in_response->session_token = "";
}

void AuthenticationService::clear_access_token()
{
    Error error = config->load(CACHE_PATH);
    if (error != Error::OK)
        return;

    config->erase_section_key(profile, "idToken");
    config->save(CACHE_PATH);

    sign_in_response->id_token = "";
    // accessToken = new AccessToken();
}

void AuthenticationService::save_cache()
{
    config->set_value(profile, "idToken", get_access_token());
    config->set_value(profile, "sessionToken", sign_in_response->session_token);

    Error err = config->save(CACHE_PATH);
    if (err != Error::OK)
        ERR_FAIL_MSG("Failed to save cache: " + String::num(err));
}

void AuthenticationService::save_persistents()
{
    config->set_value(PERSISTENTS, "lastUsedProfile", profile);

    Error err = config->save(CACHE_PATH);
    if (err != Error::OK)
        ERR_FAIL_MSG("Failed to save persistents: " + String::num(err));
}

void AuthenticationService::load_cache()
{
    Error err = config->load(CACHE_PATH);
    if (err != Error::OK)
        return;

    sign_in_response.instantiate();
    if (config->has_section(profile))
    {
        sign_in_response->id_token = (String)config->get_value(profile, "idToken");
        sign_in_response->session_token = (String)config->get_value(profile, "sessionToken");
    }
}

void AuthenticationService::load_persistents()
{
    Error err = config->load(CACHE_PATH);
    if (err != Error::OK)
        return;

    if (config->has_section(PERSISTENTS))
        profile = (String)config->get_value(PERSISTENTS, "lastUsedProfile");
}
