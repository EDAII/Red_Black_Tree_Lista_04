#include <bits/stdc++.h>
#include "rbt.hpp"

using namespace std;

void Tree::insert(int element){
  // Insere o elemento na posição correta da árvore

  void insere(Node *temp);

  // Cria um novo nó com o o valor a ser inserido
  Node *filho = new Node;
  filho->value = element;
  filho->left = filho->right = filho->parent = NULL;
  filho->color = red;

  if(root == NULL){
    root = filho;
    insere(root);
  }
  else{

    // Percorre a árvore até chegar no último nó sem ser NULL;
    Node *temp = root;

    int parar = 0;
    while(parar == 0){
      if(element < temp->value){
        if(temp->left == NULL) parar ++;
        else temp = temp->left;
      }
      else if(element > temp->value){
        if(temp->right == NULL) parar ++;
        else temp = temp->right;
      }
    }
    // O filho aponta para o pai
    filho->parent = temp;
    // Coloca o filho na posição correta
    if(element > temp->value) temp->right = filho;
    else if(element < temp->value) temp->left = filho;
    // Função que faz as devidas mudanças para que a arvore siga as
    //regras de uma arvore preto e vermelho
    insere(filho);
  }
}

// Caso 01
// Se for raiz troca a cor do no inserido
void insere(Node *temp){

  void caso_2(Node *temp);

  if(temp->parent == NULL) temp->color = black;
  else caso_2(temp);
}

// caso 02
// Se o pai for preto não faz nada
// Caso contrario confere se é outro dos casos
void caso_2(Node *temp){
  void caso_3(Node *temp);

  Node *pai = temp->parent;
  if(pai->color == black);
  else caso_3(temp);
}

// Caso 03
// Caso onde o pai e o tio são vermelhos
// Caso contrario confere se é outro dos casos
void caso_3(Node *temp){
  void caso_4(Node *temp);

  Node *avo = temp->parent->parent;
  Node *pai = temp->parent;

  if(avo->left != NULL && avo->right != NULL){
    if(avo->left->color == red && avo->right->color == red){
      avo->left->color = avo->right->color = black;
      avo->color = red;
      if(avo->parent == NULL) avo->color = black;
    }
  }

  else caso_4(temp);
}

// Caso 04
// Pai vermelho e tio preto, nó interno
// Se for interno transforma no caso 5 (pai vermelho e tio preto, no externo)
//com a rotação, e independente deste caso vai para o caso 5
void caso_4(Node *temp){
  void caso_5(Node *temp);

  Node *pai = temp->parent;
  Node *avo = temp->parent->parent;
  if(temp == pai->right && pai == avo->left){
    if(pai->color == red){
      avo->left = temp;
      pai->right = temp->left;
      temp->left = pai;
      pai->parent = temp;
      temp->parent = avo;
    }
  }
  else if(temp == pai->left && pai == avo->right){
    if(pai->color == red){
      avo->right = temp;
      pai->left = temp->right;
      temp->right = pai;
      pai->parent = temp;
      temp->parent = avo;
    }
  }
  caso_5(temp);
}

// Caso 05
// Resolve o ultimo caso
//pai vermelho e tio preto, nó externo
void caso_5(Node *temp){
  Node *avo = temp->parent->parent;
  Node *pai = temp->parent;

  if(temp == pai->left && pai == avo->left){
    if(pai->color == red){
      pai->parent = avo->parent;
      avo->parent = pai;
      avo->left = pai->right;
      pai->right = avo;
      pai->color = black;
      avo->color = red;
    }
  }
  else if(temp == pai->right && pai == avo->right){
    if(pai->color == red){
      pai->parent = avo->parent;
      avo->parent = pai;
      avo->right = pai->left;
      pai->left = avo;
      pai->color = black;
      avo->color = red;
    }
  }
}


void Tree::erase(int element){
  // Remove o elemento da árvore, se ele existir
  // Não estafuncionando corretamente
  // Não remove o caso onde o nó oou seu predecessor é preto
  // Ao comentar o erase o programa funciona corretamente

  if (!find(element));
  // Caso o elemento não exista na arvore não faz nada
  else{
    Node *temp = root;
    int parar = 0;
    while(parar == 0){
      if(element < temp->value){
        if(temp->left == NULL)  parar++;
        else temp = temp->left;
      }else if(element > temp->value){
        if(temp->right == NULL)  parar++;
        else temp = temp->right;
      }
    }
    // Caso o nó que deve ser excluido seja raiz
    if (temp == root){
      if(size() == 1){
        root = NULL;
        free(root);
      }else if (temp->left != NULL){
        temp = temp->left;
        int caso=0;
        // Avisa se foi ao menos uma vez para direita
        if (!temp->right) caso++;
        while(temp->right){
          temp = temp->right;
        }
        if (temp->color == red){
          root->value = temp->value;
          if (caso == 1){
            root->left = temp->left;
            temp->left->parent = root;
            temp == NULL;
            free(temp);
          }
          if (temp->left){
            temp->parent->right = temp->left;
            temp->left->parent = temp->parent->right;
            temp=NULL;
            free(temp);
          }
        }
      }else if (temp->right != NULL){
        temp = temp->right;
        int caso=0;
        if (!temp->left) caso++;//avisa se foi ao menos uma vez para direita
        while(temp->left){
          temp = temp->left;
        }
        if (temp->color == red){
          root->value = temp->value;
          if (caso == 1){
            root->right = temp->right;
            temp->right->parent = root;
            temp == NULL;
            free(temp);
          }
          if (temp->right){
            temp->parent->left = temp->right;
            temp->right->parent = temp->parent->left;
            temp = NULL;
            free(temp);
          }
        }
      }
    }
    // Caso o nó seja a ser removido ou seu predecessor seja vermelho
    else if (temp->color == red || temp->parent->color == red){
      if (element < temp->parent->value){
        if (temp->left != NULL && temp->right != NULL){
          temp->parent->left = temp->right;
          temp->right->left = temp->left;
        }
        if (temp->left == NULL && temp->right != NULL) temp->parent->left = temp->right;
        if (temp->left != NULL && temp->right == NULL) temp->parent->left = temp->left;
      temp = NULL;
      free(temp);
    }
      if (element > temp->parent->value){
        if (temp->left != NULL && temp->right != NULL){
          temp->parent->right = temp->right;
          temp->right->left = temp->left;
        }
        if (temp->left == NULL && temp->right != NULL) temp->parent->left = temp->right;
        if (temp->left != NULL && temp->right == NULL) temp->parent->left = temp->left;
        temp = NULL;
        free(temp);
      }
    }else{
      // Caso o nó e seu predcessor sejam pretos
    }
  }
}

