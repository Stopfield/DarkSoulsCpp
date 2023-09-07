CLANG_CONFIG := -Wall
MAIN_EXE := main

main: weapon.o main.cpp
	clang++ ${CLANG_CONFIG} main.cpp weapon.o -o main

weapon.o: weapon.cpp weapon.h
	clang++ ${CLANG_CONFIG} weapon.cpp -c -o weapon.o

clean: $(wildcard *.o) $(MAIN_EXE)
	echo $(wildcard *.o) $(MAIN_EXE)
	rm $(wildcard *.o) $(MAIN_EXE)