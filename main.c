#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hashMap.h"
#define MAX_SIZE 100

/*
 the getWord function takes a FILE pointer and returns you a string which was
 the next word in the in the file. words are defined (by this function) to be
 characters or numbers separated by periods, spaces, or newlines.
 
 when there are no more words in the input file this function will return NULL.
 
 this function will malloc some memory for the char* it returns. it is your job
 to free this memory when you no longer need it.
 */
int countOccurrences(char *str, char *toSearch);
char *getWord(FILE *file);


/****************************************/

int main(int argc, const char* argv[]) {
    hashMap* map = hashMapNew(MAX_SIZE);
    char* word;
    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    while ((word = getWord(file)) != NULL) {
        // Convert word to lowercase
        for (int i = 0; word[i]; i++) {
            word[i] = tolower(word[i]);
        }
        
        // Check if the word is already in the map
        int* count = hashMapGet(map, word);
        if (count == NULL) {
            // If the word is not in the map, add it with a count of 1
            hashMapPut(map, word, 1);
        } else {
            // If the word is already in the map, increment its count
            (*count)++;
            free(word); // Free the memory allocated by getWord since we don't need it anymore
        }
    }

    // Print the counts of each word
    for (int i = 0; i < map->tableSize; i++) {
        hashLink* link = map->table[i];
        while (link != NULL) {
            printf("%s: %d\n", link->key, *(int*)link->value);
            link = link->next;
        }
    }

    // Free the memory allocated by the map and the file
    hashMapDelete(map);
    fclose(file);
    return 0;
}






char* getWord(FILE *file)
{
	
	int length = 0;
	int maxLength = 16;
	char character;
    
	char* word = (char*)malloc(sizeof(char) * maxLength);
	assert(word != NULL);
    
	while( (character = fgetc(file)) != EOF)
	{
		if((length+1) > maxLength)
		{
			maxLength *= 2;
			word = (char*)realloc(word, maxLength);
		}
		if((character >= '0' && character <= '9') || /*is a number*/
		   (character >= 'A' && character <= 'Z') || /*or an uppercase letter*/
		   (character >= 'a' && character <= 'z') || /*or a lowercase letter*/
		   character == 39) /*or is an apostrophy*/
		{
			word[length] = character;
			length++;
		}
		else if(length > 0)
			break;
	}
    
	if(length == 0)
	{
		free(word);
		return NULL;
	}
	word[length] = '\0';
	return word;
}

