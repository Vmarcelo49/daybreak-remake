cmake_minimum_required(VERSION 3.16)
project(daybreak_hook C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Use same toolchain as main MVP
if(DEFINED CMAKE_TOOLCHAIN_FILE)
    message(STATUS "Using toolchain: ${CMAKE_TOOLCHAIN_FILE}")
endif()

# DLL hook library
add_library(daybreak_hook SHARED
    src/daybreak_hook.c
)

# Launcher executable (console app)
add_executable(daybreak_launcher
    src/daybreak_launcher.c
)

# Link libraries
target_link_libraries(daybreak_hook PRIVATE user32)
target_link_libraries(daybreak_launcher PRIVATE kernel32 user32)

# Set output names (avoid lib prefix on DLL)
set_target_properties(daybreak_hook PROPERTIES
    OUTPUT_NAME "daybreak_hook"
    PREFIX ""
)
set_target_properties(daybreak_launcher PROPERTIES
    OUTPUT_NAME "daybreak_launcher"
    PREFIX ""
)

message(STATUS "")
message(STATUS "daybreak_hook build configured.")
message(STATUS "  Outputs: daybreak_hook.dll + daybreak_launcher.exe")
message(STATUS "  Build with: cmake --build build")
message(STATUS "")
