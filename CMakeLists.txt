cmake_minimum_required(VERSION 3.8)
project(Bomberman_Liam)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -g3")

if (NOT IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/DEPENDANTS/nanogui/build")
    message(ERROR "The NanoGUI dependency repositories (GLFW, etc.) are missing! "
            "You probably did not clone the project with --recursive.")
    execute_process(COMMAND git submodule update --init --recursive)
    execute_process(COMMAND /bin/sh installnanogui.sh
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/DEPENDANTS/nanogui)
endif()

set(SOURCE_FILES
        include/Bomb.hpp
        include/Box.hpp
        include/BreakableBox.hpp
        include/Character.hpp
        include/Core.hpp
        include/Drop.hpp
        include/EnemyDrop.hpp
        include/Exceptions.hpp
        include/ExtraBomb.hpp
        include/Game.hpp
        include/GraphicsHandler.hpp
        include/GraphicsInterface.hpp
        include/header.hpp
        include/LevelHatch.hpp
        include/Player.hpp
        include/RangeExtender.hpp
        include/RemoteDetonator.hpp
        include/Settings.hpp
        include/UnbreakableBox.hpp
        src/Bomb.cpp
        src/Box.cpp
        src/BreakableBox.cpp
        src/Character.cpp
        src/Core.cpp
        src/Drop.cpp
        src/EnemyDrop.cpp
        src/Exceptions.cpp
        src/ExtraBomb.cpp
        src/Game.cpp
        src/GraphicsHandler.cpp
        src/LevelHatch.cpp
        src/main.cpp
        src/Player.cpp
        src/RangeExtender.cpp
        src/RemoteDetonator.cpp
        src/Settings.cpp
        src/UnbreakableBox.cpp)

find_package(PkgConfig)

pkg_search_module(GLEW REQUIRED glew)
pkg_search_module(GLM REQUIRED glm)

include_directories(
        include
        DEPENDANTS/nanogui/ext/glfw/include
        DEPENDANTS/nanogui/include
        DEPENDANTS/nanogui/ext/eigen
        DEPENDANTS/nanogui/ext/nanovg/src
        ${GLEW_INCLUDE_DIR}
        ${GLM_INCLUDE_DIR}
)

link_directories(
        ${PROJECT_SOURCE_DIR}/DEPENDANTS/nanogui
        ${PROJECT_SOURCE_DIR}/DEPENDANTS/nanogui/ext/eigen
        ${PROJECT_SOURCE_DIR}/DEPENDANTS/nanogui/ext/nanovg/src
        ${GLEW_LIBRARY_DIRS}
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
        nanogui
)

if (APPLE)
    target_link_libraries(${PROJECT_NAME}
            "-framework OpenGL")
endif()