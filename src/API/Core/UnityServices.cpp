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
}

UnityServices::UnityServices()
{
    // cpr::Response r = cpr::Get(cpr::Url{"http://www.httpbin.org/get"});

    // if (r.error)
    // {
    //     UtilityFunctions::print("HTTP request error: " + String(r.error.message.c_str()));
    //     return;
    // }

    // String text = r.text.c_str();
    // UtilityFunctions::print("Response text: " + text);
}

UnityServices::~UnityServices()
{
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
