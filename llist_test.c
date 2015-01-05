/****************************************************************
 * llist_test.c
 * MPATE-GE 2618
 * Problem Set 5
 * 
 * An interactive program to test the llist class implemented in llist.c
 * and defined in llist.h.   
 ****************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "inputlib.h"
#include "llist.h"

/* functions for testing list functions */
void print_menu();
int prompt_user();
void test_insert(llist *list);      
void test_delete(llist *list); 
void test_search(llist *list);      

int main() 
{
    // Allocate memory for a new list
    llist *list = (llist *)malloc(sizeof(llist));
    if (list == NULL) {
        printf("Unable to allocate memory\n");
        exit(1);
    }
    init_list(list);

    int option = 0;
    bool quit = false;

    // Display menu and prompt user for action
    while (!quit) {
        option = prompt_user();
        switch (option) {
            case 1:
                printf("\n\tNumber of elements in list: %d\n", list->length);
                print(list);
                break;
            case 2: test_insert(list);
                    break;
            case 3: test_delete(list);
                    break;
            case 4: test_search(list);
                    break;
            case 5: print_backwards(list);
                    break;
            case 6: printf("Bye.\n");
                    quit = true;
                    break;
        }
    }
    // call function to free memory for entire list
    delete_list(list);

    return 0;
}

// Displays options to user
void print_menu()
{
    printf("\n[1] PRINT LIST\n"
            "[2] INSERT ELEMENT\n"
            "[3] DELETE ELEMENT\n"
            "[4] SEARCH BY NAME\n"
            "[5] PRINT LIST BACKWARDS\n"
            "[6] QUIT\n");
}

// Get the option number chosen by the user
int prompt_user()
{
    int option;
    print_menu();
    printf("\nPlease select an option by typing 1-6: ");
    option = getInt();
    // checking for both incorrect number and other bad input (like characters)
    while (option < 1 || option > 6) {
        printf("Invalid option. Please select a number 1-6: ");
        option = getInt();
    }
    return option;
}

// Function test insertion into list
void test_insert(llist *list)
{
    char *string;
    int id_number;

    printf("Enter a name: ");
    string = getString();
    printf("Please enter an ID number: ");
    id_number = getInt();
    if (!insert(list, string, id_number)) {
        printf("Insertion failed: duplicate string found.\n");
    }
}

// Function to test deletion from list, given a string to search for.
void test_delete(llist *list)
{
    char *string;
    printf("Enter a name: ");
    string = getString();
    if(delete_given_string(list, string)) {
        printf("\n\tElement found and deleted\n");
    } else {
        printf("\n\tElement not found.\n");
    }
    free (string);
}

// Function to test searching of the list given a string.
void test_search(llist *list) 
{
    int id_number;
    char *string;

    printf("Enter a name: ");
    string = getString();
    if (find(list, string, &id_number)) {
        printf("\n\t%s was found. ID number is %d.\n", string, id_number);
    } else {
        printf("\n\t%s was not found.\n", string);
    }
    free (string);
}
