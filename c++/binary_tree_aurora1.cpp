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
    node* left,right;
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
  
    node<kt,vt>* root;  //std::unique_ptr< node<kt,vt> > root=nullptr;
    unsigned int _size; //private variable to keep tree size

    
    public:
    
    Tree();
    
  
  




};

template<typename kt, typename vt>
Tree<kt,vt>::Tree(){  //default cosntructor for Tree
    _size=0;
    root=nullptr;
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
    
}


