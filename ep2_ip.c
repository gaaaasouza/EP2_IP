#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define true 1
#define false 0
#define TAM 150
#define TAMNOMES 200

#define COMPUTACAO 0
#define LITERATURA 1
#define CIENCIAS 2
#define ARTES 3
#define GERAL 4

typedef int bool;

typedef struct{
	char nome [TAMNOMES];
	char primeiro_autor [TAMNOMES];
	char demais_autores [TAMNOMES];
	bool emprestado;
	int noEmprestimos;
  char nomeDoEmprestador [TAMNOMES];
	char editora [TAMNOMES];
	int area;
	int anopub;
} Livro;


typedef struct{
	Livro * livros[TAM];
	int posLivre;
} Biblioteca;



/********************** FUNCOES PARA CRIAR LIVROS ******/


/* Funcao para a criacao de um novo Livro.
   A funcao preenche todos os valores de seus campos e retorna esse novo Livro.
*/
Livro * novoLivro(char* nome, char * nAutorPrin, char * nOutrosAutores, char * emprestador, int nArea,
	char *  nEditora, int nAnoPub){
  //printf("Parametros: %s, %s, %s, %s, %d, %s, %d\n", nome, nAutorPrin, nOutrosAutores, emprestador, nArea, nEditora, nAnoPub);
	Livro * novo = (Livro *) malloc(sizeof(Livro));

	if (novo == NULL)
	   return NULL; // Nao consegui alocar memoria para o registro Livro. Vou cair fora!

	strncpy(novo->nome,nome,TAMNOMES-1);
	strncpy(novo->primeiro_autor,nAutorPrin,TAMNOMES-1);
  strncpy(novo->demais_autores,nOutrosAutores,TAMNOMES-1);

	novo->emprestado = false;
  novo->noEmprestimos = 0;

	strncpy(novo->nomeDoEmprestador,emprestador,TAMNOMES-1);
	strncpy(novo->editora,nEditora,TAMNOMES-1);

	novo->area = nArea;
	novo->anopub = nAnoPub;

	return novo;
}

/********************** FUNCOES DOS alunos *********************************/

/* Funcao para imprimir informacoes  sobre o livro l1 (passado como parametro)
Veja na descricao do EP2 como essas informacoes devem ser impressas
*/
void imprimirDados(Livro * l1){
  /* Insira seu codigo aqui! */

	printf("Nome: %s\n", l1->nome);
	printf("Autor: %s\n", l1->primeiro_autor);

		if(l1->demais_autores[0] == '\0'){
		printf("Autores secundarios: nao ha\n");
		}
		else{
			printf("Autores secundarios: %s\n", l1->demais_autores);
		}

	printf("Editora: %s\n", l1->editora);
	
	switch (l1->area)
	{
		case 0:
		printf("Area: computacao\n");
		break;
		case 1:
		printf("Area: literatura\n");
		break;
		case 2:
		printf("Area: ciencias\n");
		break;
		case 3:
		printf("Area: artes\n");
		break;
		case 4:
		printf("Area: geral\n");
		break;
		default:
		break;
	}

	printf("Ano publicacao: %d\n", l1->anopub);
	printf("Numero de emprestimos: %d\n", l1->noEmprestimos);
	
	switch (l1->emprestado)
	{
		case 0:
		printf("Emprestado? Nao\n");
		break;
		case 1:
		printf("Emprestado? Sim\n");
		break;
		default:
		break;
	}


}

/*
A funcao abaixo recebe como parametro um ponteiro para a biblioteca e ordena-a por
numero de emprestimos.
*/

void ordenaBibliotecaPorNumeroEmprestimos(Biblioteca * bib)
{
  /* Insira seu codigo aqui! */

	int ultimo, i;
	Livro * aux;

	for (ultimo = bib->posLivre - 1; ultimo >= 0; ultimo--){
		for (i=0; i < ultimo; i++){
			if (bib->livros[i]->noEmprestimos < bib->					livros[i+1]->noEmprestimos) {
				aux = bib->livros[i];
				bib->livros[i] = bib->livros[i+1];
				bib->livros[i+1] = aux;
			}
		}
	}

}
/*
A funcao abaixo recebe como parametro um ponteiro para a biblioteca e ordena-a por
nome do livro em ordem lexicografica.
*/

