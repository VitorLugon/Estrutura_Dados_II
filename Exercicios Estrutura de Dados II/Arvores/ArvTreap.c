#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura de um nó da Treap
struct No {
  int chave;
  int prioridade;
  struct No *esquerda;
  struct No *direita;
};

// Função para criar um novo nó na Treap
struct No *CriarNo(int chave) {
  struct No *novoNo = (struct No *)malloc(sizeof(struct No));

  if (novoNo != NULL) {
    novoNo->chave = chave;
    novoNo->prioridade = rand() % 100;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
  }

  return novoNo;
}

// Função para realizar a rotação à direita
struct No *RotacaoDireita(struct No *no) {
    struct No *aux = no->esquerda; 
    struct No *aux2 = aux->direita;
    
    aux->direita = no;
    no->esquerda = aux2;
    
    return aux;
}

// Função para realizar a rotação à esquerda
struct No *RotacaoEsquerda(struct No *no) {
    struct No *aux = no->direita; 
    struct No *aux2 = aux->esquerda;
    
    aux->esquerda = no;
    no->direita = aux2;
    
    return aux;
}

// Função para inserir um nó na Treap
struct No *InserirTreap(struct No *raiz, int chave) {
  if (raiz == NULL) {
    return CriarNo(chave);
  }

  if (raiz->chave > chave) {
    raiz->esquerda = InserirTreap(raiz->esquerda, chave);
    if (raiz->esquerda != NULL && raiz->esquerda->prioridade > raiz->prioridade)
        raiz = RotacaoDireita(raiz);
  } else if (raiz->chave < chave) {
    raiz->direita = InserirTreap(raiz->direita, chave);
    if (raiz->direita != NULL && raiz->direita->prioridade > raiz->prioridade)
        raiz = RotacaoEsquerda(raiz);
  }

  return raiz;
}

// Função para remover um nó da Treap
struct No *RemoverNo(struct No *no) {
  struct No *aux;
  
  if (no->esquerda == NULL)
    aux = no->direita;
  else if (no->direita == NULL)
    aux = no->esquerda;
  else {
    if (no->esquerda->prioridade > no->direita->prioridade) {
        no = RotacaoDireita(no);
        no->direita = RemoverNo(no->direita);
    } else {
        no = RotacaoEsquerda(no);
        no->esquerda = RemoverNo(no->esquerda);
    }
    return no;
  }

  free(no);
  return aux;
}

// Função para remover uma chave da Treap
struct No *RemoverTreap(struct No *raiz, int chave) {
    if (raiz == NULL) return raiz;
    
    if (raiz->chave > chave)
        raiz->esquerda = RemoverTreap(raiz->esquerda, chave);
    else if (raiz->chave < chave)
        raiz->direita = RemoverTreap(raiz->direita, chave);
    else
        return RemoverNo(raiz);
    
    return raiz;
}

// Função para imprimir a Treap
void ImprimirArvore(struct No *no, int nivel) {
    if (no != NULL) {
        for (int i = 0; i < nivel; i++)
            printf("  ");

        printf("%d(%d)\n ", no->chave, no->prioridade);
        ImprimirArvore(no->esquerda, nivel + 1);
        ImprimirArvore(no->direita, nivel + 1);
    }
}

int main() {
    srand(time(NULL));
    
    struct No *raiz = NULL;
    
    int valores[7] = {25, 15, 50, 20, 5, 30, 40};
    
    for (int i = 0; i < 7; i++) {
        raiz = InserirTreap(raiz, valores[i]);
    }
    
    ImprimirArvore(raiz, 0);
    
    printf("\nRemoção do 30\n\n");
    
    raiz = RemoverTreap(raiz, 30);
  
    ImprimirArvore(raiz, 0);

    return 0;
}
