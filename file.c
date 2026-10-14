#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
 {
    FILE *fp;
 //1.open the file in read mode contacts.csv
 fp = fopen("contacts.csv","w");

 if(fp ==NULL)
 {
    printf("File not opened!\n");
    return;
 }

 //2.total count in first line
  fprintf(fp, "%d\n",addressBook->contactCount);

 //store contacts in csv format
 //write the name , phone number, email\n
 for(int i=0; i<addressBook->contactCount;i++)
 {
    fprintf(fp,"%s,%s,%s\n",
      addressBook->contacts[i].name,
      addressBook->contacts[i].phone,
      addressBook->contacts[i].email);
 }

 //close the file.
 fclose(fp);
 printf("Contacts saved successfully\n");
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fptr;
 //open the file in read mode contacts.csv
 fptr = fopen("contacts.csv","r");
 // check condtion 
 if(fptr ==NULL)
 {
    return;//file not present
 }
 // reset count
 addressBook->contactCount=0;
 // stored count in first line
 fscanf(fptr, "%d\n",&addressBook->contactCount);
 // Read contacts
 for(int i=0; i<addressBook->contactCount;i++)
 {
    //read name,phone,email
    fscanf(fptr,"%[^,],%[^,],%s\n",
      addressBook->contacts[i].name,
      addressBook->contacts[i].phone,
      addressBook->contacts[i].email);
 }
 //printf("Loaded contacts: %d\n",addressBook->contactCount);
 //close the file
 fclose(fptr);
}
