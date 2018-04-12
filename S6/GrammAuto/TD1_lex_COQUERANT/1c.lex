%{
int nbLine = 1;
int nbWord = 0;
int nbChar = 0;

%}

caract [^ \t\n]
newline \n

%%
{newline} { ++nbLine; ++nbChar; }

{caract}+ {
	nbChar+=yyleng; ++nbWord;
}
. 	 { ++nbChar; }


%%

int main(){
	yylex();
	printf("Lignes : %d; Mots : %d; Caractères : %d\n", nbLine, nbWord, nbChar);
}