void ordenaBibliotecaNomeLivro(Biblioteca * bib)
{
  /* Insira seu codigo aqui! */

	Livro * aux;
	int i, j, k;
  
  		for(i = 0; i < bib->posLivre; i++){
	  		for(j = i + 1; j < bib->posLivre; j++){
				k = strcmp(bib->livros[i]->nome, bib->livros[j]->nome);   
					if(k > 0){
					aux = bib->livros[i];
					bib->livros[i] = bib->livros[j];
                			bib->livros[j] = aux;
            			}
			}
		}


}

/*
A funcao abaixo busca um livro na biblioteca pelo nome do livro. Ela retorna
o ponteiro para o livro, se existir, e NULL, se nao existir, na biblioteca.
*/

Livro * buscaLivro(Biblioteca * bib, char * nNomeLivro)
{
  /* Insira seu codigo aqui! */


	int i, j;

	for(i = 0;i < bib->posLivre; i++){
		j = strcmp(bib->livros[i]->nome, nNomeLivro);
			if(j == 0){
				return bib->livros[i];
			}
		
	}

	return NULL;

}

/*
A funcao abaixo insere um livro na biblioteca. Ela recebe como parametros os
ponteiros para a biblioteca e o livro. O livro deve ser criado antes. Se a
biblioteca ja estiver lotada, deve ser seguida especificacao contida na
descricao do EP2 para tratar essa situacao.
*/

void insereLivro(Biblioteca *  bib, Livro * l)
{
  /* Insira seu codigo aqui! */



  if(bib->posLivre < TAM){
		bib->livros[bib->posLivre] = l;
		bib->posLivre = bib->posLivre + 1;
  }
	if(bib->posLivre < 0){
		    printf("PosLivre tem que ser um numero positivo\n");
	}
		if(bib->posLivre >= TAM){
							ordenaBibliotecaPorNumeroEmprestimos(bib);
			for(int i = TAM - 1; i >= 0; i--){
				if(bib->livros[i]->emprestado == false){
					bib->livros[i] = l;
              			break;
              		}
			  			if(i == 0 && bib->livros[i]->emprestado == true){
							printf("Todos os livros estao emprestados, nao e possivel inserir o livro\n");
						}
            				
          
          			}
        
      		}        

}

/*
A fun��o emprestaLivro procura o livro pelo nome na biblioteca e empresta
para o nEmprestador. A fun��o retorna o ponteiro para o livro emprestador
se existir; caso contr�rio, volta NULL. A funcao retorna NULL tambem se
o livro ja estiver emprestado. Uma vez emprestado o livro,  seu campo
emprestado deve ser igual a true e seu campo noEmprestimos deve ser incrementado.
*/

Livro * emprestaLivro(Biblioteca * bib, char * nNomeLivro, char * nEmprestador)
{
  /* Insira seu codigo aqui! */
	
	Livro * l = buscaLivro(bib, nNomeLivro);
	if(l == NULL){
		return NULL;
	}
		if(l->emprestado == true){
		return NULL;
		}
			else{
			strncpy(l->nomeDoEmprestador,nEmprestador,TAMNOMES-1);
			l->noEmprestimos = l->noEmprestimos + 1;
	 		l->emprestado = true;
			}	
			return l;

}

/*
A fun��o devolveLivro procura o livro pelo nome na biblioteca e atualiza
o nEmprestador com o string "" e o campo emprestado com false.
A fun��o retorna o ponteiro para o livro devolvido
se existir; caso contr�rio, volta NULL. A funcao nao altera o
valor do campo  noEmprestimos.
*/

Livro * devolveLivro(Biblioteca * bib, char * nNomeLivro)
{
 /* Insira seu codigo aqui! */

Livro * l = buscaLivro(bib, nNomeLivro);
	
	if(l == NULL){
		return NULL;
	}
		if(l->emprestado == false){
			printf("O livro encontra-se na bilioteca.\n");
			return NULL;
		}
			else{
				strncpy(l->nomeDoEmprestador,"",TAMNOMES-1);
	 			l->emprestado = false;
				return l;
			}

}

/*
 Esta funcao devolve o numero de livros na biblioteca
*/

int tamanho(Biblioteca * bib)
{
	
	int total = 0;

		for(int i = 0; i < bib->posLivre; i++){
			if(bib->livros[i])
			total = total + 1;
		}
	
return total;


}

/*
Esta funcao imprime o conteudo da biblioteca ordenada por numero de noEmprestimos
de cada livro. Os mais emprestados primeiro.
*/

