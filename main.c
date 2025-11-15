/* 
Documentation

Name         : S Sanjay Kumar
Language     : C
Date         : 24-10-2025
Program Name : Address Book to Create, search, edit, delete & list all contacts

Sample I/P :

Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit
Enter your choice: 5
Sort the contact :
1. Sort by name
2. Sort by phone
3. Sort by email
Enter your option: 1

Sample O/P :

Alice Smith      0987654321      alice@example.com
Bob Johnson      1112223333      bob@company.com
Brown      7778889999      david@example.com
Carol White      4445556666      carol@company.com David
Eve Davis      6665554444      eve@example.com
Frank Miller      3334445555      frank@example.com
Grace Wilson      2223334444      grace@example.com
Hannah Clark      5556667777      hannah@example.com
Ian Lewis      8889990000      ian@example.com
John Doe      1234567890      john@example.com
kumar      9445587868      sanjay@gmail.com

*/

#include <stdio.h>     // library header file
#include "contact.h"  //user defined header file

int main() {
    int choice;                 //Variable to store User Choice
    AddressBook addressBook;   // Datatype & structure variable
    initialize(&addressBook); // Initialize the address book

    do {
        //displaying menu options
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);   //read the user choice
        
        switch (choice) {
            case 1:
                createContact(&addressBook);     //Add a new contact
                break;
            case 2:
                searchContact(&addressBook);    //Search for contact by name or phone number or email 
                break;
            case 3:
                editContact(&addressBook);      //Edit the exsisting contact by name or phone number or email 
                break;
            case 4:
                deleteContact(&addressBook);    //Delete the exsisting contact by name or phone number or email 
                break;
            case 5:
                listContacts(&addressBook);     //Display the contacts by sorting using user choice
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);     //saving contacts to file
                break;
            default:
                printf("Invalid choice. Please try again.\n");    //If choice is not between 1-6
        }
    } while (choice != 6);  //6 is for exiting the program
    
       return 0;  //program sucessfully executed
}
