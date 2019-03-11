#include <stdio.h>
#include "locadora.h"
int main(int argc, char *argv[]) {
	int op;
	char a;
//inicia o programa com os dados	
	inicia_dados();
//mostra o menu para o usuario	
	do{
	printf("\nMENU PRINCIPAL:\n1-Locação\n2-Entrega\n3-Buscar filme(s)\n4-Relatorios\n0-Fechar ");
	scanf("%d",&op);
	menu(op);
	limpar();
//caso o usuario queria fechar o programa é dada a opição de fazer um backup	
	if(op==0){
		printf("Deseja fazer um backup? (S/N) ");
		scanf("%s",&a);
		if(a=='s'||a=='S'){
			beckup();
			printf("PROGRAMA FECHADO:\n");
		}else{
			printf("TUDO BEM:\nPROGRAMA FECHADO:\n");
		}
	}
	}while(op!=0);
	
	system("pause");
	return 0;
}