void imprimeBibliotecaPorNumeroEmprestimos(Biblioteca * bib)
{
/* Insira seu codigo aqui! */

ordenaBibliotecaPorNumeroEmprestimos(bib);

		for(int i = 0; i < bib->posLivre; i++){
			imprimirDados(bib->livros[i]);
			printf("\n\n");
		}

}

/*
Esta funcao imprime o conteudo da biblioteca ordenada pelo nome de cada livro em
ordem lexicografica.
*/
void imprimirBibliotecaOrdenadaNomeLivro(Biblioteca * bib)
{
/* Insira seu codigo aqui! */

	ordenaBibliotecaNomeLivro(bib);

		for(int i = 0; i < bib->posLivre; i++){
			imprimirDados(bib->livros[i]);
			printf("\n");
			printf("\n");
		}


}

int main(){
	int i;
	int noErros = 0;
	Livro * l1, * l2, * l3, * l4, * l5, * l6, * l7;
	printf("ATENCAO: Nem todas as caracteristicas do enunciado sao testadas neste exemplo.\n");
	printf("         Cabe a cada aluno(a) testar cuidadosamente seu EP.\n\n");


	printf("*** Criando Biblioteca **************************************\n");
  Biblioteca biblioteca;
  biblioteca.posLivre=0; // Nao se esqueca de iniciar o campo posLivre com zero!
  
  // Fazendo apontar os elementos do array biblioteca.livros para NULL

  for (i=0; i< TAM; ++i)
     biblioteca.livros[i] = NULL;

  printf("==> Teste insercao de livros:\n");
  l1 = novoLivro("The great gatsby", "Scott Fitzgerald", "Mathew j. Bruccoli", "",LITERATURA,"Collier books",1991);
	insereLivro(&biblioteca,l1);

	if(!(l1 != NULL && strcmp(l1->nome,"The great gatsby") == 0 &&
			strcmp(l1->primeiro_autor,"Scott Fitzgerald") == 0  &&
			strcmp(l1->demais_autores,"Mathew j. Bruccoli") == 0 &&
			l1->area == LITERATURA &&
			strcmp(l1->editora,"Collier books") == 0 &&
			l1->anopub == 1991 &&
			l1->emprestado == false))
	{
		printf("==> Erro: Insercao de livro com problema\n");
		imprimirDados(l1);
		noErros++;
	}

	l1 = novoLivro("No Caminho de Swann", "Marcel Proust", "", "",LITERATURA,"Ediouro",1993);

	if(!(l1 != NULL && strcmp(l1->nome,"No Caminho de Swann") == 0 &&
			strcmp(l1->primeiro_autor,"Marcel Proust") == 0 &&
			strcmp(l1->demais_autores,"") == 0 &&
			l1->area == LITERATURA &&
			strcmp(l1->editora,"Ediouro") == 0 &&
			l1->anopub == 1993 &&
			l1->emprestado == false))
	{
		printf("==> Erro: Insercao de livro com problema\n");
		imprimirDados(l1);
		noErros++;
	}

	l2 = novoLivro("� Sobra das Mo�as em Flor", "Marcel Proust", "", "",LITERATURA,"Ediouro",1993);
	l3 = novoLivro("O Caminho de Guermantes", "Marcel Proust", "", "",LITERATURA,"Ediouro",1993);
	l4 = novoLivro("Sodoma e Gomorra", "Marcel Proust", "", "",LITERATURA,"Ediouro",1993);
	l5 = novoLivro("A Prisioneira", "Marcel Proust", "", "",LITERATURA,"Ediouro",1993);
	l6 = novoLivro("Albertine Desaparecida", "Marcel Proust", "", "",LITERATURA,"Ediouro",1993);
	l7 = novoLivro("O Tempo Reencontrado", "Marcel Proust", "", "",LITERATURA,"Ediouro",1993);

  insereLivro(&biblioteca,l1);
  insereLivro(&biblioteca,l2);
  insereLivro(&biblioteca,l3);
  insereLivro(&biblioteca,l4);
  insereLivro(&biblioteca,l5);
  insereLivro(&biblioteca,l6);
  insereLivro(&biblioteca,l7);

  l1 = novoLivro("O mundo assombrado pelos demonios","Carl Sagan","","",CIENCIAS,"Companhia da Letras",1995);
  insereLivro(&biblioteca,l1);
  l1 = novoLivro("Armas, germes...","Jared Diamond","","",CIENCIAS,"Record",1997);
  insereLivro(&biblioteca,l1);
  l1 = novoLivro("O codigo da vinci","Dan Brown","","",CIENCIAS,"Sextante",2004);
  insereLivro(&biblioteca,l1);
  l1 = novoLivro("A noite escura e mais eu","Lygia Fagundes Telles","","",LITERATURA,"Nova Fronteira",1995);
  insereLivro(&biblioteca,l1);
  l1 = novoLivro("Guerra e Paz", "Leon Tolstoy","","",LITERATURA,"Ediouro",1993);
  insereLivro(&biblioteca,l1);
  l1 = novoLivro("O apanhador no campo de centeio","Jerome David Salinger","","",LITERATURA,"Editora do Autor",1945);
	insereLivro(&biblioteca,l1);

	printf("==> Teste tamanho biblioteca\n");

	if(tamanho(&biblioteca) != 14)
	{
		printf("==> Erro: no tamanho da biblioteca\n");
		noErros++;
	}

	printf("==> Teste busca de livro inexistente no acervo\n");

	l1 = buscaLivro(&biblioteca,"The code breaker");
	if (l1 != NULL)
	 {
		 printf("==> Erro: busca de livro inexistente com problema\n");
		 noErros++;
	 }
	 printf("==> Teste busca de livro existente no acervo\n");

   l1 = buscaLivro(&biblioteca,"A noite escura e mais eu");

	 if(l1 != NULL) {
		 if (strcmp(l1->nome,"A noite escura e mais eu"))
	    {
	      printf("==> Erro: busca de livro existente com problema\n");
	      noErros++;
	    }
	 }
	 else
	 {
		 printf("==> Erro: busca de livro existente com problema\n");
		 noErros++;
	 }

	printf("==> Teste emprestimo de livro do acervo\n");
	l1 = emprestaLivro(&biblioteca,"O Tempo Reencontrado", "John Le Carre");

	if(l1 != NULL) {
		if (strcmp(l1->nomeDoEmprestador,"John Le Carre") || l1->emprestado == false)
		 {
			 printf("==> Erro: emprestimo de livro existente com problema\n");
			 noErros++;
		 }
	}
	else
	{
		printf("==> Erro: nao encontrei o livro a ser emprestado\n");
		noErros++;
	}

	printf("==> Teste devolucao de livro acervo\n");

	l1 = devolveLivro(&biblioteca,"O Tempo Reencontrado");

	if(l1 != NULL) {
		if (strcmp(l1->nomeDoEmprestador,"") || l1->emprestado == true || l1->noEmprestimos <= 0)
		 {
			 printf("==> Erro: devolucao de livro existente com problema\n");
			 noErros++;
		 }
	 }
	else
	{
		printf("==> Erro: nao encontrei o livro a ser devolvido\n");
		noErros++;
	}

	l1 = devolveLivro(&biblioteca,"Fake book");
	if(l1 != NULL) {
		printf("==> Erro:  encontrei um livro que n�o foi existe na biblioteca, logo nao pode ser devolvido\n");
		noErros++;
	}

	// Teste relatorios

	printf("==> Teste ordenacao acervo\n");

  ordenaBibliotecaNomeLivro(&biblioteca);
	printf("===> Ordenado por nome do livro:\n");

  l1 = biblioteca.livros[0]; // Peguei o primeiro elemento da biblioteca ordenada por Nome do Livro

  imprimirDados(l1);

	if(!(	l1 != NULL &&
		  strcmp(l1->nome,"A Prisioneira") == 0 &&
			strcmp(l1->primeiro_autor,"Marcel Proust")  == 0 &&
			strcmp(l1->demais_autores,"")  == 0 &&
			l1->area == LITERATURA &&
			strcmp(l1->editora,"Ediouro") == 0 &&
			l1->anopub == 1993 &&
			l1->emprestado == false))
	{
		printf("==> Erro: Ordenacao por nome de livro com problema\n");
		noErros++;
	}

	l1 = biblioteca.livros[1]; // Peguei o segundo elemento da biblioteca ordenada por Nome do Livro
  imprimirDados(l1);
	if(!(l1 != NULL &&
		  strcmp(l1->nome,"A noite escura e mais eu") == 0 &&
			strcmp(l1->primeiro_autor,"Lygia Fagundes Telles") == 0 &&
		  strcmp(l1->demais_autores,"") == 0 &&
			l1->area == LITERATURA &&
			strcmp(l1->editora,"Nova Fronteira") == 0 &&
			l1->anopub == 1995 &&
			l1->emprestado == false))
	{
		printf("==> Erro: Ordenacao por nome de livro com problema\n");
		noErros++;
	}

	printf("===> Ordenado por frequencia:\n");
	emprestaLivro(&biblioteca,"O Tempo Reencontrado", "Gabi Gol");
	emprestaLivro(&biblioteca,"O apanhador no campo de centeio", "Felipe Coutinho");

ordenaBibliotecaPorNumeroEmprestimos(&biblioteca);
l1 = biblioteca.livros[0];

	if(!(l1 != NULL && strcmp(l1->nome,"O Tempo Reencontrado")  == 0 &&
			strcmp(l1->primeiro_autor,"Marcel Proust") == 0 &&
			strcmp(l1->demais_autores,"") == 0 &&
			l1->area == LITERATURA &&
			strcmp(l1->editora,"Ediouro") == 0 &&
			l1->anopub == 1993 &&
			l1->emprestado == true))
	{
		printf("==> Erro: Ordenacao por frequencia com problema\n");
		noErros++;
	}

ordenaBibliotecaPorNumeroEmprestimos(&biblioteca);

	l1 = biblioteca.livros[1]; // Peguei o segundo elemento da biblioteca ordenada por Nome do Livro

	if(!(l1 != NULL && strcmp(l1->nome,"O apanhador no campo de centeio") == 0 &&
			strcmp(l1->primeiro_autor,"Jerome David Salinger")  == 0 &&
			strcmp(l1->demais_autores,"")  == 0  &&
			l1->area == LITERATURA &&
			strcmp(l1->editora,"Editora do Autor")  == 0 &&
			l1->anopub == 1945 &&
			l1->emprestado == true))
	{
		printf("==> Erro: Ordenacao por frequencia com problema\n");
		noErros++;
	}

  // printf("==> Teste imprime ordenado por frequencia\n");
	// imprimeBibliotecaPorNumeroEmprestimos(&biblioteca);
  // printf("==> Teste imprime ordenado por nome de livro\n");
	// imprimirBibliotecaOrdenadaNomeLivro(&biblioteca);


  printf("==> Teste da biblioteca lotada\n");
	int espacolivre = TAM-tamanho(&biblioteca); // Espa�o livre na biblioteca nesse momento.

	for(i=0; i < espacolivre; ++i)
	    {
	     char nomelivro[TAMNOMES];
			 // sprintf funciona como o printf, so que escreve em um string de caracteres, no caso, nomelivro.
			 // Usei-o para criar varios nomes diferentes de livros acrescentando um inteiro no final.
			 // Mas cuidado com sprinf! O que voc� vai escrever em nomelivro nao pode ser maior que o
			 // tamanho do string, no caso TAMNOMES.
			 sprintf(nomelivro,"Zlivro-%d", i);
			 l1=novoLivro(nomelivro,"Zautor","","",ARTES,"Editora do Autor",1945);
	     insereLivro(&biblioteca,l1);
	    }

  if(tamanho(&biblioteca) != TAM)
	{
		printf("==> Erro: lotacao total da biblioteca com problema\n");
		noErros++;
	}

	printf("===> Teste insercao de novo livro:\n");
	l1=novoLivro("Zlivro-1000","Zautor","","",ARTES,"Editora do Autor",1945);
	insereLivro(&biblioteca,l1);

	l1=buscaLivro(&biblioteca,"Zlivro-1000");

	l2=buscaLivro(&biblioteca,"O Tempo Reencontrado");

	l3=buscaLivro(&biblioteca,"O apanhador no campo de centeio");

  // Tamanho tem que continuar o mesmo (==TAM), os livros que com maior frequencia de emprestismo tem que ficar
	// biblioteca e Zlivro-1000 tem que fazer parte da biblioteca agora.
	if(tamanho(&biblioteca) != TAM || l1 == NULL || l2 == NULL || l3 == NULL )
	{
		printf("==> Erro: insercao na biblioteca biblioteca lotada com problema\n");
		noErros++;
	}

	printf("Numero de erros: %d\n", noErros);
	return 0;
}