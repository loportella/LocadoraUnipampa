#include <stdio.h>
#include "locadora.h"
#include <string.h>
#include <stdlib.h>
#include <windows.h>
void menu(int op){
	switch(op){
		case 1: locar(); break;
		case 2: entrega(); break;
		case 3: busca(); break;
		case 4: relatorios(); break;
	}
	
}
//função que limpara o console
void limpar(){
	system("cls");
}
//função de teste de arquivos no inicio do programa
void inicia_dados(){
//tenta abrir o arquivo beckup	
	FILE *b=fopen("files/backup.txt","r");
	if(!b){
/*se não tiver sucesso na abertura mostra esta mensagem que significa que
 o programa não teve seus dados alterados e salvos em um beckup*/	
//executa a configuração completa do arquivo "entrada"	
	converte();
	guardar();
	fclose(b);
	printf("BEM-VINDO !!\nPROGRAMA INICIADO PELA PRIMEIRA VEZ");
	}else{
/*se já exixte o arquivo beckup mostra mensagem dos dados recuperados
 e exclui o arquivo pesquisados, que pode ter ficado de outras aberturas do programa		*/
		fclose(b);
	unlink("files/dados.txt");
	rename("files/backup.txt","files/dados.txt");
	printf("BEM-VINDO !!\nDADOS RECUPERADOS");}
}
//função de conversão do arquivo "entrada.txt"
void converte(){
//cria uma pasta com a ajuda da biblioteca windows.h	
	CreateDirectory("files",NULL);
//abre dois arquivos lê entrada e escreve em provisorio
	FILE *t=fopen("entrada.txt","r");
	FILE *tx=fopen("provisorio.txt","w");
//exclui o arquivo pesquisados (para não haver pesquisas das outras execuções)	
	unlink("file/pesquisados.txt");
//variaveis: "i" sera o dado codigo no futuro	
	char a[200];float i=0;
//inicia a leitura		
	while(fgets(a,200,t)){
//não lê a linha 0 que vai conter o numero de titulos no acervo		
		if(i>0){
//escreve no arquivo "provisorio"
		fprintf(tx,"%.0f;%s",i,a);}i++;
//ficar mais facil a pesquisa pelos dados é o motivo de ter um ";" ente as variais
	}//fecha os arquivos
	fclose(t);fclose(tx);
}
//função que ira guardar os dados lidos de entrada e salvar como dados do tipo struct
void guardar(){
//variaveis a abertura dos arquivos
	FILE *t=fopen("provisorio.txt","r");
	FILE *tx=fopen("files/dados.txt","w");
	Filme f;
//i,j,n são variais de incrementação	
	int i,j,n;
//"b" sera importante para salvar os dados	
	char a[200];char b[99];
//r sera variavel onde sera incrementado o dado codigo	
	float r=1;
//lê o arquivo provisorio
	while(fgets(a,200,t)){
//inicializa a variavel j e n em zero toda vez que uma nova linha for iniciada
		j=0;n=0;
//for para obtenção das variaveis
//o for serve para andar caracter por caracter
		for(i=0;i<200;i++){
//pegara o primeiro dado da struct o "codigo"			
			if(j==0){
//ficara nesta parte enquanto o j=0 o caracter não for um ";"
				if(a[i]==';'){
//se achar o ";" o f.codigo recebera o r incrementado					
					f.codigo=r;
//além de incrementar o r,j,i,n					
					r++;j++,i++;n++;}
			}
//o segundo dado da "titulo"
		if(j==1){
			if(a[i]==';'){
//quando achar o ";" salvara toda a string b em f.titulo				
//além de incrementar j, o "i" sera incrementado para não dar prblema de pegar o ";" no proximo codigo
				strcpy(f.titulo,b);
				j++;i++;
			}
//caso não tenha encontrado o ";" ainda, sera rodado outro teste			
			else{
//n incrementado em 1
				if(n==1){
/*limpara a string b, incrementa n
o "i" sera decrementado pois preciso pegar este caracter que foi executado nesta funçao
e ser salvo na string com o uso do else*/					
					strcpy(b,"");i--;n++;
				}
//depois da string limpa e o caracter não for um ";" ele rodara				
				else{
/*tododo caracter diferente de ";" sera salvo em b
usa-se a função sprintf, pois strcat não junta vetor com caracter*/					
					sprintf(b,"%s%c",b,a[i]);
				}
			}
		}
//o terceiro dado "ano"		
		if(j==2){
			if(a[i]==';'){
//converte a string b em um inteiro para ser salvo em f.ano
//incrementa j e i				
				f.ano=atoi(b);j++;i++;
			}else{
				if(n==2){
					strcpy(b,"");i--;n++;
				}else{
//vai juntar todos os valores necessarios em b para depois ao fim converter corretamente					
					sprintf(b,"%s%c",b,a[i]);
				}
			}
		}
//quarto dado a "quantidade"		
		if(j==3){
			if(a[i]==';'){
				f.quantidade=atoi(b);j++;i++;
			}else{
				if(n==3){
					strcpy(b,"");i--;n++;
				}else{
					sprintf(b,"%s%c",b,a[i]);
				}
			}
		}
//quinto dado o "genero"		
		if(j==4){
//o if vai verificar se o caracter é igual a um enter ou "\0", assim tera o fim da coleta dos dados			
			if(a[i]=='\0'){
//iguala o "i" em 200 para terminar o for de uma vez sem gastar mais processamento				 
				strcpy(f.genero,b);j++;i=200;
			}else{
				if(n==4){
					strcpy(b,"");i--;n++;
				}else{
					sprintf(b,"%s%c",b,a[i]);
				}
			}
		}
 }
 //grava os dados salvos na struct filme "f" no arquivo dados
 fwrite(&f,sizeof(Filme),1,tx);
}//dados já convertidos para o arquivo dados. exclui provisorio
fclose(t);fclose(tx);
unlink("provisorio.txt");
unlink("files/pesquisados.txt");
}
//função de criação de um backup
void beckup(){
	limpar();
//o arquivo backup vai ser escrito com os dados que estaão em "dados"	
	FILE *b=fopen("files/backup.txt","w");
	FILE *t=fopen("files/dados.txt","r");
	Filme f;
	while(fread(&f,sizeof(Filme),1,t)){
		fwrite(&f,sizeof(Filme),1,b);
	}
	printf("Backup feito\n\a");
	fclose(b);fclose(t);
}
//cria um arquivo com as pesquisas realizadas
void arq_pesquisa(Filme f){
	FILE *p=fopen("files/pesquisados.txt","a");
		fwrite(&f,sizeof(Filme),1,p);
	fclose(p);	
}
