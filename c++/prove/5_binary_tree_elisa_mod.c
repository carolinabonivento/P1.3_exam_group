#include <iostream> // std::cout
#include <memory> // std::unique_ptr
#include <utility> // std::pair, std::make_pair
#include <iterator>
#include <vector> // std::vector

using std::cout;
using std::endl;
// **************************************************************************
// FUNCTION DECLARATION AND DEFINITION
// **************************************************************************
/*
  (1) insert, used to insert a new pair key-value. (Alberto ne ha fatte 2) --> done
  (2) print, used to print key: value of each node. Note that the output   --> done
  should be in order with respect to the keys.
  (3) clear(), clear the content of the tree. (DA zero)                    --> done
  (4) begin(), return an iterator to the first node (which likely will not --> done
  be the root node)
  (5) end(), return a proper iterator                                      --> done
  (6) cbegin(), return a const_iterator to the first node (da zero)        --> TO DO
  (7) cend(), return a proper const_iterator ( da zero)                    --> TO DO
  (8) balance(), balance the tree. (da zero, sorting con funzione della    --> vedere Auro
  std::lib)
  (9) find, find a given key and return an iterator to that node. If the key --> TO DO
  is not found returns end(); (simile al print)
*/
template <typename kt, typename vt> class Node;
template <typename kt, typename vt> class Tree; 
template <typename kt, typename vt> class Iterator;

// ************************ CLASS NODE STARTS ************************
template <typename kt, typename vt>
class Node 
{
public:
  kt key;
  vt value;
  Node *up;
  Node *left;
  Node *right;
  Node(const kt& k, const vt& v, Node* u, Node* l, Node*r):
    key{k}, value{v},  up{u}, left{l}, right{r} {}

  Node<kt,vt>* left_most(){
    if(Node<kt,vt>::left)
      return Node<kt,vt>::left->left_most();
    else
      return this;
  }
  //    Node(const kt& k, const vt& v, Node* u=nullptr, Node* l=nullptr, Node*r=nullptr):
};
// ************************ CLASS NODE ENDS  ************************

// ------------------------ CLASS TREE STARTS ----------------------------
template<typename kt, typename vt>
class Tree
{
private:
  Node<kt,vt>* root;
  
  Node<kt,vt>* find_helper(kt key, vt val, Node<kt,vt>* root); // (1)

  Node<kt,vt>* insert_helper(kt key, vt val, Node<kt,vt>* t); // (2)  
  void clear_helper(Node<kt,vt>* n); // (3) 
  void print_preorder_helper(Node<kt,vt>* t); // (4)
  void print_inorder_helper(Node<kt,vt>* t); // (5)
  void inorderpush(Node<kt,vt>* t, std::vector<Node<kt,vt>*> &vecnodes); // (10)
  Node<kt,vt>* insert_from_vector(std::vector<Node<kt,vt>*> &vecnodes,
				  int start, int end, Node<kt,vt>* parent); // (11)

public:
  unsigned int _size;
  unsigned int size() {return _size;} // (13)

  Tree();
  class Iterator;
  Iterator begin() {
    //  if(root!=nullptr)
    return Iterator {root->left_most()};
  }
  Iterator end() {return Iterator {nullptr};}
  
  class ConstIterator; 
  ConstIterator cbegin() const {return ConstIterator {root->left_most()};}
  ConstIterator cend() const {return ConstIterator {nullptr};}
  
  Node<kt,vt>* find_noiter(kt key, vt val) {return find_helper(key, val, root);} // (6)
  void insert_noiter(kt key, vt val) {root = insert_helper(key, val, root);} // (7)
  void clear() {clear_helper(root);} 

  void print_preorder() {cout << "Print preorder: key " <<endl; 
    print_preorder_helper(root); cout << endl;}

  void print_inorder() {cout << "Print inorder: key (parent)" <<endl;
    print_inorder_helper(root); cout << endl ;} // (9)

