cmake_minimum_required(VERSION 3.8)
project(Bomberman)

include(ExternalProject)
set(BOMBERMAN_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(NANOGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.nanogui)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -g3")

if (NOT IS_DIRECTORY "$ENV{HOME}/.brew")
	message("ERROR: Please make sure brew is installed.")
endif()

if (NOT IS_DIRECTORY "$ENV{HOME}/.brew/Cellar/glew")
	execute_process(COMMAND brew install glew)
endif()

if (NOT IS_DIRECTORY "${NANOGUI_DIR}")
	execute_process(COMMAND git clone https://github.com/wjakob/nanogui.git --recursive .nanogui)
	execute_process(COMMAND sh .compile.sh)
endif()

set(SOURCE_FILES
		src/Bomb.cpp
		src/Bomberman.cpp
		src/Box.cpp
		src/BreakableBox.cpp
		src/Character.cpp
		src/Core.cpp
		src/Drop.cpp
		src/EnemyDrop.cpp
		src/Exceptions.cpp
		src/ExtraBomb.cpp
		src/Game.cpp
		src/LevelHatch.cpp
		src/Menu.cpp
		src/Player.cpp
		src/RangeExtender.cpp
		src/RemoteDetonator.cpp
		src/Settings.cpp
		src/UnbreakableBox.cpp)

include_directories(
		${PROJECT_SOURCE_DIR}/include
		${NANOGUI_DIR}/ext/glfw/include
		${NANOGUI_DIR}/include
		${NANOGUI_DIR}/ext/eigen
		${NANOGUI_DIR}/ext/nanovg/src
		$ENV{HOME}/.brew/Cellar/glew/2.1.0/include
		/System/Library/Frameworks/AGL.framework/Versions/A/Headers
)

link_directories(
		${NANOGUI_DIR}
		${NANOGUI_DIR}/ext/eigen
		${NANOGUI_DIR}/ext/nanovg/src
		$ENV{HOME}/.brew/Cellar/glew/2.1.0/lib/
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
		nanogui
		GLEW
)

if (APPLE)
	target_link_libraries(${PROJECT_NAME}
			"-framework OpenGL")
endif()