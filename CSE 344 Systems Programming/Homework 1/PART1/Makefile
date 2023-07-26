appendMeMore: src.c
	gcc -ansi -pedantic-errors -std=c99 -o appendMeMore src.c

run: 
	./appendMeMore f1 1000000 & ./appendMeMore f1 1000000
	./appendMeMore f2 1000000 x & ./appendMeMore f2 1000000 x

clean:
	rm -f appendMeMore *.o
	rm -f f1 f2

 