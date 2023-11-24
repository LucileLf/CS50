// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[26];             // creates a linkedlist for each letter of alphabet

int wordCount = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hashIndex = hash(word);     // hash the word to get a hashvalue (index)
    
    //traverse a linked list from node to node:
    node *cursor = table[hashIndex];    //set a cursor as pointer to first element (head)
    
    while(cursor != NULL) {             // looping until end of linkedlist
        if(strcasecmp(cursor->word, word) == 0) {  //compare the 2 words case-insensivitely
            return true;                           
        }      
        cursor = cursor->next;           //if not, move cursor to next node
    }    

    return false;       //when cursor is null, meaning reached the end of linked list and word not found
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //open the file
    FILE *DictFile = fopen(dictionary, "r");

    //Check if return value is NULL
    if(DictFile == NULL) {
        return false;
    }

    //read one word at a time from the file
    char str[LENGTH + 1];                           //structure of a word (includes the final null operator to signal the end)
    while(fscanf(DictFile, "%s", str) != EOF){      //fscanf return EOF oncce it reaches the end of the file
        node *n = malloc(sizeof(node));             //create a node to store the word in the hash table
        if(n == NULL) {                             //if not enought memory-> return false
            return false;
        } 
        strcpy(n->word, str);                       //copy word into node
        int hashIndex = hash(str);                  //use hash function to determine which linked list of hashtable the node will go into 
        //insert the node in the hashtable, at index returned by hash function    
        if(table[hashIndex] == NULL) {              //if the head points to null (empty linkedlist)
            n->next = NULL;                         //add first item in linkedlist
        } 
        else
        {
            n->next = table[hashIndex];             //otherwise, point to first node in linkedlist
        }

        table[hashIndex] = n;
        
        wordCount += 1;                       //point the header to n in either case
    }
    
    fclose(DictFile);
    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return wordCount;
}

void freenode(node *n)
{
    if(n->next != NULL) {
        freenode(n->next);
    } 
    free(n);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{

    for(int i = 0; i < N; i++) {
        node *cursor = table[i];
        if(cursor != NULL) {
            node *tmp = cursor; //create a copy of head 
            cursor = cursor->next;
            freenode(tmp);
        }
    }
        return true;
}
