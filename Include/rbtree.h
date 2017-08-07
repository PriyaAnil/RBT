#ifndef RBTREE_H
#define RBTREE_H

#define CRED "\x1B[31m"
#define RESET "\x1B[0m"

#define BLACK 0
#define RED 1
#define CHECK 2
#define LEFT 3
#define RIGHT 4
#define STOP 0

typedef struct rb_tree
{
	int data;
	int color;
	struct rb_tree *left, *right;
}rbtree;

void left_left_rotation(rbtree **grand_parent);
void right_right_rotation(rbtree **grand_parent);
void left_rotate(rbtree **grand_parent);
void right_rotate(rbtree **grand_parent);
void balance_tree(rbtree *main_root, rbtree **grand_parent, int r_value);
int rb_create_tree(rbtree *main_root, rbtree **root, int data);
rbtree *rb_insert_tree(rbtree *root, int data);
void rb_in_order(rbtree *root);
int rb_height_tree(rbtree *root);
void rb_bfs(rbtree *root, int breadth);
void rb_bfs_print(rbtree *root);
int rb_bfs_search(rbtree *root, int breadth, int value);
void rb_bfs_search_print(rbtree *root, int value);
int rb_find_min(rbtree *root);
int rb_find_max(rbtree *root);
int case_1(rbtree *m_root, rbtree **root);
int case_2(rbtree *m_root, rbtree **root);
int case_3(rbtree *m_root, rbtree **root);
int case_4(rbtree *m_root, rbtree **root);
int case_5(rbtree *m_root, rbtree **root);
int case_6(rbtree *m_root, rbtree **root);
int select_case(rbtree *m_root, rbtree **root);
rbtree *rb_delete_node(rbtree *main_root, rbtree *root, int value);
rbtree *manual_insert_tree(rbtree *root, int data,int color);
void read_manual_input(rbtree **root);

#endif
