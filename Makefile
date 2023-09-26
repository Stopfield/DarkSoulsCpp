CLANG_CONFIG := -Wall
MAIN_EXE := main

main: weapon.o player.o enemy.o main.cpp
	clang++ ${CLANG_CONFIG} main.cpp enemy.o weapon.o player.o -o main

weapon.o: weapon.cpp weapon.h
	clang++ ${CLANG_CONFIG} weapon.cpp -c -o weapon.o

player.o: player.cpp player.h
	clang++ ${CLANG_CONFIG} player.cpp -c -o player.o	

enemy.o: enemy.cpp enemy.h
	clang++ ${CLANG_CONFIG} enemy.cpp -c -o enemy.o	


clean: $(wildcard *.o) $(MAIN_EXE)
	echo $(wildcard *.o) $(MAIN_EXE)
	rm $(wildcard *.o) $(MAIN_EXE)