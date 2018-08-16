#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct item_t item;

struct item_t{
    char *key;
    char *value;
    item *next;
};

typedef struct hashtable_t hashtable;

struct hashtable_t{
    item **item;
	size_t size;
};

/**
* Creates a hashtable with specified number of buckets
* Return: true if memory is allocated otherwise return false
*/
bool make_hashtable(hashtable *ht, unsigned long size){
	ht->size = size;
	ht->item = (item**) calloc(ht->size, sizeof(item));
	return ht->item != 0;
}

/**
* Inserts the key => val mapping, or updates the value for key, if it is already in the hashtable.
*/
void insert(hashtable *ht, char *key, void *val){
	item* temp = (item *) malloc(sizeof(item));
	if(temp == NULL){
		printf("Make hashtable larger before adding more items.");
		return;
	}	

	temp->key = key;
	temp->value = (char*) val;
}




int main(int argc, char* argv[]){
	hashtable ht;
	if(!(make_hashtable(&ht, 10))){
		printf("Hashtable was unable to be created.\n");
		exit(EXIT_FAILURE);
	}
	
	insert(&ht, "test", "test1");

	return 0;
}
