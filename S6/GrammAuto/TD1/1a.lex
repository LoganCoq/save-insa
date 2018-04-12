%{

#include <stdio.h>
%}

L [ab]

%%

\. {
	printf("[point]");
}

@ {
	printf("[at]");
}

\- {
	printf("[tiret]");
}


%% 

int main(){
	yylex();
}
