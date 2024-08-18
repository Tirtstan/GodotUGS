#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <godot_cpp/templates/hash_map.hpp>

namespace godot
{
    static class Constants
    {

    public:
        static Pair<String, String> CONTENT_JSON;
    };
}

using namespace godot;

Pair<String, String> Constants::CONTENT_JSON = Pair<String, String>("Content-Type", "application/json");

#endif