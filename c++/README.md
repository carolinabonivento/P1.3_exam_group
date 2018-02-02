# BINARY TREE
## Introduction
1. Useful data structure for rapidly
* storing sorted data and rapidly
* retrieving stored data.
2. Composed of parent nodes, which
- store data and
- link to up to two other child nodes which can be visualized
spatially as below the first node with one placed to the left and
with one placed to the right
3. Composed of leaves: on the
* left: lesser key value
* right: equal or greater key value
4. Begins with a root node, which contains the original key value.
The root node has two child nodes, each of us might have its own child nodes
5. Ideally, the tree would be structured so that it is a perfectly
balanced tree, with each node having the same number of child nodes
to its left and to its right. (INSTEAD Alberto told: balanced if every layer
has the SAME n° of nodes !!!)
6. A perfectly balanced tree allows for the fastest average insertion
or retrieval of data. The worst case scenario is a tree in which each node
only has one child node, so it becomes as if it were a linked list
in terms of speed.
7. The typical representation of a binary tree looks like the following:
                         10
                       /    \
                     6      14
                    / \    /  \
                   5   8  11  18
## Functions
### Insert
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

### Search
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
the average search time for a binary tree is log2N.
To fill an entire binary tree, sorted, takes roughly N*log2N.

... TO BE CONTINUED ...
