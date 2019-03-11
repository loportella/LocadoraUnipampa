#include <stdio.h>
#include "locadora.h"
#include <string.h>
#include <stdlib.h>
//locação de um filme
void locar(){
	limpar();
//inicia os dados necessários	
	FILE *t=fopen("files/dados.txt","r");
	FILE *tx=fopen("files/d.txt","w");
	Filme f;
	float cod;char ch;
printf("LOCAÇÃO:\n");
do{
printf("CODIGO DO FILME: ");
	scanf("%f",&cod);
//procurar o codigo informado	
	if(cod>0&&cod<=41){
	while(fread(&f,sizeof(Filme),1,t)){
/*invariavelmente do que acontecer os dados lidos de dados serão escritos em d
para depois serem escritos em dados novamente, com valores alterados se algo foi alterado*/		
		if(cod==f.codigo){
			if(f.quantidade<=0){
//se a quantidade for zero faz nada, mas mostra uma mensagem				
				printf("Não há copias disponiveis\n");
				fwrite(&f,sizeof(Filme),1,tx);
			}else{
printf("ANTES:\n ");
//mostra o dado antes de ser locado e decrementa f.qantidade
printf("Codigo: %.0f\nTitulo: %s\nQuantidade: %d\nAno: %d\nGenero: %s\n",f.codigo,f.titulo,f.quantidade,f.ano,f.genero);
				f.quantidade--;
				fwrite(&f,sizeof(Filme),1,tx);			}
		}
		else{
//salva os dados dieferente do codigo			
			fwrite(&f,sizeof(Filme),1,tx);
		}
	}
	fclose(t);fclose(tx);
//por fim mostra os dados atualizados e salva os dados atualizados de "d" no arquivo "dados"	
	t=fopen("files/d.txt","r");
	while(fread(&f,sizeof(Filme),1,t)){
		if(cod==f.codigo){
printf("ATUALIZADO:\n");
printf("Codigo: %.0f\nTitulo: %s\nQuantidade: %d\nAno: %d\nGenero: %s\n",f.codigo,f.titulo,f.quantidade,f.ano,f.genero);
		}
	}fclose(t);
//exclui o arquivo "dados", para substituir pelo arquvo "d"	
	unlink("files/dados.txt");
	rename("files/d.txt","files/dados.txt");
	}
//caso o codigo informado seja invalido, sera mostrada esta mensagem
	else{
		printf("codigo invalido\n");
	}
//~pergunta se vai continuar executando esta função	
	printf("Deseja alugar mais um filme? (S/N) ");
	scanf("%s",&ch);
}while(ch=='s'||ch=='S');
}
//entregar algum filme
void entrega(){
	limpar();
	FILE *t=fopen("files/dados.txt","r");
	FILE *tx=fopen("files/d.txt","w");
	Filme f;
	float cod;char ch;
printf("ENTREGA:\n");
do{
printf("CODIGO DO FILME: ");
	scanf("%f",&cod);
	if(cod>0&&cod<=41){
	while(fread(&f,sizeof(Filme),1,t)){
		if(cod==f.codigo){	
//se achar o codigo mostra uma mensagem dos dados desatualizados e soma um ao dado f.quantidade
printf("ANTES:\n");
printf("Codigo: %.0f\nTitulo: %s\nQuantidade: %d\nAno: %d\nGenero: %s\n",f.codigo,f.titulo,f.quantidade,f.ano,f.genero);
				f.quantidade++;
				fwrite(&f,sizeof(Filme),1,tx);
			}
		else{
			fwrite(&f,sizeof(Filme),1,tx);
		}
	}
	fclose(t);fclose(tx);
	t=fopen("files/d.txt","r");
	while(fread(&f,sizeof(Filme),1,t)){
		if(cod==f.codigo){
printf("ATUALIZADO;\n");
printf("Codigo: %.0f\nTitulo: %s\nQuantidade: %d\nAno: %d\nGenero: %s\n",f.codigo,f.titulo,f.quantidade,f.ano,f.genero);
		}
	}fclose(t);
	unlink("files/dados.txt");
	rename("files/d.txt","files/dados.txt");
	}else{
		printf("codigo invalido\n");
	}
	printf("Há mais filmes para entregar? (S/N) ");
	scanf("%s",&ch);
}while(ch=='s'||ch=='S');
}
//buscar pelo acervo ou dentro do acervo
void busca(){
	limpar();
	int op,o; char ch;
	printf("PESQUISA:\n");
do{
	printf("1-Ver todo o acervo\n2-Procurar algun(s) titulo expecifico ");
	scanf("%d",&op);
	printf("\n");
	switch(op){
		case 1:
		printf("ACERVO COMPLETO:\n");
		//entra na função acervo
		acerrvo();break;
		case 2:
//pega uma opção para a pesquisa especifica e entra na função de procura do titulo			
			printf("Forma de pesquisa:\n");
			printf("1-Codigo:\n2-Titulo:\n3-Ano:\n4-Genero: ");
			scanf("%d",&o);
			busca_titulo(o);
			break;
		default: printf("OPIÇÃO INVALIDA! ");break;
	}
printf("Deseja continuar a busca? (S/N) ");
scanf("%s",&ch);
limpar();
}while(ch=='s'||ch=='S');
}
//mostra o acervo completo
void acerrvo(){
	Filme f;
	FILE *t=fopen("files/dados.txt","r");
	while(fread(&f,sizeof(Filme),1,t)){
printf("Codigo: %.0f\nTitulo: %s\nQuantidade: %d\nAno: %d\nGenero: %s\n",f.codigo,f.titulo,f.quantidade,f.ano,f.genero);		
	}fclose(t);
}
//mostra um titulo especifico segundo o pedido na função busca
void busca_titulo(int op){
FILE *t=fopen("files/dados.txt","r");	
Filme f;
//variavel "tam" serve para salvar valor e "s" de comparação
int tam,ano,s=1; float cod;
//"gem" serve como memoria
char gen[10],nome[100],genero[10];
	switch(op){
		case 1:
//escolha por codigo			
			printf("Digite o Codigo: "); scanf("%f",&cod);
			if(cod>0||cod<=41){
			while(fread(&f,sizeof(Filme),1,t)){
		if(cod==f.codigo){	
//mostra os dados com aquele codigo
printf("Codigo: %.0f\nTitulo: %s\nQuantidade: %d\nAno: %d\nGenero: %s\n",f.codigo,f.titulo,f.quantidade,f.ano,f.genero);		
//toda pesquisa concluida com sucesso tera os dados salvos em um arquivo	
	arq_pesquisa(f);
			}		
			}
	}else{
		printf("Não há filmes com este codigo\n");}break;
	case 2:
//busca por titulo		
		printf("Digite o titulo: ");
		fflush(stdin);	gets(nome); 
//a strupr converte toda a variavel nome em letras maiusculas, assim facilitando a pesquisa pelo dado no arquivo		
		strcpy(nome,strupr(nome));
		while(fread(&f,sizeof(Filme),1,t)){
//testa se as strings são iguais			
			if(strcmp(nome,f.titulo)==0){
	printf("Codigo: %.0f\nTitulo: %s\nQuantidade: %d\nAno: %d\nGenero: %s\n",f.codigo,f.titulo,f.quantidade,f.ano,f.genero);		
			arq_pesquisa(f);			
//se houver sucesso na pesquisa "S" fica com zero			
			s=0;}
}if(s!=0){
//mostra esta mensagem se a busca não achou nada
printf("Não há filmes com este nome\n");
}
	break;
	case 3:
//pesquisa pelo ano
printf("Digite o ano: ");	scanf("%d",&ano);
			while(fread(&f,sizeof(Filme),1,t)){
		if(ano==f.ano){	
printf("Codigo: %.0f\nTitulo: %s\nQuantidade: %d\nAno: %d\nGenero: %s\n",f.codigo,f.titulo,f.quantidade,f.ano,f.genero);		
arq_pesquisa(f);
		s=0;}		
			}
	if(s!=0){
		printf("Não há filmes deste ano\n");}
		break;
	case 4:
//busca por genero		
		printf("Didite o genero: ");
		fflush(stdin);	gets(genero); 
		strcpy(genero,strupr(genero));
		while(fread(&f,sizeof(Filme),1,t)){
//salva o dado f.genero em "gen" pois este dado contem o enter no seu final
			strcpy(gen,f.genero);
//remove o enter da string f.genero, assim facilitando a comparação com o dado digitado
			tam=strlen(f.genero); f.genero[--tam]=0;			
			if(strcmp(genero,f.genero)==0){
//o f.genero volta a receber o seu valor original. ajudando no salvamento dos dados no arquivo de pesquisa e impresão na tela
	strcpy(f.genero,gen);
printf("Codigo: %.0f\nTitulo: %s\nQuantidade: %d\nAno: %d\nGenero: %s\n",f.codigo,f.titulo,f.quantidade,f.ano,f.genero);		
	arq_pesquisa(f);
		s=0;}
}if(s!=0){
printf("Não há filmes deste genero\n");
}		break;
}fclose(t);
}
//mostra os dados das pesquisas
void pesquisas(){
	FILE *t=fopen("files/pesquisados.txt","r");
//teste para ver se o arquivo existe
if(!t){
	printf("Não foi feita nenhuma pesquisa\n");
}else{
	Filme f;
	int o,tam,ano,i=0;
	char gen[10],ch;
	fflush(stdin);
	printf("PESQUISAS:\n1-Ano\t2-Genero: ");
	scanf("%d",&o);
	fflush(stdin);
	switch(o){
case 1:
	printf("Ano: "); scanf("%d",&ano);
	while(fread(&f,sizeof(Filme),1,t)){
	if(f.ano==ano)	{i++;
printf("Codigo: %.0f\nTitulo: %s\nQuantidade: %d\nAno: %d\nGenero: %s\n",f.codigo,f.titulo,f.quantidade,f.ano,f.genero);		
	}
	}if(i==0){printf("Nada encontrado\n");
	}
	break;
case 2:
	printf("Genero: ");fflush(stdin); gets(gen);
	strcpy(gen,strupr(gen));
	while(fread(&f,sizeof(Filme),1,t)){
	tam=strlen(f.genero); f.genero[--tam]=0;			
	if(strcmp(gen,f.genero)==0)	{i++;
printf("Codigo: %.0f\nTitulo: %s\nQuantidade: %d\nAno: %d\nGenero: %s\n",f.codigo,f.titulo,f.quantidade,f.ano,f.genero);		
}
	}if(i==0){printf("Nada encontrado\n");
	}
	break;
}
}
}
//mostra as pesquisas ou cria um beckup
void relatorios(){
	limpar();
	int o;char ch;
do{
	printf("RELATORIOS:\n1-Pesquisas\t2-Criar Backup: ");
	scanf("%d",&o);
	switch(o){
		fflus(stdin);
		case 1: pesquisas();break;
		case 2: beckup();break;
	}
printf("Deseja continuar no menu relatorios? (S/N) ");
scanf("%s",&ch);
limpar();
}while(ch=='s'||ch=='S');
}
