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
    
    kt key;
    vt val;
    node* left;
    node* right;
    node* up = nullptr;
    node();  //add default constructor
    node (const kt& k = kt(), const vt& v = vt(), node* l = nullptr, node* r = nullptr): key(k),val(v),left(l), right(r) {}  //costructor con i valori di default
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

template<typename kt, typename vt>
class Tree
{
    private:
 
    Iterator<kt,vt> insert(const kt& k, const vt& v);  //since iterator class is defined outside Tree, here requires <kt,vt>
    
    //helper function private to implement recursion
    node<kt,vt>* insert_helper(kt key, vt val, node<kt,vt>* t);
    void clear_helper(node<kt,vt>* n);
  
    node<kt,vt>* root;  //std::unique_ptr< node<kt,vt> > root=nullptr;
    unsigned int _size; //private variable to keep tree size

    
    public:
    
    Tree();
    void insert_noiter(kt key, vt val) {root = insert_helper(key, val, root);}
       void clear() {clear_helper(root);}
  
  




};

template<typename kt, typename vt>
Tree<kt,vt>::Tree(){  //default cosntructor for Tree
    _size=0;
    root=nullptr;
}


template<typename kt, typename vt>
node<kt,vt>*  Tree<kt,vt>::insert_helper(kt key, vt val, node<kt,vt>* t)
{
    
    if(t == nullptr)
    {
        cout << "creazione nodo: " << key << endl;
        t = new node<kt,vt>(key,val,nullptr,nullptr);
        _size = _size+1;
        
    }
    else if(key < t->key){
        
        t->left = insert_helper(key, val, t->left); //cout << "node current L "<< t->key << endl;
        t->left->up = t;
    }
    else if(key > t->key){
        
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
    t.insert_noiter(7,7);
    t.insert_noiter(3,3);
    t.insert_noiter(13,13);
    t.insert_noiter(14,14);
    t.insert_noiter(4,4);
    
    
    t.clear();

    
}


