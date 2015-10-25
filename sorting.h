#ifndef _SORTING_H_
#define _SORTING_H_


typedef struct item_list {
	char *somestring;
	void *somedata;
	struct item_list *next;
	struct item_list *prev;
}item_list;

item_list *createItem(char *formerString, void *laterData);
void insertItemAfterList(item_list *list, char *formerString, void *laterData);
void removeProcess(item_list **list, item_list *item);
item_list *findItem(item_list *list, item_list *item);
void removeItemFromList(item_list **list, item_list *item);

#endif