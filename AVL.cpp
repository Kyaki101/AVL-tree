#include <bits/stdc++.h>
#include "AVL.h"



using namespace std;

long long int expo(int n, int exp, int mod){
    if (!exp){
        return 1L;
    }
    long long r = expo(n, exp >> 1, mod);
    r *= r;
    r %= mod;
    if(exp & 1)r*=n;
    return r % mod;
    
}

 
int SET::height(Node * current){
  if(current == NULL){return -1;}
  return max(height(current->left), height(current->right)) + 1;
}

bool SET::isBalanced(Node * current){
  if(current == NULL) return true;
  int lh = height(current->left);
  int rh = height(current->right);
  int factor = abs(lh - rh);
  if(factor > 1){
    return false;
  }
  return isBalanced(current->left) && isBalanced(current->right);
}

int SET::factor(Node * current){
  return (height(current->left) - height(current->right));
}

void SET::Balance(Node * current){
  if(current == NULL) return;
  int fact = factor(current);
  if(fact > 1 || fact < -1){
    if(fact > 1){
      
      if(!isBalanced(current->left)){Balance(current->left); return;}
      if(factor(current->left) < 0){left_right(current); return;}
      else rotateRight(current);
    }
    if(factor(current) < -1 ){
      if(!isBalanced(current->right)){Balance(current->right); return;}
      if(factor(current->right) > 0){right_left(current); return;}
      else rotateLeft(current);
    }
  }
  Balance(current->left); Balance(current->right);
}

long Node::singleHash(){
  long res = 1;
  for(int i = 0; data[i]; i++){
    res += expo(h1,(int)(data[i]), h2);
  }
  return res;
}

long Node::doubleHash(long res){
  for(int i = 0; data[i]; i++, res %= h1){
    res += (((int)(data[i])%h2) *(6907 % h2)) % h2;
  }
  return res;
}

long Node::Hash(){

  return doubleHash(singleHash());
}

int SET::estaVacio(){
  return (parent == NULL)? 0 : 1;
}

bool SET::insertar(string data){
  if(maximum == size){cout << "El AVL esta lleno" << endl; return false;}
  if (parent == NULL){Node * first = new Node(data); parent = first; size ++; return true;}
  addAux(data, parent);
  Balance(parent);
  size ++;
  return true;
}

void SET::addAux(string data, Node * current){
  Node * newNode = new Node(data);
  if(newNode->Hash() == current->Hash()){cout << newNode->data << " " << current->data <<  endl; return;}
  if(newNode->Hash() < current->Hash()){
    if(current->left == NULL){current->left = newNode; return;}
    current = current->left;
    addAux(data, current); return;}
  if(newNode->Hash() > current->Hash()){
    if(current->right == NULL){current->right = newNode; return;}
    current = current->right;
    addAux(data, current); return;
  }
}

bool SET::remove(string data, Node * current, long int hasher, bool flag){
  Node * newNode = new Node(data);
  if (current == NULL){
    return false;
  }
  if(current->right == NULL && current->Hash() > hasher){return false;}
  if(current->left == NULL && current->Hash() < hasher){return false;}
  if(hasher == current->right->Hash() && current->right->left == NULL && current->right->right == NULL){current->right = NULL; Balance(parent); return true;}
  if(hasher == current->right->Hash() && current->right->left == NULL ){current->right = current->right->right; Balance(parent); return true;}
  if(hasher == current->left->Hash() && current->left->left == NULL && current->left->right == NULL){current->left = NULL; Balance(parent); return true;}
  if(hasher == current->left->Hash() && current->left->right == NULL ){current->left = current->left->left; Balance(parent); return true;}
  if (current->Hash() == hasher){
    if (!flag){
      if(current->right->left == NULL){
        Node * lefty = new Node(); lefty = current->left;
        *current = *current->right;
        current->left = lefty;
        Balance(parent);
        return true;
      }

      Node * righty = new Node(); righty = current->right;
      Node * lefty = new Node(); lefty = current->left;
      Node * temp = current->right;
      while(temp->left->left != NULL){temp = temp->left;}
      *current = *temp->left;
      Node * store = temp->left->right;
      temp->left = store;
      current->right = righty;
      current->left = lefty;
      Balance(parent);
      return true;
    }
    if (flag){
      if(current->right->left == NULL){
        Node * lefty = new Node(); lefty = current->left;
        *current = *current->right;
        current->left = lefty;
        Balance(parent);
        return true;
      }
      Node * lefty = new Node(); lefty = current->left;
      Node * righty = new Node(); righty = current->right;
      Node * temp = current->right;
      while(temp->left->left != NULL){temp = temp->left;}
      *current = *temp->left;
      Node * store = temp->left->right;
      temp->left = store;
      current->right = righty;
      current->left = lefty;

      
      Balance(parent);
      return true;
    }

  }
  if(hasher > current->Hash() && current->right == NULL){return false;}
  if(hasher < current->Hash() && current->left == NULL){return false;}
  if(hasher > current->Hash()){
    flag = true;
    return remove(data, current->right, hasher,true);
    }
  if(hasher < current->Hash()){
    
    return remove(data, current->left, hasher, false);}
}

