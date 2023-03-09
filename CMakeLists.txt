# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("PhysxEngine")

set(EXECUTABLE_CUSTOM_NAME "Engine")
add_subdirectory ("Engine")

