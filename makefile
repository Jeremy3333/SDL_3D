all: main.exe

main.exe: main.o renderWindow.o
	g++ -o main.exe main.o renderWindow.o -L C:/SDL2-w64/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

main.o: main.cpp include/RenderWindow.hpp
	g++ -c main.cpp -I include -I C:\SDL2-w64\include -Wall

renderWindow.o: renderWindow.cpp include/RenderWindow.hpp
	g++ -c renderWindow.cpp -I include -Wall -I C:/SDL2-w64/include

clean:
	rm -f *.o *.exe

# Path: main.cpp