#include "exception.h"
#include "list.h"
#include <stdlib.h>
/*allocates memory for the list*/
struct list init(void)
{
	struct list new_list;
	new_list.items = malloc(sizeof(void*) * STARTING_SIZE);
	if (new_list.items == NULL)
	{
		throw_exp("Memory allocation failed");
		new_list.size = 0;
		new_list.length = 0;
		return new_list;
	}
	new_list.size = STARTING_SIZE;
	new_list.length = 0;
	return new_list;
}
/*inserts item into the end of the list*/
bool insert(struct list *ls, void* item)
{
	void** temp;
	if (ls->items == NULL || ls->length < 0 || ls->size < 1)
		return false;
	while(ls->length >= ls->size)
	{
		temp = realloc(ls->items, sizeof(void *) * ls->size * GROWTH_FACTOR);
		if(temp == NULL)
		{
			throw_exp("Memory allocation failed");
			free_ls(ls);
			return false;
		}
		ls->items = temp;
		ls->size = ls->size * GROWTH_FACTOR;
	}
	*(ls->items + ls->length) = item;
	ls->length = ls->length + 1;
	return true;
}
/*gets an item at a specific index*/
void* get(struct list *ls, int index)
{
	if (ls->items == NULL || ls->length < 0 || index >= ls->length || index < 0)
		return NULL;
	return *(ls->items + index);
}
/*apply a function for all the items in the list*/
bool foreach(struct list ls, void (*action)(void *))
{
	int i;
	if (ls.items == NULL || ls.length < 0)
		return false;
	for(i = 0; i < ls.length; i++)
		action(get(&ls, i));
	return true;
}
/*frees the list. note that the items are not freed, but the item's pointer are*/
void free_ls(struct list *ls)
{
	if(ls->items != NULL )
	{
		free(ls->items);
		ls->items = NULL;
	}
	ls->length = 0;
	ls->size = 0;
}
/*adds "source" into "dest"*/
struct list lstcat(struct list *dest, struct list *source)
{
	int i;
	/*if one is empty return the other*/
	if (source->items == NULL)
		return *dest;
	if (dest->items == NULL)
		return *source;
	for(i = 0; i < source->length; i++)
	{
		insert(dest, get(source, i));
	}
	/*note that "source" is not freed*/
	return *dest;
}