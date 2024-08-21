#include "UnityServices.h"
#include <cpr/cpr.h>

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

UnityServices *UnityServices::instance = nullptr;

UnityServices::UnityServices()
{
    instance = this;
}

UnityServices::~UnityServices()
{
    if (instance == this)
        instance = nullptr;
}

UnityServices *UnityServices::get_singleton()
{
    return instance;
}

void UnityServices::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("initialize"), &UnityServices::initialize);
    ClassDB::bind_method(D_METHOD("get_environment"), &UnityServices::get_environment);
    ClassDB::bind_method(D_METHOD("set_environment", "environment"), &UnityServices::set_environment);

    ADD_PROPERTY(PropertyInfo(Variant::STRING, "environment"), "set_environment", "get_environment");

    ADD_SIGNAL(MethodInfo("on_initialized", PropertyInfo(Variant::BOOL, "initialized")));
}

void UnityServices::initialize()
{
    if (environment.is_empty())
        environment = "production";

    cpr::Response response = cpr::Get(cpr::Url{UnityServicesUrl.utf8()});

    emit_signal("on_initialized", response.status_code == 200);
    if (response.status_code != 200)
    {
        Dictionary parsed_dict = JSON::parse_string(response.text.c_str());
        Ref<CoreExceptionContent> parsed_content = memnew(CoreExceptionContent);
        parsed_content->from_dict(parsed_dict);

        String msg = parsed_content->detail.is_empty() ? parsed_content->detail2 : parsed_content->detail;
        ERR_FAIL_MSG(msg);
    }
}

String UnityServices::get_environment() const
{
    return environment;
}

void UnityServices::set_environment(const String &environment)
{
    this->environment = environment;
}