  void balance(); // (12)
};
// ------------------------ CLASS TREE ENDS ----------------------------
template<typename kt, typename vt>
Tree<kt,vt>::Tree()
{  
  _size=0; 
  root=nullptr;
}
// ----------------------------------------------------------------------
template<typename kt, typename vt>
Node<kt,vt>* Tree<kt,vt>::find_helper(kt key, vt val, Node<kt,vt>* t) // (1)
{
  if (t!=nullptr)
    {
      if (key == t->key){
	cout << "The inserted key = " << key << " is in the BT" << endl;
	return t;
      }
      if (key < t->key)
	return find_helper(key, val, t->left);
      else
	return find_helper(key, val, t->right);
    }
  else
    cout << "The inserted key = " << key << " is NOT in the BT" << endl;
  return nullptr; 
}
// ----------------------------------------------------------------------
template<typename kt, typename vt>
Node<kt,vt>* Tree<kt,vt>::insert_helper(kt key, vt val, Node<kt,vt>* t) // (2) 
{
  if(t == nullptr) 
    {
      cout << "Inserting node: " << key << endl;
      t = new Node<kt,vt> (key,val,nullptr,nullptr, nullptr); // NOT nullptr
      _size = _size+1;        
    }
  else if(key < t->key){ // left child       
    t->left = insert_helper(key, val, t->left); 
    t->left->up = t;
  }
  else if(key > t->key){ // right child
    t->right = insert_helper(key, val, t->right);
    t->right->up = t->up; 
  }
  return t;
}
// ----------------------------------------------------------------------
template <typename kt, typename vt>
void Tree<kt,vt>::clear_helper(Node<kt,vt>* n){ // (3) 
  if( n == nullptr) return;
    
  clear_helper(n->left);
  clear_helper(n->right);

  _size = _size-1;        

  delete n;
  n = nullptr;
}
// ----------------------------------------------------------------------
template <typename kt, typename vt>
void Tree<kt,vt>::print_preorder_helper( Node<kt,vt>* t) //function for pre-order traversal
// (4)
{
  if (t == nullptr)
    return;
    
  cout << t->key << " ";
  print_preorder_helper(t->left);
  print_preorder_helper(t->right);
}
// ----------------------------------------------------------------------
template <typename kt, typename vt>
void Tree<kt,vt>::print_inorder_helper(Node<kt,vt>* t) // (5)
{
  if(t == nullptr)
    return;
  else
    print_inorder_helper(t->left);
    
  if(t != root)
    cout << t->key << " (" << t->up->key << ") ";
  else
    cout << t->key <<" " << "(root) ";
    
  print_inorder_helper(t->right);
}
// ----------------------------------------------------------------------
template <typename kt, typename vt> // (10)
void Tree<kt,vt>::inorderpush(Node<kt,vt>* t, std::vector<Node<kt,vt>*> &vecnodes)
{
  if (t==nullptr)
    return;
  inorderpush(t->left, vecnodes);
  vecnodes.push_back(t);
  inorderpush(t->right, vecnodes);
}
// ----------------------------------------------------------------------
template <typename kt, typename vt> 
void Tree<kt,vt>::balance() // (12)
{
  cout << endl << "Balance tree..." << endl;
  std::vector<Node<kt,vt>*> _vector_of_nodes;
  _vector_of_nodes.reserve(size());
  Node<kt,vt>* t = root;
  inorderpush(t, _vector_of_nodes);
  root = insert_from_vector(_vector_of_nodes, 0, _vector_of_nodes.size()-1, nullptr);
}

// ************************ ITERATOR STARTS ************************
template<typename kt, typename vt>
class Tree<kt,vt>::Iterator
{
private:
  Node<kt,vt> *current;
  
public:
  Iterator(Node<kt,vt>* n): current{n}{} 
  std::pair<kt,vt> operator->() {return (*this);} 
  std::pair<kt,vt> operator*() const {return{current->key, current->value};}

  // ++it
  Iterator& operator++() 
  {
    if(current){ // "if the current doesn't point to null.."
      if(current->Node<kt,vt>::right) // "if the right of the current doesn't point to null.."
	current = current->right->left_most();
      else
	current = current->up;
    }
    return *this; 
  }
  /*
  // it++
  Iterator operator++(int)
  {
  Iterator it{current};
  ++(*this); 
  return it; 
  }*/

  bool operator==(const Iterator& other)
  {
    return this->current==other.current;
  }
  
