%{

int nbOpening = 0;
int nbClosing = 0;

%}

openingParenthesis [(]
closingParenthesis [)]


%%

{openingParenthesis} { ++nbOpening; }

{closingParenthesis} { ++nbClosing; }

. {;}

%%

int main()
{
	yylex();
	if ( nbOpening == nbClosing) 
	{
		printf("Les parenthèses ouverte sont toutes biens fermées\n");
	} else {
		if ( nbOpening	> nbClosing ){
			printf("Il manque %d parenthèses fermantes\n", nbOpening-nbClosing);
		} else {
			printf("Il manque %d parenthèses ouvrantes\n", nbClosing-nbOpening);
		}
	}
	return 0;
}
