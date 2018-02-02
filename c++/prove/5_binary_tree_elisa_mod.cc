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
  
  Node<kt,vt>* find_helper(kt key, vt val, Node<kt,vt>* t); // (1)
  Node<kt,vt>* insert_helper(kt key, vt val, Node<kt,vt>* t); // (2)  
  void clear_helper(Node<kt,vt>* n); // (3) 

  
public:
  Tree(); 
  class Iterator; 
  Iterator begin() {return Iterator {root};}
  Iterator end() {return Iterator {nullptr};}
  class ConstIterator; 
  ConstIterator cbegin() const {return ConstIterator {root};}
  ConstIterator cend() const {return ConstIterator {nullptr};}
  
  Node<kt,vt>* find_noiter(kt key, vt val) {return find_helper(key, val, root);} // (6)
  void insert_noiter(kt key, vt val) {root = insert_helper(key, val, root);} // (7)
  void clear() {clear_helper(root);} // (8)

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
  if (t!=NULL)
    {
      if (key == t->key)
	cout << "Node found." << endl;
	return t;
      if (key < t->key)
	return find_helper(key, val, t->left);
      else
	return find_helper(key, val, t->right);
    }
  else
    return NULL;
  //  cout << "Node not found." << endl;
}
  
// ----------------------------------------------------------------------
template<typename kt, typename vt>
Node<kt,vt>* Tree<kt,vt>::insert_helper(kt key, vt val, Node<kt,vt>* t) // (2) 
{
  if(t == nullptr) 
    {
      cout << "Inserting node: " << key << endl;
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
void Tree<kt,vt>::clear_helper(Node<kt,vt>* n){ // (3) 
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
  //private:
  // Node<kt,vt> *current;
  
public:
  Node<kt,vt> *current;
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

  cout << "1. INSERTING Nodes " << endl;
  tree.insert_noiter(1,1);
  tree.insert_noiter(2,2);
  tree.insert_noiter(3,3);
  tree.insert_noiter(2,2);

  Tree<int, int>::Iterator first = tree.begin();
  Tree<int, int>::Iterator last = tree.end();
  
  cout << "The first node of the binary tree is " << first.current->key << endl;
  /*
 cout << "The last node of the binary tree is " << last.current->key << endl;
SEGMENTATION FAULT IN PRINTING
  */  
  
  /*
    for(Tree<int,int>::Iterator it = tree.begin(); it !=last; ++it)
    {
    cout << "The tree has 3 elements" << endl;
    }*/

  cout << "2. SEARCHING Nodes" << endl;
  
  tree.find_noiter(1,1);
  tree.find_noiter(4,4);

  cout << "3. DELETING Nodes" << endl;
  
  tree.clear();
  return 0;
}
