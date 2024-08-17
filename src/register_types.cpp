#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/godot.hpp>

#include "APIResource.h"
#include "GodotUGS.h"
#include "UnityServices.h"
#include "AuthenticationService.h"

using namespace godot;

void GodotUGS_initialize(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
		return;

	GDREGISTER_CLASS(APIResource);
	GDREGISTER_CLASS(GodotUGS);
	GDREGISTER_RUNTIME_CLASS(UnityServices);
	GDREGISTER_RUNTIME_CLASS(AuthenticationService);

	Engine::get_singleton()->register_singleton("UnityServices", memnew(UnityServices));
	Engine::get_singleton()->register_singleton("AuthenticationService", memnew(AuthenticationService));
}

void GodotUGS_terminate(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
		return;

	Engine::get_singleton()->unregister_singleton("UnityServices");
	Engine::get_singleton()->unregister_singleton("AuthenticationService");
}

extern "C"
{
	GDExtensionBool GDE_EXPORT GodotUGS_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
	{
		godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

		init_obj.register_initializer(GodotUGS_initialize);
		init_obj.register_terminator(GodotUGS_terminate);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}
