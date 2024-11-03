#include <stdio.h>
#include <stdlib.h>

// Grau máximo da árvore B
#define MAX_GRAU 4

// Estrutura de um nó da árvore B
struct No
{
    int ehFolha;
    int numChaves;
    int chaves[MAX_GRAU - 1];
    struct No *filhos[MAX_GRAU];
};

// Função para criar um novo nó na árvore
struct No *CriarNo(int ehFolha)
{
    struct No *novoNo = (struct No *)malloc(sizeof(struct No));
    novoNo->ehFolha = ehFolha;
    novoNo->numChaves = 0;
    for (int i = 0; i < MAX_GRAU; i++)
        novoNo->filhos[i] = NULL;
    return novoNo;
}

// Função para dividir um nó filho cheio
void DividirFilho(struct No *pai, int indice)
{
    struct No *filho = pai->filhos[indice];
    struct No *novoNo = CriarNo(filho->ehFolha);

    for (int i = 0; i < MAX_GRAU / 2 - 1; i++)
    {
        novoNo->chaves[i] = filho->chaves[i + MAX_GRAU / 2];
    }

    if (!filho->ehFolha)
    {
        for (int i = 0; i < MAX_GRAU / 2; i++)
        {
            novoNo->filhos[i] = filho->filhos[i + MAX_GRAU / 2];
        }
    }

    filho->numChaves = MAX_GRAU / 2 - 1;
    novoNo->numChaves = MAX_GRAU / 2 - 1;

    for (int i = pai->numChaves; i > indice; i--)
    {
        pai->filhos[i + 1] = pai->filhos[i];
    }
    pai->filhos[indice + 1] = novoNo;

    for (int i = pai->numChaves - 1; i >= indice; i--)
    {
        pai->chaves[i + 1] = pai->chaves[i];
    }
    pai->chaves[indice] = filho->chaves[MAX_GRAU / 2 - 1];
    pai->numChaves++;
}

// Função para inserir uma chave em um nó não cheio
void InserirNaoCheio(struct No *no, int chave)
{
    int i = no->numChaves - 1;

    if (no->ehFolha)
    {
        while (i >= 0 && chave < no->chaves[i])
        {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        no->chaves[i + 1] = chave;
        no->numChaves++;
    }
    else
    {
        while (i >= 0 && chave < no->chaves[i])
        {
            i--;
        }
        i++;
        if (no->filhos[i]->numChaves == MAX_GRAU - 1)
        {
            DividirFilho(no, i);
            if (chave > no->chaves[i])
            {
                i++;
            }
        }
        InserirNaoCheio(no->filhos[i], chave);
    }
}

// Função para inserir uma nova chave na árvore B
struct No *Inserir(struct No *raiz, int chave)
{
    if (raiz == NULL)
    {
        raiz = CriarNo(1);
        raiz->chaves[0] = chave;
        raiz->numChaves = 1;
    }
    else
    {
        if (raiz->numChaves == MAX_GRAU - 1)
        {
            struct No *novaRaiz = CriarNo(0);
            novaRaiz->filhos[0] = raiz;
            DividirFilho(novaRaiz, 0);
            int i = 0;
            if (chave > novaRaiz->chaves[0])
            {
                i++;
            }
            InserirNaoCheio(novaRaiz->filhos[i], chave);
            raiz = novaRaiz;
        }
        else
        {
            InserirNaoCheio(raiz, chave);
        }
    }
    return raiz;
}

// Função para imprimir a árvore B
void ImprimirArvore(struct No *no, int nivel)
{
    if (no != NULL)
    {
        for (int i = 0; i < nivel; i++)
            printf("  ");
        for (int i = 0; i < no->numChaves; i++)
            printf("%d ", no->chaves[i]);
        printf("\n");

        for (int i = 0; i <= no->numChaves; i++)
        {
            ImprimirArvore(no->filhos[i], nivel + 1);
        }
    }
}

// Função principal para teste da árvore B
int main()
{
    struct No *raiz = NULL;

    raiz = Inserir(raiz, 15);
    raiz = Inserir(raiz, 25);
    raiz = Inserir(raiz, 8);
    raiz = Inserir(raiz, 10);
    raiz = Inserir(raiz, 18);
    raiz = Inserir(raiz, 40);
    raiz = Inserir(raiz, 12);
    raiz = Inserir(raiz, 22);

    ImprimirArvore(raiz, 0);

    return 0;
}
