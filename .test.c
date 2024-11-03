// void test_shunting (t_tree	*tree, t_tree *new, t_tree *op)
// {
// 	t_tree *tmp;

// 	tmp = tree;
// 		printf ("tree->");
// 	while (tmp)
// 	{	
// 		if (tmp->type == CMD)
// 			printf ("%s ",tmp->p_cmd);
// 		else if (tmp->type == LPR)
// 			printf ("( ");
// 		else if (tmp->type == RPR)
// 			printf (") ");
// 		else if (tmp->type == PIPE)
// 			printf ("| ");
// 		else if (tmp->type == OR)
// 			printf ("|| ");
// 		else if (tmp->type == AND)
// 			printf ("&& ");
// 		tmp = tmp->r_child;
// 	}
// 		printf ("\t");
// 	tmp = new;
// 		printf ("new->");
// 	while (tmp)
// 	{	
// 		if (tmp->type == CMD)
// 			printf ("%s ",tmp->p_cmd);
// 		else if (tmp->type == LPR)
// 			printf ("( ");
// 		else if (tmp->type == RPR)
// 			printf (") ");
// 		else if (tmp->type == PIPE)
// 			printf ("| ");
// 		else if (tmp->type == OR)
// 			printf ("|| ");
// 		else if (tmp->type == AND)
// 			printf ("&& ");
// 		tmp = tmp->r_child;
// 	}
// 		printf ("\t");
// 	tmp = op;
// 		printf ("op->");
// 	while (tmp)
// 	{	
// 		if (tmp->type == CMD)
// 			printf ("%s ",tmp->p_cmd);
// 		else if (tmp->type == LPR)
// 			printf ("( ");
// 		else if (tmp->type == RPR)
// 			printf (") ");
// 		else if (tmp->type == PIPE)
// 			printf ("| ");
// 		else if (tmp->type == OR)
// 			printf ("|| ");
// 		else if (tmp->type == AND)
// 			printf ("&& ");
// 		tmp = tmp->r_child;
// 	}
// 	printf ("\n");
// }


// #define RED     "\x1b[31m"
// #define GREEN   "\x1b[32m"
// #define YELLOW  "\x1b[33m"
// #define BLUE    "\x1b[34m"
// #define RESET   "\x1b[0m"

// void print_token_colored(t_tree *node)
// {
//     if (node->type == CMD)
//         printf(GREEN "%s" RESET, node->p_cmd);
//     else if (node->type == AND)
//         printf(YELLOW "&&" RESET);
//     else if (node->type == OR)
//         printf(RED "||" RESET);
//     else if (node->type == PIPE)
//         printf(BLUE "|" RESET);
// }

// void print_tree_recursive(t_tree *root, int level, char *prefix, int is_left)
// {
//     if (!root)
//         return;

//     printf("%s", prefix);
//     printf("%c-- ", is_left ? '`' : ',');
//     print_token_colored(root);
//     printf("\n");

//     char new_prefix[1024];
//     sprintf(new_prefix, "%s%c   ", prefix, is_left ? ' ' : '|');

//     print_tree_recursive(root->r_child, level + 1, new_prefix, 0);
//     print_tree_recursive(root->l_child, level + 1, new_prefix, 1);
// }

// void test_tree(t_tree *root)
// {
//     printf("\nTree Structure:\n");
//     print_tree_recursive(root, 0, "", 1);
// }
