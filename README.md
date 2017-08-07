# RBT
A red–black tree is a kind of self-balancing binary search tree. Each node of the binary tree has an extra bit, and that bit is often interpreted as the color (red or black) of the node. These color bits are used to ensure the tree remains approximately balanced during insertions and deletions. Though it is not perfectly balanced tree, it is good enough to allow it to guarantee searching in O (log n).

ALGORITHM

Insert:
Step 1: Start
Step 2 : If tree empty create BLACK root node else go to Step 3.
Step 3: Insert new LEAF node as RED.
Step 4: If parent is BLACK then done.
Step 5: if parent is RED then check for sibling .
Step 6: If sibling is BLACK or absent then rotate and 
recolor.
Step 7: If sibling is RED then recolor and check.
Step 8: stop

Search:
Step 1: Start
Step 2: Check root is empty it returns NULL means base case.
Step 3: Check the given value present at left by calling the search function recursively for left side node
Step 4: Check the given value present at right by calling 
the search function recursively for right side node
Step 5 : If the value is found in either of the node it returns 
non nagative value else it returns 0
Step 8: Stop 

Find max:
Step 1: Start

Step 2: check for root->right is not equal to NULL.

Step 3: call the  find max function recursively at right side of the Tree and returns the max value from right.
 
Step 8: Stop

Find min:
Step 1: Start

Step 2: Check the root->left is not equal to NULL
 
Step 3: Call the  find min function recursively at left side of             the tree which returns the min value from left.

Step 4: Stop 

Delete:
Step 1: Start
Step 2:  check for the base case
Step 3:  if root->data  greater than value call delete node  function recursively at right side of the tree
Step 4:  if root->data  less than value call delete node function recursively at left  side of the tree.
Step 5:  if root->left is equal to NULL then root->right has some value store that into temp variable. Free that root and connect temp content to node above the root.
Step 6: if root->right is equal to NULL  then root->left has some value store that into temp variable .free that root and connect to above the root
Step 7:  to handle the multi child  find the successive min from right  and delete the node  and replace the min.
Step 8: Stop
