calc.y
%{
    #include<stdio.h>
%}
%token digit
%%

start:  E       { printf("%d\n", $1); }
        ;

E:  E'+'T      { $$ = $1 + $3; }
    | E'-'T    { $$ = $1 - $3; }
    | T               
    ;

T:  T'*'F      { $$ = $1 * $3; }
    | T'/'F    {  if($3) $$ = $1 / $3; 
                        else return yyerror("Divide by zero"); }           
    | F               
    ;

F:  '(' E ')'  { $$ = $2; }
    | digit    { $$ = $1; }
    ;
%%

int yyerror(char* s) {
    fprintf(stderr, "%s\n", s);
    return 0;
}

int main() {
    printf("Input the expression: ");
    yyparse();
}

calc.l
%{
    #include<stdio.h>
    #include "y.tab.h"
    extern int yylval;
%}

%%
[0-9]+ { 
    yylval = atoi(yytext);
    return digit;
}
[\t ]+  ;
.       return yytext[0];
\n      return 0;
%%

int yywrap() { 
    return 1; 
}
