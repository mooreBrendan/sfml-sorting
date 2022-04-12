EXE_NAME=Sorting
SFMLPath=D:/sfml

DEBUG_FLAGS = -DDEBUG

SRCS = src/*.cpp
includes = -I include -I $(SFMLPath)/include
libs = -L $(SFMLPath)/lib
links = -l sfml-audio -l sfml-graphics -l sfml-window -l sfml-system
OBJS = $(SRCS:%.cpp=%.o)

all: compile link

remake: clean all
remake-debug: clean debug link

debug:
	g++ $(includes) -c $(SRCS) $(DEBUG_FLAGS)

compile:
	g++ $(includes) -c $(SRCS)
link:
	g++ -o $(EXE_NAME) *.o $(libs) $(links)


clean:
	del .\$(EXE_NAME).exe
	del *.o