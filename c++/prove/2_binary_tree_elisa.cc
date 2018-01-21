#include <iostream> // std::cout
#include <memory> // std::unique_ptr
//#include <utility> // std::pair, std::make_pair
//#include <string> // std::string
//#include <iterator>

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
// ------------------------ CLASS TREE STARTS ----------------------------
template<typename kt>
class Tree
{
private:
  class Node 
  {
  public:
    Node *left;
    Node *right;
    Node *up;
    kt key;
    // da chiedere: come utilizzare il std::pair
    Node(const kt& k, Node* u): left{nullptr}, right{nullptr},
					     up{u}, key{k} {}
  };
  std::unique_ptr<Node> root;
public:
  Tree(): root{nullptr} {}
  
  class Iterator; 
  Iterator begin() {return Iterator {root.get()};}
  Iterator end() {return Iterator {nullptr};}

  class ConstIterator; // da mettere una c all'inizio
  ConstIterator cbegin() const {return ConstIterator {root.get()};}
  ConstIterator cend() const {return ConstIterator {nullptr};}
  
};
// ------------------------ CLASS TREE ENDS ----------------------------
// ************************ ITERATOR STARTS ************************
template<typename kt>
class Tree<kt>::Iterator
{
 
private:
  using Node = Tree<kt>::Node; // alias
  Node *current;
  
public:  
  Iterator(Node* n): current{n}{} 
  kt& operator*() const {return current->value;}
  //  std::pair<kt,vt> operator->() {return (*this);} 

  // ++it
  Iterator& operator++() 
  {
    current = current->up.get(); 
    return *this; 
  }
  // it++: capire se è necessario un post-increment
  // the object increment itself and the return a tm with its previous value
  Iterator operator++(int)
  {
    Iterator it{current};
    ++(*this); 
    return it; 
  }
  // It's better to ignore a node with a key == a previous one
  bool operator==(const Iterator& other)
  {
    return this->current==other.current;
  }
  bool operator!=(const Iterator& other) {return !(*this == other);}
};
// ************************ ITERATOR ENDS ************************
// ++++++++++++++++++ CONST ITERATOR STARTS ++++++++++++++++++
template<typename kt>
class Tree<kt>::ConstIterator:public Tree<kt>::Iterator
{
  using parent = Tree<kt>::Iterator;
public:
  using parent::Iterator;
  const kt& operator*() const {return parent::operator*();}
};
// ++++++++++++++++++ CONST ITERATOR ENDS ++++++++++++++++++

// ************************************************************************
// MAIN
// ************************************************************************
int main()
{
  Tree<int>tree{};
  /*
  tree.insert(1);
  tree.insert(2);
  tree.insert(3);
  */
  //  list.print();
  /*
    btree b;
    int tmp;
  
    std::cout << "Enter the number to be inserted\n";
    std::cin>>tmp;
    b.insert(tmp);
  */

  return 0;
}
