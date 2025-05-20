cmake_minimum_required(VERSION 3.27)
project(vulkan-smoketest)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
set (GLMINC_PREFIX ${PROJECT_SOURCE_DIR}/libs)

macro(generate_dispatch_table out)
    add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${out}
        COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/generate-dispatch-table ${CMAKE_CURRENT_SOURCE_DIR}/${out}
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/generate-dispatch-table
    )
endmacro()

macro(glsl_to_spirv src)
    add_custom_command(OUTPUT ${src}.h
        COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/glsl-to-spirv ${CMAKE_CURRENT_SOURCE_DIR}/${src} ${src}.h
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/glsl-to-spirv ${CMAKE_CURRENT_SOURCE_DIR}/${src}
    )
endmacro()

generate_dispatch_table(HelpersDispatchTable.h)
generate_dispatch_table(HelpersDispatchTable.cpp)
glsl_to_spirv(Smoke.frag)
glsl_to_spirv(Smoke.vert)
glsl_to_spirv(Smoke.push_constant.vert)

set(smoketest_sources
    Game.cpp
    Game.h
    Helpers.h
    HelpersDispatchTable.cpp
    HelpersDispatchTable.h
    Smoke.cpp
    Smoke.h
    Smoke.frag.h
    Smoke.vert.h
    Smoke.push_constant.vert.h
    Main.cpp
    Meshes.cpp
    Meshes.h
    Meshes.teapot.h
    Simulation.cpp
    Simulation.h
    Shell.cpp
    Shell.h
)

set(definitions
    PRIVATE -DVK_NO_PROTOTYPES
    PRIVATE -DGLM_FORCE_RADIANS)

set(includes
    PRIVATE ${GLMINC_PREFIX}
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

set(libraries PRIVATE ${CMAKE_THREAD_LIBS_INIT})

if(TARGET vulkan)
    list(APPEND definitions PRIVATE -DUNINSTALLED_LOADER="$<TARGET_FILE:vulkan>")
endif()

if(WIN32)
    list(APPEND definitions PRIVATE -DVK_USE_PLATFORM_WIN32_KHR)
    list(APPEND definitions PRIVATE -DWIN32_LEAN_AND_MEAN)
    list(APPEND smoketest_sources ShellWin32.cpp ShellWin32.h)
else()
    list(APPEND libraries PRIVATE dl rt pthread)
    if(BUILD_SELECTION STREQUAL "WAYLAND")
        find_package(Wayland REQUIRED)
        message(STATUS "Wayland includes: ${WAYLAND_CLIENT_INCLUDE_DIR}")
        message(STATUS "Wayland libraries: ${WAYLAND_CLIENT_LIBRARIES}")
        set(TYPE -wayland)
        list(APPEND smoketest_sources ShellWayland.cpp ShellWayland.h)
        list(APPEND definitions PRIVATE -DVK_USE_PLATFORM_WAYLAND_KHR)
        list(APPEND includes PRIVATE ${WAYLAND_CLIENT_INCLUDE_DIR})
        list(APPEND libraries PRIVATE ${WAYLAND_CLIENT_LIBRARIES})
    elseif(BUILD_SELECTION STREQUAL "XCB" OR CMAKE_SYSTEM_NAME STREQUAL "Linux")
        find_package(XCB REQUIRED)
        message(STATUS "XCB includes: ${XCB_INCLUDE_DIRS}")
        message(STATUS "XCB libraries: ${XCB_LIBRARIES}")
        list(APPEND smoketest_sources ShellXcb.cpp ShellXcb.h)
        list(APPEND definitions PRIVATE -DVK_USE_PLATFORM_XCB_KHR)
        list(APPEND includes PRIVATE ${XCB_INCLUDES})
        list(APPEND libraries PRIVATE ${XCB_LIBRARIES})
    endif()
endif()

add_executable(vulkan-smoketest${TYPE} ${smoketest_sources})
target_compile_definitions(vulkan-smoketest${TYPE} ${definitions})
target_include_directories(vulkan-smoketest${TYPE} ${includes})
target_link_libraries(vulkan-smoketest${TYPE} ${libraries})
