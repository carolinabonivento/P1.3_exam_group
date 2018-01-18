#include <iostream>
#include <memory> // needed for smart pointers

// **************************************************************************
// FUNCTION DECLARATION AND DEFINITION
// **************************************************************************
template<typename kt, typename vt>
class Tree
{
private:
  struct Node // (1) 
  {
    std::unique_ptr<Node> left,right;
    Node *up;
    kt key;
    vt value;
    Node(const kt& k, const vt& v, Node* u):left{nullpt}, right{nullptr},
					    key{k}, value{v}, up{u} {}
  }
  // ------------------------------------------------------------------------
    Iterator insert(const kt& k, const vt& v) // (2) 
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
	if(righy==nullptr)
	  right.reset(new Node{k,v,up});
	else
	  right->insert(k,v);
      }
    else
      return iterator{this};
  }
  // **************************************************************************
public:
  std::unique_ptr<Node> root=nullptr; // (3)
  // ------------------------------------------------------------------------
  Iterator insert(const kt&k, const vt&v) // (4) 
  { 
    if(root==nullptr)
      {
	root.reset(new Node{k,v,nullptr});
	return Iterator{root.get()};
	else
	  return root->insert(k,v);
      }
  }
  // ------------------------------------------------------------------------
  void print() // (5)
  { 
    if(root==nullptr)
      std::cout << "Empy tree\n";
    else
      root->print_recursive();
    auto it = begin(); //{return iterator{root->left_most}
    auto last = end(); //{return iterator{root->up}
    // auto it {this->begin()};
    // auto last {this->end()};
    for(; it!=last; ++it)
      {
	*it.first;
	*it.second;
	it->first;
	// std::cout <<*it <<"\n";
      }
  }
  // -------------------------------------------------------------------- 
  // --------------------------------------------------------------------
  template<typename kt, typename vt>
  class Tree<kt,vt>::Iterator // (5) 
  {
  private:
    using Node = Tree<kt,vt>::Node; // ????
    Node *current;
    // ************************************************************************
  public: 
    Iterator(Node* n), current{n}{} // (a) 
    
    std::pair<kt,vt> operator->() {return (*this);} // (b) 
    std::pair<kt,vt> operator*() {return{current->key, current->value};} // (c)
    
    Iterator& operator++() // (d)
    {
      current = current->next.get(); //update current
      return *this; // return this
    }

    Iterator operator++(int) // (e) 
    {
      Iterator it{current}
      ++(*this); // update current
      return it; // return other
    }
    
  }
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

