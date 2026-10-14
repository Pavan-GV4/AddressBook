#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include<ctype.h>

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts 
    for(int i=0; i<addressBook->contactCount-1;i++)
    {
        for(int j=0; j<addressBook->contactCount-i-1;j++)
        {
            if(strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0)
            //swap 
            {
                Contact temp=addressBook->contacts[j];
                addressBook->contacts[j]=addressBook->contacts[j+1];
                addressBook->contacts[j+1]=temp;
            }
        }
    }
    //Display contacts
    for(int i=0; i<addressBook->contactCount;i++)
    printf("%s\t%s\t%s\n",
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
}

void initialize(AddressBook *addressBook) 
{
    //1.reset contact count
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    //2. Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);

    //show status
   /* if(addressBook->contactCount==0)
    {
        printf("No contacts found.\n");
    }
    else
    {
        printf("Contacts loaded successfully.. Total: %d\n",addressBook->contactCount);
    }*/

}
void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    //step 1: for check for its full
    if(addressBook->contactCount>=MAX_CONTACTS)
    {
        printf("Address Book is full!\n");
        return;
    }
    //step 2: take input directly into array position
    int index = addressBook->contactCount;

    int ret_name;
    do{
        printf("Enter Name: ");
        scanf(" %[^\n]",addressBook->contacts[index].name);
        ret_name= Validation_Name(addressBook->contacts[index].name);

        if(ret_name==0)
        {
            printf("Invalid name! only letters allowed.\n");
        }
    }while (ret_name !=1);
   //with phone validation + duplicate + email validation
//with phone validation + duplicate + email validation
int valid = 0;
char choice;

do
{
    printf("Enter Phone: ");
    scanf("%s", addressBook->contacts[index].phone);

    if (!Validate_Phone_No(addressBook->contacts[index].phone))
    {
        printf("Invalid phone! Enter exactly 10 digits.\n");
        continue;
    }

    //  PHONE DUPLICATE CHECK (DIRECT)
    int phoneDuplicate = 0;
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].phone,
                  addressBook->contacts[index].phone) == 0)
        {
            phoneDuplicate = 1;
            break;
        }
    }

    if(phoneDuplicate)
    {
        printf("Phone already exists! Do you want to continue? (y/n): ");
        scanf(" %c", &choice);

        if(choice == 'n' || choice == 'N')
        {
            continue;
        }
    }

    printf("Enter Email: ");
    scanf("%s", addressBook->contacts[index].email);

    if (!Validation_Email(addressBook->contacts[index].email))
    {
        printf("Invalid email format!\n");
        continue;
    }

    //  EMAIL DUPLICATE CHECK (DIRECT)
    int emailDuplicate = 0;
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].email,
                  addressBook->contacts[index].email) == 0)
        {
            emailDuplicate = 1;
            break;
        }
    }

    if(emailDuplicate)
    {
        printf("Email already exists! Cannot continue.\n");
        continue;
    }

    valid = 1;

} while(valid == 0);
    //step 3: Increase count
    addressBook->contactCount++;;

    //step 4: Success message
    printf("Contact added successfully!\n");
    
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int choice;
    char search[50];
    int found=0;

    printf("\nSearch Contact By:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter choise: ");
    scanf("%d",&choice);

    printf("Enter value to search: ");
    scanf(" %[^\n]",search);

    for(int i=0; i<addressBook->contactCount; i++)
    {
        if(choice==1)// Search by name
        {
            if(strcmp(addressBook->contacts[i].name,search)==0)
            {
                printf("\nFound Contact:\n");
                printf("Name  :%s\n",addressBook->contacts[i].name);
                printf("Phone  :%s\n",addressBook->contacts[i].phone);
                printf("Email   :%s\n",addressBook->contacts[i].email);
                found=1;
            }
        }
        else if(choice==2)//search by phone
        {
            if(strcmp(addressBook->contacts[i].phone,search)==0) 
            {  
                printf("\nFound Contact:\n");
                printf("Name  :%s\n",addressBook->contacts[i].name);
                printf("Phone  :%s\n",addressBook->contacts[i].phone);
                printf("Email   :%s\n",addressBook->contacts[i].email);
                found=1;
            }
        }
        else if(choice==3)//search by email
        {
            if(strcmp(addressBook->contacts[i].email,search)==0)
            {
                 printf("\nFound Contact:\n");
                printf("Name  :%s\n",addressBook->contacts[i].name);
                printf("Phone  :%s\n",addressBook->contacts[i].phone);
                printf("Email   :%s\n",addressBook->contacts[i].email);
                found=1;
            }

        }
        else
        {
            printf("Invalid choice!\n");
            return;
         
        }
    }
    if(found==0)
    {
        printf("Contact not found!\n");
    }
}

