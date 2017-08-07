#include <stdio.h>
#include <stdlib.h>
#include <rbtree.h>

// Left line rotation to right
void left_left_rotation(rbtree **grand_parent)
{
 	rbtree *parent = (*grand_parent)->left;

	(*grand_parent)->left = parent->right;
	parent->right = *grand_parent;
	*grand_parent = parent;
	
	// Recolor
	parent->color = BLACK;
	parent->right->color = RED;

}

// Right line rotation to left
void right_right_rotation(rbtree **grand_parent)
{
 	rbtree *parent = (*grand_parent)->right;

	(*grand_parent)->right = parent->left;
	parent->left = *grand_parent;
	*grand_parent = parent;

	// Recolor
	parent->color = BLACK;
	parent->left->color = RED;
}

// Left traingle rotate 
void left_rotate(rbtree **grand_parent)
{
 	rbtree *parent = (*grand_parent)->left;
 	rbtree *child = (*grand_parent)->left->right;

	(*grand_parent)->left = child;
	parent->right = child->left;
	child->left = parent;

}

// Right triangle rotate
void right_rotate(rbtree **grand_parent)
{
	rbtree *parent = (*grand_parent)->right;
	rbtree *child = (*grand_parent)->right->left;

	(*grand_parent)->right = child;
	parent->left = child->right;
	child->right = parent;

}

// Balance tree
void balance_tree(rbtree *main_root, rbtree **grand_parent, int r_value)
{
	// If left child is red
	if (r_value == LEFT)
	{
		// If parent's sibling is red
		if ((*grand_parent)->right != NULL && (*grand_parent)->right->color == RED)
		{
			// Recolor the parent and its sibling
			(*grand_parent)->left->color = BLACK;
			(*grand_parent)->right->color = BLACK;

			// Rocolor the grandparent
			if (*grand_parent != main_root)
			{
				(*grand_parent)->color = RED;
			}
		}

		// If the sibling is black or absent
		else if ((*grand_parent)->right == NULL || (*grand_parent)->right->color == BLACK)
		{
			// Check for parents's left child's color
			if ((*grand_parent)->left->left != NULL && (*grand_parent)->left->left->color == RED)
			{
				// Left line rotation to right 
				left_left_rotation(grand_parent);
			}
	
			// Check parent's right child's color
			else if ((*grand_parent)->left->right != NULL && (*grand_parent)->left->right->color == RED)
			{
				// Left triangle rotate
				left_rotate(grand_parent);

				// Left line rotation to right
				left_left_rotation(grand_parent);
			}
		}
	}

	// If right child is red
	if (r_value == RIGHT)
	{
		// If parent's sibling is red
		if ((*grand_parent)->left != NULL && (*grand_parent)->left->color == RED)
		{

			// Recolor the parent and the sibling
			(*grand_parent)->right->color = BLACK;
			(*grand_parent)->left->color = BLACK;

			// Recolor the grandparent
			if (*grand_parent != main_root)
			{
				(*grand_parent)->color = RED;
			}
		}

		// If the parent's sibling is black or absent
		else if((*grand_parent)->left == NULL || (*grand_parent)->left->color == BLACK)
		{
			
			// Check for parent's right child's color
			if ((*grand_parent)->right->right != NULL && (*grand_parent)->right->right->color == RED)
			{
				// Right line rotation to left
				right_right_rotation(grand_parent);
			}

			// Check for parent's left child's color
			else if ((*grand_parent)->right->left != NULL && (*grand_parent)->right->left->color == RED)
			{
				// Right triangle rotation
				right_rotate(grand_parent);

				// Right line rotation to left
				right_right_rotation(grand_parent);
			}
		}

	}
}

// Create and insert new node other than the root
int rb_create_tree(rbtree *main_root, rbtree **root, int data)
{
	int r_value;

	// Create new node
	if (*root == NULL)
	{
		*root = malloc(sizeof(rbtree));
		(*root)->left = NULL;
		(*root)->right = NULL;
		(*root)->data = data;
		(*root)->color = RED;
		return (*root)->color;
	}

	// Insert data to the right
	if (data > (*root)->data)
	{
		r_value = rb_create_tree(main_root, &(*root)->right, data);

		// Balance the tree
		if (r_value == CHECK)
		{
			balance_tree(main_root, root, RIGHT);
			return (*root)->color;
		}
	}

	// Insert data to the left
	else if (data < (*root)->data)
	{
		r_value = rb_create_tree(main_root, &(*root)->left, data);
	
		// Balance the tree
		if (r_value == CHECK)
		{
			balance_tree(main_root, root, LEFT);
			return (*root)->color;
		}
	}

	else
		printf("Data already exists..!!\n");

	// Check for red-red violation
	if ((*root)->color == r_value && r_value == RED)
		return CHECK;
	
	return (*root)->color;
}

