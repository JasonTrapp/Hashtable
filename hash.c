#include <stdio.h>
#include <stdlib.h>

typedef struct item_t item_t;

struct item_t{
    char *key;
    int value;
    item_t *next;
};

typedef struct hashtable_t* hashtable;

struct hashtable_t{
    item_t **item;
	size_t size;
};

int main(int argc, char* argv[]){
	
	return 0;
}
