#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>	

struct list_t {
	char *somestring;
	void *somedata;
	struct list_t *next;
	struct list_t *prev;
}*list;

void readFile(char *fileName, char voidType);
void writeFile(char *fileName, char sortType);
void insertItemBeforeList(char *somestring, void* somedata);
void removeItem(struct list_t *item);
struct list_t* createItem(char *somestring, void *somedata);
struct list_t* searchItem(void *laterdata);
void increaseSort(char voidType);
void decreaseSort(char voidType);
void randomSort();
void swap(struct list_t *item1, struct list_t *item2);


struct list_t* searchItem(void *laterdata) {
	struct list_t *head = list;
	while(head) {
		if(head->somedata == laterdata) 
			return head;
		head = head->next;
	}
	return NULL;
}

struct list_t* createItem(char *formerstring, void *laterdata) { 
	struct list_t *temp = (struct list_t *)malloc(sizeof(struct list_t));
	temp->next = temp->prev = NULL;
	temp->somestring = formerstring;
	temp->somedata = laterdata;
	return temp;
}

void insertItemBeforeList(char *somestring, void* somedata) {
	if(list == NULL) {
		list = createItem(somestring, somedata);
	} else {
		struct list_t *temp = list;
		list = createItem(somestring, somedata);
		list->next = temp;		
		temp->prev = list;
	}
}

void removeItem(struct list_t *item) {
	free(item->somestring);
	free(item->somedata);
	if(list == item) {
		list = item->next;
		list->prev = item->prev;
	} else {
		struct list_t *temp = list;
		while(temp && temp->next != item) {
			temp = temp->next;
		}
		temp->next = item->next;
		temp->next->prev = item->prev;
	}
}

void readFile(char *fileName, char voidType) {
	FILE *inputFile = fopen(fileName, "r");
	char buffer[1024];
	while(fgets(buffer, 1024, inputFile)) {
		char *equalPositon = strchr(buffer, '=');
		char *somestring = (char*)malloc(sizeof(char)*(equalPositon-buffer+1));
		void *somedata = NULL;
		strncpy(somestring, buffer, equalPositon-buffer);
		somestring[equalPositon-buffer] = '\0';
		switch(voidType) {
			case 'i': {
				int *temp = (int*)malloc(sizeof(int));
				*temp = atoi(equalPositon+1);
				somedata = temp;
				break;
			}
			case 'd': {
				double *temp = (double*)malloc(sizeof(double));
				*temp = atof(equalPositon+1);
				somedata = temp;
				break;
			}
			case 'c': {
				char *temp = (char *)malloc(sizeof(char)*(strlen(equalPositon)-1));
				strncpy(temp, (equalPositon+1), (strlen(equalPositon)-1));
				temp[strlen(equalPositon)-1] = '\0';
				somedata = temp;
				break;
			}
		}
		insertItemBeforeList(somestring, somedata);
	}
	fclose(inputFile);
} 

void increaseSort(char voidType) {
	for(struct list_t *head = list; head->next != NULL; head = head->next) {
		for(struct list_t *temp = head; temp != NULL; temp = temp->next) {
			if(voidType == 'i') {
				if(*(int *)(head->somedata) > *(int *)(temp->somedata) ) 
						swap(head, temp);
			} else if(voidType == 'd') {
				if(*(double *)(head->somedata) > *(double *)(temp->somedata) )
					swap(head, temp);
			} else if(voidType == 'c') {
				if(strcmp((char *)(head->somedata), (char *)(temp->somedata)) > 0 ) 
					swap(head, temp);
			}
		}
	}
}
	
void decreaseSort(char voidType) {
	for(struct list_t *head = list; head->next != NULL; head = head->next) {
		for(struct list_t *temp = head; temp != NULL; temp = temp->next) {
			if(voidType == 'i') {
				if(*(int *)(head->somedata) < *(int *)(temp->somedata) ) 
						swap(head, temp);
			} else if(voidType == 'd') {
				if(*(double *)(head->somedata) < *(double *)(temp->somedata) )
					swap(head, temp);
			} else if(voidType == 'c') {
				if(strcmp((char *)(head->somedata), (char *)(temp->somedata)) < 0 ) 
					swap(head, temp);
			}
		}
	}
}

void randomSort() {
	srand(0);
	for(struct list_t *head = list; head->next != NULL; head = head->next) {
		for(struct list_t *temp = head; temp != NULL; temp = temp->next) {
			if(rand() % 2 == 0)
				swap(head, temp);
		}
	}
}

void swap(struct list_t *node1, struct list_t *node2) {
	char *tempstring; void *tempdata;
	tempstring = node1->somestring; tempdata = node1->somedata;
	node1->somestring = node2->somestring; node1->somedata = node2->somedata;
	node2->somestring = tempstring; node2->somedata = tempdata;
}

void writeFile(char *fileName, char voidType){
	FILE *outputFile = fopen(fileName, "w");
	struct list_t *head = list;
	while(head) {
		if(voidType == 'i') {
			fprintf(outputFile, "%s=%d\n", head->somestring, *(int *)(head->somedata));		
		}else if(voidType == 'd'){
			fprintf(outputFile, "%s=%f\n", head->somestring, *(double *)(head->somedata));
		}else if(voidType == 'c'){
			fprintf(outputFile, "%s=%s\n", head->somestring, (char *)(head->somedata));
		}
		head = head->next;
	}
	fclose(outputFile);
}

int main(int argc, char *argv[]) {
	char *fileName = argv[1];
	char *temp = strchr(fileName, '_');
	char voidType = temp[1];
	
	printf("reading %s\n", argv[1]);
	readFile(fileName, voidType);

	printf("sorting elements\n");
	char sortType = argv[2][0];
	switch (sortType) {
		case 'i':
			increaseSort(voidType);
			break;
		case 'd':
			decreaseSort(voidType);
			break;
		case 'r':
			randomSort();
			break;
		default:
			increaseSort(voidType);
			break;
	}

	char *outputFileName = malloc(sizeof(char)*(strlen(argv[2]) + strlen(temp)));
	strncpy(outputFileName, argv[2], strlen(argv[2]));
	strncpy(outputFileName+strlen(argv[2]), temp, strlen(temp));
	outputFileName[strlen(argv[2]) + strlen(temp)] = '\0';
	printf("writing %s\n", outputFileName);
	writeFile(outputFileName, voidType);

}