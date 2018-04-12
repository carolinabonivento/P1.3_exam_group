#include <iostream>


using std::cout;
using std::endl;

template <typename kt, typename vt> class Tree;
template <typename kt, typename vt> class Iterator;

// *** BEGIN CLASS NODE ********

template <typename kt, typename vt>
class node

{
public:
    
    kt key;
    vt val;
    node* left;
    node* right;
    node* up = nullptr;
    node();
    node (const kt& k = kt(), const vt& v = vt(), node* l = nullptr, node* r = nullptr): key(k),val(v),left(l), right(r) {}
    
// *** NEW NODE FOR COPY ***
    // the copy constructor must mantiain the same order of the arguments as the orignal constructor of the nodes of the old tree
    //??? does it copy both keys and value or keys only

    node (node* orig, node* p):key(orig->key), val(orig->val), up(p) {
        if (orig->left)
            left=new node (orig->left, this);
        if (orig->right)
            right=new node (orig->right, up);
    }
    
    
    
};


// *** BEGIN CLASS TREE ********

template <typename kt, typename vt>
node<kt,vt>::node(){
    left=nullptr;
    up=nullptr;
    right=nullptr;
    val = vt();
    key = kt();
}

// *** BEGIN CLASS TREE ********

template<typename kt, typename vt>
class Tree
{
    //private:
    
public:
    
    
    node<kt,vt>* insert_helper(kt key, vt val, node<kt,vt>* t);
    
    void preorder(node<kt,vt>* t);
    // this is the node that will be in the copyed tree. it points to the target node of the orignial old tree and to up.
    node<kt,vt>* copy(node<kt,vt>* orig, node<kt,vt>* p);
    
    //----------------------------------------
    
    node<kt,vt>* root;
    
    void insert_noiter(kt key, vt val) {root = insert_helper(key, val, root);}
    
    void print_preorder() {cout << "Print preorder: key " <<endl; preorder(root); cout << endl;}
    
    //-----------------------------------------
    
    Tree() {root=nullptr;}
    
    // *** COPY SEMANTIC ***
    // when the program calls a copy, this brings here at the copy semantic function. This says: copy 'other' (where other= old tree). other.root= root of the old tree. the construcor is this: node<kt,vt>* copy(node<kt,vt>* orig, node<kt,vt>* p);
    
    Tree (const Tree& other){
        //std::cout << "dovrei copiare ma non mi va\n";
        
        if(other.root !=nullptr)
            root= new node<kt,vt>{other.root, nullptr};
    }
    //-------------------------------------------------
    
    // *** MOVE SEMANTIC ***
    //other=old tree
    
    Tree( Tree&& other){
        root = other.root;
     
    }
};


template<typename kt, typename vt>
node<kt,vt>*  Tree<kt,vt>::insert_helper(kt key, vt val, node<kt,vt>* t)

{
    
    if(t == nullptr)
    {
        cout << "creazione nodo: " << key << endl;
        t = new node<kt,vt>(key,val,nullptr,nullptr);
        
    }
    else if(key <= t->key){
        
        t->left = insert_helper(key, val, t->left);
        
        t->left->up = t;
    }
    else if(key > t->key){
        
        t->right = insert_helper(key, val, t->right);
        
        t->right->up = t;
    }
    return t;
}


template <typename kt, typename vt>
void Tree<kt,vt>::preorder( node<kt,vt>* t) //function for pre-order traversal
{
    if (t == nullptr)
        return;
    
    if(t->left)
        preorder(t->left);
        
    cout << t->key << " ";
    
    if(t->right)
        preorder(t->right);
}


int main(){
    
    //this initialize the original tree
    Tree<int,int> t{};
    
    cout << "Insert nodes... " << endl;
    //t.func = call the function that is in class tree
    t.insert_noiter(7,7);
    t.insert_noiter(3,3);
    t.insert_noiter(13,13);
    t.insert_noiter(14,14);
    t.insert_noiter(4,4);
    t.insert_noiter(1,1);
    t.insert_noiter(6,6);
    t.insert_noiter(10,10);
    t.insert_noiter(8,8);
    t.insert_noiter(18,18);
    t.insert_noiter(27,27);
    t.insert_noiter(35,35);
    t.insert_noiter(9,9);
    t.insert_noiter(0,0);

    cout << "COPY " << endl;
    // c{t} means: "do a copy (called c) of the original tree (called t)
    Tree<int,int> c{t};
    
    cout << "this is the old tree" << endl;
    t.print_preorder();
    cout << "this is the copied tree" << endl;
    c.print_preorder();
    
    cout << "MOVE " << endl;
    Tree<int,int> m{std::move(t)};
    std::cout << "moved tree\n";
    m.print_preorder();
    std::cout << "old tree\n";
    t.print_preorder();
    
    
    
    
    

    
}


