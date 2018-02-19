#include <iostream> // std::cout
#include <memory> // std::unique_ptr
#include <utility> // std::pair, std::make_pair
#include <iterator>
#include <vector> // std::vector
#include <cstdbool>
#include <cmath> // to use pow(a,b) (= a^b)
#include <ctime>

using std::cout;
using std::endl;

// **************************************************************************
// FUNCTION DECLARATION AND DEFINITION
// **************************************************************************
/*
  (1) insert, used to insert a new pair key-value --> OK
  (2) print, used to print key: value of each node. Note that the output   
  should be in order with respect to the keys --> OK
  (3) clear(), clear the content of the tree  --> OK                          
  (4) begin(), return an iterator to the first node (which likely will not 
  be the root node) --> OK
  (5) end(), return a proper iterator --> OK                                    
  (6) cbegin(), return a const_iterator to the first node --> OK        
  (7) cend(), return a proper const_iterator --> OK                    
  (8) balance(), balance the tree. (da zero, sorting con funzione della    
  std::lib) --> TO DO
  (9) find, find a given key and return an iterator to that node. If the key 
  is not found returns end(); (simile al print) --> OK

  LEGEND
  (n): function n°
  (a): function version WITHOUT iterator
  (b): function version WITH iterator
*/
template <typename kt, typename vt> class Node;
template <typename kt, typename vt> class Tree; 
template <typename kt, typename vt> class Iterator;

// ************************ CLASS NODE STARTS *******************************
template <typename kt, typename vt>
class Node {
public:
  kt key;
  vt value;
  Node *up;
  Node *left;
  Node *right;
  Node(const kt& k, const vt& v, Node* u, Node* l=nullptr, Node*r=nullptr):
    key{k}, value{v},  up{u}, left{l}, right{r} {}

  Node<kt,vt>* left_most(){
    if(Node<kt,vt>::left)
      return Node<kt,vt>::left->left_most();
    else
      return this;
  }
  // ------------------------------------------------------------------------- 
  using Iterator = typename Tree<kt,vt>::Iterator; 
  Iterator insert(const kt&k, const vt&v){ // (1)(b)
    if(k<key){
      if(left==nullptr){
  	left = new Node<kt,vt>{k,v,this};
	return Iterator{left};
      }
      else
  	return left->insert(k,v);
    }
    else if(k>key){
      if(right==nullptr){
  	right = new Node<kt,vt> {k,v,up};
  	return Iterator{right};
      }
      else
  	return right->insert(k,v);
    }
    else
      return Iterator{this};
  }
  // ------------------------------------------------------------------------- 
  size_t count_levels() const{
    size_t l_levels=0, r_levels=0;
    if(left)
      l_levels = 1+left->count_levels();
    if(right)
      r_levels = 1+right->count_levels();

    return std::max(l_levels, r_levels);
    }
  
};
// ************************ CLASS NODE ENDS  ****************************
// ------------------------ CLASS TREE STARTS ----------------------------
template<typename kt, typename vt>
class Tree{
private:
  Node<kt,vt>* root;
  
  Node<kt,vt>* insert_helper(kt key, vt val, Node<kt,vt>* t); // (1)(a)
  void clear_helper(Node<kt,vt>* n); // (3)(a)
  void inorderpush(Node<kt,vt>* t, std::vector<Node<kt,vt>*> &vecnodes);//(8)(a)
  Node<kt,vt>* insert_from_vector(std::vector<Node<kt,vt>*> &vecnodes,
				  int start, int end,
				  Node<kt,vt>* parent); // (8)(a)
  Node<kt,vt>* find_helper(kt key, vt val, Node<kt,vt>* root); //(9)(a)

public:
  // ----------------------------------------------------------------------
  unsigned int _size;
  unsigned int size() {return _size;} 

  Tree(){_size=0; root=nullptr;}
  
  Node<kt,vt>* insert_noiter(kt key, vt val){
    root = insert_helper(key, val, root);
    return root;
  } //(1)(a)
  
  void clear() {clear_helper(root);} // (3)(a)

  Node<kt,vt>* find_noiter(kt key, vt val){
    return find_helper(key, val, root);} //(9)(a)
  
  void balance();// (8)(a)
  // ----------------------------------------------------------------------
  class Iterator;
  
