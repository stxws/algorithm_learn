/**
 ************************************
 * @file     : 02_huffman_tree.c
 * @author   : stxw
 * @date     : 2022-01-04
 ************************************
 * @brief :
 * 		哈夫曼树
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DATA_LEN 20

typedef struct tree_node
{
	char data;
	int weight;
	struct tree_node *left_child;
	struct tree_node *right_child;
} tree_node;

/**
 * @brief : 遍历结点列表，返回权重最小结点的位置
 * @param nodes : [in]结点列表
 * @param book : [in]标记数组，标记对应结点是否已经使用过
 * @param node_num : [in]结点的个数
 * @return : 权重最小结点的位置
 */
int find_min_weight_index(tree_node *nodes[], int book[], int node_num)
{
	int i, index, min_weight;

	min_weight = 0x3FFFFFFF;
	index = -1;
	for(i = 0; i < node_num; i++)
	{
		if(book[i] == 0 && nodes[i]->weight < min_weight)
		{
			index = i;
			min_weight = nodes[i]->weight;
		}
	}
	return index;
}

/**
 * @brief : 构建哈夫曼树
 * @param data_list : [in]数据数组
 * @param weight_list : [in]权重数组
 * @param data_len : [in]数据个数
 * @return : 构建好的哈夫曼树的头结点地址
 */
tree_node *build_huffman_tree(char data_list[], int weight_list[], int data_len)
{
	tree_node *nodes[MAX_DATA_LEN * 2];
	int book[MAX_DATA_LEN * 2];
	int i, node_num, index_1, index_2;

	node_num = 0;
	for(i = 0; i < data_len; i++)
	{
		nodes[i] = (tree_node *)malloc(sizeof(tree_node));
		nodes[i]->data = data_list[i];
		nodes[i]->weight = weight_list[i];
		node_num++;
	}
	memset(book, 0, sizeof(book));

	for(i = 1; i < data_len; i++)
	{
		index_1 = find_min_weight_index(nodes, book, node_num);
		book[index_1] = 1;
		index_2 = find_min_weight_index(nodes, book, node_num);
		book[index_2] = 1;
		
		nodes[node_num] = (tree_node *)malloc(sizeof(tree_node));
		nodes[node_num]->data = -1;
		nodes[node_num]->weight = nodes[index_1]->weight + nodes[index_2]->weight;
		nodes[node_num]->left_child = nodes[index_1];
		nodes[node_num]->right_child = nodes[index_2];
		node_num++;
	}
	return nodes[node_num - 1];
}

/**
 * @brief : 输出所有哈夫曼编码
 * @param root : [in]树根结点地址
 * @param path : [in]用来记录路径
 * @param depth : [in]当前结点的深度
 * @return : None
 */
void print_huffman_code(tree_node *root, char path[], int depth)
{
	int i;

	if(root != NULL)
	{
		if(root->data > 0)
		{
			printf("%c: ", root->data);
			for(i = 0; i < depth; i++)
			{
				printf("%d", path[i]);
			}
			printf("\n");
		}
		else
		{
			path[depth] = 0;
			print_huffman_code(root->left_child, path, depth + 1);
			path[depth] = 1;
			print_huffman_code(root->right_child, path, depth + 1);
		}
	}
}

int main(int argc, char *argv[])
{
	int i, data_len = 7;
	char data_list[MAX_DATA_LEN] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
	int weight_list[MAX_DATA_LEN] = {8, 7, 4, 5, 20, 15, 1};
	char path[MAX_DATA_LEN];

	tree_node *root = build_huffman_tree(data_list, weight_list, data_len);
	print_huffman_code(root, path, 0);

	return 0;
}