

main.exe: main.o exceptionbst.o
	g++ -std=c++0x main.o exceptionbst.o -o main.exe

exceptionbst.o: exceptionbst.cpp exceptionbst.h
	g++ -std=c++0x -c exceptionbst.cpp -o exceptionbst.o

main.o: main.cpp bst.h
	g++ -std=c++0x -c main.cpp -o main.o

.PHONY: clean

clean:
	rm *.exe *.o