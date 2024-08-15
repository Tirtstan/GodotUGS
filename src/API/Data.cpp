#include "Data.h"

using namespace godot;

void Data::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_id"), &Data::get_id);
    ClassDB::bind_method(D_METHOD("set_id", "p_id"), &Data::set_id);

    ClassDB::bind_method(D_METHOD("get_name"), &Data::get_name);
    ClassDB::bind_method(D_METHOD("set_name", "p_name"), &Data::set_name);

    ClassDB::bind_method(D_METHOD("get_surname"), &Data::get_surname);
    ClassDB::bind_method(D_METHOD("set_surname", "p_surname"), &Data::set_surname);

    ClassDB::bind_method(D_METHOD("get_age"), &Data::get_age);
    ClassDB::bind_method(D_METHOD("set_age", "p_age"), &Data::set_age);

    ClassDB::bind_method(D_METHOD("get_full_name"), &Data::get_full_name);
}

Data::Data()
{
    id = -1;
    name = "";
    surname = "";
    age = 0;
}

Data::~Data()
{
}

void Data::set_id(const int p_id)
{
    id = p_id;
}

int Data::get_id() const
{
    return id;
}

void Data::set_name(const String p_name)
{
    name = p_name;
}

String Data::get_name() const
{
    return name;
}

void Data::set_surname(const String p_surname)
{
    surname = p_surname;
}

String Data::get_surname() const
{
    return surname;
}

void Data::set_age(const int p_age)
{
    age = p_age;
}

int Data::get_age() const
{
    return age;
}

String Data::get_full_name() const
{
    return vformat("%s %s", name, surname);
}
