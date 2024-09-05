CC = g++
CFLAGS = -Wall
LIBS = -lGL -lGLU -lglut

all: bin/output_program


bin/output_program: src/main.o
	$(CC) $(CFLAGS) -o bin/output_program src/main.o $(LIBS)

src/main.o: src/main.cpp
	$(CC) $(CFLAGS) -c -o src/main.o -Iinclude src/main.cpp


clean:
	rm -f src/*.o bin/output_program

run:
	bin/output_program
