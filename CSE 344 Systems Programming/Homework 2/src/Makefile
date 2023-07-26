compile:
	gcc src.c -ansi -pedantic-errors -std=c99 -o hw2

memoryLeak:
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./hw2

run:
	./hw2

clean:
	rm -f *.o hw2
	rm -f *2023*
