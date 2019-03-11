/*estrutura filme com a alteração do dado codigo para float
pois estava dando conflito a logica do meu codigo com uma variavel int*/
struct filme{
	float codigo;
	char titulo[100];
	int ano;
	int quantidade;
	char genero[10];
};typedef struct filme Filme;
//funções
void menu(int op);
void converte();
void guardar();
void acerrvo();
void locar();
void entrega();
void busca();
void busca_titulo(int op);
void beckup();
void arq_pesquisa(Filme f);
void pesquisas();
void relatorios();
void limpar();
void inicia_dados();

//foram muitos erros linguisticos =)
