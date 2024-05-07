#include "OLED.h"
#include "OLED_Data.h"
#include <string.h>
#include <stdlib.h>

typedef struct DoubleListNode
{
	int data;
	struct DoubleListNode* last;
	struct DoubleListNode* next;
} DoubleListNode;

DoubleListNode* DoubleList_Init(void)
{
	DoubleListNode* list = malloc(sizeof(DoubleListNode));
	list->data = -1;
	list->last = NULL;
	list->next = NULL;
	
	return list;
}

int DoubleList_Insert(DoubleListNode* phead, int data, int num)
{
	if (phead == NULL || num < 1)
	{
		return -1;
	}
	
	DoubleListNode* node = phead;
	int node_count = 0;
	while (node_count < (num - 1) && node->next != NULL)
	{
		node = node->next;
		node_count++;
	}
	
	DoubleListNode* new_node = malloc(sizeof(DoubleListNode));
	new_node->data = data;
	new_node->last = node;
	
	if (node->next == NULL)
	{
		new_node->next = NULL;
	}
	else
	{
		node->next->last = new_node;
		new_node->next = node->next;
	}
	
	node->next = new_node;
	
	return 0;
}




