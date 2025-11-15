#ifndef CONTACT_H    //file is defined or not
#define CONTACT_H    //if not defined define it

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;             //contact is data type of the struct

typedef struct {
    Contact contacts[MAX_CONTACTS];   //Array of structutre 
    int contactCount;                 //number of contact to find
} AddressBook;         //addressbook is data type of the struct  

//function prototype or declaration

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook); 
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);

#endif   //should be closed with end if
