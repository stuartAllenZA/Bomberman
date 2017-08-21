cmake_minimum_required(VERSION 3.8)
project("Bomberman")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

set(SOURCE_FILES src/main.cpp
                src/Character.cpp
                src/Exceptions.cpp
                src/Game.cpp
                src/GraphicsHandler.cpp
                src/Player.cpp
                src/Settings.cpp
                include/Character.hpp
                include/Exceptions.hpp
                include/Game.hpp
                include/GraphicsHandler.hpp
                include/GraphicsInterface.hpp
                include/header.hpp
                include/Player.hpp
                include/Settings.hpp)

include_directories(
    include
    opengl_dynamic_library/deps/nanogui/include
    opengl_dynamic_library/deps/nanogui/ext_build
    opengl_dynamic_library/deps/nanogui/ext_build/glfw
)

link_directories(
    ${PROJECT_SOURCE_DIR}/opengl_dynamic_library/deps/nanogui
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
    nanogui
)