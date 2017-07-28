TARGET =  bomberman

CC = g++

I = -I include

SP = ./src/

SRC = $(SP)main.cpp\
	  $(SP)GameClass.cpp\
	  $(SP)GraphicsHandler.cpp

all : $(TARGET)

$(TARGET):
	$(CC) $(I) $(SRC) -o $(TARGET)

clean:
	rm $(TARGET)

re: clean all
