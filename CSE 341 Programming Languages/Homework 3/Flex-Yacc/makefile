run:
	lex lexer.l
	yacc -d parser.y -Wother -Wcounterexamples
	cc lex.yy.c y.tab.c -ll  
	./a.out 