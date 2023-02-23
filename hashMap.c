#include <stdlib.h>
#include "hashMap.h"
#include "structs.h"
#include <string.h>

int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between 1 and 2 is on this line*/
	return r;
}

void initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

void freeMap (struct hashMap * ht)
{  /*write this*/
    int i;
    struct hashLink *temp, *current;
    if (ht == NULL)
        return;
    for (i = 0; i < ht->tableSize; i++) {
        current = ht->table[i];
        while (current != NULL) {
            temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
    free(ht->table);
    ht->tableSize = 0;
    ht->count = 0;
}

void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{  /*write this*/
    int hashIdx;
    struct hashLink *newLink, *current;
    if (ht == NULL || k == NULL)
        return;
    /* Get the hash index */
    hashIdx = stringHash1(k) % ht->tableSize;
    /* Check if key already exists in the table */
    current = ht->table[hashIdx];
    while (current != NULL) {
        if (strcmp(current->key, k) == 0) {
            current->value = v;
            return;
        }
        current = current->next;
    }
    /* If key not found, insert new link at the beginning of the list */
    newLink = (struct hashLink*) malloc(sizeof(struct hashLink));
    newLink->key = (char*) malloc(strlen(k) + 1);
    strcpy(newLink->key, k);
    newLink->value = v;
    newLink->next = ht->table[hashIdx];
    ht->table[hashIdx] = newLink;
    ht->count++;
}

ValueType* atMap (struct hashMap * ht, KeyType k)
{ /*write this?*/
    int hashIdx;
    struct hashLink *current;
    if (ht == NULL || k == NULL)
        return NULL;
    /* Get the hash index */
    hashIdx = stringHash1(k) % ht->tableSize;
    /* Traverse the linked list and search for the key */
    current = ht->table[hashIdx];
    while (current != NULL) {
        if (strcmp(current->key, k) == 0) {
            return &(current->value);
        }
        current = current->next;
    }
    /* Key not found */
    return NULL;

}

int containsKey (struct hashMap * ht, KeyType k)
{  /*write this*/
    if (ht == NULL || k == NULL)
        return 0;
    return (atMap(ht, k) != NULL);
}

void removeKey (struct hashMap * ht, KeyType k)
{  /*write this?*/
    int hashIdx;
    struct hashLink *current, *prev;
    if (ht == NULL || k == NULL)
        return;
    /* Get the hash index */
    hashIdx = stringHash1(k) % ht->tableSize;
    /* Traverse the linked list and search for the key */
    prev = NULL;
    current = ht->table[hashIdx];
    while (current != NULL) {
        if (strcmp(current->key, k) == 0) {
            /* Key found, remove the link from the list */
            if (prev == NULL)
                ht->table[hashIdx] = current->next;
            else
                prev->next = current->next;
            /* Free memory allocated for the link */
            free(current->key);
            free(current);
            ht->count--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

int sizeMap (struct hashMap *ht)
{  /*write this*/
    if (ht == NULL)
        return 0;
    return ht->count;
}

int capacityMap(struct hashMap *ht)
{  /*write this*/
    if (ht == NULL)
        return 0;
    return ht->tableSize;
}

int emptyBuckets(struct hashMap *ht)
{  /*write this*/
    int i, count = 0;
    if (ht == NULL)
        return 0;
    for (i = 0; i < ht->tableSize; i++) {
        if (ht->table[i] == NULL)
            count++;
    }
    return count;
}

float tableLoad(struct hashMap *ht)
{  /*write this*/
    if (ht == NULL)
        return 0;
    return (float)ht->count / ht->tableSize;
}
