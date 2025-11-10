# makefile task 3
.PHONY : all clean

all : menu_map

menu_map : menu_map.c
	gcc -g -m32 -Wall -o menu_map menu_map.c

run : menu_map
	./menu_map

gdb : menu_map
	gdb --quiet --args ./menu_map

clean : 
	-rm -f *.o build