  bool operator!=(const Iterator& other) {return !(*this == other);}
};
// ************************ ITERATOR ENDS ************************
// ++++++++++++++++++ CONST ITERATOR STARTS ++++++++++++++++++
template<typename kt, typename vt> 
class Tree<kt,vt>::ConstIterator:public Tree<kt,vt>::Iterator
{
  using parent = Tree<kt,vt>::Iterator;
public:
  using parent::Iterator;
  const std::pair<kt,vt> operator*() const {return parent::operator*();} 
};
// ++++++++++++++++++ CONST ITERATOR ENDS ++++++++++++++++++
template<typename kt, typename vt> 
Node<kt,vt>* Tree<kt,vt>::insert_from_vector(std::vector<Node<kt,vt>*>&vecnodes, // (11)
					     int start, int end, Node<kt,vt>* parent)
{
  if(start>end)
    return nullptr;
  int middle = (start+end)/2;
  Node<kt,vt>* t = vecnodes[middle];
  t->up = parent;
  t->left = insert_from_vector(vecnodes, start, middle-1, t);
  t->right = insert_from_vector(vecnodes, middle+1, end, t);
  return t;
}
// ************************************************************************
// MAIN
// ************************************************************************
int main()
{
  Tree<int, int> tree{};

  cout << "1. INSERTING Nodes " << endl; // to modify with iterator
  tree.insert_noiter(1,1);
  tree.insert_noiter(2,2);
  tree.insert_noiter(3,3);
  tree.insert_noiter(4,4);
  tree.insert_noiter(5,5);
  tree.insert_noiter(6,6);
  tree.insert_noiter(10,10);
  tree.insert_noiter(8,8);
  tree.insert_noiter(18,18);
  tree.insert_noiter(27,27);
  tree.insert_noiter(35,35);
  tree.insert_noiter(9,9);
  cout << "--------------------------------------------------------------" << endl;							
  cout << "2a. PRINTING Nodes preorder rx to the key (NO Iterator)" << endl;
  tree.print_inorder();
  cout << "--------------------------------------------------------------" << endl;							
  cout << "2b. PRINTING Nodes in order rx to the key (WITH Iterator)" << endl;
  Tree<int,int>::Iterator it = tree.begin();
  Tree<int,int>::Iterator stop = tree.end();
  
  for(; it !=stop; ++it)
    {
      cout << (*it).first << endl;
    }
  cout << "Now the list has " << tree._size << " elements" << endl;
  cout << "--------------------------------------------------------------" << endl;						       
  /*
    cout << "2a. PRINTING Nodes preorder rx to the key (NO Iterator)" << endl;
    tree.print_preorder(); --> ora non stampa in preorder corretto :(

    cout << "2b. PRINTING Nodes in order rx to the key (NO Iterator)" << endl;
    tree.print_inorder(); --> ora da segmentation fault :(
  */
  cout << "9a. FINDING  Nodes (NO Iterator)" << endl;
  tree.find_noiter(1,1); // trova la root
  tree.find_noiter(2,2); 
  tree.find_noiter(4,4);

  cout << "--------------------------------------------------------------" << endl;							
  cout << "8. BALANCING the tree" << endl;
  tree.balance();
    
  /*for(; it !=stop; ++it)
    {
      cout << (*it).first << endl;
    }
    cout << "Now the list has " << tree._size << " elements" << endl;*/

  cout << "--------------------------------------------------------------" << endl;							
  cout << "3. DELETING Nodes" << endl;
  tree.clear();
  cout << "Now the list has " << tree._size << " elements" << endl;
  return 0;
}

/*
  TO DO
  -sistemare il codice (ordine!)
  -error handling
  -copy and move semantics
  -testare tutto
  -cambiare key e value (usare anche stringhe)
  -analizzare performance (scambiando anche key e value)
  -usare smart pointers
  -come organizzare std::pair
  -da testare:  
  std::pair<kt,vt> operator->() {return (*this);} 
  bool operator==(const Iterator& other)
  bool operator!=(const Iterator& other) {return !(*this == other);}


  Le funzioni che devono restituire un iterator sono:
  - print (eliminare il print_noiter e sostuituirlo con quanto messo nel main)
  - insert (modificare il nostro insert)
  - find (modificarla)

http://www.cplusplus.com/forum/general/147955/
*/
