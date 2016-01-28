/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"


typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
    struct node* previous;
} node;

typedef struct bucket
{
    int id;
    node* next;
} bucket;

typedef struct freep
{
    node* left;
    node* right;
} freep;

bucket head[1170];

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int length = strlen(word);
    int position = tolower(word[0]) - 97;
    int hash = (45 * position + length - 1);
    node* tmp = head[hash].next;
    if (tmp == NULL)
        return false;
    while(tmp != NULL)
    {
        char a, b;
        int i=0;
        while(i < length)
        {
            a = tolower(tmp->word[i]);
            b = tolower(word[i]); 
            if ( a == b )
                ++i;
            else
                break; 
        }
        if (i == length)
            return true;
        tmp = tmp->next;
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* file = fopen(dictionary,"r");
    if (file == NULL)
        return false;

    for(int i = 0 ; i < 26 ;++i)
    {
        head[i].id = i + 1;
        head[i].next = NULL;
    }

    char word[LENGTH + 1] = { '\0' } ;	

    while(fscanf(file,"%s",word) == 1 )  
    {   
        int length = strlen( word );
        int position = tolower(word[0]) - 97;
        int hash = (45 * position + length - 1);
        if (head[hash].next == NULL)
        {
            node* newnode = (node*) malloc(sizeof(node));
            head[hash].next = newnode;
            newnode->next = NULL;
            newnode->previous = NULL;

            int i = 0;
            for(i = 0 ; i < length ;++i)
                newnode->word[i] = word[i];

            newnode->word[i] = '\0';
        }
        else if (head[hash].next != NULL)
        {
            node* newnode = (node*) malloc(sizeof(node));
            newnode->next = NULL;
            newnode->previous = head[hash].next;

            while(newnode->previous->next != NULL)
                newnode->previous = newnode->previous->next;


            newnode->previous->next = newnode; 
            int i = 0;
            for(i = 0 ; i < length ;++i)
                newnode->word[i] = word[i];

            newnode->word[i] = '\0';
        }
    }
    fclose(file);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    unsigned int size = 0;
    for(int i = 0; i < 1170 ;++i )
    {
        if (head[i].next == NULL)
            continue;
        node* tmp = head[i].next;
        while(tmp != NULL)
        {
            size++;
            tmp = tmp->next;
        }
    }
    return size;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    freep new;
    for(int i = 0 ; i < 1170 ;++i)
    {
        new.left = NULL;
        new.right = NULL;
        if (head[i].next == NULL)
            continue;  
        else
        {
            new.left = head[i].next;
            if (new.left->next != NULL)
                new.right = new.left->next;
            else if(new.left->next == NULL)
            {
                free(new.left);
                continue;
            }
        }

        while(new.right->next != NULL)
        {
            new.left = new.right;
            new.right = new.right->next;      
        }

        while(new.left != head[i].next)
        {
            free(new.right);
            new.right = new.left;
            if (new.right->previous == NULL)
            {
                free(head[i].next);
                break;
            }
            new.left = new.right->previous;     
        }
    }
    return true;
}

