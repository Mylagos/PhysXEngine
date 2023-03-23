# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("newEngine")

set(EXECUTABLE_CUSTOM_NAME "Engine")
add_subdirectory ("Engine")

option(ENABLE_PROFILER "Enable Tracy Profiling" OFF)
if(ENABLE_PROFILER)
add_subdirectory(engine/externals/tracy)
endif()