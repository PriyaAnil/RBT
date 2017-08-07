#include <stdio.h>
#include <rbtree.h>

int main()
{
	int index, option, val, data, min, max, limit;
	char ch;
	rbtree *root = NULL;

	do
	{

		printf("Enter the options:\n1. Insert\n2. Find min\n3. Find max\n4. Search\n5. Delete\n6. Display\n");
		scanf("%d", &option);

		switch (option)
		{
			case 1:

				printf("Enter the limit: ");
				scanf("%d", &limit);

				for (index = 0; index < limit; index++)
				{
					scanf("%d", &val);
					root = rb_insert_tree(root, val);
				}
				break;

			case 2:
				min = rb_find_min(root);
				printf("min = %d\n", min);
				break;

			case 3:
				max = rb_find_max(root);
				printf("max = %d\n", max);
				break;

			case 4:
				printf("Enter the value to be searched: ");
				scanf("%d", &data);
				rb_bfs_search_print(root, data);
				break;

			case 5:
				
				root = NULL;

				printf("Enter the limit: ");
				scanf("%d", &limit);
				
				for (index = 0; index < limit; index++)
					read_manual_input(&root);
	
				rb_bfs_print(root);	
				
				printf("Enter the value to be deleted: ");
				scanf("%d", &data);

				root = rb_delete_node(root, root, data);

				break;

			case 6:

				printf("\n");
				rb_bfs_print(root);	
				printf("\n");
				break;
	
			default:	
				printf("Invalid option\n");
				break;

		}

		printf("continue... ");
		scanf("\n%c", &ch);
	}while (ch  == 'y');

	return 0;
}
