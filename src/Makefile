CLANG_CONFIG := -Wall
MAIN_EXE := main

main: weapon.o player.o enemy.o main.cpp Item.o
	clang++ ${CLANG_CONFIG} main.cpp enemy.o weapon.o player.o Item.o -o main

weapon.o: weapon.cpp weapon.h
	clang++ ${CLANG_CONFIG} weapon.cpp -c -o weapon.o

player.o: player.cpp player.h
	clang++ ${CLANG_CONFIG} player.cpp -c -o player.o	

enemy.o: enemy.cpp enemy.h
	clang++ ${CLANG_CONFIG} enemy.cpp -c -o enemy.o

Item.o: Item.cpp Item.h
	clang++ ${CLANG_CONFIG} Item.cpp -c -o Item.o


clean: $(wildcard *.o) $(MAIN_EXE)
	echo $(wildcard *.o) $(MAIN_EXE)
	rm $(wildcard *.o) $(MAIN_EXE)