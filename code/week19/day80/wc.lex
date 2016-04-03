%option noyywrap

%{
int chars = 0;
int words = 0;
int lines = 0;
%}

%%
[a-zA-Z]+	{ words++; chars += strlen(yytext); }
\n		{ chars++; lines++; }
.		{ chars++; }
%%

int main()
{
	yylex();
	printf("%6s %6s %6s\n", "lines", "wrods", "chars");
	printf("%6d %6d %6d\n", lines, words, chars);
}
