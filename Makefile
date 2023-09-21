CLANG_CONFIG := -Wall
MAIN_EXE := main

main: weapon.o player.o main.cpp
	clang++ ${CLANG_CONFIG} main.cpp weapon.o player.o -o main

weapon.o: weapon.cpp weapon.h
	clang++ ${CLANG_CONFIG} weapon.cpp -c -o weapon.o

player.o: player.cpp player.h
	clang++ ${CLANG_CONFIG} player.cpp -c -o player.o	

clean: $(wildcard *.o) $(MAIN_EXE)
	echo $(wildcard *.o) $(MAIN_EXE)
	rm $(wildcard *.o) $(MAIN_EXE)