#include "UnityServices.h"
#include <cpr/cpr.h>

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/classes/node.hpp>

using namespace godot;

void UnityServices::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("initialize"), &UnityServices::initialize);
    ClassDB::bind_method(D_METHOD("get_environment"), &UnityServices::get_environment);
    ClassDB::bind_method(D_METHOD("set_environment", "environment"), &UnityServices::set_environment);

    ADD_SIGNAL(MethodInfo("on_initialized"), PropertyInfo(Variant::BOOL, "initialized"));
}

UnityServices::UnityServices()
{
}

UnityServices::~UnityServices()
{
}

void UnityServices::initialize()
{
    if (environment.is_empty())
        environment = "production";

    String project_id = get_project_id();
    cpr::Response response = cpr::Get(cpr::Url{UnityServicesUrl.utf8()});

    emit_signal("on_initialized", response.error.code == cpr::ErrorCode::OK);
    if (response.error.code == cpr::ErrorCode::OK)
    {
        String text = response.text.c_str();
        UtilityFunctions::print("Response Text: " + text);
    }
    else
    {
        ERR_FAIL_MSG(response.error.message.c_str());
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

String UnityServices::get_project_id() // TODO: make this better, just not sure how to communicate effectively with a Godot autoload (not singleton)
{
    SceneTree *tree = (SceneTree *)Engine::get_singleton()->get_main_loop();
    Node *godotUgs = tree->get_root()->find_child("GUGS", true, false);

    String project_id = "";
    if (godotUgs)
    {
        project_id = String(godotUgs->call("get_project_id"));
    }
    else
    {
        UtilityFunctions::print("Autoload node not found!");
    }

    return project_id;
}
