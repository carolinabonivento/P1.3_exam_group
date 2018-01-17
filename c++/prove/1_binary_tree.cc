// https://www.cprogramming.com/tutorial/lesson18.html
#include <iostream>
/*
  BINARY TREE
*/
// ***************************************************************************
// FUNCTION DECLARATION AND DEFINITION
// ***************************************************************************
/*
  1. First it is necessary to have a struct, or class, defined as a node.
  The struct:
  - has the ability to store the key_value and
  - contains the two child nodes which define the node as part of a tree.
  2. The node itself is very similar to the node in a linked list.
  3. Pointers are necessary to allow the arbitrary creation of  new nodes 
  in the tree.
*/
struct node
{
  int key_value;
  node *left;
  node *right;
};
/*
  1. It is most logical to create a binary tree class to encapsulate 
  the workings of the tree into a single area, and also making it reusable. 
  2. The class will contain functions to 
  - insert data into the tree and to 
  - search for data. 
  3. Due to the use of pointers, it will be necessary to include a function 
  to delete the tree in order to conserve memory after the program has finished.
*/
class btree
{
private:
  // In this example, the private functions call the corresponding public ones
  node *search(int key, node *leaf); // (1) defined !!!
  // search for a value and return a pointer to the element
  void insert(int key, node *leaf); // (2) defined !!!
  // insert a value and return a pointer to the element
  void destroy_tree(node *leaf); // (3) defined !!!
  // destroy the tree from a given node
  // (a) MA COME PROCEDE SE NON GLI DO IL ROOT NODE? "FROM BOTTOM TO UP"
  node *root;
  
public: // (b) COMMENTARE SULLA SCELTA DI PUBBLICO/PRIVATO
  btree(); // Constructor  (4) defined !!!
  ~btree(); // Destructor  (5) defined !!!
  // (c) POSSO DEFINIRE 2 FUNZIONI CON LO STESSO NOME MA UN N° DI ARGOMENTI DIVERSO? MA POI PERCHÈ LO FA?
  node *search(int key); // (6) defined !!!
  void insert(int key); // (7) defined !!!
  void destroy_tree(); // (8) defined !!!
};
/*
  1. The insert and search functions are:
  - public members of the class 
  - designed to allow the user of the class to use the class 
  without dealing with the underlying design. 
  - will be called recursively,
  - contain two parameters, allowing them to travel down the tree. 

  2. The destroy_tree function is: 
  - without arguments
  - a front for the destroy_tree function which will recursively 
  destroy the tree, node by node, from the bottom up.
*/

