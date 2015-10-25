#ifndef _SORTING_H_
#define _SORTING_H_


typedef struct item_list {
	char *somestring;
	void *somedata;
	struct item_list *next;
	struct item_list *prev;
}item_list;

struct item_list *head;
struct item_list *tail;

item_list *createItem(char *formerString, void *laterData);
void insertItemAfterList(item_list *list, char *formerString, void *laterData);
void removeProcess(item_list **list, item_list *item);
item_list *findItem(item_list *list, item_list *item);
void removeItemFromList(item_list **list, item_list *item);
char *substring(char* dest, char* source, int length);
bool notIncreaseSorted(item_list *list);
void increaseSort(item_list *list);
bool notDecreaseSorted(item_list *list);
void decreaseSort(item_list *list);
void randomSort(item_list *list);

#endif