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
UNIX_DEP = git clone https://github.com/Tolsadus/42homebrewfix.git && brew install sdl && brew install glew

TARGET =  bomberman
LNAME = libopengl_$(HOSTTYPE).so

FLAGS = -Wall -Werror -Wextra -std=c++11 -g -g3 -I include -ldl
LFLAGS = -Wall -Werror -Wextra -fPIC -shared -o

SP = ./src/

SRC = $(SP)Bomb.cpp\
	  $(SP)BreakableBox.cpp\
	  $(SP)Character.cpp\
	  $(SP)Exceptions.cpp\
	  $(SP)Game.cpp\
	  $(SP)GraphicsHandler.cpp\
	  $(SP)main.cpp\
	  $(SP)Player.cpp\
	  $(SP)Settings.cpp

LDIR = opengl_dynamic_library/

LFILES = $(LDIR)libopengl.cpp

all : lib $(TARGET)

lib: $(LNAME)

$(TARGET):
	#@cd ~ && $(DEP) #need to trigger condition as to when it will install dependencies, i.e. if dependencies are missing only
	@clang++ $(FLAGS) $(SRC) -o $(TARGET)
	@echo "$(TARGET) compiled sucsessfully."

$(LNAME):
	@clang++ $(LFLAGS) $(LNAME) $(LFILES)
	@echo $(LNAME) "compiled sucsessfully."

inj:
	export DYLD_LIBRARY_PATH=${PWD}/$(LDIR)
	export DYLD_INSERT_LIBRARIES=$(LNAME)
	export DYLD_FORCE_FLAT_NAMESPACE=1
	env
	@echo $(LNAME) "injected"

fclean:
	@rm -f $(TARGET) $(LNAME)
	@echo "$(TARGET) & $(LNAME) deleted."

mclean:
	@find . -name '._*' -type f -delete
	@echo "Removed hidden ._ files."

re: fclean all
