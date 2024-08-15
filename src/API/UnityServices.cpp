#include "UnityServices.h"
#include <cpr/cpr.h>

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void UnityServices::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_project_id"), &UnityServices::get_project_id);
    ClassDB::bind_method(D_METHOD("set_project_id", "p_id"), &UnityServices::set_project_id);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "project_id", PROPERTY_HINT_PASSWORD), "set_project_id", "get_project_id");
}

UnityServices::UnityServices()
{
}

UnityServices::~UnityServices()
{
}

void UnityServices::_ready()
{
    UtilityFunctions::print("UnityServices::_ready() called");

    UtilityFunctions::print("Before making HTTP request...");
    cpr::Response r;
    try
    {
        r = cpr::Get(cpr::Url{"http://www.httpbin.org/get"});
    }
    catch (...)
    {
        UtilityFunctions::print("Exception caught during HTTP request");
        return;
    }
    UtilityFunctions::print("HTTP request completed");

    if (r.error)
    {
        UtilityFunctions::print("HTTP request error: " + String(r.error.message.c_str()));
        return;
    }

    UtilityFunctions::print("Before processing response text...");
    String text = r.text.c_str();
    UtilityFunctions::print("Response text: " + text);
}

String UnityServices::get_project_id() const
{
    return project_id;
}

void UnityServices::set_project_id(const String p_id)
{
    project_id = p_id;
}