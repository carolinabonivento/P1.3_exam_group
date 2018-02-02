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
  (8) balance(), balance the tree. (da zero, sorting con funzione della 
std::lib)
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
  unsigned int _size;
  
  Node<kt,vt>* find_helper(kt key, vt val, Node<kt,vt>* t); // (1)
  Node<kt,vt>* insert_helper(kt key, vt val, Node<kt,vt>* t); // (2)  
  void clear_helper(Node<kt,vt>* n); // (3) 
  void print_preorder_helper(Node<kt,vt>* t); // (4)
  void print_inorder_helper(Node<kt,vt>* t); // (5) 

  
public:
  Tree();
  class Iterator;
  
  Iterator begin() {
    //  if(root!=nullptr)
      return Iterator {root->left_most()};
      }
 
  
 

    
  //  Iterator begin() {return Iterator {root};}
  Iterator end() {return Iterator {nullptr};}
  class ConstIterator; 
  ConstIterator cbegin() const {return ConstIterator {root};}
  ConstIterator cend() const {return ConstIterator {nullptr};}
  
  Node<kt,vt>* find_noiter(kt key, vt val) {return find_helper(key, val, root);}
  // (6)
  void insert_noiter(kt key, vt val) {root = insert_helper(key, val, root);}
  // (7)
  void clear() {clear_helper(root);} // (8)

  void print_preorder() {cout << "Print preorder: key " <<endl; // (8)
    print_preorder_helper(root); cout << endl;}
  /* It
     - prints the tree in preorder
     - doesn't need iterators
     - uses the corresponding private helper function*/

   void print_inorder() {cout << "Print inorder: key (parent)" <<endl;
    print_inorder_helper(root); cout << endl ;} // (9)
  /* It 
   - prints in order, sorting using key value. 
   - doesn't need iterators.
   - uses the corresponding private helper function.*/
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
      if (key == t->key)
	cout << "Node found." << endl;
	return t;
      if (key < t->key)
	return find_helper(key, val, t->left);
      else
	return find_helper(key, val, t->right);
    }
  else
    return nullptr;
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
      t = new Node<kt,vt> (key,val,nullptr,nullptr, nullptr); // NOT nullptr
      _size = _size+1;        
    }
  else if(key < t->key){ // left child       
    t->left = insert_helper(key, val, t->left); // ???
    t->left->up = t;
  }
  else if(key > t->key){ // right child
    t->right = insert_helper(key, val, t->right);
    t->right->up = t->up; // "up of the right of t"
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
// function for in-order traversal
{
    if(t == nullptr)
        return;
    print_inorder_helper(t->left);
    ////cout << t->key <<" "; //  decomment for standard print without up node
    
    if(t != root)
      cout << t->key << " (" << t->up->key << ") ";
    //print with the parent node also (comment to simplify output)
    else cout << t->key <<" " << "(root) ";
    // print with parent (comment to simplify output)
    print_inorder_helper(t->right);
}
// ************************ ITERATOR STARTS ************************
template<typename kt, typename vt>
class Tree<kt,vt>::Iterator
{
 private:
 Node<kt,vt> *current;
  
public:
  //Node<kt,vt> *current;
  Iterator(Node<kt,vt>* n): current{n}{} 
  std::pair<kt,vt> operator->() {return (*this);} 
  std::pair<kt,vt> operator*() const {return{current->key, current->value};}

  // ++it
  Iterator& operator++() 
  {
    if(current){
      if(current->Node<kt,vt>::right) // if current righ doesn't pint to null
	current = current->right->left_most();
      else
	current = current->up;
    }
    return *this; 
    /* current = current->up; 
       return *this; */
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
  tree.insert_noiter(1,1);
  tree.insert_noiter(6,6);
  tree.insert_noiter(10,10);
  tree.insert_noiter(8,8);
  tree.insert_noiter(18,18);
  tree.insert_noiter(27,27);
  tree.insert_noiter(35,35);
  tree.insert_noiter(9,9);
    
  /* tree.print_preorder(); 
  tree.print_inorder();
  */

  // Tree<int, int>::Iterator first = tree.begin();
  //  Tree<int, int>::Iterator last = tree.end();
  
  // cout << "The first node of the binary tree is " << first.current->key << endl;
  /*
 cout << "The last node of the binary tree is " << last.current->key << endl;
SEGMENTATION FAULT IN PRINTING
  */  
  
  Tree<int,int>::Iterator it = tree.begin();
  Tree<int,int>::Iterator stop = tree.end();
  
  for(; it !=stop; ++it)
    {
      cout << (*it).first << endl;
    }

  /*
  cout << "2. SEARCHING Nodes" << endl;
  
  tree.find_noiter(1,1);
  tree.find_noiter(4,4);

  cout << "3. DELETING Nodes" << endl;
  
  tree.clear();*/
  return 0;
}

/*
WARNINGS


ITERATOR: where do we use them?
- print ?

TO DO
error handling

*/
