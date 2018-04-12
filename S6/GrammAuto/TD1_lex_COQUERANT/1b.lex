%{

#include <stdio.h>

%}


%%


^[ab]*a[ab]{4}$ {
        printf("1b");
}

%%

int main(){
        yylex();
}
 
