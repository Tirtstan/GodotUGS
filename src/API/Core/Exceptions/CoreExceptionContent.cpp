#include "CoreExceptionContent.h"

using namespace godot;

CoreExceptionContent::CoreExceptionContent()
{
    title = "";
    status = 0;
    detail = "";
    detail2 = "";
}

CoreExceptionContent::CoreExceptionContent(const String &text)
{
    this->from_dict(JSON::parse_string(text));
}

String CoreExceptionContent::get_message() const
{
    return detail.is_empty() ? detail2 : detail;
}

void CoreExceptionContent::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("to_dict"), &CoreExceptionContent::to_dict);
    ClassDB::bind_method(D_METHOD("from_dict", "dict"), &CoreExceptionContent::from_dict);
}

Dictionary CoreExceptionContent::to_dict() const
{
    Dictionary dict;
    dict["title"] = title;
    dict["status"] = status;
    dict["detail"] = detail;
    dict["Detail"] = detail2;
    return dict;
}

void CoreExceptionContent::from_dict(const Dictionary &dict)
{
    title = dict.get("title", "");
    status = dict.get("status", 0);
    detail = dict.get("detail", "");
    detail2 = dict.get("Detail", "");
}