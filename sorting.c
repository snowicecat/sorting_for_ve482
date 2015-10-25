#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "sorting.h"

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
		if(list == item)
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

char *substring(char* dest, char* source, int length) {
	char *p = source;
	char *q = dest;
	int len = strlen(source);
	if(length > len) length = len;
	while(length--) {
		*(q++) = *(p++);
	}
	*(q++) = '\0';
	return dest;
}


int main(int argc, char* argv[]) {
	char* fileName = argv[1];
	printf("filename is: %s \n", fileName);

	FILE *fp;
	fp = fopen(fileName, "r");
	char buffer[1024];

	while(fgets(buffer, 1024, fp) != NULL) {
		char *formerString;
		char *originData;
		void *laterData;
		char *position = strrchr(buffer, '=');
		originData = (position+1);
		formerString = substring(buffer, buffer, (strlen(buffer)-strlen(position)));

		printf("position: %s, %s", formerString, originData);
	}



	fclose(fp);
	return 0;
}











