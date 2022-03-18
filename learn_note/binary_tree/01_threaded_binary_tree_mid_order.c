/**
 ************************************
 * @file     : 01_mid_order_threaded_binary_tree.c
 * @author   : stxw
 * @date     : 2021-12-28
 ************************************
 * @brief :
 * 		中序线索二叉树的建立与遍历
 * 		主要参考大佬的这篇博客<https://www.jianshu.com/p/3965a6e424f5>写的
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum pointer_flag
{
	POINTER_NODE,
	POINTER_THREAD
} pointer_flag;

typedef struct tree_node
{
	char data;
	struct tree_node *left_child;
	struct tree_node *right_child;
	pointer_flag left_flag, right_flag;
} tree_node;

void mid_order_traverse_build_tree(tree_node *root, tree_node **pre_node)
{
	if(root != NULL)
	{
		mid_order_traverse_build_tree(root->left_child, pre_node);
		if(root->left_child == NULL)
		{
			root->left_child = *pre_node;
			root->left_flag = POINTER_THREAD;
		}
		else
		{
			root->left_flag = POINTER_NODE;
		}

		if((*pre_node)->right_child == NULL)
		{
			(*pre_node)->right_child = root;
			(*pre_node)->right_flag = POINTER_THREAD;
		}
		else
		{
			(*pre_node)->right_flag = POINTER_NODE;
		}
		*pre_node = root;
		mid_order_traverse_build_tree(root->right_child, pre_node);
	}
}

tree_node* build_thread_binary_tree(tree_node *root)
{
	tree_node *head_node = (tree_node *)malloc(sizeof(tree_node));
	tree_node *pre_node;

	if(root != NULL)
	{
		head_node->left_child = root;
		pre_node = head_node;
		mid_order_traverse_build_tree(head_node->left_child, &pre_node);
		head_node->right_child = pre_node;
		head_node->right_flag = POINTER_THREAD;
		pre_node->right_child = head_node;
		pre_node->right_flag = POINTER_THREAD;
	}
	else
	{
		head_node->left_child = head_node;
		head_node->right_child = head_node;
	}
	return head_node;
}

void traverse_thread_binary_tree(tree_node *head_node)
{
	tree_node *p = head_node->left_child;

	while(p != head_node)
	{
		while(p->left_flag == POINTER_NODE)
		{
			p = p->left_child;
		}
		printf("%c ", p->data);
		while(p->right_flag == POINTER_THREAD && p->right_child != head_node)
		{
			p = p->right_child;
			printf("%c ", p->data);
		}
		p = p->right_child;
	}
	printf("\n");
}


void __build_binary_tree(char tree[], int index, tree_node **root)
{
	if(tree[index] > 0)
	{
		(*root) = (tree_node *)malloc(sizeof(tree_node));
		(*root)->data = tree[index];
		__build_binary_tree(tree, 2 * index, &((*root)->left_child));
		__build_binary_tree(tree, 2 * index + 1, &((*root)->right_child));
	}
	else
	{
		(*root) = NULL;
	}
}

tree_node *build_binary_tree(char tree[])
{
	tree_node *root;

	if(tree[1] > 0)
	{
		__build_binary_tree(tree, 1, &root);
	}
	else
	{
		root = NULL;
	}
	return root;
}

int main(int argc, char *argv[])
{
	char tree[40] = {-1, 'A', 'B', 'C', 'D', 'E', -1, 'F', -1, -1, 'G', 'H', -1, -1, 'I', 'J', -1, -1};
	memset(tree + 16, -1, sizeof(tree) - 16);

	tree_node *root, *head_node;
	root = build_binary_tree(tree);
	head_node = build_thread_binary_tree(root);
	traverse_thread_binary_tree(head_node);

	return 0;
}