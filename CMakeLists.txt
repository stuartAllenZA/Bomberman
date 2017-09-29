cmake_minimum_required(VERSION 3.8)
project(Bomberman)

include(ExternalProject)
set(BOMBERMAN_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.libraries)
set(NANOGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.libraries/nanogui)
set(TINYGLTF_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.libraries/tinygltf)
set(IRRKLANG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.libraries/irrklang)
set(GLM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.libraries/glm)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -g3")

if (NOT IS_DIRECTORY "$ENV{HOME}/.brew/Cellar/glew")
	execute_process(COMMAND brew install glew)
endif()

if (NOT IS_DIRECTORY "${LIB_DIR}")
	execute_process(COMMAND git clone https://github.com/stuartAllenZA/BombermanLibraries.git .libraries)
endif()

if (NOT IS_DIRECTORY "${NANOGUI_DIR}")
	execute_process(COMMAND git clone https://github.com/wjakob/nanogui.git --recursive .libraries/nanogui)
	execute_process(COMMAND sh .compile.sh)
endif()

if (NOT IS_DIRECTORY "${TINYGLTF_DIR}")
	execute_process(COMMAND git clone https://github.com/syoyo/tinygltf.git .libraries/tinygltf)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(STATUS "GCC detected, adding compile flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -Wextra")
endif()

set(SOURCE_FILES
	src/Animation.cpp
	src/Bomb.cpp
	src/Bomberman.cpp
	src/Box.cpp
	src/BreakableBox.cpp
	src/Camera.cpp
	src/Character.cpp
	src/Core.cpp
	src/Drop.cpp
	src/Enemy.cpp
	src/EnemyDrop.cpp
	src/Exceptions.cpp
	src/ExtraBomb.cpp
	src/Game.cpp
	src/GraphicsEngine.cpp
	src/LevelHatch.cpp
	src/Material.cpp
	src/Menu.cpp
	src/Model.cpp
	src/ModelShader.cpp
	src/Player.cpp
	src/RangeExtender.cpp
	src/RemoteDetonator.cpp
	src/Settings.cpp
	src/Sound.cpp
	src/Stb_image.cpp
	src/UnbreakableBox.cpp
	src/Util.cpp)

include_directories(
		${PROJECT_SOURCE_DIR}/include
		SYSTEM ${IRRKLANG_DIR}/include
		SYSTEM ${NANOGUI_DIR}/ext/glfw/include
		SYSTEM ${NANOGUI_DIR}/include
		SYSTEM ${NANOGUI_DIR}/ext/eigen
		SYSTEM ${NANOGUI_DIR}/ext/nanovg/src
		SYSTEM ${TINYGLTF_DIR}
		SYSTEM ${LIB_DIR}/misc
		SYSTEM $ENV{HOME}/.brew/Cellar/glew/2.1.0/include
		SYSTEM ${GLM_DIR}
		SYSTEM ${GLM_DIR}/gtx
		SYSTEM ${GLM_DIR}/gtc
)

link_directories(
		${IRRKLANG_DIR}
		${NANOGUI_DIR}
		${NANOGUI_DIR}/ext/eigen
		${NANOGUI_DIR}/ext/nanovg/src
		$ENV{HOME}/.brew/Cellar/glew/2.1.0/lib
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_custom_command(TARGET ${PROJECT_NAME}
		PRE_BUILD
		COMMAND install_name_tool -id "${IRRKLANG_DIR}/libirrklang.dylib"
		${IRRKLANG_DIR}/libirrklang.dylib
)

target_link_libraries(${PROJECT_NAME}
		irrklang
		nanogui
		GLEW
)

if (APPLE)
	target_link_libraries(${PROJECT_NAME}
			"-framework OpenGL")
endif()
