/* 
 * File:   Cache.h
 * Author: dmitriy
 *
 * Created on September 30, 2017, 9:44 AM
 * Implementation of LinkedHashMap with head for first element
 */
 
#ifndef CACHE_H
#define CACHE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>
#define GetCurrentDir getcwd
#define DEF_BASKETS (1 << 15) //default number of buckets
#define MAX_WORD_SIZE 128
#define MAX_SIZE DEF_BASKETS*10

struct Node{   
    struct Node *after; //pointer to element before that
    struct Node *before; //pointer to element after that
    struct Node *next; //pointer to next element with same hash
    int a;
    char word[MAX_WORD_SIZE];
    char description[900];    
};

struct Hash{
    int buckets;
    long long size;
    struct Node *array[DEF_BASKETS]; //links for first element in basket
    struct Node *head; // head for first element in Queue
};

// for Node
int newNode(struct Node* ,struct Node** ,char * ,char *);

int node_remove(struct Node* ); //remove node from hash list

int check_basket(struct Node*); //change null to element before last in basket

//For Hash

int init(struct Hash*); //initialize cache

int hashCode(char*); //calculate hash code

int hash_put(struct Hash*, char* ,char* ); //insert into cache 

int exchange_cell(); //exchange cells

int hash_get(struct Hash*, char*); //get from cache and add it to start of list

int hash_remove(struct Hash*); // remove cache

int remove_word(struct Hash*, char* ); //delete word

void show(struct Hash*); //for debugging

#endif /* CACHE_H */

