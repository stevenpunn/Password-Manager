cmake_minimum_required(VERSION 3.16)
project(PasswordManager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
file(GLOB_RECURSE SOURCES
    "main.cpp"
    "core/*.cpp"
    "gui/*.cpp"  # Optional now
)

# Find Qt (GUI later)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Add executable
add_executable(PasswordManager ${SOURCES})

# Link Qt
target_link_libraries(PasswordManager PRIVATE Qt6::Widgets)

