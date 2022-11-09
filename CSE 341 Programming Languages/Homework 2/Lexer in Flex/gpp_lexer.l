%{
    #include <stdio.h>
    int str_sign = 0;
%}
OP_OC "\""
VALUEI [0]|[1-9][0-9]*
VALUEF {VALUEI}f[0-9]*
VALUESTR {OP_OC}[^"\""]*{OP_OC}*
COMMENT ";;".*
IDENTIFIER ([A-Za-z]|"_")([A-Za-z]|[0-9]|"_")*
LEADINGZERO [0][0-9]+
NOTHAVEFRACTION {VALUEI}f((" ")|("\n"))
LEADINGNUMBERIDENTIFIER [0-9]([A-Za-z]|[0-9]|"_")+
%%
"and" {printf("%s: KW_AND\n", yytext);}
"or" {printf("%s: KW_OR\n", yytext);}
"not" {printf("%s: KW_NOT\n", yytext);}
"equal" {printf("%s: KW_EQUAL\n", yytext);}
"less" {printf("%s: KW_LESS\n", yytext);}
"nil" {printf("%s: KW_NIL\n", yytext);}
"list" {printf("%s: KW_LIST\n", yytext);}
"append" {printf("%s: KW_APPEND\n", yytext);}
"concat" {printf("%s: KW_CONCAT\n", yytext);}
"set" {printf("%s: KW_SET\n", yytext);}
"deffun" {printf("%s: KW_DEFFUN\n", yytext);}
"for" {printf("%s: KW_FOR\n", yytext);}
"if" {printf("%s: KW_IF\n", yytext);}
"exit" {printf("%s: KW_EXIT\n", yytext);}
"load" {printf("%s: KW_LOAD\n", yytext);}
"disp" {printf("%s: KW_DISP\n", yytext);}
"true" {printf("%s: KW_TRUE\n", yytext);}
"false" {printf("%s: KW_FALSE\n", yytext);}
"+" {printf("%s: OP_PLUS\n", yytext);}
"-" {printf("%s: OP_MINUS\n", yytext);}
"/" {printf("%s: OP_DIV\n", yytext);}
"*" {printf("%s: OP_MULT\n", yytext);}
"(" {printf("%s: OP_OP\n", yytext);}
")" {printf("%s: OP_CP\n", yytext);}
"**" {printf("%s: OP_DBLMULT\n", yytext);}
"," {printf("%s: OP_COMMA\n", yytext);}
" " ;
"\n" ;
{OP_OC} {printf("%s: OP_OC\n", yytext);}
{VALUEI} {printf("%s: VALUEI\n", yytext);}
{VALUEF} {printf("%s: VALUEF\n", yytext);}
{VALUESTR} {printf("\": OP_OC\n %s: VALUESTR\n", yytext + 1);
            if(strcmp("\"", yytext + yyleng - 1) == 0){
                printf("\": OP_CC\n");
            }
            }
{COMMENT} {printf("%s: COMMENT\n", yytext);}
{IDENTIFIER} {printf("%s: IDENTIFIER\n", yytext);}
{LEADINGZERO} {printf("%s: LEADING ZERO(S) ERROR\n", yytext);
                return 0;
;}
{NOTHAVEFRACTION} {printf("%s: NOT HAVE FRACTION ERROR\n", yytext);
                return 0;
;}
{LEADINGNUMBERIDENTIFIER} {printf("%s: LEADING NUMBER FOR IDENTIFIER ERROR\n", yytext);
                return 0;
;}

. {printf("%s: SYNTAX ERROR\n", yytext);
                return 0;
;}
%%
int main(int argc, char **argv){
	yyin=fopen(argv[1], "r");
	yylex();
	return 0;
}
