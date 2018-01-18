(1) Ero nel branch elisa,
ho fatto i commit delle cose modificate
git push origin elisa

Perchè mette la freccia verde sotto quella azzurra??
Non dovrei essere sempre nel branch elisa?

(2) Metodo per essere tutti allo stesso livello (collaboratori),
quale scegliere?

***************************************************************************
 1) Differenza tra key e value per il nodo
 
 2) Impostare i template:
    uno per a key --> pointer to int/double
    uno per il value --> int/double

3) Key di un nodo è dinamica (cambia ogni volta che inseriamo un elemento)?

4) Cosa significa un tree bilanciato?
Cioè se abbiamo come elemento maggiore nel tree un 11 e gli elementi
che vogliamo inserire da un momento in poi sono tutti maggiori di 11,
è ovvio che andranno tutti a destra... e quindi come lo bilanciamo?

5) Funzionamento Find: dobbiamo sempre partire dalla root o
possiamo partire da un certo valore di una key?

6)Performance: come misurarle? Come contare il n° di mosse che facciamo
per trovare un elemento?
*****************************************************************************
ALBERTO
chiave: intero
valore: stringa
swappare e vedere come cambia le performance
cosa scegliere

APPUNTI
PARTE OPZIONALE: templetizzare
confrontare le performance con stdmap
usiamo esplicitamente il termine minore

Node ...
....
std::unique_ptr<Node>left
*****************************************************************************
*** CLASS TREE ***
template<typename kt, typename vt>
class tree{
//std::pair (iterator insert(const kt&k, const vt&v){
iterator insert(const kt&k, const vt&v){
if(root==NULLPTR)
root.reset(new Node{k,v,NULLPTR})
return iterator{root.get()};
else
return root->insert(k,v)
//return {iterator root->insert(k,v),bool}
}

std::unique_ptr<Node>root=NULLPTR;
*****************************************************************************
*** INSERT ***
struct Node{
iterator insert(const kt&k, const vt&v);
if(k<key){
if(left==NULLPTR)
left.reset(new Node{k,v,this});
return iterator{left.get()};
else
return left->insert(k,v);
}
else if(k>key){
if(left==NULLPTR)
right.reset(new Node{k,v,up});
else
right->insert(k,v);
}
else {
return iterator{this}
}
*****************************************************************************
return an iterator to teh node
better
k=key -->overwrite/NOT overwrite
by default std::map ignore the new value
*****************************************************************************
ITERATOR
struct, class which internally has a row pointer to a node
watcher, NOT deallocate
navigate
class iterator should be derived from something
****************************************
struct iterator public
iterator(Node* n), current{n}{}{
std::pair<kt,vt> operator*(){return{current->key, current->value};}
// dereference operator
std::pair<kt,vt> operator->(){return (*this) }
operator++(){"update current"", return this} // PRE
// how to go the next position
// --> return a reference to iterator
operator++(int){"create  current", update current, return other} // POST
// how to go the next position POST
Node * current;
}
*****************************************************************************
// FOR LOOP: the same
for (i=0;i<10;++i){

}

++it // pre-increment
it++ // post-increment

DIFFERENCE
i=0
std::cout << i++; // 0 
std::cout << i; // 1

std::cout << ++i; // 1 update current value and return myself
std::cout << i; // 1
*****************************************************************************
*** PRE ***
double& operator++(double&v){v+=1;return v}
// value updated and returned

*** POST ***
double& operator++(int, double&v){
double other=v;
v+=1;
return other; // return the old one
}
*****************************************************************************
Iterator:
PRE is better
POST: we're creating a new value, worst on a memory point of view
*****************************************************************************
OPTION 1 --> SOME INFOS ARE MISSING...
template<class kt,class vt>

void tree<kt,vt> print(){
if(root==NULLPTR)
std::cout<<"Empty tree\n";
else
root->print();
*it.first;
*it.first;
}
******************************************
OPTION 2
template<class kt,class vt>

void tree<kt,vt> print(){
if(root==NULLPTR)
std::cout<<"Empty tree\n";
else
root->print_recursive();

auto it=begin(); // return the left most mode
// return an iterator constructed
// return{root{root->left_most()};}

// auto: return a specific type
auto last=end(); {return iterator{root->up};
{if (right!=NULLPTR) right->print_recursive();
// tree<kt,vt>..iterator = auto: alias
// checked at compile time
for( ; it=last, ++it)
*it.first;
*it.second;
it->first;
//it->print();
//it.print();
}

ITERATOR 
aim: exposed us to stored data, no matter how they are organized 
*****************************************************************************
PRINT RECURSIVE
void Node print_recursive(){
if(left!=NULLPTR)
left->print_recursive();

std::cout<<key <<"" << value <<"\n";

if(right!=NULLPTR)
right->print_recursive();
*****************************************************************************
Node *left_most(){
if(left)
return left->left_most();
else
return this; // not star because it's a pointer
}
*****************************************************************************
OPERATOR ++ // want to move forward
//double& operator++(double&v){v+=1;return v}
// The class iterator is NOT a node, so we can't use only right
iterator& operator++(){
if(current->right)
current=current->right->left_most();
else
current=current->up;
return *this; 
// * because we are returning a reference, so we de-reference the pointer
// if I can go left, go left and print
*****************************************************************************
if(k<key)
if(!left)
light reset(new Node{k,v,up}

UP POINTER
the up is a row because many pointers point to teh same stuff


SMART POINTER
when we want to express the ownership 
only a node will be able to deallocate

*****************************************************************************
FIND FUNCTION
should not use iterator

