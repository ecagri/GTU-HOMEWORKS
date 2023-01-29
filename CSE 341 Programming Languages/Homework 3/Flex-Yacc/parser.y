%{
    /* FUNCTIONS AND IF CONDITIONS DO NOT WORK PROPERLY BECAUSE THERE IS NOT ENOUGH RESOURCES ABOUT HOW TO HANDLE THEM. */
    /* Some changes are made in cfg because of some reduce-reduce and reduce-shift conflicts. */
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <float.h>
    extern FILE *yyin;
    extern char* yytext;
    int yylex();
    void yyerror(char *s);

    struct symbolTableVariable{ /* Helps for creating symbol table. */
        char * name; /* Name of the variable. */
        int line_number; /* Line number where variable is created. */
        float value; /* Value of the variable. */
    }variableTable[100];

    struct Node{ /* Helps for creating abstract syntax tree. */
        char * terminal; /* Name of the terminal. */
        struct Node * child; /* Child node. */ 
        struct Node * sibling; /* Sibling node. */
    }Node;

    struct Node * createNode(struct Node * sibling, struct Node * child, char * name){ /* Creates a node. */
        struct Node * node = (struct Node * ) malloc(sizeof(struct Node)); 
        node->child = child; /* Sets child of the node as child. */
        node->sibling = sibling; /* Sets sibling of the node as sibling. */
        node->terminal = strdup(name); /* Sets terminal name. */
        return node;
    }

    void printAST(struct Node * node, int intend){ /* Prints the abstract syntax tree in pretty way. */
        if(node->sibling != NULL) /* Prints all siblings. */
            printAST(node->sibling, intend);
        for(int i = 0; i < intend; i++)
            printf("__");
        printf("%s\n", node->terminal); /* Prints current terminal. */
        if(node->child != NULL) /* Prints all children. */
            printAST(node->child, intend + 1);
    }

    int count = 0; /* Counter for symbol table. */

    extern int line_number;

    struct Node * head; /* Head of the abstract syntax tree. */

    float lookupVariable(char * name){ /* Looks up for a variable in symbol table. */
        float value = FLT_MAX; /* Sets the value as max float number. */
        for(int i = 0; i < count; i++){
            if(strcmp(name, variableTable[i].name) == 0){ /* If the variable is found in symbol table, gets its value. */
                value = variableTable[i].value;
            }
        }
        return value;
    }

    void addVariable(char * name, float val){ /* Adds a variable to symbol table. Because there is only one type in our language, a variable can be updated via set or defvar.*/
        int index = count;
        for(int i = 0; i < count; i++){ /* Finds the index of the variable if it exists on symbol table. If the variable does not exist on symbol table, adds it to the at the end of the symbol table. */
            if(strcmp(name, variableTable[i].name) == 0){
                index = i;
            }
        }
        variableTable[index].name = strdup(name);
        variableTable[index].line_number = line_number;
        variableTable[index].value = val;
        if(index == count)
            count++;
    }


    void printSymbolTable(){ /* Prints symbol table in pretty way. */
        printf("-----SYMBOL TABLE-----\n");
        printf("%s\t%s\t%s\n", "NAME", "LINE NO", "VALUE");
        for(int i = 0; i < count; i++){
            printf("%s\t%d\t%f\n", variableTable[i].name, variableTable[i].line_number, variableTable[i].value);
        }
    }


%}
%union{
    struct type{
        struct Node * node;
        float fval;
        char * name;
        int boolean;
    }type;
};
%token <type> ID VALUEF OP_PLUS OP_OP OP_CP OP_DIV OP_MINUS OP_MULT DEFF KW_NIL KW_WHILE KW_IF KW_LOAD KW_DISP KW_TRUE KW_FALSE DEFV OP_GT OP_SET OP_AND OP_OR OP_NOT OP_EQ OP_COMMA
%type <type> asg exp explist set_of_ids set_of_exps fcall function expb input
%%
start: /* start terminal continues with input and new line sign or input, new line sign or start. It was changed because it could parse only one line at one time. */
    input '\n' {} | 
    input '\n' start {} 
