CC = gcc
EXEC = KnightTour

KnightTour:./src/main.o ./src/generate.o ./src/pathway.o ./src/knighttour.o ./src/menu.o
	$(CC) -o $(EXEC) ./src/main.o ./src/generate.o ./src/pathway.o ./src/knighttour.o ./src/menu.o -std=c99
	./$(EXEC)

./src/main.o:./src/main.c ./headers/generate.h ./headers/pathway.h ./headers/knighttour.h ./headers/menu.h
	$(CC) -o ./src/main.o -c ./src/main.c -std=c99

./src/generate.o:./src/generate.c ./headers/generate.h
	$(CC) -o ./src/generate.o -c ./src/generate.c -std=c99

./src/pathway.o:./src/pathway.c ./headers/pathway.h
	$(CC) -o ./src/pathway.o -c ./src/pathway.c -std=c99

./src/knighttour.o:./src/knighttour.c ./headers/knighttour.h
	$(CC) -o ./src/knighttour.o -c ./src/knighttour.c -std=c99

./src/menu.o:./src/menu.c ./headers/menu.h
	$(CC) -o ./src/menu.o -c ./src/menu.c -std=c99

clean:
	rm -rf ./src/*.o

mrproper:clean
	rm -rf $(EXEC)