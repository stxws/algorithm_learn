/**
 ************************************
 * @file     : 03_binary_sort_tree.c
 * @author   : stxw
 * @date     : 2022-01-11
 ************************************
 * @brief :
 * 		二叉排序树的插入、查找和删除
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tree_node
{
	int data;
	struct tree_node *left_child;
	struct tree_node *right_child;
} tree_node;

/**
 * @brief : 向二叉排序树中插入数据
 * @param root : [in]树的根节点
 * @param date : [in]需要插入的数据
 * @return : 树的根节点地址
 */
tree_node* insert_data(tree_node *root, int data)
{
	if(root == NULL)
	{
		root = (tree_node *)malloc(sizeof(tree_node));
		root->data = data;
		root->left_child = NULL;
		root->right_child = NULL;
		return root;
	}
	if (root->data < data)
	{
		root->left_child = insert_data(root->left_child, data);
	}
	else
	{
		root->right_child = insert_data(root->right_child, data);
	}
	return root;
}

/**
 * @brief :  在二叉排序树中查找某个数据
 * @param root : [in]树的根节点
 * @param data : [in]需要查找的数据
 * @return : 若找到，返回对应的节点地址，否则返回NULL
 */
tree_node *search_data(tree_node *root, int data)
{
	if(root == NULL)
	{
		return NULL;
	}
	if(root->data == data)
	{
		return root;
	}
	if(root->data < data)
	{
		return search_data(root->left_child, data);
	}
	else
	{
		return search_data(root->right_child, data);
	}
}

/**
 * @brief : 删除二叉排序树中的某个数据
 * @param root : [in]树的根节点
 * @param data : [in]需要删除的数据
 * @return : None
 */
void delete_data(tree_node *root, int data)
{

}

int main(int argc, char *argv[])
{
	int i;
	tree_node *root = NULL;

	/* 插入 */
	int data_list[] = {61, 87, 59, 47, 35, 73, 51, 98, 37, 93};
	int data_len = 10;
	for(i = 0; i < data_len; i++)
	{
		root = insert_data(root, data_list[i]);
	}

	/* 查找 */
	int search_list[] = {73, 34, 59, 42, 37};
	int search_len = 5;
	for (i = 0; i < search_len; i++)
	{
		if (search_data(root, search_list[i]) != NULL)
		{
			printf("found data: %d\n", search_list[i]);
		}
		else
		{
			printf("data: %d no found\n", search_list[i]);
		}
	}

	/* 删除 */
	int delete_list[] = {35};
	int delete_len = 1;
	for (i = 0; i < delete_len; i++)
	{
		delete_data(root, delete_list[i]);
	}
	return 0;
}
