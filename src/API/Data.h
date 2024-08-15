#ifndef DATA_H
#define DATA_H

#include <godot_cpp/classes/ref_counted.hpp>

namespace godot
{

    struct Data : public RefCounted
    {
        GDCLASS(Data, RefCounted)

    private:
        int id;
        String name;
        String surname;
        int age;

    protected:
        static void _bind_methods();

    public:
        Data();
        ~Data();

        void set_id(const int p_id);
        int get_id() const;

        void set_name(const String p_name);
        String get_name() const;

        void set_surname(const String p_surname);
        String get_surname() const;

        void set_age(const int p_age);
        int get_age() const;

        String get_full_name() const;
    };
}

#endif