void editContact(AddressBook *addressBook)
{
    char search[50];
    int found = 0;

    // Take input
    printf("Enter name to edit: ");
    scanf(" %[^\n]", search);

    // Search contact
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].name, search) == 0)
        {
            found = 1;

            printf("\nContact Found:\n");
            printf("Name  : %s\n", addressBook->contacts[i].name);
            printf("Phone : %s\n", addressBook->contacts[i].phone);
            printf("Email : %s\n", addressBook->contacts[i].email);

            int choice;

            printf("\nWhat do you want to edit?\n");
            printf("1. Name\n2. Phone\n3. Email\n");
            printf("Enter choice: ");

            // Input validation
            if (scanf("%d", &choice) != 1)
            {
                printf("Invalid input!\n");
                while (getchar() != '\n');
                return;
            }

            // Edit Name
            if (choice == 1)
            {
                int ret;
                do
                {
                    printf("Enter new name: ");
                    scanf(" %[^\n]", addressBook->contacts[i].name);

                    ret = Validation_Name(addressBook->contacts[i].name);

                    if (ret == 0)
                        printf("Invalid name! Only letters allowed.\n");

                } while (ret != 1);
            }

            // Edit Phone
            else if (choice == 2)
            {
                int ret;
                do
                {
                    printf("Enter new phone: ");
                    scanf("%s", addressBook->contacts[i].phone);

                    ret = Validate_Phone_No(addressBook->contacts[i].phone);

                    if (ret == 0)
                        printf("Invalid phone! Enter 10 digits.\n");

                } while (ret != 1);
            }

            // Edit Email
            else if (choice == 3)
            {
                int ret;
                do
                {
                    printf("Enter new email: ");
                    scanf("%s", addressBook->contacts[i].email);

                    ret = Validation_Email(addressBook->contacts[i].email);

                    if (ret == 0)
                        printf("Invalid email format!\n");

                } while (ret != 1);
            }

            else
            {
                printf("Invalid choice!\n");
            }

            printf("Contact updated successfully!\n");
            return;
        }
    }

    // If not found
    if (found == 0)
    {
        printf("Contact not found!\n");
    }
}
void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    char search[50];
    int found=0;

    // 1.take input(name)
    printf("Enter name to delete: ");
    scanf(" %[^\n]",search);

    //2. search contact
    for(int i=0; i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].name,search)==0)
        {
            found =1;
            //3.shift contacts left
            for(int j=i; j<addressBook->contactCount-1;j++)
            {
                addressBook->contacts[j]=addressBook->contacts[j+1];
            }
            //decrease count
            addressBook->contactCount--;
            printf("Contacts deleted successfully..\n");
            break;
        }
    }
    //if not found
    if(found == 0)
    {
        printf("Contact not found!\n");
    }
   
}


// validationssssssss


// name validation 
int Validation_Name(char *name)
{
  for(int i=0; name[i]!='\0';i++)
  {
    //allow only alphabets and space
    if(!(isalpha(name[i])|| name[i]==' '))
    {
        return 0;
    }
  }
  return 1;
}

//number validation
int Validate_Phone_No(char *phone)
{
    int len=strlen(phone);
    if(len !=10)
    return 0;

    for(int i=0; i<len; i++)
    {
        if(!isdigit(phone[i]))
        return 0;
    }
    return 1;
}

// Email validation
int Validation_Email(char *email)
{
    int i=0;
    int at_found=0;
    int dot_found=0;

    // check first character(should not be @ or .)
    if(email[0]=='@' || email[0]=='.')
    return 0;

    while (email[i]!='\0')
    {
        //count @
        if(email[i]=='@')
        {
            if(at_found==1)//already found once are before
            return 0;
            at_found=1;

            //next char should not be '.'
            if(email[i+1]=='.')
            return 0;
        }
        // chcking dot after @
        if(email[i]=='.')
        {
            if(at_found==1) //dot must after @
            dot_found=1;

            // dot should not be last
            if(email[i+1]=='\0')
            return 0;
        }
        i++;

    }
    // final check
    if(at_found==1 && dot_found==1)
    return 1;
return 0;

}