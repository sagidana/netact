#include "../headers/list.h"

struct node* head = NULL;

unsigned int list_size = 0;

struct node* list_get_head()
{
	return head;
}

unsigned int list_get_size()
{
	return list_size;
}

bool list_add(unsigned char* value)
{
	struct node* new = (struct node * )malloc(sizeof(struct node));
	if (!new)
		return false; // malloc failed.

	new->value = value;
	new->next = head;
	head = new;

	list_size++;

	return true;
}

void list_link(struct node* prev, struct node* next)
{
	if (prev == NULL) // Removing the first entry.
	{
		head = next;
		return;
	}
	prev->next = next;
}

bool list_remove(unsigned char* value, void* compare_function)
{
	struct node* prev = NULL;
	struct node* ptr = head;
	bool (*comp_func)(unsigned char*,unsigned char*) = compare_function;
	
	while(ptr != NULL)
	{
		if (comp_func(value, ptr->value))
		{
			list_link(prev, ptr->next);
			list_size--;
			free(ptr);
			return true;
		}

		prev = ptr;
		ptr = ptr->next;
	}
	return false;
}

bool list_update(unsigned char* value, void* compare_function, void* update_function)
{
	struct node* ptr = head;
	bool (*comp_func)(unsigned char*,unsigned char*) = compare_function;
	void (*update_func)(unsigned char*,unsigned char*) = update_function;

	while(ptr != NULL)
	{
		if (comp_func(value, ptr->value))
		{
			update_func(ptr->value, value);
			return true;
		}

		ptr = ptr->next;
	}
	return false;
}

bool list_search(unsigned char* value, void* compare_function)
{
	struct node* ptr = head;
	bool (*comp_func)(unsigned char*,unsigned char*) = compare_function;

	while(ptr != NULL)
	{
		if (comp_func(value, ptr->value))
		{
			return true;
		}

		ptr = ptr->next;
	}
	return false;
}
