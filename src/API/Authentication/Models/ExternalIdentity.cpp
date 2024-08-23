#include "ExternalIdentity.h"

using namespace godot;

ExternalIdentity::ExternalIdentity()
{
    external_id = "";
    provider_id = "";
}

void ExternalIdentity::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("to_dict"), &ExternalIdentity::to_dict);
    ClassDB::bind_method(D_METHOD("from_dict", "dict"), &ExternalIdentity::from_dict);
}

Dictionary ExternalIdentity::to_dict() const
{
    Dictionary dict;
    dict["externalId"] = external_id;
    dict["providerId"] = provider_id;
    return dict;
}

void ExternalIdentity::from_dict(const Dictionary &dict)
{
    external_id = dict.get("externalId", "");
    provider_id = dict.get("providerId", "");
}