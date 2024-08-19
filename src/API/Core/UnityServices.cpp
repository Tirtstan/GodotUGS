#include "UnityServices.h"
#include <cpr/cpr.h>

#include <godot_cpp/variant/utility_functions.hpp>
#include "GodotUGS.h"

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

    ADD_SIGNAL(MethodInfo("on_initialized"), PropertyInfo(Variant::BOOL, "initialized"));
}

void UnityServices::initialize()
{
    if (environment.is_empty())
        environment = "production";

    cpr::Response response = cpr::Get(cpr::Url{UnityServicesUrl.utf8()});

    emit_signal("on_initialized", response.error.code == cpr::ErrorCode::OK);
    if (response.error.code != cpr::ErrorCode::OK)
    {
        String msg = "Failed to initialize Unity Services\n" + (String)response.error.message.c_str();
        ERR_FAIL_MSG(msg);
    }
}

String UnityServices::get_environment() const
{
    return environment;
}

void UnityServices::set_environment(const String environment)
{
    this->environment = environment;
}
