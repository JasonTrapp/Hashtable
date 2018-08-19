#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct item_t item;

struct item_t{
    char *key;
    int value;
    item *next;
};

typedef struct hashtable_t hashtable;

struct hashtable_t{
    item **item;
	size_t size;
};

/**
* Bernstein hash function
* Param: 
*		char* values
* Return: The hash of input
*/
size_t hashBern(hashtable *ht, char* string){
	size_t hash = 2357;
	int i;
	while((i = *string++) != '\0'){
		hash = ((hash << 5) + hash) + i;
	}

	return hash % ht->size;
}

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
void insert(hashtable *ht, char *key, int val){
	item* temp = (item *) malloc(sizeof(item));
	if(temp == NULL){
		printf("Make hashtable larger before adding more items.");
		return;
	}	

	temp->key = key;
	temp->value =  val;

	size_t bucket = hashBern(ht, key);
	temp->next = ht->item[bucket];
	ht->item[bucket] = temp;
}

item* getIndex(hashtable *ht, char* key){
	return ht->item[hashBern(ht, key)];
}

/**
* Removes the mapping for key
*/
void del(hashtable *ht, char *key){
	item *head =  getIndex(ht, key);
	item *current = head;
	item *prev = NULL;
	while(current != NULL){
		if(strcmp(key, current->key) == 0){
			if(prev == NULL){
				ht->item[hashBern(ht, key)] = current->next;
			}
			else{
				prev->next = current->next;
			}
			
			free(current);
			return;
		}
		prev = current;
		current = current->next;
		
	}
	printf("key \"%s\" was not found.\n", key);
}

void destroyHash(hashtable *ht){
	for(int i = 0; i < ht->size; i++){
		item* temp = ht->item[i];
		while(temp != NULL){
			item* curr = temp->next;
			free(temp);
			temp = NULL;
		}
	}	
	
	free(ht->item);
	ht->item = NULL;
	ht->size = 0;
}

void printTable(hashtable *ht){
	if(ht->size == 0){
		printf("Hashtable must have a size greater than zero.\n");
		return;
	}
	
	printf("Printing hashtable with size %ld\n", ht->size);	
	for(int i=0; i < ht->size; i++){
		if(ht->item[i] == NULL){
			printf("Empty position.\n");
		}
		else{
			for(item *it = ht->item[i]; it != NULL; it = it->next){
				printf("key=%s, value=%d \n", it->key, it->value);
				if(it->next != NULL)
					printf(" -> ");
			}
		}	
	}
	printf("\n");
	return;
}


int main(int argc, char* argv[]){
	hashtable ht;
	if(!(make_hashtable(&ht, 10))){
		printf("Hashtable was unable to be created.\n");
		exit(EXIT_FAILURE);
	}
	
	insert(&ht, "You're", 4);
	insert(&ht, "tearing", 2);
	insert(&ht, "me", 1);
	insert(&ht, "apart", 5);
	insert(&ht, "Lisa", 1);
	insert(&ht, "Hello", 4);
	insert(&ht, "doggy", 2);
	insert(&ht, "favourite", 1);
	insert(&ht, "customer", 5);
	insert(&ht, "Mark", 1);

	printTable(&ht);	
	del(&ht, "lisa");
	printTable(&ht);	

	destroyHash(&ht);
	printTable(&ht);	
	return 0;
}
