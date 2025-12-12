COMPILER=gcc

C_FLAGS=

all: huffman

huffman: main.o huffman.o io_func.o
	$(COMPILER) $(C_FLAGS) main.o io_func.o huffman.o -o huffman

main.o: src/main.c
	$(COMPILER) $(C_FLAGS) -c src/main.c

huffman.o: src/huffman.c
	$(COMPILER) $(C_FLAGS) -c src/huffman.c

io_func.o: src/io_func.c
	$(COMPILER) $(C_FLAGS) -c src/io_func.c

obj_clean:
	rm -rf *.o

clean:
	rm -rf *.o huffman
