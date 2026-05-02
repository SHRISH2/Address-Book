#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include "contact.h"
#include "file.h"
//#include "populate.h"
int check_number(char* new_num,AddressBook *addressBook);
int check_mail(char *new_mail,AddressBook *addressBook);
int match_index[100];

int gi=-1;
int gm=0;
void header()  //For printing the title of the content
{
    printf("\n\033[1;96m%-10s %-20s %-20s %-25s\033[0m\n", "S.no", "Name", "Phone", "Email");

    printf("\033[36m");
    for(int i = 0; i < 78; i++) 
    printf("-"); 
    printf("\033[0m\n");
}
void displayrow(AddressBook *addressBook,int i)   //For printing elements of the contents
{
    printf("\033[33m%-10d\033[0m \033[1;32m%-20s\033[0m \033[34m%-20s\033[0m \033[4;37m%-25s\033[0m\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);

}
void listContacts(AddressBook *addressBook)    //To list all the contact in the address book
{ 
    if(addressBook->contactCount==0)
    {
        printf("\n\033[31m Address book is empty\033[0m\n");  //To check whether the address book is empty or not
        return;
    }
    header();
    for(int i=0;i<addressBook->contactCount;i++)
    {
        displayrow(addressBook,i);   //passing the arguments to print the contents
    }
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0; //initialize with zero to start
    
    loadContactsFromFile(addressBook);  //calling the load contact function in another file
}

void saveAndExit(AddressBook *addressBook) {
      saveContactsToFile(addressBook); // Save contacts to file
      printf("\n\033[1;32mExiting program...............\033[0m\n");
      exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
    int verify_name,verify_num,verify_mail;
    int index=addressBook->contactCount;
    int attempts = 0; 
    char new_name[100],new_num[100],new_mail[100];

    //for entering the Name
    do
    {
        printf("\033[1;33mEnter the name: \033[0m");
        scanf(" %[^\n]",new_name);
        
        verify_name = check_name(new_name);
        
        if (verify_name != 1)
        {
            attempts++; 
            
            if (attempts >= 5)    //to give attempts to the user
            {
                printf("\n\033[1;31mError: 5 failed attempts reached. Terminating program...\033[0m\n");
                exit(1); // Forcefully closes the entire program
            }

            printf("\033[1;31mInvalid name! (Min 5 chars, no leading digits).\033[0m\n");
            printf("Attempts left: %d\n", 5 - attempts);
        }

    } while (verify_name != 1);

    //for entering the phone number
    attempts=0;
    do
    {
        printf("\033[1;33mEnter the number: \033[0m");
        scanf(" %[^\n]",new_num);
        verify_num=check_number(new_num,addressBook);
        if(verify_num != 1)
        {
            attempts++;
            if(attempts>=5)    //to give attempts to the user
            {
                printf("\033[1;31mToo many failed attempts for number\033[0m");
                exit(1);
            }
            printf("\nAttempts left:%d\n",5-attempts);
        }
    }while(verify_num != 1);

    //For entering E-mail

    attempts=0;
    do
    {
        printf("\033[1;33mEnter the Email: \033[0m");
        scanf(" %[^\n]",new_mail);
        verify_mail=check_mail(new_mail,addressBook);
        if(verify_mail != 1)
        {
            attempts++;
            if(attempts>=5)    //to give attempts to the user
            {
                printf("\033[1;31mToo many failed attempts for mail\033[0m\n");
                exit(1);
            }
            printf("Attempts left:%d\n",5-attempts);
        }
    }while(verify_mail != 1);


    strcpy(addressBook->contacts[index].name, new_name);   //assign the temp name after validation to the structure array
    strcpy(addressBook->contacts[index].phone, new_num);   //assign the temp phone number after validation to the structure array
    strcpy(addressBook->contacts[index].email, new_mail);  //assign the temp email after validation to the structure array

    addressBook->contactCount++;   //we need to track how many contacts updated

    printf("\033[1;32mContact successfully saved!\033[0m\n");  //printing the success message
}

//for validating the Name

int check_name(char *new_name)
{
    int len = strlen(new_name);  //to know the length of the name

    if (isdigit(new_name[0]))
    {
        printf("\033[1;31mFirst character can't be a Digit!\033[0m\n");
        return 0;
    }

    if (len < 5)
    {
        printf("\033[1;31mMinimum 5 Characters required!\033[0m\n");
        return 0;
    }

    for (int i = 0; i < len; i++)
    {
        if (i < len - 1)
        {
            // Body: Letters and spaces only
            if (!(isalpha(new_name[i]) || new_name[i] == ' '))
            {
                printf("\033[1;31mDigit can only be present at the end!\033[0m\n");
                return 0;
            }
        }
        else
        {
            // Last char: Letters, spaces, OR digits allowed
            if (!(isalpha(new_name[i]) || isdigit(new_name[i]) || new_name[i] == ' '))
            {
                printf("\033[1;31mNo special Characters at the End!\033[0m\n");
                return 0;
            }
        }
    }
    return 1;
}

//for validating the mobile number

int check_number(char* new_num,AddressBook *addressBook)
{
    int len=strlen(new_num);  //To know the lenght of the mobile number
    if(len!=10)
    {
        printf("\033[1;31mError : Number must be 10 digit.\033[0m\n");
        return 0;
    }
    if(new_num[0]<'6' || new_num[0]>'9')
    {
        printf("\033[1;31mError : Must start with 6-9\033[0m\n");
        return 0;
    }
    for(int i=0;i<len;i++)
    {
        if(!isdigit(new_num[i]))
        {
            printf("\033[1;31mError : Only Digits allowed\033[0m\n");
            return 0;
        }
    }
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(new_num,addressBook->contacts[i].phone)==0)
        {
            printf("\033[1;31mError:Number already exists\033[0m\n");
            return 0;
        }
    }
    return 1;
}

