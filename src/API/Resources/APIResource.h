#ifndef APIRESOURCE_H
#define APIRESOURCE_H

#include <godot_cpp/classes/resource.hpp>

namespace godot
{

    class APIResource : public Resource
    {
        GDCLASS(APIResource, Resource)

    private:
        String project_id;

    protected:
        static void _bind_methods();

    public:
        String get_project_id() const;
        void set_project_id(const String p_id);
    };

}

#endif