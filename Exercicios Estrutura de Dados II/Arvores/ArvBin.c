#include <stdio.h>
#include <stdlib.h>
// Vitor Lugon Cacciari Martinelli CC6M

struct Node{
int data;
struct Node* left;
struct Node* right;
};

struct Node* CreateNode(int data){
struct  Node* newNode = (struct Node*)malloc(sizeof(struct Node)); 
  if(newNode !=NULL){
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
  }
  return newNode;
}

struct Node* Insert(struct Node* root, int data){
  if(root==NULL){
    root = CreateNode(data);
  }
  else if (data <= root->data){
    root->left = Insert(root->left, data);
  }
  else{
    root->right = Insert(root->right,data);
  }
    return root;
}

struct Node* Search(struct Node* root, int data){
  if(root == NULL || root->data == data) {
    return root;
  }
    
   else if (data<=root->data){
     return Search(root->left,data);
    }
   else {
    return Search(root->right, data);
   }
}

struct Node* FindMin(struct Node* root){
  struct Node* min = root;
  while(min->left != NULL){
    min = min->left;
  }
  return min;
}

struct Node* Delete(struct Node* root, int data){
  if(root==NULL ){
    return root;
  }
  else if(data < root->data){
    root->left = Delete(root->left, data);
  }
  else if (data > root->data){
    root->right = Delete(root->right, data);
  }
  else{
    //Caso 1: Nó sem filhos
    if(root->left == NULL && root->right == NULL){
      free(root);
      root = NULL;
    }
    //Caso 2: Nó com um filho
    else if(root->left == NULL){
      struct Node* temp = root;
      root = root->right;
      free(temp);
    }
    else if(root->right == NULL){
      struct Node* temp = root;
      root = root->left;
      free(temp);
    }
    //Caso 3: Nó com dois filhos
    else{
      struct Node *temp = FindMin(root->right);
      root->right = Delete(root->right, temp->data);
    }
  }
    return root;
}

void printNode(int c, int b)
{
    int i;
    for (i = 0; i < b; i++)
        printf("   ");
    printf("%i\n", c);
}

void showTree(struct Node *a, int b)
{
    if (a == NULL)
    {
        return;
    }
    showTree(a->right, b + 1);
    printNode(a->data, b); 
    showTree(a->left, b + 1);
}

int main(void) {
  struct Node *root = NULL;  
  root = Insert(root, 1);
  root = Insert(root, 2);
  root = Insert(root, 3);
  root = Insert(root, 4);
  root = Insert(root, 5);
  root = Insert(root, 6);
  root = Insert(root, 7);
  root = Insert(root, 8);
  root = Insert(root, 9);
  root = Insert(root, 10);

  showTree(root, 3);
  Delete(root, 5);
  showTree(root, 3);
  
  printf(Search(root, 9) != NULL ? "Found\n" : "Not Found\n");
  printf(Search(root, 19) != NULL ? "Found\n": "Not Found\n");
  return 0;
};