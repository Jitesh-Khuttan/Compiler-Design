%{
	#include<stdio.h>
	int n;
%}

%%

\n		++n;

("/*")([a-z | A-Z | 0-9])*("*/")	

("main")|("int")|("scanf")|("printf")|("if")|("else")|("float")|("else")|("while")|("for")|("char") printf("%s is a keyword\n",yytext);

"("|")"|"{"|"}"|"="|"+"|"-"|"*"|"%"|"/"]	printf("%s is an operator\n",yytext);


[a-zA-Z]*	printf("%s is a  word\n", yytext);

[,| " " ]	printf("%s is a seperator\n",yytext);

digit[0-9]*  printf("%s is a number\n",yytext);

%%

int main()
{
	yylex();
	printf("\n %d is the number of new lines ", n);
	return 0;
}

int yywrap()
{
	return 1;
}

