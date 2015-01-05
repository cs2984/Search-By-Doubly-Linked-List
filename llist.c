/****************************************************************
 * llist.c
 * MPATE-GE 2618
 * Problem Set 5
 *
 * Implementation of a doubly-linked list.
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "llist.h"

void create_node ( llist *list, node *prev, node *next, const char *name, int id_number);


// Initialize list
void init_list(llist *list)
{
    if (list == NULL)
        return;

    list->length = 0;
    list->head = NULL;
    list->tail = NULL;
}

// Delete the entire list.  This includes deleting all memory that's
// been allocated for nodes and strings.
void delete_list(llist *list)
{
    node *np = list->head, *tmp;
    int i = 0;

    for ( i = 0; i < list->length; i++ ) {
        tmp = np->next;
        free( np );
        np = tmp;
    }

    free( list );
}

// Inserts an element alphabetically into a list. Checks to see if an 
// element with the same name exists already. 
// Returns false if duplicate string found.
// Recommendationmivm : Use the function strcasecmp() from the string.h library; 
// it is _not_ case sensitive.  strcasecmp(s1, s2) returns a value less 
// than 0 if s1 comes alphabetically before s2, greater than 0 if s1 comes 
// after s2, and equal to zero if s1 and s2 are identical. 
bool insert(llist *list, const char *string, int number) 
{
    //node *prev = NULL, *next = list->head
    int i;
    node *prev = NULL, *next = NULL, *curr = list->head;
    //node *np = list->head;

    /* If the list is empty */
    if (list->length == 0){
        create_node (list, prev, next, string, number); 
        return true;
    }

    /* If adding to the list */
    else {
        for (i=0; i < list->length; i++){

            /*if alphabetically identical return false */
            if(strcasecmp(string, curr->name) == 0){
                return false;
            }

            /* String is alphabetically before*/
            else if (strcasecmp(string, curr->name) < 0) {
                next = curr;
                prev = curr->prev;
                create_node(list, prev, next, string, number);
                return true;

            }

            /* String is alphabetically after*/
            else {
                prev = curr;
                next = curr->next;
                curr = curr->next;
            }
        }
        create_node(list, prev, next, string, number);
        return true;
    }
}

// Removes an element in a given list if its name matches a given string.
// Returns true if element found and delete, false otherwise.
bool delete_given_string(llist *list, const char *string)
{
    int i; 
    node *curr = list->head;

    if (list == NULL) {
        return false;
    }

    /* If there is nothing in the list*/
    if (list->length == 0){
        return false;
    }


    else {
        for (i=0; i<list->length; i++){

            if (strcasecmp(string, curr->name)==0){
                /* If only one element */
                if (list->length == 1){
                    list->head = NULL;
                    list->tail = NULL; 

                }
                /* If head of the list */
                else if (curr == list->head) {

                    list->head = curr->next;
                    (list->head)->prev = NULL;
                }

                /* if tail of list */
                else if (curr == list->tail){
                    list->head = curr->prev;
                    (list->head)->next = NULL;

                }

                /* If in the middle */
                else {
                    /* set pointers for previous and next */
                    (curr->next)->prev = curr->prev;
                    (curr->prev)->next = curr->next;
                    free (curr);
                    list->length--;
                    return true; 
                }
                list->length--; 
                free (curr->name);
                free(curr);
                return true; 

            }
            curr = curr->next;
        }
    }

    return false;
}

// Searches a list for an element which matches the given string.  If found,
// the element's ID number is stored in id_number, which is passed by reference
bool find(llist *list, const char *string, int *id_number)
{
    // TO DO
    int i; 
    node *curr =list->head; 

    if (list == NULL){
        return false;
    }

    if (list->length == 0){
        return false;
    }

    else {
        for (i=0; i<list->length; i++){

            if (strcasecmp(string, curr->name)==0){

                return true;
            }
            curr = curr->next;    
        }
    }
    return false;
}
// Prints all name/id pairs in the list.
void print(llist *list)
{

    node *np;
    for ( np = list->head; np != NULL; np = np->next ) {
        printf( "Name and ID: %s\t\t%i\n", np->name, np->id) ;
    }
}

// Prints all name/id pairs in the list from last to first element.
void print_backwards(llist *list)
{

    node *np; 
    for ( np = list->tail; np!= NULL; np = np->prev) {
        printf ("Name and ID: %s\t\t%i\n", np->name, np->id);
    }

}

// Creates a new node with the given number
void create_node ( llist *list, node *prev, node *next, const char *name, int id_number) {

    node *new;

    /* Allocate memory for the new node */
    new = (node *)malloc( sizeof(node) );

    /* Store the number */
    new->id = id_number;
    /* Store the string */
    new->name = (char *)malloc(sizeof(char)*strlen(name)+1);

    /* Make sure memory is available */
    if (new->name == NULL){
        printf("Out of Memory"); 
        exit(1); 
    }
    strcpy(new->name, name);

    /* Update pointers */
    if ( prev == NULL) {
        list->head = new;

        if (next == NULL){
            list->tail = new; 
        }
        else {
            next->prev = new;
        }
    }

    else if (next == NULL){
        list->tail = new;
        prev->next = new;
    }

    /* Inserting in the middle */
    else {
        prev->next = new;
        next->prev = new;
    }
    new->next = next;
    new->prev = prev;

    /* Update lenght size of the list */
    list->length++;

}

