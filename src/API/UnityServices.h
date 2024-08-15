#ifndef UNITYSERVICES_H
#define UNITYSERVICES_H

#include <godot_cpp/classes/node.hpp>

namespace godot
{

    class UnityServices : public Node
    {
        GDCLASS(UnityServices, Node)

    private:
        String project_id;

    protected:
        static void _bind_methods();

    public:
        UnityServices();
        ~UnityServices();

        String get_project_id() const;
        void set_project_id(const String p_id);

        void _ready() override;
    };

}

#endif