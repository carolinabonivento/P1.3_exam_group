# PART 1
## BINARY TREE
1. Fundamental data structure used in computer science.
2. Useful data structure for rapidly
* storing sorted data and rapidly
* retrieving stored data.
3. Composed of parent nodes, or leaves, each of which
- stores data and also
- links to up to two other child nodes (leaves) which can be visualized
spatially as below the first node with one placed to the left and
with one placed to the right
4. Efficient data structure due to the relationship between the leaves
linked to and the linking leaf, also known as the parent node.
5. Composed of leaves: on the
* left: lesser key value
* right: equal or greater key value
6. Due to this nature, it is possible to easily access and insert data
in a binary tree using search and insert functions recursively called
on successive leaves
7. Begins with a root node, which contains the original key value.
The root node has two child nodes, each of us might have its own child nodes
8. Ideally, the tree would be structured so that it is a perfectly
balanced tree, with each node having the same number of child nodes
to its left and to its right.
9. A perfectly balanced tree allows for the fastest average insertion
or retrieval of data. The worst case scenario is a tree in which each node
only has one child node, so it becomes as if it were a linked list
in terms of speed.
10. The typical representation of a binary tree looks like the following:

						       10
						     /    \
						    6      14
						   / \    /  \
						  5   8  11  18
## FUNCTIONS
The structure of a binary tree makes the insertion and search functions
simple to implement using recursion.
In fact, the two
- insertion and
- search functions
are also both very similar.

### INSERT FUNCTION
1. To insert data into a binary tree involves a function searching for
an unused node in the proper position in the tree in which to insert
the key value.
2. The insert function is generally a recursive function that continues
moving down the levels of a binary tree until there is an unused leaf
in a position which follows the rules of placing nodes.
3. Following the rules, an insert function should check each node to see
if it is empty: if so, it would insert the data to be stored along
with the key value.
4. In most implementations, an empty node will simply be a NULL pointer
from a parent node, so the function would also have to create the node.
5. If the node is filled already, the insert function should check to see
if the key value to be inserted is
* less than the key value of the current node: the insert function should be
recursively called on the left child node
* greater than or equal to the key value of the current node: the insert
function should be recursively called on the right child node.

### SEARCH FUNCTION
1. It should check to see if the key value of the current node is
the value to be searched.
If not, it should check to see if the value to be searched for is
* less than the value of the node: should be recursively called on
the left child node
* greater than the value of the node: it should be recursively called on
the right child node.
2. It is also necessary to check to ensure that the left or right
child node actually exists before calling the function on the node.
3. Because binary trees have log2N layers,
the average search time for a binary tree is log2N. (a)
4. To fill an entire binary tree, sorted, takes roughly N*log2N (b)

## CODE
...






*****************************************************************************
# QUESTIONS
(a) Perchè il binary tree ha log2(N) layer? N=n° di elementi?
(b) Perchè anniamo che
- tempo medio di ricerca di un elemento =   log2N
- tempo per riempire tutto il tree      = N*log2N (search/insert)
??

Come ci si divide il lavoro? Funzioni diverse a testa??