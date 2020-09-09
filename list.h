#if !defined(__LIST__HEADER__)
#define __LIST__HEADER__
#include <stdbool.h>
struct list
{
	void** items;
	int length;
	int size;
};

#define STARTING_SIZE 1
#define GROWTH_FACTOR 2
#define NOT_FOUND_LIST (struct list) { NULL, 0, 0 }

struct list init(void);
bool insert(struct list *, void *);
void *get(struct list *, int);
bool foreach(struct list, void (*)(void*));
void free_ls(struct list *);
struct list lstcat(struct list* , struct list* );
#endif
