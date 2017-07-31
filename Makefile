ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

TARGET =  bomberman
LNAME = libopengl_$(HOSTTYPE).so

FLAGS = -Wall -Werror -Wextra -g -g3 -I include
LFLAGS = -Wall -Werror -Wextra -I include -shared -o

SP = ./src/

SRC = $(SP)Character.cpp\
	  $(SP)Game.cpp\
	  $(SP)GraphicsHandler.cpp\
	  $(SP)main.cpp\
	  $(SP)Player.cpp\
	  $(SP)Settings.cpp

CLFILES = ./opengl_dynamic_library/libopengl.cpp

cur_dir = $(shell pwd)

all : $(TARGET)

lib: $(LNAME)

$(TARGET):
	@clang++ $(FLAGS) $(SRC) -o $(TARGET)
	@echo "$(TARGET) compiled sucsessfully."

$(LNAME):
	@clang++ $(LFLAGS) $(LNAME) $(CLFILES)
	@echo $(LNAME) "compiled"

inj:
	$(shell export DYLD_LIBRARY_PATH=$(cur_dir))
	$(shell export DYLD_INSERT_LIBRARIES=$(LNAME))
	$(shell export DYLD_FORCE_FLAT_NAMESPACE=1)
	env
	@echo $(LNAME) "injected"

fclean:
	@rm -f $(TARGET)
	@echo "$(TARGET) cleaned."

mclean:
	@find . -name '._*' -type f -delete
	@echo "Removed hidden ._ files."

re: fclean all
