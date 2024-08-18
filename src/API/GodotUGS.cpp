#include "GodotUGS.h"

#include <godot_cpp/classes/engine.hpp>

using namespace godot;

GodotUGS *GodotUGS::instance = nullptr;

GodotUGS::GodotUGS()
{
    instance = this;
}

GodotUGS::~GodotUGS()
{
    if (instance == this)
        instance = nullptr;
}

GodotUGS *GodotUGS::get_singleton()
{
    return instance;
}

void GodotUGS::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_api_resource"), &GodotUGS::get_api_resource);
    ClassDB::bind_method(D_METHOD("set_api_resource", "p_resource"), &GodotUGS::set_api_resource);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "api_resource", PROPERTY_HINT_RESOURCE_TYPE, "APIResource"), "set_api_resource", "get_api_resource");
}

Ref<APIResource> GodotUGS::get_api_resource() const
{
    return api_resource;
}

void GodotUGS::set_api_resource(const Ref<APIResource> &p_resource)
{
    api_resource = p_resource;
}

String GodotUGS::get_project_id()
{
    ERR_FAIL_NULL_V_MSG(api_resource, "", "API Resource has not been set!");

    String project_id = api_resource->get_project_id();
    ERR_FAIL_COND_V_MSG(project_id.is_empty(), "", "Project ID is empty!");

    return project_id;
}
