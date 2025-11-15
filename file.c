#include <stdio.h>     // library header file
#include <stdlib.h>    // library header file
#include <string.h>    // library header file
#include "file.h"      //user defined header file

//Function to save all contacts to a file

void saveContactsToFile(AddressBook *addressBook) {

   FILE *fptr =  fopen("contact.csv", "w");  //opens the file in write mode
   int size = addressBook->contactCount;     //get number of contact count
   fprintf(fptr,"#%d#\n", size);             //Write the number of contacts 
   for(int i=0;i<size;i++)
    {
        fprintf(fptr,"%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);    //writes each contact details to the file
    }
    fclose(fptr);  //close the file
}

//Function to load the contact from file to Structure

void loadContactsFromFile(AddressBook *addressBook) {
    
    char str[100];  //to store the entire line
    FILE *fptr = fopen("contact.csv","r");  //open the file in read mode
    if(fptr == NULL)                        //checking is the file exsit
    {
        printf("File is not present\n");
    }
    else
    {
        fscanf(fptr, "%[^\n]", str);           //read the first line
        int size = atoi(strtok(&str[1],"#"));  //extract size from the first line
        addressBook->contactCount = size;      //updating the count value

        for(int i = 0;i<size;i++)
        {
            fscanf(fptr, " %[^\n]", str);                               //read the next line
            strcpy(addressBook->contacts[i].name, strtok(str,","));     //Extract the name and store in Structure
            strcpy(addressBook->contacts[i].phone, strtok(NULL,","));   //Extract the Phone No. and store in Structure
            strcpy(addressBook->contacts[i].email, strtok(NULL,","));   //Extract the Email and store in Structure
        }
        fclose(fptr);  //close the file
    }

}