// Create root and insert new node
rbtree *rb_insert_tree(rbtree *root, int data)
{
	// Create root
	if (root == NULL)
	{
		root = malloc(sizeof(rbtree));
		(root)->left = NULL;
		(root)->right = NULL;
		(root)->data = data;
		(root)->color = BLACK;
		return root;
	}

	else
	{
		// Insert nodes other than root
		rb_create_tree(root, &root, data);
		return root;
	}
}

// Calculate height of the tree
int rb_height_tree(rbtree *root)
{
	int left_ht, right_ht;

	// If root is NULL
	if (root == NULL)
		return 0;
	
	else
	{
		// Calculate the left side height of the tree
		left_ht = rb_height_tree(root->left);

		// Calculate the right side height of the tree
		right_ht = rb_height_tree(root->right);

		// Compare the left and right side height of the tree and return the greatest height
		if (left_ht > right_ht)
			return (left_ht + 1);
		else
			return (right_ht + 1);
	}
}

// bfs function
void rb_bfs(rbtree *root, int breadth)
{	
	// If breadth is zero
	if (breadth == 0)
	{
		// If root is not null
		if (root != NULL) 
		{
			if (root->color == RED)
				printf(CRED "%d\t" RESET, root->data);
			else if (root->color == BLACK)
				// Print the root data
				printf("%d\t", root->data);
		}
	}

	// If root is not null
	else if (root != NULL)
	{
		// Move to the left node 
		rb_bfs(root->left, breadth - 1);
		
		// Move to the right node
		rb_bfs(root->right, breadth - 1);
	}
	
}

// Bfs print
void rb_bfs_print(rbtree *root)
{
	int height, idx;

	// Calculate the height of the tree
	height = rb_height_tree(root);

	// Print the tree level by level
	for (idx = 0; idx < height; idx++)
	{
		rb_bfs(root, idx);
		printf("\n");
	}
}

// bfs node search 
int rb_bfs_search(rbtree *root, int breadth, int value)
{
	// If breadth is zero and root is not null
	if (breadth == 0 && root != NULL)	
	{
		// if value is found in the root
		if (root->data == value)
			return 1;
		else 
			return 0;
	}

	// If value is not found in the root
	else if (root != NULL)
	{
		// Search in the left side of the tree
		if (rb_bfs_search(root->left, breadth - 1, value))
			return 1;

		// Search in the right side of the tree
		else if (rb_bfs_search(root->right, breadth - 1, value))
			return 1;
		else
			return 0;

	}

	else
		return 0;
}

// Bfs search and print
void rb_bfs_search_print(rbtree *root, int value)
{
	int height, idx, flag = 0;

	// Calculate the height
	height = rb_height_tree(root);

	// Search for node level by level
	for (idx = 0; idx < height; idx++)
	{
		// If found
		if (rb_bfs_search(root, idx, value))
		{
			// Print the data
			printf("Value found at level %d\n", idx);
			flag = 0;
			break;
		}

		else 
			flag = 1;
	}

	// If not found
	if (flag)
		printf("Value not found\n");
}

// Find minimum node
int rb_find_min(rbtree *root)
{
	// If root is NULL
	if (root == NULL)
		printf("No tree available\n");

	// Get to the left most node
	if (root->left != NULL)
		return rb_find_min(root->left);

	// Return the data
	return root->data;
}

// Find maximum node
int rb_find_max(rbtree *root)
{
	// If root is NULL
	if (root == NULL)
		printf("No tree available\n");

	// Get to the right most node
	if (root->right != NULL)
		return rb_find_max(root->right);

	// Return the data
	return root->data;
}

int case_1(rbtree *m_root, rbtree **root)
{
	if (*root == m_root)
		return STOP;
}

int case_2(rbtree *m_root, rbtree **root)
{
	right_right_rotation(root);
	select_case(m_root, &(*root)->left);
}

int case_flag;

int case_3(rbtree *m_root, rbtree **root)
{
	(*root)->right->color = RED;

	if (*root == m_root)
		case_1(m_root, root);
	else 
		case_flag = 1;
}

int case_4(rbtree *m_root, rbtree **root)
{
	(*root)->color = BLACK;
	(*root)->right->color = RED;

	return STOP;
}

int case_5(rbtree *m_root, rbtree **root)
{
	right_rotate(root);

	(*root)->right->color = BLACK;
	(*root)->right->right->color = RED;
	select_case(m_root, root);
}

