# Biblioteca particular

## Descrição

Neste exercício você deve desenvolver um programa para controlar uma biblioteca particular. Essa
biblioteca possui espaço para 150 livros. Todo livro deve ser catalogado, isto é, inserido na biblioteca.
Um livro pode ser retirado (emprestado) da biblioteca, porém deve ser informado o nome da pessoa
que fez o empréstimo. O livro emprestado deve ser devolvido e, neste caso, o nome de quem estava
com o livro deve ser eliminado. Como se trata de uma biblioteca particular, não é preciso controlar
se a devolução está ocrrendo em atraso. É possível também fazer uma consulta ao acervo utilizando
o título para saber se o livro existe na biblioteca e se ele se encontra disponível para empréstimo.
Quando o limite físico da biblioteca (150 livros) é atingido, a inserção de um novo livro causa o descarte
de um dos livros correntemente presente na biblioteca. A política de eliminação é a seguinte: livro 
emprestado não pode ser eliminado; livros emprestados com bastante frequência devem ser mantidos
na biblioteca, ou seja, livros pouco emprestados são os candidatos ao descarte.
O sistema deve produzir os seguintes relatórios: livros ordenados em ordem lexicográfica (também
conhecida como ordem do dicionário, ordem alfabética) por nome do livro e livros ordenados por
frequência de empréstimos (mais emprestados em primeiro lugar).

## Estruturas da biblioteca particular

A biblioteca pode ser implementada usando duas estruturas: *Biblioteca* e *Livro*. A estrutura
*Biblioteca* possuirá como campo um arranjo de pelo menos 150 posições. Cada posição deste arranjo
poderá conter uma estrutura do tipo *Livro*. A estrutura *Livro* deverá conter campos para armazenar
os seguintes dados sobre o livro:

 1. nome do livro;
 2. primeiro autor;
 3. demais autores;
 4. área: computação, literatura, ciências, artes, geral;
 5. editora;
 6. se está emprestado ou não;
 7. número de empréstimos do livro;
 8. nome do emprestador;
 9. ano de publicação.

Já consta a declaração dessas estruturas e uma função para criar um novo livro, mas
deverá escrever funções que manipulam os elementos *Livros* da estrutura *Biblioteca*. Além disso,
uma função 'imprimirDados' deve ser implementada de forma a imprimir a saída da ficha de um livro
semelhante à seguinte.

 Nome: The great gatsby\
 Autor: Scott Fitzgerald\
 Autores secundarios: Mathew j. Bruccoli\
 Editora: Collier books\
 Area: literatura\
 Ano publicacao: 1991\
 Numero de emprestimos: 0\
 Emprestado? Nao

 Outro exemplo:

 Nome: O mundo assombrado pelos demonios\
 Autor: Carl Sagan\
 Autores secundarios: nao ha\
 Editora: Companhia da Letras\
 Area: ciencias\
 Ano publicacao: 1995\
 Numero de emprestimos: 0\
 Emprestado? Nao

 A estrutura *Biblioteca* deve ser acessada por meio de funções para inserção, ordenação, empréstimo
 e devolução de livros, para consulta ao acervo e para os relatórios solicitados. Será fornecido um
 arquivo template que contém todas as funções que os alunos devem implementar.
