@echo off
echo Running doc tool...
cd /d %~dp0
godot --doctool ../ --gdextension-docs --verbose
pause