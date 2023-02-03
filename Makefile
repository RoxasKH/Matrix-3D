main.exe: main.o
	g++ main.o -o main.exe

main.o: main.cpp Matrix3D.h
	g++ -c main.cpp -o main.o

.PHONY:

clean:
	rm -f main.exe main.o
