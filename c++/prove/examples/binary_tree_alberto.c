#include <iostream>
#include <memory> // NEEDED FOR WHAT??

//#include <iterator>

// Structure Node

template<typename kt, typename vt>

struct Node
{
  std::unique_ptr<Node> left,right;
  Node *up;
  kt key;
  vt value;
}

/*
left.reset(new Node{2,v,this});
right.reset(new Node{4,v,up});
 */
// Constructor
  Node(const kt&k, const vt&v, Node*u):left{nullpt}, right{nullptr}, key{k},
				       value{v}, up{u} {}
 
  struct Node{ // occhio perchè stiamo utilizzando un'altra struct Node!!!
    iterator insert(const kt&k, const vt&v){
      if(k<key){
	if(left==nullptr){
	  left.reset(new Node{k,v,this});
	  return iterator{left.get()};
	}
	else
	  return let->insert(k,v);
      }
      else if(k>key){
	if(righ==nullptr)
	  right.reset(new Node{k,v,up});
	else
	  right->insert(k,v);
      }
      else
	return iterator{this};
    }


    class Tree{
  iterator insert(const kt&k, const vt&v){
    if(root==nullptr){
      root.reset(new Node{k,v,nullptr});
      return iterator{root.get()};
      else
	return root->insert(k,v);
    }
  std::unique_ptr<Node> root=nullptr;

    // Iterator

  struct iterator public //{
    iterator(Node* n), current{n}{} {
    std::pair<kt,vt> operator->() {return (*this);}
    std::pair<kt,vt> operator*() {return{current->key, current->value};}
    iterator operator++() {"update current", return this}
    iterator operator++(int) {"create otherit", "update current", return other}
    Node *current;
  
template<class kt, class vt>
  void tree<kt,vt> print(){
  if(root==nullptr)
    std::cout << "Empy tree\n";
  else
    root->print_recursive();
  auto it = begin(); {return iterator{root->left_most}
  auto last = end(); {return iterator{root->up}
  
  for(; it!=last; ++it){
    *it.first;
    *it.second;
    it->first;
  }

  void Node::print_recursive(){
    if(left!=nullptr)
      left->print_recursive();
    std::cout<< key << "" << value << "\n";

    if(right!=nullptr)
      right->print_recursive();
  }
