/*
There is some problem with open file. So unfortunately I cannot test the whole program
But I think the rest and logic is correct.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "sorting.h"

//create item - ready
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

//insert item -ready
void insertItemAfterList(item_list *list, char *formerString, void *laterData) {
	item_list *newItem = createItem(formerString, laterData);
	if(newItem != NULL) {
		newItem->prev = tail->prev;
		newItem->next = NULL;
		tail->prev->next = newItem;
		tail->prev = newItem;
	}
}

//remove process - ready
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

//find item - ready
item_list *findItem(item_list *list, item_list *item) {
	while(list) {
		if(list == item)
			break;
		list = list->next;
	}
	return list;
}

// choose special item from list - ready
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

//judgement
bool notIncreaseSorted(item_list *list) {
	item_list *curr = head->next;
	bool notIncreaseSorted = false;
	while(curr->next != NULL) {
		if (strcmp((char*)(curr->somedata), (char*)(curr->next->somedata)) ) {
			notIncreaseSorted = true;
		}
	}
	return notIncreaseSorted;
}

// increase sort - should be ready
void increaseSort(item_list *list) {
	item_list *curr = head->next;
	while(curr->next != NULL) {
		if(strcmp((char*)(curr->somedata), (char*)(curr->next->somedata))) {
			// change place
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			curr->next = curr->next->next;
			curr->next->prev = curr;
			curr->prev = curr->prev->next;
			curr->prev->next = curr;
		}
		curr = curr->next;
	}
}

//judgement
bool notDecreaseSorted(item_list *list) {
	item_list *curr = head->next;
	bool notDecreaseSorted = false;
	while(curr->next != NULL) {
		if (strcmp((char*)(curr->next->somedata), (char*)(curr->somedata)) ) {
			notDecreaseSorted = true;
		}
	}
	return notDecreaseSorted;
}

// increase sort - should be ready
void decreaseSort(item_list *list) {
	item_list *curr = head->next;
	while(curr->next != NULL) {
		if(strcmp((char*)(curr->next->somedata), (char*)(curr->somedata)) ) {
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			curr->next = curr->next->next;
			curr->next->prev = curr;
			curr->prev = curr->prev->next;
			curr->prev->next = curr;
		}
		curr = curr->next;
	}
}

// increase sort - should be ready
void randomSort(item_list *list) {
	item_list *curr = head->next->next->next;
	while(curr->next != NULL) {
		if(strcmp((char*)(curr->next->somedata), (char*)(curr->somedata)) ) {
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			curr->next = curr->next->next;
			curr->next->prev = curr;
			curr->prev = curr->prev->next;
			curr->prev->next = curr;
		}
		curr = curr->next;
	}
	curr = tail->prev->prev->prev;
	while(curr->next != NULL) {
		if(strcmp((char*)(curr->somedata), (char*)(curr->next->somedata))) {
			// change place
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			curr->next = curr->next->next;
			curr->next->prev = curr;
			curr->prev = curr->prev->next;
			curr->prev->next = curr;
		}
		curr = curr->next;
	}
}

//the problem is opening file
int main(int argc, char* argv[]) {
	char* fileName = argv[1];
	printf("filename is: %s \n", argv[1]);

	FILE *fp = fopen(fileName, "rw");
	char buffer[1024];
	item_list *list;

	while(fgets(buffer, 1024, fp) != NULL) {
		char *formerString;
		char *originData;

		char *position = strrchr(buffer, '=');
		originData = (position+1);
		formerString = substring(buffer, buffer, (strlen(buffer)-strlen(position)));
		void *laterData = (void *)originData;

		if(list == NULL) {
			list = createItem(formerString, laterData);
			head = list;
			head->next = list;
			tail = list;
			tail->prev = list;
		} else {
			insertItemAfterList(list, formerString, laterData);			
		}
	}

	//sort
	if(strstr(fileName, "inc")) {
		while(notIncreaseSorted(list)) {
			increaseSort(list);
		}
	}else if(strstr(fileName, "dec")) {
		while(notDecreaseSorted(list)) {
			decreaseSort(list);
		}
	}else if(strstr(fileName, "rand")) {
		randomSort(list);
	}

	//print
	item_list *curr = head->next;
	while(curr->next != NULL) {
		fprintf(fp, "%s=%s\n", curr->somestring, (char*)(curr->somedata));
	}


	fclose(fp);
	return 0;
}











