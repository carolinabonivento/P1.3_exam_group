#include <iostream> // std::cout
#include <memory> // std::unique_ptr
#include <utility> // std::pair, std::make_pair
#include <iterator>

using std::cout;
using std::endl;
// **************************************************************************
// FUNCTION DECLARATION AND DEFINITION
// **************************************************************************
/*
  (1) insert, used to insert a new pair key-value. (Alberto ne ha fatte 2)
  (2) print, used to print key: value of each node. Note that the output 
  should be in order with respect to the keys.
  (3) clear(), clear the content of the tree. (DA zero)
  (4) begin(), return an iterator to the first node (which likely will not 
  be the root node)
  (5) end(), return a proper iterator
  (6) cbegin(), return a const_iterator to the first node (da zero)
  (7) cend(), return a proper const_iterator ( da zero)
  (8) balance(), balance the tree. (da zero, sorting con funzione della std::lib)
  (9) find, find a given key and return an iterator to that node. If the key 
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
  Node *left;
  Node *right;
  Node *up;
  Node(const kt& k, const vt& v, Node* l, Node*r, Node* u):
    key{k}, value{v}, left{nullptr}, right{nullptr}, up{nullptr} {}
};
// ************************ CLASS NODE ENDS  ************************

// ------------------------ CLASS TREE STARTS ----------------------------
template<typename kt, typename vt>
class Tree
{
private:
  Node<kt,vt>* root;
  unsigned int _size;
  Node<kt,vt>* insert_helper(kt key, vt val, Node<kt,vt>* t);
  void clear_helper(Node<kt,vt>* n);

  
public:
  Tree(); 
  class Iterator; 
  Iterator begin() {return Iterator {root};}
  Iterator end() {return Iterator {nullptr};}
  class ConstIterator; 
  ConstIterator cbegin() const {return ConstIterator {root};}
  ConstIterator cend() const {return ConstIterator {nullptr};}
  void insert_noiter(kt key, vt val) {root = insert_helper(key, val, root);}
  void clear() {clear_helper(root);}

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
Node<kt,vt>* Tree<kt,vt>::insert_helper(kt key, vt val, Node<kt,vt>* t)
{
  if(t == nullptr) 
    {
      cout << "creazione nodo: " << key << endl;
      //   t = new Node<kt,vt> (key,val,nullptr); //  --> by AURO, but error
      t = new Node<kt,vt> (key,val,nullptr,nullptr, nullptr);
      _size = _size+1;        
    }
  else if(key < t->key){        
    t->left = insert_helper(key, val, t->left);
    t->left->up = t;
  }
  else if(key > t->key){ 
    t->right = insert_helper(key, val, t->right);
    t->right->up = t;
  }
  return t;
}
// ----------------------------------------------------------------------
template <typename kt, typename vt>
void Tree<kt,vt>::clear_helper(Node<kt,vt>* n){
  if( n == nullptr) return;
    
  clear_helper(n->left);// if(n->left != nullptr) clear_helper(n->left);
  clear_helper(n->right);// if(n->left != nullptr) clear_helper(n->left);
    
  delete n;
  n = nullptr;
}
// ----------------------------------------------------------------------

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
    current = current->up; 
    return *this; 
  }
  // it++
  Iterator operator++(int)
  {
    Iterator it{current};
    ++(*this); 
    return it; 
  }

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


// ************************************************************************
// MAIN
// ************************************************************************
int main()
{
  Tree<int, int>tree{};

  cout << "Insert nodes... " << endl;
  tree.insert_noiter(1,1);
  tree.insert_noiter(2,2);
  tree.insert_noiter(3,3);

  
    Tree<int, int>::Iterator last = tree.end();
    for(Tree<int,int>::Iterator it = tree.begin(); it !=last; ++it)
    {
    cout << "The tree has 3 elements" << endl;
    }
  
      
  tree.clear();
  return 0;
}


/*
  ALTRE DOMANDE PER AURORA
  (1) Ma se mettiamo la classe Nodo all'interno della classe Tree
  templata su kt e vt
  anche il Nodo erediterà il fatto di essere templato?
  (2) Dobbiamo templare anche il Nodo?
  Se provo a NON templarlo ad un certo punto mi fa:
  5_binary_tree_elisa.cc:111:1: error: ‘Node’ does not name a type
  Node* Tree<kt,vt>::insert_helper(kt key, vt val, Node* t)
  (3) Warnings: non usa puntatori LEFT, RIGHT, UP
*/
