# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

project ("newEngine")

# CMakeList.txt : CMake project for Formative10, include source and define
# project specific logic here.
cmake_minimum_required (VERSION 3.8)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)



set_property(GLOBAL PROPERTY USE_FOLDERS On)

# Get SFML and box2d libraries
find_package(OpenGL REQUIRED)
find_package(SFML COMPONENTS system window graphics main CONFIG REQUIRED)
find_package(box2d CONFIG REQUIRED)
find_package(OpenMP REQUIRED)
find_package(benchmark CONFIG REQUIRED)


# Add source to this project's executable.  
file(GLOB_RECURSE PROJECT_SRC Engine/src/*.cpp Engine/include/*.h)

# Add data files
file(GLOB_RECURSE DATA_FILES data/*)
source_group("data/" FILES ${DATA_FILES})
foreach(DATA ${DATA_FILES})
    get_filename_component(FILE_NAME ${DATA} NAME)
    get_filename_component(PATH_NAME ${DATA} DIRECTORY)
    get_filename_component(EXTENSION ${DATA} EXT)
    file(RELATIVE_PATH PATH_NAME "${PROJECT_SOURCE_DIR}" ${PATH_NAME})
    set(DATA_OUTPUT "${PROJECT_BINARY_DIR}/${PATH_NAME}/${FILE_NAME}")
    add_custom_command(
            OUTPUT ${DATA_OUTPUT}
            DEPENDS ${DATA}
            DEPENDS
            COMMAND ${CMAKE_COMMAND} -E copy ${DATA} "${PROJECT_BINARY_DIR}/${PATH_NAME}/${FILE_NAME}"
    )
    list(APPEND DATA_BINARY_FILES ${DATA_OUTPUT})
endforeach()

add_executable(main Engine/main/main.cpp ${PROJECT_SRC})

# Link libraries
target_link_libraries(main PRIVATE sfml-main sfml-graphics sfml-audio sfml-window sfml-system)
target_link_libraries(main PRIVATE benchmark::benchmark benchmark::benchmark_main)
target_link_libraries(main PUBLIC OpenMP::OpenMP_CXX)

if(ENABLE_PROFILER)
target_compile_definitions(main PUBLIC TRACY_ENABLE)
target_link_libraries(main PUBLIC TracyClient)
endif()
if(MSVC)
target_link_libraries(main PRIVATE sfml-main FLAC OpenAL OpenGL Vorbis)
else()
target_link_libraries(main PRIVATE X11 FLAC UDev OpenAL  ${OPENGL_LIBRARIES} )
endif()

target_link_libraries(main PRIVATE box2d::box2d)
target_include_directories(main PRIVATE "Engine/include")

file(GLOB BENCH_FILE Benchmarks/*.cpp)
foreach(BENCH_FILE ${BENCH_FILE})
    # TODO: use the line with "win32" in it if you don't want the console
    get_filename_component(BENCH_NAME ${BENCH_FILE} NAME_WE)
    add_executable(${BENCH_NAME} ${BENCH_FILE} ${PROJECT_SRC})
    # add_executable(${EXECUTABLE_CUSTOM_NAME} win32 ${PROJECT_SRC})

    # Link libraries
    target_link_libraries(${BENCH_NAME} PRIVATE sfml-main sfml-graphics sfml-audio sfml-window sfml-system)
    target_link_libraries(${BENCH_NAME} PRIVATE benchmark::benchmark benchmark::benchmark_main)
    target_link_libraries(${BENCH_NAME} PUBLIC OpenMP::OpenMP_CXX)

    if(ENABLE_PROFILER)
        target_compile_definitions(${BENCH_NAME} PUBLIC TRACY_ENABLE)
        target_link_libraries(${BENCH_NAME} PUBLIC TracyClient)
    endif()
    if(MSVC)
        target_link_libraries(${BENCH_NAME} PRIVATE sfml-main FLAC OpenAL OpenGL Vorbis)
    else()
        target_link_libraries(${BENCH_NAME} PRIVATE X11 FLAC UDev OpenAL  ${OPENGL_LIBRARIES} )
    endif()

    target_link_libraries(${BENCH_NAME} PRIVATE box2d::box2d)
    target_include_directories(${BENCH_NAME} PRIVATE "Engine/include")
endforeach()

option(ENABLE_PROFILER "Enable Tracy Profiling" OFF)
if(ENABLE_PROFILER)
add_subdirectory(engine/externals/tracy)
endif()
