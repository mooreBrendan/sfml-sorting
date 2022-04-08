FileName=Sorting
SFMLPath=D:/sfml

SRCS = src/*.cpp
OBJS = $(SRCS:%.c=%.o)

all: compile link


compile:
	g++ -I include -I $(SFMLPath)/include -c $(SRCS)
link:
	g++ -o $(FileName) *.o -L $(SFMLPath)/lib -l sfml-audio -l sfml-graphics -l sfml-window -l sfml-system


clean:
	del .\$(FileName).exe
	del *.o