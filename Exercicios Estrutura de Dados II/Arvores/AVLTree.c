#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    int height;
    struct Node *left;
    struct Node *right;
};

int GetHeight(struct Node *node);
int BalanceFactor(struct Node *node);
int Max(int a, int b);
struct Node *RotateLeft(struct Node *node);
struct Node *RotateRight(struct Node *node);
struct Node *CreateNode(int data);
void PrintTree(struct Node *node, int lvl);
struct Node *BalanceAVL(struct Node *node, int data);
struct Node *InsertAVL(struct Node *root, int data);
struct Node *FindMaxInLeftSubtree(struct Node *node);
struct Node *RemoveNode(struct Node *root);
struct Node *RemoveAVL(struct Node *root, int data);

// Função para obter a altura de um nó
int GetHeight(struct Node *node)
{
    return (node == NULL) ? -1 : node->height;
}

// Função para calcular o fator de balanceamento
int BalanceFactor(struct Node *node)
{
    return (node == NULL) ? 0 : GetHeight(node->left) - GetHeight(node->right);
}

// Função auxiliar para retornar o maior valor entre dois números
int Max(int a, int b)
{
    return (a > b) ? a : b;
}

// Função para realizar rotação à esquerda
struct Node *RotateLeft(struct Node *node)
{
    struct Node *aux = node->left;
    node->left = aux->right;
    aux->right = node;

    // Atualiza alturas
    node->height = Max(GetHeight(node->left), GetHeight(node->right)) + 1;
    aux->height = Max(GetHeight(aux->left), GetHeight(aux->right)) + 1;

    return aux;
}

// Função para realizar rotação à direita
struct Node *RotateRight(struct Node *node)
{
    struct Node *aux = node->right;
    node->right = aux->left;
    aux->left = node;

    // Atualiza alturas
    node->height = Max(GetHeight(node->left), GetHeight(node->right)) + 1;
    aux->height = Max(GetHeight(aux->left), GetHeight(aux->right)) + 1;

    return aux;
}

// Função para criar um novo nó
struct Node *CreateNode(int data)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));

    if (node != NULL)
    {
        node->data = data;
        node->height = 0;
        node->left = NULL;
        node->right = NULL;
    }

    return node;
}

// Função para imprimir a árvore (modo hierárquico)
void PrintTree(struct Node *node, int lvl)
{
    if (node != NULL)
    {
        for (int i = 0; i < lvl; i++)
            printf("  ");
        printf("%d\n", node->data);
        PrintTree(node->left, lvl + 1);
        PrintTree(node->right, lvl + 1);
    }
}

// Função para balancear a árvore AVL após inserção ou remoção
struct Node *BalanceAVL(struct Node *node, int data)
{
    node->height = Max(GetHeight(node->left), GetHeight(node->right)) + 1;
    int bf = BalanceFactor(node);

    // Rotação esquerda-direita (LL ou LR)
    if (bf > 1)
    {
        if (data < node->left->data)
            return RotateLeft(node); // LL
        else
        { // LR
            node->left = RotateRight(node->left);
            return RotateLeft(node);
        }
    }
    // Rotação direita-esquerda (RR ou RL)
    else if (bf < -1)
    {
        if (data > node->right->data)
            return RotateRight(node); // RR
        else
        { // RL
            node->right = RotateLeft(node->right);
            return RotateRight(node);
        }
    }
    return node;
}

// Função para inserir um novo nó na árvore AVL
struct Node *InsertAVL(struct Node *root, int data)
{
    if (root == NULL)
        return CreateNode(data);

    if (data < root->data)
        root->left = InsertAVL(root->left, data);
    else if (data > root->data)
        root->right = InsertAVL(root->right, data);

    return BalanceAVL(root, data);
}

// Função para encontrar o maior valor na subárvore esquerda
struct Node *FindMaxInLeftSubtree(struct Node *node)
{
    while (node->right != NULL)
    {
        node = node->right;
    }
    return node;
}

// Função para remover um nó e reestruturar a árvore
struct Node *RemoveNode(struct Node *root)
{
    struct Node *temp;
    if (root->left == NULL)
        temp = root->right;
    else if (root->right == NULL)
        temp = root->left;
    else
    {
        temp = FindMaxInLeftSubtree(root->left);
        root->data = temp->data;
        root->left = RemoveAVL(root->left, temp->data);
        return root;
    }

    free(root);
    return temp;
}

// Função para remover um nó da árvore AVL
struct Node *RemoveAVL(struct Node *root, int data)
{
    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = RemoveAVL(root->left, data);
    else if (data > root->data)
        root->right = RemoveAVL(root->right, data);
    else
        return RemoveNode(root);

    return BalanceAVL(root, data);
}

int main()
{
    struct Node *root = NULL;

    // Alterei os valores inseridos na árvore
    int v[9] = {50, 25, 75, 10, 30, 60, 80, 5, 35};
    for (int i = 0; i < 9; i++)
    {
        root = InsertAVL(root, v[i]);
    }

    printf("Árvore AVL após inserções:\n");
    PrintTree(root, 0);

    // Remover alguns valores diferentes
    root = RemoveAVL(root, 10);
    root = RemoveAVL(root, 25);
    root = RemoveAVL(root, 60);

    printf("\nÁrvore AVL após remoções:\n");
    PrintTree(root, 0);

    return 0;
}
