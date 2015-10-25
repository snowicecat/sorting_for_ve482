#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <malloc.h>

struct item_list {
	char *somestring;
	void *somedata;
	struct item_list *next;
	struct item_list *prev;
}

item_list *createItem(char *formerString, void *laterData) {
	item_list *newItem = malloc(sizeof(item_list));
	if (newItem != NULL) {
		newItem->next = NULL;
		newItem->prev = NULL;
		newItem->somestring = formerString;
		newItem->somedata = laterData;
	}

	return newItem;
}

void insertItemAfterList(item_list *list, char *formerString, void *laterData) {
	item_list *temp = NULL;
	item_list *newItem = createItem(formerString, laterData);
	temp = list;
	if(newItem != NULL) {
		while(temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newItem;
	}
}

void removeProcess(item_list **list, item_list *item) {
	item_list *temp = NULL;
	if(list == NULL || *list == NULL || item == NULL)
		return;
	if(*list == item) {
		*list = (*list)->next;
		free(item);
		item = NULL;
	} else {
		temp = *list;
		while(temp->next && temp->next != item) 
			temp = temp->next;

		if(temp->next != NULL) {
			temp->next = item->next;
			free(item);
			item = NULL;
		}
	}
}

item_list *findItem(item_list *list, item_list *item) {
	while(list) {
		if(list == node)
			break;
		list = list->next;
	}
	return list;
}

void removeItemFromList(item_list **list, item_list *item) {
	if(list == NULL || *list == NULL || item == NULL)
		return;
	removeProcess(list, findItem(*list, item));
}














