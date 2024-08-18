#include "AuthenticationService.h"
#include "UnityServices.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>
#include "GodotUGS.h"

using namespace godot;

AuthenticationService *AuthenticationService::instance = nullptr;

AuthenticationService::AuthenticationService()
{
    instance = this;
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
    ClassDB::bind_method(D_METHOD("test"), &AuthenticationService::test);
}

void AuthenticationService::test()
{
    UtilityFunctions::print(UnityServices::get_singleton()->get_environment());
}