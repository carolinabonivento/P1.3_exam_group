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
class node //class node implementation (outside tree)
{
public:
    
    kt key; //PROVARE A USARE PAIR 
    vt val;
    node* left;
    node* right;
    node* up = nullptr;
    node();  //add default constructor senno nn compila ..serve x classe standad vector
    node (const kt& k = kt(), const vt& v = vt(), node* l = nullptr, node* r = nullptr): key(k),val(v),left(l), right(r) {}  //costructor con i valori di default
//k and v are dummy variables that live only here
};

template <typename kt, typename vt>
node<kt,vt>::node(){    //implementation of the default constructor
    left=nullptr;
    up=nullptr;
    right=nullptr;
    val = vt();
    key = kt();  //default constructor explicitely use default constructors for the types kt, vt
    
}

// *** END CLASS NODE ********


// *** BEGIN CLASS TREE ********

//DEFINIZIONE  della `insert helper`

template<typename kt, typename vt>
class Tree
{
    private:
    
    //helper function private to implement recursion
    node<kt,vt>* insert_helper(kt key, vt val, node<kt,vt>* t); //insert helper needs key value and root
                                                                //the first time (e.g. key 7, val 7) they are 7, 7, nullptr
                                                                //because I initialize with root=nullptr
    void clear_helper(node<kt,vt>* n); //clear_helper needs a variable pointer to node
  
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

//FUNZIONE `insert_helper`
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



template <typename kt, typename vt>
void Tree<kt,vt>::clear_helper(node<kt,vt>* n){
    if( n == nullptr) return;
    
    clear_helper(n->left);// if(n->left != nullptr) clear_helper(n->left);
    clear_helper(n->right);// if(n->left != nullptr) clear_helper(n->left);
    
    delete n;
    n = nullptr;
}

// *** END CLASS TREE ********

// *** MAIN ********

int main(){
    
    Tree<int,int> t{};
    
    cout << "Insert nodes... " << endl;
    t.insert_noiter(7,7); //insert_noiter(key,value)
    t.insert_noiter(3,3);
    t.insert_noiter(13,13);
    t.insert_noiter(14,14);
    t.insert_noiter(4,4);
    
    
    t.clear();

    
}