//for Validating Email

int check_mail(char *new_mail,AddressBook *addressBook)
{
    int len=strlen(new_mail);  //to know the length of the mail id
    char *at_ptr=strchr(new_mail,'@'); //to point at the @ where it is present
    char *com_pointer=strstr(new_mail,".com"); //to point to the ".com" where it is present
    if(isdigit(new_mail[0]))
    {
        printf("\033[1;31mFirst char can't be digit\033[0m\n");
        return 0;
    }
    for(int i=0;i<len;i++)
    {
     if(isupper(new_mail[i]))
      {
        printf("\033[1;31mMail id can't be in Upper case\033[0m\n");
        return 0;
      }
    }

    //to check whether @ and .com present or not
    if(at_ptr==NULL || com_pointer==NULL)
    {
        printf("\033[1;31mMail id should contain '@' and '.com' \033[0m\n");
        return 0;
    }
    if(strchr(at_ptr+1,'@')!=NULL)
    {
        printf("\033[1;31mError: '@' must appear only once\033[0m\n");
        return 0;
    }

    if(strstr(com_pointer+1,".com")!=NULL)
    {
        printf("\033[1;31mError: '.com' must appear only once\033[0m\n");
        return 0;
    }
    if(com_pointer==NULL || strcmp(com_pointer,".com")!=0)
    {
        printf("\033[1;31mNo other characters are allowed after .com\033[0m\n");
        return 0;
    }

    if(com_pointer<at_ptr)
    {
        printf("\033[1;31mError : '.com' must come after '@'\033[0m\n");
        return 0;
    }

    if((at_ptr-new_mail)<5)
    {
        printf("\033[1;31mError: Min 5 chars required before '@'\033[0m\n");
        return 0;
    }

    int checkchar=com_pointer-(at_ptr+1);
    if(checkchar<4)
    {
        printf("\033[1;31mError : Min 4 alpha characters required for domain\033[0m\n");
        return 0;
    }

    for(char *p=at_ptr+1;p<com_pointer;p++)
    {
        if(!isalpha(*p))
        {
            printf("\033[1;31m Domain must be alphabet characters \033[0m\n");
            return 0;
        }
    }

    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(new_mail,addressBook->contacts[i].email)==0)
        {
            printf("\033[1;31mError:Email already exists\033[0m\n");
            return 0;
        }
    }
    return 1;

}

//For Searching the contact

void searchContact(AddressBook *addressBook) 
{
    gi=-1;
    gm=0;
    if(addressBook->contactCount==0)
    {
        printf("\033[1;31mAddress book is empty.Nothing to search\033[0m\n");
        return;
    }
    int choice;
    char target[100];

    printf("\033[95m""\n search by:\n1.Name\n2.Phone number\n3.Email id\n4.Exit\n\nEnter the choice:" "\033[0m");
    scanf("%d",&choice);
        if(choice==4)
        {
            return; //for the exiting option
        }
        if(choice < 1 || choice > 4)
        {
            printf("\033[1;31mInvalid Choice........\033[0m\n");
            return;
        }
    printf("\033[1;33mEnter the search term: \033[0m");
    scanf(" %[^\n]",target);
    for(int i=0;i<addressBook->contactCount;i++)
    {
        int ismatch=0;
        if(choice==1 && strcasecmp(addressBook->contacts[i].name,target)==0)  //to check for the search element match with that name in address book
        {
            ismatch=1;
        }
        else if(choice==2 && strcmp(addressBook->contacts[i].phone,target)==0)  //To check for the serch element match with that phone number in address book
        {
            ismatch=1;
        }
        else if(choice==3 && strcmp(addressBook->contacts[i].email,target)==0)  //To check for the search element match with the email Id in address book
        {
            ismatch=1;
        }
        if(ismatch)
        {
            if(gm==0)
            {
                header(); //That title need to print only once
            }
            match_index[gm]=i;
            gm++;
            printf("\033[33m%-10d\033[0m \033[1;32m%-20s\033[0m \033[34m%-20s\033[0m \033[4;37m%-25s\033[0m\n", 
                   gm, 
                   addressBook->contacts[i].name, 
                   addressBook->contacts[i].phone, 
                   addressBook->contacts[i].email); //to print all contents which is matched
            gi=i;
        }

    }
    if(gm==0)
    {
        printf("\n\033[1;31m No record found matching:%s,please try again\033[0m\n",target);
    }

    /* Define the logic for search */
}

