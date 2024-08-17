#include "APIResource.h"

using namespace godot;

void APIResource::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_project_id"), &APIResource::get_project_id);
    ClassDB::bind_method(D_METHOD("set_project_id", "p_id"), &APIResource::set_project_id);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "project_id", PROPERTY_HINT_PASSWORD), "set_project_id", "get_project_id");
}

String APIResource::get_project_id() const
{
    return project_id;
}

void APIResource::set_project_id(const String p_id)
{
    project_id = p_id;
}