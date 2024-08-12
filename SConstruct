#!/usr/bin/env python
from glob import glob
from pathlib import Path

# TODO: Do not copy environment after godot-cpp/test is updated <https://github.com/godotengine/godot-cpp/blob/master/test/SConstruct>.
env = SConscript("godot-cpp/SConstruct")

# Initialize the CPPPATH with the src directory and all its subdirectories
cpppath = ["src/"] + glob("src/**/", recursive=True)

# Add include paths for the third-party library (e.g., cpr)
cpppath.append("dependencies/include/")

# Append the collected paths to the CPPPATH
env.Append(CPPPATH=cpppath)

# Use glob to find all .cpp files in src directory and its subdirectories
sources = glob("src/**/*.cpp", recursive=True)

# Find gdextension path even if the directory or extension is renamed (e.g. project/addons/example/example.gdextension).
(extension_path,) = glob("project/addons/*/*.gdextension")

# Find the addon path (e.g. project/addons/example).
addon_path = Path(extension_path).parent

# Find the project name from the gdextension file (e.g. example).
project_name = Path(extension_path).stem

# Add library paths for the third-party library (e.g., cpr)
env.Append(LIBPATH=["dependencies/lib/"])

# Link the third-party library (e.g., cpr)
env.Append(LIBS=["cpr", "libcurl", "zlib"])

# Ensure the runtime library setting matches
env.Append(CCFLAGS=['/MT'])  # Use /MD for dynamic runtime or /MT for static runtime

# TODO: Cache is disabled currently.
# scons_cache_path = os.environ.get("SCONS_CACHE")
# if scons_cache_path != None:
#     CacheDir(scons_cache_path)
#     print("Scons cache enabled... (path: '" + scons_cache_path + "')")

# Create the library target (e.g. libexample.linux.debug.x86_64.so).
debug_or_release = "release" if env["target"] == "template_release" else "debug"
if env["platform"] == "macos":
    library = env.SharedLibrary(
        "{0}/bin/lib{1}.{2}.{3}.framework/{1}.{2}.{3}".format(
            addon_path,
            project_name,
            env["platform"],
            debug_or_release,
        ),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "{}/bin/lib{}.{}.{}.{}{}".format(
            addon_path,
            project_name,
            env["platform"],
            debug_or_release,
            env["arch"],
            env["SHLIBSUFFIX"],
        ),
        source=sources,
    )

Default(library)
