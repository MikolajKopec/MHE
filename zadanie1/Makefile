CPP=g++

LIBS=-lSDL2 -lGL
CARGS=-std=c++17 -I/usr/include/SDL2


APP=game

all: $(APP) 

$(APP): game.cpp
	$(CPP) $(CARGS) $(LIBS) game.cpp -o $(APP) $(LIBS)

run: all
	@LD_LIBRARY_PATH=$(SDLLIB) $(APP)

clean:
	rm -f $(APP)