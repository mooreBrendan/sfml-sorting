FileName=Catan
SFMLPath=D:/sfml

all: compile link

compile:
	g++ -I include -I $(SFMLPath)/include -c src/*.cpp -o $(FileName).o
link:
	g++ $(FileName).o -o $(FileName) -L $(SFMLPath)/lib -l sfml-graphics -l sfml-window -l sfml-system -l sfml-audio


clean:
	del .\$(FileName).exe
	del .\$(FileName).o