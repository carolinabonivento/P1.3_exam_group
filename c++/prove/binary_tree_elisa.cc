#include <iostream> // std::cout
#include <memory> // std::unique_ptr
#include <utility> // std::pair, std::make_pair
//#include <string> // std::string
#include <iterator>

// **************************************************************************
// FUNCTION DECLARATION AND DEFINITION
// **************************************************************************
/*
(1) insert, used to insert a new pair key-value. (Alberto ne ha fatte 2)
(2) print, used to print key: value of each node. Note that the output should be in order with respect to the keys.
(3) clear(), clear the content of the tree. (DA zero)
(4) begin(), return an iterator to the first node (which likely will not be the root node)
(5) end(), return a proper iterator
(6) cbegin(), return a const_iterator to the first node (da zero)
(7) cend(), return a proper const_iterator ( da zero)
(8) balance(), balance the tree. (da zero, sorting con funzione della std::lib)
(9) find, find a given key and return an iterator to that node. If the key is not found returns end(); (simile al print)
 */
// ------------------------ CLASS TREE STARTS ----------------------------
template<typename kt, typename vt>
class Tree
{
private:
  struct Node // (1) Structure Node
  {
    std::unique_ptr<Node> left,right;
    Node *up;
    kt key;
    vt value;
    std::pair <kt,vt> key_value;
    
    // Constructor for the node
    Node(const kt& k, const vt& v, Node* u): left{nullptr}, right{nullptr},
					     key{k}, value{v}, up{u} {}
  };
  // ------------------------------------------------------------------------
public:
  class Iterator; // (4) Class Iterator
  Iterator begin() {return Iterator {root.get()};}
  Iterator end() {return Iterator {nullptr};}
  
private:
  Iterator insert(const kt& k, const vt& v) // (2) Function Insert 
  {
    if(k<key)
      {
	if(left==nullptr)
	  {
	    left.reset(new Node{k,v,this});
	    return Iterator{left.get()};
	  }
	else
	  return left->insert(k,v);
      }
    else if(k>key)
      {
	if(right==nullptr)
	  right.reset(new Node{k,v,up});
	else
	  right->insert(k,v);
      }
    else
      return Iterator{this};
  }
  // -------------------------------------------------------------------- 
  // --------------------------------------------------------------------
public:
  Tree(): std::unique_ptr<Node>root{nullptr} {}; // (3) Constructor of the Tree
  // ------------------------------------------------------------------------
 
  
  /* We should also add:
     class ConstIterator;
     ConstIterator  begin() {return ConstIterator {root.get()};}
     ConstIterator  end() {return ConstIterator {nulptr};}
  */
  Iterator insert(const kt&k, const vt&v) // (5) Function Insert 
  { 
    if(root==nullptr)
      {
	root.reset(new Node{k,v,nullptr});
	return Iterator{root.get()};
	else
	  {
	  return root->insert(k,v);
	  }
      }
  }
  // ------------------------------------------------------------------------
  // The function PRINT should be CONST anyway ...
  void print()/*const*/ // (6)
  { 
    if(root==nullptr)
      std::cout << "Empy tree\n";
    else
      root->print_recursive();
    auto it = begin(); //{return iterator{root->left_most}
    auto last = end(); //{return iterator{root->up}
    // auto it {this->begin()};
    // auto last {this->end()};
    for(; it!=last; ++it) // Doesn't need the first argument since "it" is already intialized
      {
	/* If we are using pair, we will write:*/
	*it.first;
	*it.second;
	it->first;      
	// If we do not use std::pair
	// std::cout << *it <<"\n";
      }
  }
};
// ------------------------ CLASS TREE ENDS ----------------------------

// ************************************************************************
// ************************************************************************
template<typename kt, typename vt>
class Tree<kt,vt>::Iterator
{
private:
  using Node = Tree<kt,vt>::Node; // alias
  Node *current;
  // -------------------------------------------------------------------- 
  // --------------------------------------------------------------------
public: 
  Iterator(Node* n), current{n}{} // (a) Constructor of the Iterator
    
  std::pair<kt,vt> operator->() {return (*this);} // (b) 
  std::pair<kt,vt> operator*() {return{current->key, current->value};} // (c)
    
  Iterator& operator++() // (d)
  {
    current = current->up.get(); //update current
    return *this; // return this
  }

  Iterator operator++(int) // (e) 
  {
    Iterator it{current}
    ++(*this); // update current
    return it; // return other
  }
    
};
// -------------------------------------------------------------------- 
// --------------------------------------------------------------------
void Node::print_recursive()
{
  if(left!=nullptr)
    left->print_recursive();
  std::cout<< key << "" << value << "\n";
    
  if(right!=nullptr)
    right->print_recursive();
}

/*
std::ostream& operator<<(std::ostream& os, const Month& m) //(7e)
{
  return os;
}
*/
// ************************************************************************
// MAIN
// ************************************************************************
int main()
{
  Tree<int>tree{};
  tree.insert(1);
  tree.insert(2);
  tree.insert(3);

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
