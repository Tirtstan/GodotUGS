#include "SignInResponse.h"

using namespace godot;

SignInResponse::SignInResponse()
{
    expires_in = 0;
    id_token = "";
    session_token = "";
    last_notification_date = "";
    user = Ref<User>();
}

void SignInResponse::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("to_dict"), &SignInResponse::to_dict);
    ClassDB::bind_method(D_METHOD("from_dict", "dict"), &SignInResponse::from_dict);
}

Dictionary SignInResponse::to_dict() const
{
    Dictionary dict;
    dict["expiresIn"] = expires_in;
    dict["idToken"] = id_token;
    dict["sessionToken"] = session_token;
    dict["lastNotificationDate"] = last_notification_date;
    dict["user"] = user->to_dict();
    dict["userId"] = user_id;
    return dict;
}

void SignInResponse::from_dict(const Dictionary &dict)
{
    expires_in = dict.get("expiresIn", 0);
    id_token = dict.get("idToken", "");
    session_token = dict.get("sessionToken", "");
    last_notification_date = dict.get("lastNotificationDate", "");
    user.instantiate();
    user->from_dict(dict.get("user", Dictionary()));
    user_id = dict.get("userId", "");
}
