#ifndef __OLED_MULTILEVELMENU_H
#define __OLED_MULTILEVELMENU_H

typedef struct DoubleListNode
{
	int data;
	struct DoubleListNode* phead;
	struct DoubleListNode* next;
} DoubleListNode;

DoubleListNode* DoubleList_Init(void);
int DoubleList_Insert(DoubleListNode* phead, int data, int num);

#endif
