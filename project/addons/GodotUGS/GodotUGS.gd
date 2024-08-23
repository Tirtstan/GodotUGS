@tool
extends EditorPlugin

const AUTOLOAD_NAME = "GUGS"

func _enter_tree() -> void:
	add_autoload_singleton(AUTOLOAD_NAME, "res://addons/GodotUGS/Autoloads/GodotUGS.tscn")

func _enable_plugin() -> void:
	print_rich("[b]Please set the API Resource & Project ID fields in [code]res://addons/GodotUGS/Autoloads/GodotUGS.tscn[/code]![/b]")

func _exit_tree() -> void:
	remove_autoload_singleton(AUTOLOAD_NAME)
