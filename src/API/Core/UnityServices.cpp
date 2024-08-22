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

    cpr::GetCallback([](const cpr::Response &response)
                     {
                        bool success = response.status_code == 200;

                        instance->emit_signal("on_initialized", success);
                        if (!success)
                        {
                            Ref<CoreExceptionContent> parsed_content = memnew(CoreExceptionContent(response.text.c_str()));
                            ERR_FAIL_MSG(parsed_content->get_message());
                        } },
                     cpr::Url{UnityServicesUrl.utf8()});
}

String UnityServices::get_environment() const
{
    return environment;
}

void UnityServices::set_environment(const String &environment)
{
    this->environment = environment;
}