int case_6(rbtree *m_root, rbtree **root)
{
	int flag_1 = 1;

	if (*root == m_root)
		flag_1 = 0;
	
	rbtree *parent = (*root)->right;

	(*root)->right = parent->left;
	parent->left = *root;
	*root = parent;

	parent->right->color = BLACK;
	parent->right->color = BLACK;

	if (parent->left->left == NULL && flag_1)
		parent->color =  RED;

	return STOP;
}

int select_case(rbtree *m_root, rbtree **root)
{

	if((*root)->color == BLACK && (*root)->right->color == RED)
	{
		if ((*root)->right->right == NULL && (*root)->right->left == NULL || (*root)->right->right->color == BLACK && (*root)->right->left->color == BLACK)
			case_2(m_root, root);
	}

	else if ((*root)->color == BLACK && (*root)->right->color ==  BLACK)
	{
		if ((*root)->right->right == NULL && (*root)->right->left == NULL || (*root)->right->right->color == BLACK && (*root)->right->left->color == BLACK)

			case_3(m_root, root);
	}

	else if ((*root)->color == RED)
		case_4(m_root, root);

	else if ((*root)->color == BLACK && (*root)->right->color ==  BLACK && (*root)->right->left->color == RED && (*root)->right->right == NULL || (*root)->right->right->color == BLACK )
		case_5(m_root, root);

	else if ((*root)->right->color == BLACK && (*root)->right->right != NULL && (*root)->right->right->color == RED)
		case_6(m_root, root);
}

int dl_flag, a_flag, b_flag;

// Delete node
rbtree *rb_delete_node(rbtree *main_root, rbtree *root, int value)
{
	rbtree *tmp;
	int min;

	// Check for empty tree
	if (root == NULL)
		printf("Tree is empty\n");

	else
	{
		// Search the value in left side
		if(root->left != NULL && root->data > value)
		{
			root->left = rb_delete_node(main_root, root->left, value);

			if (dl_flag)
			{
				dl_flag = 0;
				select_case(main_root, &root);

				if (case_flag)
				{
					case_flag = 0;
					a_flag = 1;
				}
			}
		}

		// Search the value in right side
		else if (root->right != NULL && root->data < value)
		{
			root->right = rb_delete_node(main_root, root->right, value);

			if (dl_flag)
			{
				dl_flag = 0;
				select_case(main_root, &root);

				if (case_flag)
				{
					case_flag = 0;
					a_flag = 1;
				}
			}
		}

		// If value is found
		else if (root->data == value)
		{
			// Delete if only one left child
			if (root->left == NULL)
			{
				// Store the right node in a variable
				tmp = root->right;

				if (root->color == BLACK)
				{
					if (tmp != NULL)
						tmp->color = BLACK;

					else
						dl_flag = 1;
				}

				// Free the root
				free(root);

				// Return the variable
				return tmp;
			}

			// Delete if only right child
			else if (root->right == NULL)
			{
				// Store the left node in a variable
				tmp = root->left;

				if (root->color == BLACK)
				{
					if (tmp != NULL)
						tmp->color = BLACK;

					else
						dl_flag = 1;
				}

				// Free the root
				free(root);
			
				// Return the variable
				return tmp;
			}

			// If node has two children
			else
			{
				// Find the min node 
				min = find_min(root->right);

				// Replace the parent node with the min value
				root->data = min;

				// Delete the duplicate min  node
				root->right = rb_delete_node(main_root, root->right, min);
			}
			
			if (dl_flag)
			{
				dl_flag = 0;
				select_case(main_root, &root);
			}
		}

		// If node is not found
		else
			printf("Node not present\n");
	}

	if (b_flag)
	{
		b_flag = 0;
		select_case(main_root, &root);
	}

	if (a_flag)
	{
		a_flag = 0;
		b_flag = 1;
	}

	return root;
}

// Insert tree
rbtree *manual_insert_tree(rbtree *root, int data,int color)
{
	// Create root
	if (root == NULL)
	{
		root = malloc(sizeof(rbtree));
		root->left = NULL;
		root->right = NULL;
		root->data = data;
		root->color = color;
		return root;
	}

	// Insert data to the right
	if (data > root->data)
		root->right = manual_insert_tree(root->right, data, color);

	// Insert data to the left
	else if (data < root->data)
		root->left = manual_insert_tree(root->left, data, color);
	else
		printf("Data already exists..!!\n");

	return root;
}

void read_manual_input(rbtree **root)
{
	int data, color;

	printf("Enter the data: ");
	scanf("%d", &data);
	
	printf("Enter the color: ");
	scanf("%d", &color);

	*root = manual_insert_tree(*root, data, color);
}
