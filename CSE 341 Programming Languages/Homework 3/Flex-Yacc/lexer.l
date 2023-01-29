%{
    #include <stdio.h>
    #include <string.h>
    #include "y.tab.h"
    void yyerror(char *s);
    int line_number = 0;
%}


UNSIGNEDINTEGER [1-9]+
VALUEF {UNSIGNEDINTEGER}f{UNSIGNEDINTEGER}
IDENTIFIER [a-zA-Z][a-zA-Z0-9_]*
NOTIDENTIFIER [a-zA-Z0-9_]+
COMMENT ";;".*
%%


{VALUEF} {
    int index = 0;
    for(int i = 0; i < yyleng; i++){
        if(yytext[i] == 'f')
            index = i;
    }
    int first_part = atoi(yytext);
    int second_part = atoi(yytext+index + 1);
    float value = (float)first_part / second_part;
    yylval.type.fval =  value;
    return(VALUEF);
}
{COMMENT} ;
"nil" {yylval.type.name = strdup(yytext);
    return(KW_NIL);
}
"while" {yylval.type.name = strdup(yytext);
    return(KW_WHILE);
}
"if" {yylval.type.name = strdup(yytext);
    return(KW_IF);
}
"load" {yylval.type.name = strdup(yytext);
    return(KW_LOAD);
}
"disp" {yylval.type.name = strdup(yytext);
    return(KW_DISP);
}
"true" {yylval.type.name = strdup(yytext);
    return(KW_TRUE);
}
"false" {yylval.type.name = strdup(yytext);
    return(KW_FALSE);
}
"defvar" {yylval.type.name = strdup(yytext);
    return(DEFV);
}
"deffun" {yylval.type.name = strdup(yytext);
    return(DEFF);
}
"gt" {yylval.type.name = strdup(yytext);
    return(OP_GT);
}
"set" {yylval.type.name = strdup(yytext);
    return(OP_SET);
}
"and" {yylval.type.name = strdup(yytext);
    return(OP_AND);
}
"or" {yylval.type.name = strdup(yytext);
    return(OP_OR);
}
"not" {yylval.type.name = strdup(yytext);
    return(OP_NOT);
}
"eq" {yylval.type.name = strdup(yytext);
    return(OP_EQ);
}
"(" {yylval.type.name = strdup(yytext);
    return(OP_OP);
}
")" {yylval.type.name = strdup(yytext);
    return(OP_CP);
}
\+ {yylval.type.name = strdup(yytext);
    return(OP_PLUS);
}
\- {yylval.type.name = strdup(yytext);
    return(OP_MINUS);
}
\/ {yylval.type.name = strdup(yytext);
    return(OP_DIV);
}
\* {yylval.type.name = strdup(yytext);
    return(OP_MULT);
}
\, {yylval.type.name = strdup(yytext);
    return(OP_COMMA);
}
\n {
    line_number+=1;
    return('\n');
}
{IDENTIFIER} {
    yylval.type.name = strdup(yytext);
    return(ID);
}
{NOTIDENTIFIER} {
    printf("Identifier \"%s\" cannot start with anything except letters!\n", yytext);
    return 0;
}
" " ;
. {
    printf("UNKNOWN CHARACTER OR STRING");
    return 0;
}
%%

int yywrap(){
    return 1;
} 