btree::btree() // (4)
{
  root=NULL;
}
/*
It is necessary to initialize root to NULL for the later functions 
to be able to recognize that it does not exist.
(d) IN CHE SENSO?
*/
btree::~btree() // (5)
{
  destroy_tree();
}
/*
The destroy_tree function will set off the recursive function destroy_tree 
shown below which will actually delete all nodes of the tree.
(Recursive function: function that calls itself)
*/
void btree::destroy_tree(node *leaf) // (3) 
{
  if(leaf!=NULL)
  {
    destroy_tree(leaf->left);
    destroy_tree(leaf->right);
    delete leaf;
  }
}
/*
1. The function destroy_tree goes to the bottom of each part of the tree, 
that is, 
- searching while there is a non-null node, 
- deletes that leaf, and then it 
- works its way back up. 

2. The function deletes the leftmost node, then the right child node 
from the leftmost node's parent node, then it deletes the parent node, 
then works its way back to deleting the other child node of the parent 
of the node it just deleted, and it continues this deletion working its 
way up to the node of the tree upon which delete_tree was originally called. 

3. destroy_tree(10)
In the example tree above, the order of deletion of nodes would be 
5 8 6 11 18 14 10 
It is necessary to delete all the child nodes to avoid wasting memory.
*/
void btree::insert(int key, node *leaf) // (2) (e) NON CAPISCO...
// IN OGNI CASO DA DISEGNARE ALLA LAVAGNA
{
  if(key< leaf->key_value)
    // QUESTO KEY_VALUE È IL VALORE DELLA ROOT O DEL "CURRENT NODE"??
  {
    if(leaf->left!=NULL)
     insert(key, leaf->left);
    else
    {
      leaf->left=new node;
      leaf->left->key_value=key;
      leaf->left->left=NULL;    // Set the left child of the child node to NULL
      leaf->left->right=NULL;   // Set the right child of the child node to NULL
    }  
  }
  else if(key>=leaf->key_value)
  {
    if(leaf->right!=NULL)
      insert(key, leaf->right);
    else
    {
      leaf->right=new node;
      leaf->right->key_value=key;
      leaf->right->left=NULL;  // Set the left child of the child node to NULL
      leaf->right->right=NULL; // Set the right child of the child node to NULL
    }
  }
}
/*
The case where the root node is still NULL will be taken care of (f) ???
by the insert function that is 
- nonrecursive and 
- available to non-members of the class. 

The insert function searches, 
- moving down the tree of children nodes, 
- following the prescribed rules (left for a lower value to be inserted 
and right for a greater value) 
- until it finds an empty node which it 
-- creates using the 'new' keyword and 
-- initializes with the key value 
while setting the new node's child node pointers to NULL. 

After creating the new node, the insert function will no longer call itself.
*/
node *btree::search(int key, node *leaf) // (1)
{
  if(leaf!=NULL)
  {
    if(key==leaf->key_value)
      return leaf;
    if(key<leaf->key_value)
      return search(key, leaf->left);
    else
      return search(key, leaf->right);
  }
  else return NULL;
  // (g) COME FA AD ESSERE NULLA LA FOGLIA(ELEMENTO)?
  // O FORSE CAPISCE CHE L'ELEMNTO NON È NELLA LISTA??
  // IN OGNI CASO DA DISEGNARE ALLA LAVAGNA
}
/*
The search function shown above (search)
1. recursively moves down the tree until it either
- reaches a node with a key value equal to the value for which the function 
is searching or until
-  the function reaches an uninitialized node, meaning that the value 
being searched for is not stored in the binary tree. 
2. returns a pointer to the node to the previous instance of the function 
which called it, ...handing the pointer back up to the search function 
accessible outside the class.......??????? (h)
*/
void btree::insert(int key) // (7)
// (i) PERCHÈ IL CHECK NELLA INSERT È SOLO NELLA FUNZIONE PRIVATA?
// QUESTA A COSA SERVE? SEMBRA CHE SOLO QUESTA CONSIDERI IL CASO CHE
// NON CI SIA UN ROOT NODE...
// IN OGNI CASO DA DISEGNARE ALLA LAVAGNA
{
  if(root!=NULL)
    insert(key, root);
  else
  {
    root=new node; // Create the new node
    root->key_value=key; // Let the inserted key be the root
    root->left=NULL; // Set the left child of the root node to NULL
    root->right=NULL; // Set the right child of the root node to NULL
  }
}
/*
1. The public version of the insert function takes care of the case 
where the root has not been initialized by 
- allocating the memory for it and 
- setting both child nodes to NULL and 
- setting the key_value to the value to be inserted. 
2. If the root node already exists, insert is called with the root node 
as the initial node of the function, and the recursive insert function 
takes over.
*/
node *btree::search(int key) // (6)
{
  return search(key, root);
}
/*
The public version of the search function is used to set off 
the search recursion at the root node, keeping it from being necessary 
for the user to have access to the root node.
(i) E COSA POTREBBE SUCCEDERE SE L'UTENTE AVESSE ACCESSO AL ROOT NODE?
*/
void btree::destroy_tree() // (8)
{
  destroy_tree(root);
}
/*
 The public version of the destroy tree function is merely used to 
initialize the recursive destroy_tree function which then deletes 
all the nodes of the tree.
*/ 
// ***************************************************************************
// MAIN
// ***************************************************************************
int main(){
  btree b;
  int tmp;
  
  std::cout << "Enter the number to be inserted\n";
  std::cin>>tmp;
  b.insert(tmp);

  return 0;
}
