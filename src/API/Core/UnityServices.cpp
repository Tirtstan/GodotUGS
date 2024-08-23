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
    ADD_SIGNAL(MethodInfo("on_error", PropertyInfo(Variant::INT, "error"), PropertyInfo(Variant::STRING, "error_message")));
}

void UnityServices::initialize()
{
    if (environment.is_empty())
        environment = "production";

    String project_id = GodotUGS::get_singleton()->get_project_id();
    default_headers = cpr::Header{{"ProjectId", (std::string)project_id.utf8()},
                                  {"UnityEnvironment", (std::string)environment.utf8()},
                                  {"Content-Type", "application/json"}};

    cpr::GetCallback([this](const cpr::Response &response)
                     {
                        bool success = response.status_code == 200;

                        this->emit_signal("on_initialized", success);
                        if (!success)
                        {
                            Ref<CoreExceptionContent> parsed_content = memnew(CoreExceptionContent(response.text.c_str()));
                            emit_signal("on_error", Error::FAILED, parsed_content->get_message());
                        } },
                     cpr::Url{UnityServicesUrl.utf8()});
}

cpr::Header UnityServices::get_default_headers() const
{
    return default_headers;
}

String UnityServices::get_environment() const
{
    return environment;
}

void UnityServices::set_environment(const String &environment)
{
    this->environment = environment;
}