input: 
    | /* input can be empty if it is a comment. */
    function { /* input can be a function. */
        $$.node = createNode(NULL, $1.node, strdup("FUNCTION")); /* Creates a node with no siblings and function is child of it. */
        head = createNode(NULL, $$.node, strdup("INPUT"));
        printAST(head, 0); /* Prints the abstract syntax tree. */
        printSymbolTable(); /* Prints the symbol table. */
    }| 
    exp {
        $$.node = createNode(NULL, $1.node, strdup("EXPRESSION")); /* Creates a node with no siblings and exp is child of it. */
        head = createNode(NULL, $$.node, strdup("INPUT"));
        printAST(head, 0); /* Prints the abstract syntax tree. */
        printSymbolTable(); /* Prints the symbol table. */
    } |
    explist {
        $$.node = createNode(NULL, $1.node, strdup("EXPLIST")); /* Creates a node with no siblings and explist is child of it. */
        head = createNode(NULL, $$.node, strdup("INPUT"));
        printAST(head, 0); /* Prints the abstract syntax tree. */
        printSymbolTable(); /* Prints the symbol table. */
    }
asg: 
    OP_OP OP_SET ID exp OP_CP { /* Assignment continues with "(" "set" ID exp ")". */
        struct Node * temp8 = createNode(NULL, NULL, $5.name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp7 = createNode(NULL, NULL, $3.name); /* Creates a node for OP_ID with only its name. */
        struct Node * temp6 = createNode(NULL, NULL, $2.name); /* Creates a node for OP_SET with only its name. */
        struct Node * temp5 = createNode(NULL, NULL, $1.name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp4 = createNode(NULL, temp8, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling and temp8 is child of it. */
        struct Node * temp3 = createNode(temp4, $4.node, strdup("EXPRESSION")); /* Creates a node for exp with temp4 is sibling of it and result of the expression is child of it. */
        struct Node * temp2 = createNode(temp3, temp7, strdup("ID")); /* Creates a node for ID with temp3 is sibling of it and temp7 is child of it. */
        struct Node * temp1 = createNode(temp2, temp6, strdup("OP_SET")); /* Creates a node for OP_SET with temp2 is sibling of it and temp6 is child of it. */  
        $$.node = createNode(temp1, temp5, strdup("OP_OP")); /* Creates a node for OP_OP with temp1 is sibling of it and temp5 is child of it. */
        $$.fval = $4.fval; /* Returns the value of last expression. */
        printf("%s = %f\n", $3.name, $4.fval);
        addVariable($3.name, $4.fval); /* Adds the variable to the symbol table. */
    }
exp: 
    OP_OP OP_PLUS exp exp OP_CP {
        struct Node * temp7 = createNode(NULL, NULL, $5.name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp6 = createNode(NULL, NULL, $2.name); /* Creates a node for OP_PLUS with only its name. */
        struct Node * temp5 = createNode(NULL, NULL, $1.name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp4 = createNode(NULL, temp7, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling and temp7 is child of it. */
        struct Node * temp3 = createNode(temp4, $4.node, strdup("EXPRESSION")); /* Creates a node for exp with temp4 is sibling of it and result of the expression is child of it. */
        struct Node * temp2 = createNode(temp3, $3.node, strdup("EXPRESSION")); /* Creates a node for exp with temp3 is sibling of it and result of the expression is child of it. */
        struct Node * temp1 = createNode(temp2, temp6, strdup("OP_PLUS")); /* Creates a node for OP_PLUS with temp2 is sibling of it and temp6 is child of it. */
        $$.node = createNode(temp1, temp5, strdup("OP_OP")); /* Creates a node for OP_OP with temp1 is sibling of it and temp5 is child of it. */
        $$.fval = $4.fval; /* Returns the value of last expression. */
        printf("%f\n", $3.fval + $4.fval);
    } |
    OP_OP OP_MINUS exp exp OP_CP {
        struct Node * temp7 = createNode(NULL, NULL, $5.name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp6 = createNode(NULL, NULL, $2.name); /* Creates a node for OP_MINUS with only its name. */
        struct Node * temp5 = createNode(NULL, NULL, $1.name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp4 = createNode(NULL, temp7, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling and temp7 is child of it. */
        struct Node * temp3 = createNode(temp4, $4.node, strdup("EXPRESSION")); /* Creates a node for exp with temp4 is sibling of it and result of the expression is child of it. */
        struct Node * temp2 = createNode(temp3, $3.node, strdup("EXPRESSION")); /* Creates a node for exp with temp3 is sibling of it and result of the expression is child of it. */
        struct Node * temp1 = createNode(temp2, temp6, strdup("OP_MINUS")); /* Creates a node for OP_MINUS with temp2 is sibling of it and temp6 is child of it. */ 
        $$.node = createNode(temp1, temp5, strdup("OP_OP")); /* Creates a node for OP_OP with temp1 is sibling of it and temp5 is child of it. */
        $$.fval = $4.fval;  /* Returns the value of last expression. */
        printf("%f\n", $3.fval - $4.fval);
    } |
    OP_OP OP_MULT exp exp OP_CP {
        struct Node * temp7 = createNode(NULL, NULL, $5.name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp6 = createNode(NULL, NULL, $2.name); /* Creates a node for OP_MULT with only its name. */
        struct Node * temp5 = createNode(NULL, NULL, $1.name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp4 = createNode(NULL, temp7, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling and temp7 is child of it. */
        struct Node * temp3 = createNode(temp4, $4.node, strdup("EXPRESSION")); /* Creates a node for exp with temp4 is sibling of it and result of the expression is child of it. */
        struct Node * temp2 = createNode(temp3, $3.node, strdup("EXPRESSION")); /* Creates a node for exp with temp3 is sibling of it and result of the expression is child of it. */
        struct Node * temp1 = createNode(temp2, temp6, strdup("OP_MULT")); /* Creates a node for OP_MULT with temp2 is sibling of it and temp6 is child of it. */   
        $$.node = createNode(temp1, temp5, strdup("OP_OP")); /* Creates a node for OP_OP with temp1 is sibling of it and temp5 is child of it. */
        $$.fval = $4.fval;  /* Returns the value of last expression. */
        printf("%f\n", $3.fval * $4.fval);
    } | 
    OP_OP OP_DIV exp exp OP_CP {
        struct Node * temp7 = createNode(NULL, NULL, $5.name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp6 = createNode(NULL, NULL, $2.name); /* Creates a node for OP_DIV with only its name. */
        struct Node * temp5 = createNode(NULL, NULL, $1.name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp4 = createNode(NULL, temp7, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling and temp7 is child of it. */
        struct Node * temp3 = createNode(temp4, $4.node, strdup("EXPRESSION")); /* Creates a node for exp with temp4 is sibling of it and result of the expression is child of it. */
        struct Node * temp2 = createNode(temp3, $3.node, strdup("EXPRESSION")); /* Creates a node for exp with temp3 is sibling of it and result of the expression is child of it. */
        struct Node * temp1 = createNode(temp2, temp6, strdup("OP_DIV")); /* Creates a node for OP_DIV with temp2 is sibling of it and temp6 is child of it. */   
        $$.node = createNode(temp1, temp5, strdup("OP_OP")); /* Creates a node for OP_OP with temp1 is sibling of it and temp5 is child of it. */
        $$.fval = $4.fval;  /* Returns the value of last expression. */
        printf("%f\n", $3.fval / $4.fval);
    } |
    OP_OP DEFV ID exp OP_CP {
        struct Node * temp8 = createNode(NULL, NULL, $5.name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp7 = createNode(NULL, NULL, $3.name); /* Creates a node for ID with only its name. */
        struct Node * temp6 = createNode(NULL, NULL, $2.name); /* Creates a node for DEFV with only its name. */
        struct Node * temp5 = createNode(NULL, NULL, $1.name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp4 = createNode(NULL, temp8, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling and temp8 is child of it. */
        struct Node * temp3 = createNode(temp4, $4.node, strdup("EXPRESSION")); /* Creates a node for exp with temp5 is sibling of it and result of the expression is child of it. */
        struct Node * temp2 = createNode(temp3, temp7, strdup("ID")); /* Creates a node for ID with temp3 is sibling of it and temp7 is child of it. */
        struct Node * temp1 = createNode(temp2, temp6, strdup("DEFV")); /* Creates a node for DEFV with temp2 is sibling of it and temp6 is child of it. */ 
        $$.node = createNode(temp1, temp5, strdup("OP_OP")); /* Creates a node for OP_OP with temp1 is sibling of it and temp5 is child of it. */
        $$.fval = $4.fval;  /* Returns the value of last expression. */
        printf("%s = %f\n", $3.name, $4.fval);
        addVariable($3.name, $4.fval);
    } |
    OP_OP KW_IF expb explist explist OP_CP {
        struct Node * next; /* To decide next expression according to expb value. */
        struct Node * temp7 = createNode(NULL, NULL, $6.name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp6 = createNode(NULL, NULL, $2.name); /* Creates a node for KW_IF with only its name. */
        struct Node * temp5 = createNode(NULL, NULL, $1.name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp4 = createNode(NULL, temp7, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling and temp7 is child of it. */
        if($3.boolean == 0){ /* Creates the next node according to expb value. */
            next = createNode(temp4, $5.node, "EXPLIST");
        }
        else{
            next = createNode(temp4, $4.node, "EXPLIST");
        }
        struct Node * temp2 = createNode(next, $3.node, strdup("EXPB")); /* Creates a node for expb with next is sibling of it and result of the expb is child of it. */
        struct Node * temp1 = createNode(temp2, temp6, strdup("KW_IF")); /* Creates a node for KW_IF with temp2 is sibling of it and temp6 is child of it. */   
        $$.node = createNode(temp1, temp5, strdup("OP_OP")); /* Creates a node for OP_OP with temp1 is sibling of it and temp5 is child of it. */
        $$.fval = $5.fval;  /* Returns the value of last expression. */
    } |
    ID {
        struct Node * temp = createNode(NULL, NULL, $1.name); /* Creates a node for ID with only its name. */
        $$.node = createNode(NULL, temp, strdup("ID")); /* Creates a node for ID with no sibling and temp is child of it. */
        float value = lookupVariable($1.name); /* Gets value of the variable. */
        if(value == FLT_MAX){ /* If the variable is not declared before, prints an error. */
            char message[100];
            printf("The variable \"%s\" is not recognized!\n", $1.name);
            YYABORT;
        }
        $$.fval = value;  /* Returns the value of last expression. */
    }|
    VALUEF {
        char * valuef = (char *)malloc(100*sizeof(char)); 
        sprintf(valuef, "%f", $1.fval); /* Convert the float value to string. */
        struct Node * temp = createNode(NULL, NULL, valuef); /* Creates a node for VALUEF with only its name. */
        $$.node = createNode(NULL, temp, strdup("VALUEF")); /* Creates a node for VALUEF with no sibling and temp is child of it. */
        $$.fval = $1.fval;  /* Returns the value of last expression. */
    } |
    fcall {
        $$.node = createNode(NULL, $1.node, strdup("FCALL")); /* Creates a node for fcall with no sibling and result of the fcall is child of it. */
        $$.fval = $1.fval;  /* Returns the value of last expression. */
    } | 
    asg {
        $$.node = createNode(NULL, $1.node, strdup("ASSIGNMENT")); /* Creates a node for assignment with no sibling and result of the assignment is child of it. */
        $$.fval = $1.fval;  /* Returns the value of last expression. */
    } 
explist: 
    OP_OP explist OP_CP {
        struct Node * temp4 = createNode(NULL, NULL, $3.name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp3 = createNode(NULL, NULL, $1.name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp2 = createNode(NULL, temp4, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling of and temp4 is child of it. */
        struct Node * temp1 = createNode(temp2, $2.node, strdup("EXPLIST")); /* Creates a node for explist with temp2 is sibling of it and result of the explist is child of it. */
        $$.node = createNode(temp1, temp3, strdup("OP_OP"));  /* Creates a node for OP_OP with temp1 is sibling of it and temp3 is child of it. */
        $$.fval = $2.fval;
    } |
    OP_OP exp OP_CP {
        struct Node * temp4 = createNode(NULL, NULL, $3.name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp3 = createNode(NULL, NULL, $1.name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp2 = createNode(NULL, temp4, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling of and temp4 is child of it. */
        struct Node * temp1 = createNode(temp2, $2.node, strdup("EXPRESSION")); /* Creates a node for exp with temp2 is sibling of it and result of the expression is child of it. */
        $$.node = createNode(temp1, temp3, strdup("OP_OP")); /* Creates a node for OP_OP with temp1 is sibling of it and temp3 is child of it. */
        $$.fval = $2.fval;
    }
function: 
    OP_OP DEFF ID OP_OP set_of_ids OP_CP explist OP_CP {
        struct Node * temp13 = createNode(NULL, NULL, $8.name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp12 = createNode(NULL, NULL, $6.name); /* Creates a node for OP_CP with only its name. */ 
        struct Node * temp11 = createNode(NULL, NULL, $4.name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp10 = createNode(NULL, NULL, $3.name); /* Creates a node for ID with only its name. */
        struct Node * temp9 = createNode(NULL, NULL, $2.name); /* Creates a node for DEFF with only its name. */
        struct Node * temp8 = createNode(NULL, NULL, $1.name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp7 = createNode(NULL, temp13, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling of and temp13 is child of it. */
        struct Node * temp6 = createNode(temp7, $7.node, strdup("EXPLIST")); /* Creates a node for explist with temp7 is sibling of it and result of the explist is child of it. */
        struct Node * temp5 = createNode(temp6, temp12, strdup("OP_CP")); /* Creates a node for OP_CP with temp6 is sibling of it and temp12 is child of it. */
        struct Node * temp4 = createNode(temp5, $5.node, strdup("SETOFIDS")); /* Creates a node for set_of_ids with temp5 is sibling of it and result of the set_of_ids is child of it. */
        struct Node * temp3 = createNode(temp4, temp11, strdup("OP_OP")); /* Creates a node for OP_OP with temp4 is sibling of it and temp11 is child of it. */
        struct Node * temp2 = createNode(temp3, temp10, strdup("ID")); /* Creates a node for ID with temp3 is sibling of it and temp10 is child of it. */
        struct Node * temp1 = createNode(temp2, temp9, strdup("DEFF")); /* Creates a node for DEFF with temp2 is sibling of it and temp9 is child of it. */
        $$.node = createNode(temp1, temp8, strdup("OP_OP")); /* Creates a node for OP_OP with temp1 is sibling of it and temp8 is child of it. */
        $$.fval = 0.0;
    }
set_of_ids: 
    {}|
    ID {
        struct Node * temp = createNode(NULL, NULL, $1.name); /* Creates a node for ID with only its name. */
        $$.node = createNode(NULL, temp, strdup("ID")); /* Creates a node for ID with no sibling of and temp is child of it. */
    }|
    ID ID {
        struct Node * temp2 = createNode(NULL, NULL, $2.name); /* Creates a node for ID with only its name. */
        struct Node * temp1 = createNode(NULL, temp2, "ID"); /* Creates a node for ID with no sibling of and temp2 is child of it. */
        struct Node * temp = createNode(NULL, NULL, $1.name); /* Creates a node for ID with only its name. */
        $$.node = createNode(temp1, temp, strdup("ID")); /* Creates a node for ID with temp1 is sibling of it and temp is child of it. */
    }|
    ID ID ID {
        struct Node * temp4 = createNode(NULL, NULL, $3.name); /* Creates a node for ID with only its name. */
        struct Node * temp3 = createNode(NULL, temp4, "ID"); /* Creates a node for ID with no sibling of and temp4 is child of it. */
        struct Node * temp2 = createNode(NULL, NULL, $2.name); /* Creates a node for ID with only its name. */
        struct Node * temp1 = createNode(temp3, temp2, "ID"); /* Creates a node for ID with temp3 is sibling of it and temp2 is child of it. */
        struct Node * temp = createNode(NULL, NULL, $1.name); /* Creates a node for ID with only its name. */
        $$.node = createNode(temp1, temp, strdup("ID")); /* Creates a node for ID with temp1 is sibling of it and temp is child of it. */
    }
fcall: 
    OP_OP ID set_of_exps OP_CP {
        struct Node * temp6 = createNode(NULL, NULL, $4.name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp5 = createNode(NULL, NULL, $2.name); /* Creates a node for ID with only its name. */ 
        struct Node * temp4 = createNode(NULL, NULL, $1.name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp3 = createNode(NULL, temp6, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling of and temp6 is child of it. */
        struct Node * temp2 = createNode(temp3, $3.node, strdup("SETOFEXPRESSIONS")); /* Creates a node for set_of_expression with temp3 is sibling of it and result of the set_of_expression is child of it. */
        struct Node * temp1 = createNode(temp2, temp5, strdup("ID")); /* Creates a node for ID with temp2 is sibling of it and temp5 is child of it. */   
        $$.node = createNode(temp1, temp4, strdup("OP_OP")); /* Creates a node for OP_OP with temp1 is sibling of it and temp4 is child of it. */
        $$.fval = 0.0;
    }
set_of_exps: 
    exp {
        $$.node = createNode(NULL, $1.node, strdup("EXPRESSION")); /* Creates a node for exp with no sibling and result of the expression is child of it. */
    } |
    exp exp {
        struct Node * temp = createNode(NULL, $2.node, strdup("EXPRESSION")); /* Creates a node for exp with no sibling and result of the expression is child of it. */
        $$.node = createNode(temp, $1.node, strdup("EXPRESSION")); /* Creates a node for exp with temp is sibling of it and result of the expression is child of it. */
    } |
    exp exp exp {
        struct Node * temp1 = createNode(NULL, $3.node, strdup("EXPRESSION")); /* Creates a node for exp with no sibling and result of the expression is child of it. */
        struct Node * temp = createNode(temp1, $2.node, strdup("EXPRESSION")); /* Creates a node for exp with temp1 is sibling of it and result of the expression is child of it. */
        $$.node = createNode(temp, $1.node, strdup("EXPRESSION")); /* Creates a node for exp with temp1 is sibling of it and result of the expression is child of it. */
    }
expb:
    OP_OP OP_NOT expb OP_CP {
        struct Node * temp6 = createNode(NULL, NULL, $4.name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp5 = createNode(NULL, NULL, $2.name); /* Creates a node for OP_NOT with only its name. */
        struct Node * temp4 = createNode(NULL, NULL, $1.name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp3 = createNode(NULL, temp6, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling and temp6 is child of it. */
        struct Node * temp2 = createNode(temp3, $3.node, strdup("EXPB")); /* Creates a node for expb with temp3 is sibling of it and result of the expb is child of it. */
        struct Node * temp1 = createNode(temp2, temp5, strdup("OP_NOT")); /* Creates a node for OP_NOT with no sibling and temp5 is child of it. */    
        $$.node = createNode(temp1, temp4, strdup("OP_OP")); /* Creates a node for OP_OP with no sibling and temp4 is child of it. */
        $$.boolean = ($3.boolean == 1) ? 0: 1; /* If expb is 0 returns 1, otherwise returns 0. */
    } |
    OP_OP OP_OR expb expb OP_CP {
        struct Node * temp7 = createNode(NULL, NULL, $5.name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp6 = createNode(NULL, NULL, $2.name); /* Creates a node for OP_OR with only its name. */
        struct Node * temp5 = createNode(NULL, NULL, $1.name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp4 = createNode(NULL, temp7, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling and temp7 is child of it. */
        struct Node * temp3 = createNode(temp4, $4.node, strdup("EXPB")); /* Creates a node for expb with temp4 is sibling of it and result of the expb is child of it. */
        struct Node * temp2 = createNode(temp3, $3.node, strdup("EXPB")); /* Creates a node for expb with temp3 is sibling of it and result of the expb is child of it. */
        struct Node * temp1 = createNode(temp2, temp6, strdup("OP_OR")); /* Creates a node for OP_OR with no sibling and temp6 is child of it. */     
        $$.node = createNode(temp1, temp5, strdup("OP_OP")); /* Creates a node for OP_OP with no sibling and temp5 is child of it. */
        $$.boolean = ($3.boolean + $4.boolean < 1) ? 0: 1; /* If one of the expb1 and expb2 is 1 returns 1, otherwise returns 0. */
    } |
    OP_OP OP_AND expb expb OP_CP {
        struct Node * temp7 = createNode(NULL, NULL, $5.name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp6 = createNode(NULL, NULL, $2.name); /* Creates a node for OP_AND with only its name. */
        struct Node * temp5 = createNode(NULL, NULL, $1.name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp4 = createNode(NULL, temp7, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling and temp7 is child of it. */
        struct Node * temp3 = createNode(temp4, $4.node, strdup("EXPB")); /* Creates a node for expb with temp4 is sibling of it and result of the expb is child of it. */
        struct Node * temp2 = createNode(temp3, $3.node, strdup("EXPB")); /* Creates a node for expb with temp3 is sibling of it and result of the expb is child of it. */
        struct Node * temp1 = createNode(temp2, temp6, strdup("OP_AND")); /* Creates a node for OP_AND with no sibling and temp6 is child of it. */     
        $$.node = createNode(temp1, temp5, strdup("OP_OP")); /* Creates a node for OP_OP with no sibling and temp5 is child of it. */
        $$.boolean = ($3.boolean + $4.boolean == 2) ? 1: 0; /* If both expb1 and expb2 is 1 returns 1, otherwise returns 0. */
    } |
    OP_OP OP_GT exp exp OP_CP {
        struct Node * temp7 = createNode(NULL, NULL, $5.name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp6 = createNode(NULL, NULL, $2.name); /* Creates a node for OP_GT with only its name. */
        struct Node * temp5 = createNode(NULL, NULL, $1.name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp4 = createNode(NULL, temp7, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling and temp7 is child of it. */
        struct Node * temp3 = createNode(temp4, $4.node, strdup("EXPRESSION")); /* Creates a node for exp with temp4 is sibling of it and result of the expression is child of it. */
        struct Node * temp2 = createNode(temp3, $3.node, strdup("EXPRESSION")); /* Creates a node for exp with temp3 is sibling of it and result of the expression is child of it. */
        struct Node * temp1 = createNode(temp2, temp6, strdup("OP_GT")); /* Creates a node for OP_GT with no sibling and temp6 is child of it. */     
        $$.node = createNode(temp1, temp5, strdup("OP_OP")); /* Creates a node for OP_OP with no sibling and temp5 is child of it. */
        $$.boolean = ($3.fval > $4.fval) ? 1: 0; /* Compares exp1 and exp2, and returns 1 if exp1 is greater than exp2, otherwise returns 0. */
    } | 
    OP_OP OP_EQ exp exp OP_CP {
        struct Node * temp7 = createNode(NULL, NULL, $5.name); /* Creates a node for OP_CP with only its name. */
        struct Node * temp6 = createNode(NULL, NULL, $2.name); /* Creates a node for OP_EQ with only its name. */
        struct Node * temp5 = createNode(NULL, NULL, $1.name); /* Creates a node for OP_OP with only its name. */
        struct Node * temp4 = createNode(NULL, temp7, strdup("OP_CP")); /* Creates a node for OP_CP with no sibling and temp7 is child of it. */
        struct Node * temp3 = createNode(temp4, $4.node, strdup("EXPRESSION")); /* Creates a node for exp with temp4 is sibling of it and result of the expression is child of it. */
        struct Node * temp2 = createNode(temp3, $3.node, strdup("EXPRESSION")); /* Creates a node for exp with temp3 is sibling of it and result of the expression is child of it. */
        struct Node * temp1 = createNode(temp2, temp6, strdup("OP_EQ")); /* Creates a node for OP_EQ with no sibling and temp6 is child of it. */   
        $$.node = createNode(temp1, temp5, strdup("OP_OP")); /* Creates a node for OP_OP with no sibling and temp5 is child of it. */
        $$.boolean = ($3.fval == $4.fval) ? 1: 0; /* Compares exp1 and exp2, and returns 1 if they are equal, otherwise returns 0. */
    } |
    KW_TRUE {
        struct Node * temp = createNode(NULL, NULL, $1.name); /* Creates a node for KW_TRUE with only its name. */
        $$.node = createNode(NULL, temp, strdup("KW_TRUE")); /* Creates a node for KW_TRUE with no sibling and temp is child of it. */
        $$.boolean = 1; /* Returns 1. */
    } |
    KW_FALSE {
        struct Node * temp = createNode(NULL, NULL, $1.name); /* Creates a node for KW_FALSE with only its name. */
        $$.node = createNode(NULL, temp, strdup("KW_FALSE")); /* Creates a node for KW_FALSE with no sibling and temp is child of it. */
        $$.boolean = 0; /* Returns 0. */
    } 
%%

int main(int argc, char **argv){
    //yyin = fopen(argv[1], "r");
    yyparse();
}

void yyerror(char * message){
    printf("Syntax Error!\n");
}



