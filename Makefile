FileName=Catan
SFMLPath=D:/sfml

SRCS = src/*.cpp
OBJS = $(SRCS:%.c=%.o)

all: compile link

.c.o: 
	$(GCC) -I include -I $(SFMLPath)/include -c $(SRCS)

compile:
	g++ -I include -I $(SFMLPath)/include -c $(SRCS)
link:
	g++ *.o -o $(FileName) -L $(SFMLPath)/lib -l sfml-graphics -l sfml-window -l sfml-system -l sfml-audio


clean:
	del .\$(FileName).exe
	del *.o