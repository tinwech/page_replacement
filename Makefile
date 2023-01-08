all: main.o
	g++ -o main main.o
main.o: main.cpp
	g++ -c main.cpp -o main.o
clean:
	rm main main.o