/****************************************************************
 * llist.h
 * MPATE-GE 2618
 * Problem Set 5
 *
 * Header file for functions that that allows insertions and deletions from 
 * a doubly-linked list. 
 * 
 * The list is accessed by both a head and a tail pointer. 
 * Dynamically allocated string (name) and  an associated int (ID number) 
 * is stored in the elements as well. The list is not allowed to 
 * contain two identical strings.  The nodes are stored in ascending 
 * alphabetical order from head to tail. 
 *
 * Functions can insert a new string/id pair, delete a node when 
 * identified by a matching string, and search for a string and return 
 * the associated id number.  The following error conditions are detected:  
 * inserting a duplicate string, deleting a non-existent string, failing to
 * find a specified search string.
 ****************************************************************/

#ifndef _LLIST_H_
#define _LLIST_H_

#include <stdio.h>
#include <stdbool.h>

typedef struct _node {
    char *name;   
    int id;       
    struct _node *next;
    struct _node *prev;
} node;

typedef struct _llist {
    int length;
    node *head;
    node *tail;
} llist;


// initialize list
void init_list(llist *list);

// Deletes an entire list.
void delete_list(llist *list);

// Inserts a new node into list, ignores duplicate strings.  
// Returns true if insertion succeeds, false if it fails (e.g. duplicate
// string found.  
bool insert(llist *list, const char *string, int number);

// Searches a list for an element which matches the given string.  If found,
// the element's ID number is stored in id_number, which is passed by ref.
bool find(llist *list, const char *string, int *id_number);

// Searches for a Given a string and deletes the node associated with it.
bool delete_given_string(llist *list, const char *string);

// Prints all elements in list.
void print(llist *list);

// Prints all elements in list backwards, from last to first element.
void print_backwards(llist *list);



#endif // _LLIST_H_










