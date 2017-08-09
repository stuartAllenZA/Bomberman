ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

TARGET =  bomberman
LNAME = libopengl_$(HOSTTYPE).so

FLAGS = -Wall -Werror -Wextra -std=c++11 -g -g3 -I include -ldl
LFLAGS = -Wall -Werror -Wextra -std=c++11 -I../.brew/Cellar/sdl2/2.0.5/include\
    -Iopengl_dynamic_library/include -I../.brew/Cellar/glew/2.1.0/include/\
    -L../.brew/Cellar/sdl2/2.0.5/lib -lSDL2 -L../.brew/Cellar/glew/2.1.0/lib/ -lGLEW -framework OpenGL -fPIC -shared -o

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

LDIR = opengl_dynamic_library/src/

LFILES = $(LDIR)libopengl.cpp\
         $(LDIR)Window.cpp

all : lib $(TARGET)

lib: $(LNAME)

$(TARGET):
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
