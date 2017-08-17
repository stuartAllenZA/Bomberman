ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	DEP = $(LINUX_DEP) 
else ifeq ($(UNAME), Darwin)
	DEP = $(UNIX_DEP)
endif

LINUX_DEP = sudo apt-get update && sudo apt-get install libXmu-dev libXi-dev libgl-dev dos2unix libsdl2-dev

TARGET =  bomberman

FLAGS = -Wall -Werror -Wextra -std=c++11 -g -g3 -I include\
		-I../.brew/Cellar/sdl2/2.0.5/include\
		-I../.brew/Cellar/glew/2.1.0/include/\
		-L../.brew/Cellar/sdl2/2.0.5/lib -lSDL2\
		-L../.brew/Cellar/glew/2.1.0/lib/ -lGLEW -framework OpenGL

SP = ./src/

SRC = $(SP)Bomb.cpp\
	  $(SP)BreakableBox.cpp\
	  $(SP)Character.cpp\
	  $(SP)EnemyDrop.cpp\
	  $(SP)Exceptions.cpp\
	  $(SP)ExtraBomb.cpp\
	  $(SP)Game.cpp\
	  $(SP)GraphicsHandler.cpp\
	  $(SP)LevelHatch.cpp\
	  $(SP)main.cpp\
	  $(SP)Player.cpp\
	  $(SP)RangeExtender.cpp\
	  $(SP)RemoteDetonation.cpp\
	  $(SP)Settings.cpp\
	  $(SP)UnbreakableBox.cpp\
	  $(SP)Window.cpp

ifneq ("$(wildcard ~/.brew)","")
INSTALLBREW = 
else
INSTALLBREW = $(shell sh -c "$(curl -fsSL https://raw.githubusercontent.com/Tolsadus/42homebrewfix/master/install.sh)")
endif

ifneq ("$(wildcard ~/.brew/Cellar/sdl2/2.0.5/include/SDL2/SDL.h)","")
INSTALLSDL = 
else
INSTALLSDL = brew install sdl2
endif

ifneq ("$(wildcard ~/.brew/Cellar/glew/2.1.0/include/GL/glew.h)","")
INSTALLGLEW = 
else
INSTALLGLEW = brew install glew
endif

all : $(TARGET)

$(TARGET):
	$(INSTALLBREW)
	$(INSTALLSDL)
	$(INSTALLGLEW)
	@clang++ $(FLAGS) $(SRC) -o $(TARGET)
	@echo "$(TARGET) compiled sucsessfully."

fclean:
	@rm -f $(TARGET) $(LNAME)
	@echo "$(TARGET) & $(LNAME) deleted."

mclean:
	@find . -name '._*' -type f -delete
	@find . -name '*.sw*' -type f -delete
	@echo "Removed hidden ._ & vi temp files."

re: fclean all
