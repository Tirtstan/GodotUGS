#ifndef GODOTUGS_H
#define GODOTUGS_H

#include <godot_cpp/classes/node.hpp>
#include "APIResource.h"

namespace godot
{
    class GodotUGS : public Node
    {
        GDCLASS(GodotUGS, Node)

    private:
        static GodotUGS *instance;

        Ref<APIResource> api_resource;

    protected:
        static void _bind_methods();

    public:
        GodotUGS();
        ~GodotUGS();
        static GodotUGS *get_singleton();

        Ref<APIResource> get_api_resource() const;
        void set_api_resource(const Ref<APIResource> &p_resource);

        String get_project_id();
    };
}

#endif