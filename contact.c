#include <stdio.h>          // library header file
#include <stdlib.h>         // library header file
#include <string.h>         // library header file
#include "contact.h"        //user defined header file
#include "file.h"           //user defined header file
#include "populate.h"       //user defined header file

// Function to swap two Contact structures
void swapcontacts(Contact *a, Contact *b)
{
    Contact temp;   //temporary Structure
    temp = *a;      //copy a to temp
    *a = *b;        //copy b to a
    *b = temp;      //copy a to b
}

// Function to check if a phone number is valid
int validphone(char *phone)
{ 
    int len = strlen(phone);   //Length of the input string
    if (len != 10)
        return 0;              //Invalid String length

    // Check all characters are digits
    for (int i = 0; i < len; i++)
    {
        if (!(phone[i] >= '0' && phone[i] <= '9'))  
            return 0;                                   //Invalid character not between 0 to 9
    }
    return 1;        //length is 10 and character is b/w 0 to 9
}

// Function to check if a email is valid
int validemail(char *email)
{
    if (strchr(email, '@') == NULL)      //Check if '@' symbol is present in the email
        return 0;
    if (strstr(email, ".com") == NULL)   //Check if ".com" is present in the email
        return 0;
    return 1; //if both presents then its valid email
}

//  Function to find the index of a contact in the address book
int findindex(AddressBook *addressBook, char *find, int option)
{
    for (int i = 0; i < addressBook->contactCount; i++)               //loop through all contacts in address book
    {
        switch (option)
        {
        case 1:                                                         //search by name
            if (strcmp(addressBook->contacts[i].name, find) == 0)     
                return i;
            break;
        case 2:                                                         //search by phone 
            if (strcmp(addressBook->contacts[i].phone, find) == 0)    
                return i;
            break;
        case 3:                                                         //search by email
            if (strcmp(addressBook->contacts[i].email, find) == 0)
                return i;
            break;
        }
    }
    return -1;     //if no match found                                 
}

// Function to check if a phone number already exists in the address book
int checkphoneno(AddressBook *addressBook, char *phone)
{
    for (int i = 0; i < addressBook->contactCount; i++)           // Loop through all contacts in the address book
    {
        if (strcmp(phone, addressBook->contacts[i].phone) == 0)   //Compare the given phone number with each contact phone number

            return 0;       //phone no. already exist
    }
    return 1;       //phone no. is unique
}

// Sort contacts in the address book based on the selected option
void sortcontacts(AddressBook *addressBook, int option)
{
    int size = addressBook->contactCount;  //no. of the contacts
    //Bubble Sort Algortithm to sort the contacts
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            int cmp = 0;
            switch (option)
            {
            case 1: //sort by name
                cmp = strcmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name);
                break;
            case 2: //sort by phome
                cmp = strcmp(addressBook->contacts[j].phone, addressBook->contacts[j + 1].phone);
                break;
            case 3: //sort by email
                cmp = strcmp(addressBook->contacts[j].email, addressBook->contacts[j + 1].email);
                break;
            }

            if (cmp > 0) //swap the contacts
                swapcontacts(&addressBook->contacts[j], &addressBook->contacts[j + 1]);
        }
    }
}

// Function to print all contacts in the address book
void printcontacts(AddressBook *addressBook)
{
    for (int i = 0; i < addressBook->contactCount; i++)  // Loop through each contact and print their details
    {
        printf("%s      %s      %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
}

// Function to initialize the address book by loading saved contacts from file
void initialize(AddressBook *addressBook)
{
    loadContactsFromFile(addressBook);  // Load existing contacts into the address book structure
}


// Function to save all contacts to file and exit the program
void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook);  // Save current contacts to file
    exit(EXIT_SUCCESS);               // terminate the program immediately   
}

// Function to list contacts sorted by a selected field
void listContacts(AddressBook *addressBook)
{
    int option;  //store user choice
    // Prompt user to choose sorting option
    printf("Sort the contact :\n");
    printf("1. Sort by name\n");
    printf("2. Sort by phone\n");
    printf("3. Sort by email\n");
    printf("Enter your option: ");
    scanf("%d", &option);  //collecting user choice
    getchar();
    // Check if the entered option is valid
    if (option >= 1 && option <= 3)
    {
        sortcontacts(addressBook, option);   // Sort contacts based on selected field
        printcontacts(addressBook);       // Display sorted contacts
    }
    else
    {
        printf("Please Select between 1 - 3");   // Invalid option
    }
}

