#ifndef GODOTUGS_H
#define GODOTUGS_H

#include <godot_cpp/classes/node.hpp>

namespace godot
{

    class HttpExample : public Node
    {
        GDCLASS(HttpExample, Node)

    protected:
        static void _bind_methods();

    public:
        HttpExample();
        ~HttpExample();

        void _ready() override;
        void _on_request_completed(int result, int response_code, PackedStringArray headers, PackedByteArray body);
    };

}

#endif