  void print(){ // (2)(b)
    auto it = cbegin();
    auto stop = cend();
    
    for(; it !=stop; ++it) {
      cout << (*it).first << " " << (*it).second << endl;
    }
  }
 
  Iterator begin() {return Iterator {root->left_most()};} // (4)(b)
  /* if(root!=nullptr)...?*/
  Iterator end() {return Iterator {nullptr};} // (5)(b)

  Iterator find(Iterator begin, Iterator end, const kt& key){ //(9)(b)
    for(; begin !=end; ++begin){
      //     cout << "Hello!" << endl;
      if ((*begin).first == key){
	cout << "Node " << key << " found." << endl;
	return Iterator {begin};
      }
    }
    cout << "Node not found." << endl;
    return Iterator {root};
  }

  Iterator insert(const kt&k, const vt&v){ // (1)(b)
    if(root==nullptr){
      root = new Node<kt,vt>{k,v,nullptr,nullptr,nullptr};
      _size = _size+1;
      return Iterator{root};
    }
    else
      _size = _size+1;
    return root->insert(k,v);
  }
  // ----------------------------------------------------------------------
  size_t count_levels() const{
    if(root ==nullptr)
      return 0;
    else
      return root->count_levels();
  }
  // ----------------------------------------------------------------------
  bool is_balanced() const{
    unsigned int n_levels = count_levels();
    unsigned int leaves = 0;
    auto it = cbegin();
    auto stop = cend();

    for(; it!=stop; ++it){
      if(it.is_leaf())
	++leaves;
      if(leaves<= pow(2, n_levels) && leaves>= pow(2, n_levels -1))
	return true;
    }
    return false;
  }
  // ----------------------------------------------------------------------
  Node<kt,vt>* create_random_tree(int N_nodes){
    create_random_tree(N_nodes, root);
    return root;
  }
  // ----------------------------------------------------------------------
  Node<kt,vt>* create_random_tree(int N_nodes, Node<kt,vt>* node){
    
    for(int i=0; i<N_nodes; i++){
      srand(time(NULL));
      int x = rand()%100 + 1;
      if(node==nullptr){
	node = new Node<kt,vt>{x,x,nullptr,nullptr,nullptr};
      }
      
      if(x < node->key)
	create_random_tree(x, node->left);
      else if (x > node->key)
	create_random_tree(x, node->right);
    }
    return node;
  }
    // ----------------------------------------------------------------------
    class ConstIterator; 
    ConstIterator cbegin()const {return ConstIterator{root->left_most()};}//(6)(b)
    ConstIterator cend() const {return ConstIterator{nullptr};} // (7)(b) 
  };
  // ------------------------ CLASS TREE ENDS ----------------------------

  template<typename kt, typename vt> //(9)(a)
  Node<kt,vt>* Tree<kt,vt>::find_helper(kt key, vt val, Node<kt,vt>* t){
    if (t!=nullptr){
      if (key == t->key){
	cout << "The inserted key = " << key << " IS in the BT." << endl;
	return t;
      }
      if (key < t->key)
	return find_helper(key, val, t->left);
      else
	return find_helper(key, val, t->right);
    }
    else
      cout << "The inserted key = " << key << " is NOT in the BT." << endl;
    return nullptr; 
  }
  // ----------------------------------------------------------------------
  template<typename kt, typename vt> // (1)(a)
  Node<kt,vt>* Tree<kt,vt>::insert_helper(kt key, vt val, Node<kt,vt>* t){ 
    if(t == nullptr) {
      cout << "Inserting node: " << key << endl;
      t = new Node<kt,vt> (key,val,nullptr,nullptr, nullptr);
      /* PERCHÈ PARENTESI TONDE?*/
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
  template <typename kt, typename vt> //(3)(a)
  void Tree<kt,vt>::clear_helper(Node<kt,vt>* n){ 
    if( n == nullptr) return;
    
    clear_helper(n->left);
    clear_helper(n->right);

    _size = _size-1;     

    delete n;
    n = nullptr;
  }
  // ----------------------------------------------------------------------
  template <typename kt, typename vt> //(8)(a)
  void Tree<kt,vt>::inorderpush(Node<kt,vt>* t,
				std::vector<Node<kt,vt>*> &vecnodes){
    if (t==nullptr)
      return;
    inorderpush(t->left, vecnodes);
    vecnodes.push_back(t);
    inorderpush(t->right, vecnodes);
  }
  // ----------------------------------------------------------------------
  template <typename kt, typename vt> //(8)(a)
  void Tree<kt,vt>::balance() {   
    std::vector<Node<kt,vt>*> _vector_of_nodes;
    _vector_of_nodes.reserve(size());
    Node<kt,vt>* t = root;
    inorderpush(t, _vector_of_nodes);
    root = insert_from_vector(_vector_of_nodes, 0, _vector_of_nodes.size()-1,
			      nullptr);
  }
  // ************************ ITERATOR STARTS ************************
  template<typename kt, typename vt>
  class Tree<kt,vt>::Iterator {
  private:
    Node<kt,vt> *current;
  
  public:
    Iterator(Node<kt,vt>* n): current{n}{} 
    std::pair<kt,vt> & operator->() {return (*this);} 
    std::pair<kt&,vt&>  operator*() const {return{current->key, current->value};}
    //  std::pair<kt,vt>  operator*() const {return{current->key, current->value};} (*)

    // ++it
    Iterator& operator++() {
      if(current){ // "if the current doesn't point to null.."
	if(current->Node<kt,vt>::right) /* "if the right of the current 
					   doesn't point to null.."*/
	  current = current->right->left_most();
	else
	  current = current->up;
      }
      return *this; 
    }
  
    bool operator==(const Iterator& other){return this->current==other.current;}
  
    bool operator!=(const Iterator& other) {return !(*this == other);}

    bool is_leaf() const{
      if(current->left==nullptr && current->right==nullptr)
	return true;
      else return false;
    }
  };
  // ************************ ITERATOR ENDS ************************
  // ++++++++++++++++++ CONST ITERATOR STARTS ++++++++++++++++++
  template<typename kt, typename vt> 
  class Tree<kt,vt>::ConstIterator:public Tree<kt,vt>::Iterator {
    using parent = Tree<kt,vt>::Iterator; // alias
  public:
    using parent::Iterator; // using the constructor of the class Iterator
    const std::pair<kt,vt> operator*() const {return parent::operator*();} 
  };
  // ++++++++++++++++++ CONST ITERATOR ENDS ++++++++++++++++++
  template<typename kt, typename vt> 
  Node<kt,vt>* Tree<kt,vt>::insert_from_vector(std::vector<Node<kt,vt>*>&vecnodes,
					       int start, int end,
					       Node<kt,vt>* parent){
    if(start>end)
      return nullptr;
    int middle = (start+end)/2;
    Node<kt,vt>* t = vecnodes[middle];
    //  if(left child: up =parent)
    // else (right child: up = up del mio parent)
    
    /* if(key< t->key)
      t->up = parent;
    else if(key > t->key)
    t->up = parent->up;*/

    
      t->up = parent; // MODIFY IT
   
    //  t->up = parent->up; => segmfault
    
    t->left = insert_from_vector(vecnodes, start, middle-1, t);
    t->right = insert_from_vector(vecnodes, middle+1, end, t->up);
    return t;
  }

  // ************************************************************************
  // MAIN
  // ************************************************************************
  int main() {
    Tree<int, int> tree{};
    cout << "-------------------------------------------------------" << endl;
    cout << "1a. INSERTING Nodes (NO Iterator)" << endl;
    Node<int,int> *root;
    root = tree.insert_noiter(6,3);
    tree.insert_noiter(2,2);
    tree.insert_noiter(1,1);
    tree.insert_noiter(7,5);
    tree.insert_noiter(5,6);
    tree.insert_noiter(4,4);
    tree.insert_noiter(3,7);
  
    cout << "The root is " << root->key << " " << root->value << "." << endl;
    cout << "Now the tree has " << tree._size << " nodes." << endl;
  
    cout << "----------------------------------------------------" << endl;
    cout << "1b. INSERTING Nodes (WITH Iterator)" << endl;
    Tree<int,int>::Iterator insert_1 = tree.insert(26,26);
    Tree<int,int>::Iterator insert_2 = tree.insert(30,30);
  
    cout << (*insert_1).first << endl;
    cout << (*insert_2).first << endl;
    cout << "Now the tree has " << tree._size << " nodes." << endl;

    cout << "Now the tree has " << tree.count_levels() << " levels." << endl;
    
    cout << "-------------------------------------------------------" << endl;
    cout << "2b. PRINTING Nodes in order rx to the key (WITH Iterator)" << endl;
    Tree<int,int>::Iterator it = tree.begin();
    Tree<int,int>::Iterator stop = tree.end();

    tree.print();
    cout << "Now the tree has " << tree._size << " nodes." << endl;
  
    cout << "-------------------------------------------------------" << endl;
    cout << "9a. FINDING  Nodes (NO Iterator)" << endl;
    tree.find_noiter(1,1); 
    tree.find_noiter(2,2); 
    tree.find_noiter(4,4);
    cout << "Now the tree has " << tree._size << " nodes." << endl;

    cout << "-------------------------------------------------------" << endl;
    cout << "9b. FINDING  Nodes (WITH Iterator)" << endl;
    it = tree.begin();
    
    clock_t pre_begin = clock();
    tree.find(it,stop,7);
    clock_t pre_end = clock();
    double pre_time = double(pre_end-pre_begin)/CLOCKS_PER_SEC;

    cout << "BEFORE the balance, the time for find node 7 is " << pre_time << " s." << endl; 
    cout << "Now the tree has " << tree._size << " nodes." << endl;

    cout << "-------------------------------------------------------" << endl;
    
      cout << "8. BALANCING the tree" << endl;

    bool pre_balance = tree.is_balanced();
    if(pre_balance == 1) 
    cout << "BEFORE the balance, the tree IS balanced." << endl;
    else
      cout << "BEFORE the balance, the tree is NOT balanced." << endl;

    tree.balance();
    
    bool post_balance = tree.is_balanced();
     if(post_balance == 1) 
    cout << "AFTER the balance, the tree IS balanced." << endl;
    else
      cout << "AFTER the balance, the tree is NOT balanced." << endl;

     clock_t post_begin = clock();
     tree.find(it,stop,7);
     clock_t post_end = clock();
     double post_time = double(post_end-post_begin)/CLOCKS_PER_SEC;

     cout << "AFTER the balance, the time for find node 7 is " << post_time << "." << endl;
     
     cout << "Now the list has " << tree._size << " elements." << endl;
     tree.print();

    cout << "-------------------------------------------------------" << endl;
    cout << "3. DELETING Nodes" << endl;
    tree.clear();
    cout << "Now the tree has " << tree._size << " nodes." << endl;
  
    cout << "-------------------------------------------------------" << endl;

    /*
    cout << "10. TESTING the performances" << endl;

    int nodes = 0;
    Tree<int, int> bin_tree{};
     
	Tree<int, int> * bin_tree = new Tree<int,int>;
	nodes = 1;
	bin_tree->create_random_tree(nodes);
	cout << "The tree has (key,value) = " << endl;
	bin_tree->print();  
	cout << "Now the tree has " << bin_tree->_size << " nodes." << endl << endl;
	bin_tree->clear(); // SE NON LO METTO, MI GENERA UN TREE CON 1 SOLO NODO :(
    */
    //  srand(time(NULL));
    /*
       nodes = 1;
       root = bin_tree.create_random_tree(nodes);
       cout << "The tree has (key,value) = " << endl;
       bin_tree.print();
    
       cout << "Now the tree has " << bin_tree._size << " nodes." << endl;
       //bin_tree.clear();

       */

    return 0;
  }

  /*
    TO DO
    -error handling
    -copy and move semantics
    -testare tutto
    -cambiare key e value (usare anche stringhe)
    -analizzare performance (scambiando anche key e value)
    -usare smart pointers
    -come organizzare std::pair

    C++ NOTES
    * std::unique_ptr Node<kt,vt>* root;
    * Reset:
    - if empty --> takes ownership of pointer;
    - if NOT empty --> deletes managed object, acquires new pointer.
     
    REFERENCES
    http://www.cplusplus.com/forum/general/147955/
    https://www.cs.helsinki.fi/u/tpkarkka/alglib/k06/lectures/iterators.html#sequential-search

    http://www.cplusplus.com/forum/beginner/74980/
    https://www.geeksforgeeks.org/how-to-determine-if-a-binary-tree-is-balanced/
    https://helloacm.com/how-to-check-balanced-binary-tree-in-cc/
    https://www.geeksforgeeks.org/a-program-to-check-if-a-binary-tree-is-bst-or-not/

  */
