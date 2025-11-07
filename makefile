#  makefile for count-words file:

.PHONY : all run debug asan clean

all : count-words

count-words : count-words.c
	gcc -g -O0 -Wall -Wextra -Wpedantic -o count-words count-words.c

run : count-words
	./count-words oneword

debug : count-words
	gdb --args ./count-words oneword


clean : 
	-rm -f *.o count-words

# make file for all files:

# .PHONY : all clean

# all : base addresses count-words

# base : base.c 
# 	gcc -g -m32 -Wall -o base base.c

# addresses : addresses.c
# 	gcc -g -m32 -Wall -o addresses addresses.c

# count-words : count-words.c
# 	gcc -g -m32 -Wall -o count-words count-words.c

# clean : 
# 	-rm -f *.o build