bool SET::eliminar(string data){
  if(size == 0){return false;}
  if(data == parent->data && size == 1){parent = NULL; size --; return true;}
  Node * newNode = new Node(data);
  long hasher = newNode->Hash();
  if(remove(data, parent, hasher, true)){
    Balance(parent);
    size --;
    return true;
  }
  return false;
}

void SET::rotateLeft(Node*current){
  Node * temp = new Node();
  Node * lefty = new Node();
  *temp = *current;
  lefty = (current->right->left);
  current->right->left = temp;
  *current = *(current->right);
  current->left->right = lefty;
  if (lefty == NULL) return;
}




void SET::rotateRight(Node*current){
  Node * temp = new Node();
  Node * righty = new Node();
  *temp = *current;
  righty = (current->left->right);
  current->left->right = temp;
  *current = *(current->left);
  current->right->left = righty;
}



void SET::left_right(Node * current){
  rotateLeft(current->left);
  rotateRight(current);

}

void SET::right_left(Node * current){
  rotateRight(current->right);
  rotateLeft(current);
}

void SET::show(Node * current){
  if(current == NULL){return;}
  
  cout << current->data;
  show(current->left); show(current->right);
}



int SET::cardinalidad(){
  return size;
}

int SET::cardinalidadMax(){
  return maximum;
}

bool SET::contains(string data, Node * current, long hash){
  if (current->Hash() == hash){
    return true;
  }
  if(hash > current->Hash() && current->right == NULL || hash < current->Hash() && current->left == NULL){
    return false;
  }
  return (hash < current->Hash())? contains(data, current->left, hash) : contains(data, current->right, hash);

}

bool SET::contiene(string data){
  Node * newNode = new Node(data);
  long hash = newNode->Hash();
  return (contains(data, parent, hash))? true : false;

}

void SET::intersect(SET sec, SET * nuevo, Node * current){
  if(current == nullptr){
    return;
  }
  if(sec.contiene(current->data)){
    nuevo->insertar(current->data);
  }
  intersect(sec, nuevo, current->left);
  intersect(sec, nuevo, current->right);
}

SET * SET::insterseccion(SET sec){
  SET * nueva = new SET();
  intersect(sec, nueva, parent);
  return nueva;
}

void SET::uni(SET * nuevo, Node * current){
  if(current == nullptr){
    return;
  }
  nuevo->insertar(current->data);
  uni(nuevo, current->left);
  uni(nuevo, current->right);
}
void SET::unisec(SET * nuevo, Node * current){
  if(current == nullptr){
    return;
  }
  if(!nuevo->contiene(current->data)){
    nuevo->insertar(current->data);

  }
  unisec(nuevo, current->left);
  unisec(nuevo, current->right);
}

SET * SET::unidad(SET sec){
  SET * nueva = new SET;
  uni(nueva, parent);
  sec.unisec(nueva, sec.parent);
  return nueva;
}


