#include <stdio.h>
#include<string.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fp = fopen("contacts.txt", "w");
    if (fp == NULL) {
        printf("\033[1;31mError: Could not open file for saving.\033[0m\n");
        return;
    }

    // Write the total count first so we know how many to read later
   fprintf(fp, "Total Count: %d\n", addressBook->contactCount);

    for (int i = 0; i < addressBook->contactCount; i++) {
        // We use a delimiter like '#' or ',' to separate fields
        if (strlen(addressBook->contacts[i].name) > 0)
        {
        fprintf(fp, "%s,%s,%s\n", 
                addressBook->contacts[i].name, 
                addressBook->contacts[i].phone, 
                addressBook->contacts[i].email);
        }
    }

    fclose(fp);
    printf("\n\033[1;32mContacts saved successfully to contacts.txt\033[0m\n");

  
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fp = fopen("contacts.txt", "r");
    if (fp == NULL) {
        addressBook->contactCount = 0;
        return;
    }

    int expectedCount = 0;
    // 1. Read the number from the file into a temporary variable
    if (fscanf(fp, "Total Count: %d\n", &expectedCount) != 1) {
        addressBook->contactCount = 0;
        fclose(fp);
        return;
    }

    int actualLoaded = 0;
    for (int i = 0; i < expectedCount; i++) {
        // 2. Check if fscanf successfully finds all 3 pieces of data
        // If it returns 3, it means it read Name, Phone, and Email successfully
        if (fscanf(fp, " %[^,],%[^,],%[^\n]\n", 
                   addressBook->contacts[actualLoaded].name, 
                   addressBook->contacts[actualLoaded].phone, 
                   addressBook->contacts[actualLoaded].email) == 3) 
        {
            actualLoaded++;
        }
    }

    // 3. Set the official count to the number of valid lines actually found
    addressBook->contactCount = actualLoaded;

    fclose(fp);
}



