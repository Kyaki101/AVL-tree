#include <iostream>

using namespace std;

class Node{
  private:
  public:
  string data;
  int h1;
  int h2;
  Node * left;
  Node * right;

  Node(){
    data = "";
    h1 = 104395303;
    h2 = 3051053;
    left = NULL;
    right = NULL;
  }

  Node(string data){
    this -> data = data;
    this -> left = NULL;
    this -> right = NULL;
    this -> h1 = 104395303;
    this -> h2 = 3051053;
  }
  long singleHash();
  long doubleHash(long);
  long Hash();
};

class SET{
  private:
  int size = 0;
  int maximum = ((1L << 31)) - 1;
  public:
  Node * parent;

  SET(){parent = NULL;}

  SET(int cant){parent = NULL; this->maximum = cant;}

  bool insertar(string);

  void addAux(string, Node*);

  bool remove(string, Node*, long, bool flag);

  bool eliminar(string);

  void contiene(string, Node*);

  int height(Node*);

  bool isBalanced(Node*);

  void rotateLeft(Node*);

  void rotateRight(Node*);
  
  void show(Node*);

  void climbL(Node*, Node*);

  void climbR(Node*, Node*);

  void Balance(Node*);

  void left_right(Node*);

  void right_left(Node*);

  bool contiene(string);

  bool contains(string, Node*, long);

  int cardinalidad();

  int cardinalidadMax();

  int estaVacio();

  void intersect(SET, SET *, Node *);

  SET * insterseccion(SET);

  int factor(Node*);

  void uni(SET *, Node *);

  void unisec(SET *, Node *);

  SET * unidad(SET);

};

