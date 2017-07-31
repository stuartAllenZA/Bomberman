ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

TARGET =  bomberman
LNAME = libopengl_$(HOSTTYPE).so

FLAGS = -Wall -Werror -Wextra -g -g3 -I include
LFLAGS = -Wall -Werror -Wextra -shared -o

SP = ./src/

SRC = $(SP)Character.cpp\
	  $(SP)Game.cpp\
	  $(SP)GraphicsHandler.cpp\
	  $(SP)main.cpp\
	  $(SP)Player.cpp\
	  $(SP)Settings.cpp

LDIR = opengl_dynamic_library/

LFILES = $(LDIR)libopengl.cpp

all : $(TARGET)

lib: $(LNAME)

$(TARGET):
	@clang++ $(FLAGS) $(SRC) -o $(TARGET)
	@echo "$(TARGET) compiled sucsessfully."

$(LNAME):
	@clang++ $(LFLAGS) $(LNAME) $(CLFILES)
	@echo $(LNAME) "compiled"

inj:
	export DYLD_LIBRARY_PATH=${PWD}/$(LDIR)
	export DYLD_INSERT_LIBRARIES=$(LNAME)
	export DYLD_FORCE_FLAT_NAMESPACE=1
	env
	@echo $(LNAME) "injected"

fclean:
	@rm -f $(TARGET)
	@echo "$(TARGET) cleaned."

mclean:
	@find . -name '._*' -type f -delete
	@echo "Removed hidden ._ files."

re: fclean all
