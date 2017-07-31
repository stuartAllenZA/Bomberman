TARGET =  bomberman

FLAGS = -Wall -Werror -Wextra -g -g3 -I include

SP = ./src/

SRC = $(SP)Character.cpp\
	  $(SP)Game.cpp\
	  $(SP)GraphicsHandler.cpp\
	  $(SP)main.cpp\
	  $(SP)Player.cpp\
	  $(SP)Settings.cpp\
	  

all : $(TARGET)

$(TARGET):
	@clang++ $(FLAGS) $(SRC) -o $(TARGET)
	@echo "$(TARGET) compiled sucsessfully."

clean:
	@rm $(TARGET)
	@echo "$(TARGET) cleaned."

mclean:
	@find . -name '._*' -type f -delete
	@echo "Removed hidden ._ files."

re: clean all