// Function to add a new contact to the address book
void createContact(AddressBook *addressBook)
{
    char name[50], phone[20], email[50];
    int len;

    getchar();
    printf("Enter the name : ");
    scanf("%[^\n]", name); //collecting name
    getchar();

    do
    {
        printf("Enter the Phone Number :");
        scanf("%s", phone); //collecting phone
        len = strlen(phone);

        if (!validphone(phone)) // Check if phone number is exactly 10 digits
        {
            printf("Error : Please Enter the 10 digit number\n");
            len = 0;
        }
        else if (checkphoneno(addressBook, phone) == 0)  // Check if phone number already exists in the address book
        {
            printf("The Phone number is already present, please enter a new one\n");
            len = 0;
        }

    } while (len != 10); // Continue until a valid 10 digit number is entered

    do
    {
        printf("Enter the email id : ");
        scanf("%s", email); //collecting email
        if (!validemail(email))   // Check if email contains '@' and ends with ".com"
        {
            printf("Error : Invalid email format. Please include '@' and end with '.com'\n");
        }
    } while (!validemail(email)); // Repeat until valid email is entered

    // Copy valid contact details into the address book
    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email);

    (addressBook->contactCount)++; // Increment the contact count
}

// Function to search for a contact in the address book
void searchContact(AddressBook *addressBook)
{
    int option;
    char find[50];
    int index;
    // Prompt user to choose search by
    printf("1. Search by name\n");
    printf("2. Search by phone\n");
    printf("3. Search by email\n");
    printf("Enter the choice : ");
    scanf("%d", &option);  //collecting user choice
    getchar();

    printf("\nEnter the value to search : ");
    scanf("%[^\n]", find);  //collecting the value to search

    // Search for the contact using the selected option
    index = findindex(addressBook, find, option);

     // Display result
    if (index != -1)
    {
        printf("%s      %s      %s\n", addressBook->contacts[index].name, addressBook->contacts[index].phone, addressBook->contacts[index].email);
    }
    else
    {
        printf("Contact not present in the address book\n"); // Contact not found
    }
}


// Function to edit an existing contact in the address book
void editContact(AddressBook *addressBook)
{
    int option;
    char find[50];
    int index;
    // Prompt user to choose search by
    printf("Select the contact :\n");
    printf("1. Search by name\n");
    printf("2. Search by phone\n");
    printf("3. Search by email\n");
    printf("Enter your option: ");
    scanf("%d", &option);  //collecting user choice
    getchar();

    printf("Enter the value : ");
    scanf("%[^\n]", find);  //collecting the value to search

    index = findindex(addressBook, find, option);  //find the contact index
    if (index == -1)
    {
        printf("The contact is not present in the address book.\n");  // Contact not found
        return;
    }

     // Display the contact to be edited
    printf("\nEditing Contact:\n");
    printf("%s      %s      %s\n",addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);

    // Prompt user to choose which field to edit
    printf("\n1. Edit the name\n");
    printf("2. Edit the phone\n");
    printf("3. Edit the email\n");
    printf("Enter your option: ");
    scanf("%d", &option);  //collecting user choice
    getchar();

    switch (option)
    {
    case 1:  // Edit name
        printf("Enter the new name : ");
        scanf("%[^\n]", addressBook->contacts[index].name);
        break;

    case 2:   // Edit Phone
    {
        char newPhone[20];
        int valid = 0;

        do
        {
            printf("Enter the new phone : ");
            scanf("%s", newPhone);

            if (!validphone(newPhone))
            {
                printf("Error: Please enter a valid 10-digit phone number.\n");
                valid = 0;
            }
            else if (checkphoneno(addressBook, newPhone) == 0)
            {
                printf("Error: This phone number already exists in the address book.\n");
                valid = 0;
            }
            else
            {
                valid = 1;
            }
        } while (valid == 0);   // Loop until a valid and unique phone number is entered

        strcpy(addressBook->contacts[index].phone, newPhone); // Update phone number
        break;
    }

    case 3:   // Edit email
    {
        char newEmail[50];
        int valid = 0;

        do
        {
            printf("Enter the new email : ");
            scanf("%s", newEmail);

            if (!validemail(newEmail))
            {
                printf("Error: Invalid email format. Must contain '@' and end with '.com'\n");
                valid = 0;
            }
            else
            {
                valid = 1;
            }
        } while (valid == 0);  // Loop until a valid email is entered

        strcpy(addressBook->contacts[index].email, newEmail);  // Update email
        break;
    }

    default: // Invalid edit option
        printf("Invalid option.\n");
        break;
    }
}

// Function to delete a contact from the address book
void deleteContact(AddressBook *addressBook)
{
    int option;
    char find[50];
    int index;
    // Prompt user to choose search by
    printf("Select the contact :\n");
    printf("1. Search by name\n");
    printf("2. Search by phone\n");
    printf("3. Search by email\n");
    printf("Enter your option: ");
    scanf("%d", &option); //collecting user choice
    getchar();

    printf("Enter the value : ");
    scanf("%[^\n]", find);

    index = findindex(addressBook, find, option);  // find the contact index 

    if (index == -1) // Contact not found
    {
        printf("The contact is not present in the address book.\n");
        return;
    }

    // Shift all contacts
    for (int i = index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    // Decrease the contact count
    (addressBook->contactCount)--;
}
