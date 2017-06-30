#ifndef LIST_H
#define LIST_H

#include <stdlib.h> 		/* malloc() */
#include <stdbool.h> 		/* bool */

struct node{
	unsigned char* value;
	struct node* next;
};

bool list_add(unsigned char* value);
bool list_remove(unsigned char* value, void* compare_function);
bool list_search(unsigned char* value, void* compare_function);
bool list_update(unsigned char* value, void* compare_function, void* update_function);
void list_link(struct node* prev, struct node* next);
unsigned int list_get_size();
struct node* list_get_head();

#endif
