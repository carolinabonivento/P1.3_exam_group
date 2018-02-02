#include <iostream>
#include <memory> // needed for smart pointers


using std::cout;
using std::endl; //instead of loading all the std::functions, only these one, for avoid possible conflicts

// **************************************************************************
// FUNCTION DECLARATION AND DEFINITION
// **************************************************************************

template <typename kt, typename vt> class Tree; //class declaration
template <typename kt, typename vt> class Iterator; //class declaration needed so that Tree compiles


// *** BEGIN CLASS NODE ********

template <typename kt, typename vt>
class node //class node implementation (outside tree) . Not struct because we want to be able to use the inheritance
           //for instance if we want to use a function with a modified member we need only to derive the previous class
           //node adding the new member ..see linked list
{
public:
    
    kt key; //key and value in a pair: to do!
    vt val;
    node* left;  //should be unique pointer
    node* right; //should be unique pointer
    node* up = nullptr; //might be non smart pointer
    node();  //add default constructor senno nn compila ..serve x classe standad vector
    node (const kt& k = kt(), const vt& v = vt(), node* l = nullptr, node* r = nullptr): key(k),val(v),left(l), right(r) {}  //costructor con i valori di default
//k and v are dummy variables that live only here
};

template <typename kt, typename vt> //
node<kt,vt>::node(){    //implementation of the default constructor
    left=nullptr;
    up=nullptr;
    right=nullptr;
    val = vt();
    key = kt();  //default constructor explicitely use default constructors for the types kt, vt
    
}


//examples
//mionodo = node<int,int>(4,5,nullptr, puntatore_auro);
//mionodo know that key = 4, val = 5, left = NULL, right = puntatore_auro.
//cout << mionodo->key  ///prints 4

//on the other hand
//mionodo = node<int,int>();
//gets default members (esempio val = 0, key = 0, left, right= NULL)
//cout << mionodo->key   ///prints 0


// *** END CLASS NODE ********


// *** BEGIN CLASS TREE ********

template<typename kt, typename vt>
class Tree
{
    private:
 
    Iterator<kt,vt> insert(const kt& k, const vt& v);  //since iterator class is defined outside Tree, here requires <kt,vt>
                                                       //pay attention private and public!!!
                                                       //if we put print private we will not be able to use it in the main
    
    //helper function private to implement recursion
    node<kt,vt>* insert_helper(kt key, vt val, node<kt,vt>* t); //insert helper needs key value and root
                                                                //the first time (e.g. key 7, val 7) they are 7, 7, nullptr
                                                                //because I initialize with root=nullptr
                                                                //important: every time i insert a new element i start from root!!
                                                                //insert helper is a recursive function
    void clear_helper(node<kt,vt>* n); //clear_helper function defined here: needs a variable pointer to node
  
    node<kt,vt>* root;  //std::unique_ptr< node<kt,vt> > root=nullptr;
    unsigned int _size; //private variable to keep tree size

    
    public:
    
    Tree();
    void insert_noiter(kt key, vt val) {root = insert_helper(key, val, root);} //insert_noiter recalls insert helper (wrapper of insert_helper)
                                                                               //i called it insert_noiter because I do not use iteratorsyet.
       void clear() {clear_helper(root);}                                      //clear calls clear helper starting from the root
                                                                               //if root does not exist it does return
                                                                               //otherwise it checks left and then right until right == nulptr
                                                                               //i need clear to delete the tree and have 0 leaks with valgrind
  
  

};

template<typename kt, typename vt>
Tree<kt,vt>::Tree(){  //default cosntructor for Tree
    _size=0; // at the beginning the tree is empty, size = 0
    root=nullptr;
}


template<typename kt, typename vt>
node<kt,vt>*  Tree<kt,vt>::insert_helper(kt key, vt val, node<kt,vt>* t) //key,val,root ..insert helper ricorre dentro se stessa
{
    
    if(t == nullptr) //if root == nullptr I create the first node 
    {
        cout << "creazione nodo: " << key << endl;
        t = new node<kt,vt>(key,val,nullptr,nullptr); //the first node has a key, a value and points to nullptr and nullptr left and right
        _size = _size+1; // when I create the first node the size of the tree increases and so on...
                         //every time i define a newnode a redefine the parent
        
    }
    else if(key < t->key){ //if the key of the new node is smaller than put it left
        
        t->left = insert_helper(key, val, t->left); //cout << "node current L "<< t->key << endl;
        t->left->up = t;
    }
    else if(key > t->key){ //if the key of the new node is bigger than put it left
        
        t->right = insert_helper(key, val, t->right); //cout << "node current R "<< t->key << endl;
        t->right->up = t;
    }
    return t;
}



template <typename kt, typename vt>  //it cleans the tree removing the nodes
void Tree<kt,vt>::clear_helper(node<kt,vt>* n){ //function implemented here .. void because it does not return anything
                                                //it is a member of the class tree
                                                //n dummy variable for node
    if( n == nullptr) return; //when the current node is null, return!! see picture
    
    clear_helper(n->left);// if(n->left != nullptr) clear_helper(n->left);
    clear_helper(n->right);// if(n->left != nullptr) clear_helper(n->left);
    
    delete n;
                                //first i delete the leaves and then,when there are no more leaves, i delete the root.
                                //if n is a leaf (n!=NULL) that exists and it points to null and null (left and right)
                                //when clear_helper(n->left) and n->left = NULL
                                //and
                                //clear_helper(n->right) and n-->right = NULL
                                //I can delete n and substitute it with null
                                //and procede to delete the other leaves
    n = nullptr;
}

// *** END CLASS TREE ********


// *** BEGIN CLASS ITERATOR TREE ********

template<typename kt, typename vt>
class Iterator //  remove Tree<kt,vt>::Iterator because is defined outside Tree class
{
private:
   
    node<kt,vt> *current;
    // ************************************************************************
public:
    Iterator(node<kt,vt>* n) : current(n){} //CHANGED IN THIS TO COMPILE
    
    std::pair<kt,vt> operator->() {return (*this);} // (b)
    std::pair<kt,vt> operator*() {return{current->key, current->value};} // (c)
    
    Iterator& operator++() // (d)
    {
    }
    
    Iterator operator++(int) // (e)
    {
    }
    
};

// *** END CLASS ITERATOR TREE ********

int main(){
    
    Tree<int,int> t{};
    
    cout << "Insert nodes... " << endl;
    t.insert_noiter(7,7); //insert_noiter(key,value) ...it is a wrapper for insert_helper
    t.insert_noiter(3,3);
    t.insert_noiter(13,13);
    t.insert_noiter(14,14);
    t.insert_noiter(4,4);
    
    
    t.clear();

    return 0;

    
}


/*

useful references:

https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/

https://www.geeksforgeeks.org/binary-search-tree-insert-parent-pointer/

https://www.geeksforgeeks.org/write-a-c-program-to-delete-a-tree/
*/