void Tree::rotate_right(Node *gr, Node *par, Node *ch){
  //Rotaciona para a direita os nós
  if(gr!=NULL){
      if(gr->left==par){
      gr->left = ch;
      ch->parent = gr;
    }else{
      gr->right = ch;
      ch->parent = gr;
    }
  }
  par->left = ch->right;
  ch->right->parent = par;

  ch->left = par;
  par->parent = ch;
}


void Tree::rotate_left(Node *gr , Node *par , Node *ch  ){
  //Rotaciona para a esquerda os nós
  if(gr!=NULL){
    if(gr->left == par){
      gr->left = ch;
      ch->parent = gr;
    }else{
      gr->right = ch;
      ch->parent = gr;
    }
  }
  par->right = ch->left;
  ch->left->parent = par;

  ch->left = par;
  par->parent = ch;
}

bool Tree::find(int element){
  // Procura o elemento na árvore
  // O(log n)
  Node* temp = root;
  int found(Node *temp, int element);

  if(root == NULL){
    return false;
  }else if(temp->value == element){
    return true;
  }else{
    if (found(temp,element)!=0)
      return true;
    else
      return false;
    }
  }
  int found(Node *temp,int element){
    //retorna o numero de vezes que o no aparece na arvore
    if((temp == NULL))
      return 0;
    else{
      if(temp->value!=element)
        return 0 + max(found(temp->left,element), found(temp->right,element));
      else
        return 1 + max(found(temp->left,element), found(temp->right,element));
    }
  }


void Tree::clear(){
  // Remove todos os nós da árvore
  void limpar(Node *temp);
  printf("limpar\n");
  limpar(root);
  root = NULL;
  free(root);
}
void limpar(Node *temp){
  if(temp != NULL){
    limpar(temp->left);
    limpar(temp->right);
    temp=NULL;
    free(temp);
  }
}


bool Tree::empty(){
  // Verifica se a árvore está ou não vazia
  if (size() == 0) return true;
  else  return false;
}

int Tree::size(){
  // Verifica a quantidade de nós na árvore
  int contador(Node *root);

  return contador(root);
}
int contador(Node *raiz){
  if(raiz == NULL)
    return 0;
  else
    return 1 + contador(raiz->left) + contador(raiz->right);
}


int Tree::black_height(){
  // Verifica a altura preta da árvore
  int altura_preta(Node *temp);

  return altura_preta(root);
}
int altura_preta(Node *temp){
  if((temp == NULL) || (temp->left == NULL && temp->right == NULL))
  return 0;
  else{
    if(temp->color == red)
      return 0 + max(altura_preta(temp->left), altura_preta(temp->right));
    else
      return 1 + max(altura_preta(temp->left), altura_preta(temp->right));
  }
}

// Mostra os numeros Post Order da arvore e a cor do nó
void Tree::print_preorder(){
  // Faz a impressão Post Order da árvore
  // Apresenta cor dos nós
  void preorder(Node *temp);

  preorder(root);
  printf("\n");
}
void preorder(Node *temp){
  if(temp){
    printf("\n%d", temp->value);
    if (temp->color == red) cout << "  Red";
    else cout << "  Black";
    preorder(temp->left);
    preorder(temp->right);
  }
}

// Mostra os numeros da arvore e a cor do nó, em ordem crescente
void Tree::print_inorder(){
  // Faz a impressão Post Order da árvore
  // Apresenta cor dos nós
  void emOrdem(Node *temp);

  emOrdem(root);
  printf("\n");
}
void emOrdem(Node *temp){
  if(temp){
    emOrdem(temp->left);
    printf("\n%d", temp->value);
    if (temp->color == red) cout << "  Red";
    else cout << "  Black";
    emOrdem(temp->right);
  }
}

// Mostra os numeros da arvore e a cor do nó, em ordem decrescente
void Tree::print_postorder(){
  // Faz a impressão Post Order da árvore
  // Apresenta cor dos nós
  void posOrdem(Node *temp);

  posOrdem(root);
  printf("\n");
}
void posOrdem(Node *temp){
  if(temp){
    posOrdem(temp->left);
    posOrdem(temp->right);
    printf("\n%d", temp->value);
    if (temp->color == red) cout << "  Red";
    else cout << "  Black";

  }
}