void editContact(AddressBook *addressBook)
{
    searchContact(addressBook);  //calling the search function to implement edit
    if(gm==0)
    {
        return;
    }
    if(gm>1)
    {
        int serial,attempts=0;
        while(1)
        {
        printf("\n\033[30;43mMultiple Matches Found.Enter the s.no (1-%d) to edit: \033[0m",gm);
        scanf("%d",&serial);
        if(serial > 0 && serial <= gm)
        {
            gi=match_index[serial-1]; //To access the that index we need to edit
            break;
        }
    else
    {
        attempts++;
        if(attempts >= 2)  //to handle if user entered wrong number
        {
            printf("\n\033[1;31mInvalid selection. operation cancelled.\033[0m\n");
            return;
        }
        printf("\n\033[1;31m Error: pick a number between 1 to %d.Attempts left:%d\033[0m\n",gm,2-attempts);
    }
   }
}   

    int echoice,attempts_edit=0,verify=0;
    char new_data[100];
    printf("\n\033[95m1. Edit Name\n2. Edit Phone\n3. Edit Email\n\nEnter your Choice: \033[0m");
    scanf("%d",&echoice);
    switch(echoice)
    {
        case 1:
           do
           {
           printf("\033[1;33mEnter new name: \033[0m");
           scanf(" %[^\n]",new_data);
           verify=check_name(new_data); //To check the entered name through the Edit option also satisfy all validation

            if(verify != 1)
            {
            attempts_edit++;
            if(attempts_edit>=5)
            {
                printf("\n \033[1;31m Error: Maximum attempts reached.update cancelled.\033[0m\n");
                return;
            }
            printf("Attempts left:%d\n",5-attempts_edit);
            }
           }while(verify!=1);
        strcpy(addressBook->contacts[gi].name,new_data);  //to change the already existing name with this new edited name
        printf("\033[1;32mName Updated!\033[0m\n");
        break;
        case 2:
        do{
           printf("\033[1;33mEnter new phone: \033[0m");
           scanf(" %[^\n]",new_data);
           verify=check_number(new_data,addressBook); //To check the entered phone number through the Edit option also satisfy all validation
           if(verify != 1)
           {
            attempts_edit++;
            if(attempts_edit>=5)
            {
                printf("\033[1;31mMaximum attempts reached.update cancelled.\033[0m\n");
                return;
            }
            printf("Attempts left:%d\n",5-attempts_edit);
           }
        }while(verify!=1); 
        strcpy(addressBook->contacts[gi].phone,new_data);//To change the already existing data with this edited new number
        printf("\033[1;32mPhone Updated\033[0m\n");  
        break;
        case 3:
           do{
           printf("\033[1;33mEnter new email: \033[0m");
           scanf(" %[^\n]",new_data);
           verify=check_mail(new_data,addressBook); //To check the entered email id also satisfy all the validation
           if(verify != 1)
           {
            attempts_edit++;
            if(attempts_edit>=5)
            {
                printf("\033[1;31mMaximum attempts reached,update cancelled.\033[0m\n");
                return;
            }
            printf("Attempts left:%d\n",5-attempts_edit);
            }
        }while(verify!=1);
        strcpy(addressBook->contacts[gi].email,new_data); //to change the already existing data with that Edited email id
        printf("\033[1;32mEmail Updated\033[0m\n");
        break;
        default:
           printf("\033[1;31mInvaild choice.\033[0m\n");   

    }
    
}

void deleteContact(AddressBook *addressBook)
{
    searchContact(addressBook);  //Calling the search function to implement the Delete function
    if(gm==0)
    {
        return;
    }
    if(gm>1)
    {
        int serial,attempts=0;
        while(1)
        {
        printf("\n\033[30;43mMultiple matches found.Enter the S.no (1-%d) to delete: \033[0m",gm);
        scanf("%d",&serial);
        if(serial>0 && serial<=gm)
        {
            gi=match_index[serial-1];  //To know which index to delete
            break;
        }
        else
        {
            attempts++;
            if(attempts>=2)
            {
                printf("\033[1;31m Invalid selection. Delete cancelled.\033[0m\n");
                return;
            }
            printf("\033[33m Error: pick a number between 1 to %d.\n Attempts left:%d\033[0m\n",gm,2-attempts);

        }
    }
}
    char c;
    printf("\n\033[37;41mAre you sure you want to delete [y/n]:\033[0m"); //Again asking the user to chech if he really wants to delete
    scanf(" %c",&c);
    if(c=='n' || c=='N')
    {
        printf("\033[31m Deletion Cancelled\033[0m\n");
        return;
    }
    for(int i=gi;i<addressBook->contactCount-1;i++)
    {
        addressBook->contacts[i]=addressBook->contacts[i+1];
    }
    addressBook->contactCount--;
    printf("\033[1;92m\n Contact deleted sucessfully!\033[0m\n");  //to print success delete message
   
}
