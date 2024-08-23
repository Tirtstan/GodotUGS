#include "User.h"

using namespace godot;

User::User()
{
    disabled = false;
    id = "";
    username = "";
    external_ids = Vector<Ref<ExternalIdentity>>();
}

void User::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("to_dict"), &User::to_dict);
    ClassDB::bind_method(D_METHOD("from_dict", "dict"), &User::from_dict);
}

Dictionary User::to_dict() const
{
    Dictionary dict;
    dict["disabled"] = disabled;
    dict["id"] = id;
    dict["username"] = username;

    Array external_ids_array;
    for (int i = 0; i < external_ids.size(); ++i)
        external_ids_array.append(external_ids[i]->to_dict());

    dict["externalIds"] = external_ids_array;
    return dict;
}

void User::from_dict(const Dictionary &dict)
{
    disabled = dict.get("disabled", false);
    id = dict.get("id", "");
    username = dict.get("username", "");

    external_ids.clear();
    Array external_ids_array = dict.get("externalIds", Array());
    for (int i = 0; i < external_ids_array.size(); ++i)
    {
        Ref<ExternalIdentity> external_id = Ref<ExternalIdentity>(memnew(ExternalIdentity));
        external_id->from_dict(external_ids_array[i]);
        external_ids.append(external_id);
    }
}