#include "HttpExample.h"
#include <cpr/cpr.h>

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void HttpExample::_bind_methods()
{
}

HttpExample::HttpExample()
{
}

HttpExample::~HttpExample()
{
}

void HttpExample::_ready()
{
    UtilityFunctions::print("HttpExample::_ready() called");

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
    String text = "Yo";
    text = r.text.c_str();
    UtilityFunctions::print("Response text: " + text);

    UtilityFunctions::print(text);
}