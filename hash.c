#include <stdio.h>
#include <stdlib.h>

typedef struct item_t* item;

struct item_t{
    char *key;
    int value;
    item *next;
};

typedef struct hashtable_t* hashtable;

struct hashtable_t{
    item **item;
	size_t size;
};

/**
* Creates a hashtable with size buckets.
*/
struct hashtable_t *make_hashtable(unsigned long size){
	hashtable tab = (hashtable ) malloc(size * sizeof(struct hashtable_t));
	tab->size = size;
	return tab;
}

/**
* Inserts the key => val mapping, or updates the value for key, if it is already in the hashtable.
*/
void insert(struct hashtable_t *ht, char *key, void *val){
	item newItem = (item) malloc(ht->size * sizeof(item));
	char* data = val;
	
	newItem->key = key;
	newItem->value = (int) *data;
	ht->item = (item **) newItem;
}

void printHash(struct hashtable_t *ht){
	if(ht->item == NULL){
		printf("No items found");
		return;
	}
	item newItem = (item) ht->item;
	while(newItem != NULL){
		printf("key = %s, value = %d\n", newItem->key, newItem->value);
		newItem = (item)newItem->next;
	}
}

int main(int argc, char* argv[]){
	struct hashtable_t *hash = make_hashtable(1);
	insert(hash, "one", "two");
	printHash(hash);
	return 0;
}
