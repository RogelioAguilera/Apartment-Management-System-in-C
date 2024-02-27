// assign6.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assign6.h"

#define FILENAME "apartments.dat"

void createApt();
void readApt();
void updateApt();
void deleteApt();

int main()
{
    char option;
    printf("Enter one of the following actions or press CTRL-D to exit:\n");
    printf("C - create a new apartment record\n");
    printf("R - read an existing apartment record\n");
    printf("U - update an existing apartment record\n");
    printf("D - delete an existing apartment record\n");
    while (1)
    {
        if (scanf(" %c", &option) == 1) {
            switch (option)
            {
            case 'C':
            case 'c':
                createApt();
                break;
            case 'R':
            case 'r':
                readApt();
                break;
            case 'U':
            case 'u':
                updateApt();
                break;
            case 'D':
            case 'd':
                deleteApt();
                break;

            default:
                printf("ERROR: invalid option\n");
		break;
            }
        }
	else if (scanf(" %c", &option) == EOF) {
		break;
	}
	else {
            printf("ERROR: invalid input or end of file\n");
		break; 
        }
    }

    return 0;  
}
void createApt()
{
    FILE *file = fopen(FILENAME, "rb+");

    if (file == NULL)
    {
        file = fopen(FILENAME, "wb");
        fclose(file);
        file = fopen(FILENAME, "rb+");
    }

    int apartmentNumber;
    printf("Enter the apartment number: ");
    scanf("%d", &apartmentNumber);

    fseek(file, apartmentNumber * sizeof(Apartment), SEEK_SET);
    Apartment existingApartment;
    fread(&existingApartment, sizeof(Apartment), 1, file);
    if (strlen(existingApartment.firstName) > 0)
    {
        printf("ERROR: apartment already exists\n");
        fclose(file);
        return;
    }

    Apartment newApartment;
    newApartment.balance = 900; 

    printf("Enter resident's first name: ");
    scanf("%s", newApartment.firstName);

    printf("Enter resident's last name: ");
    scanf(" %[^\n]", newApartment.lastName);

    printf("Enter the lease start date: ");
    scanf("%s", newApartment.leaseStart);

    printf("Enter the lease end date: ");
    scanf("%s", newApartment.leaseEnd);

    fseek(file, apartmentNumber * sizeof(Apartment), SEEK_SET);
    fwrite(&newApartment, sizeof(Apartment), 1, file);

    while (getchar() != '\n');
    fclose(file);

    printf("Apartment record created successfully.\n");
}

void readApt()
{
    FILE *file = fopen(FILENAME, "rb");

    if (file == NULL)
    {
        printf("ERROR: Unable to open file for reading.\n");
        return;
    }
    int apartmentNumber;
    printf("Enter an apartment number: ");
    scanf("%d", &apartmentNumber);

    fseek(file, apartmentNumber * sizeof(Apartment), SEEK_SET);
    Apartment selectedApartment;
    fread(&selectedApartment, sizeof(Apartment), 1, file);

    if (strlen(selectedApartment.firstName) > 0)
    {
        printf("Apartment Number: %d\n", apartmentNumber);
        printf("Tenant Name: %s, %s\n", selectedApartment.lastName, selectedApartment.firstName);
        printf("Lease Start: %s\n", selectedApartment.leaseStart);
        printf("Lease End: %s\n", selectedApartment.leaseEnd);
        printf("Current Balance: %d\n", selectedApartment.balance);
    }
    else
    {
        printf("ERROR: apartment not found\n");
    }
    while (getchar() != '\n');
    fclose(file);
}

void updateApt()
{
    FILE *file = fopen(FILENAME, "rb+");

    if (file == NULL)
    {
        printf("ERROR: Unable to open file for updating.\n");
        return;
    }

    int apartmentNumber;
    printf("Enter the apartment number to update: ");
    scanf("%d", &apartmentNumber);
    while (getchar() != '\n');
    fseek(file, apartmentNumber * sizeof(Apartment), SEEK_SET);
    Apartment selectedApartment;
    fread(&selectedApartment, sizeof(Apartment), 1, file);

	
    if (strlen(selectedApartment.firstName) > 0)
    {
        printf("Input resident's first name (Enter to keep original): ");
        if (getchar() != '\n') {
            scanf(" %[^\n]", selectedApartment.firstName);
        }

        printf("Input resident's last name (Enter to keep original): ");
        if (getchar() != '\n') {
            scanf(" %[^\n]", selectedApartment.lastName);
        }

        printf("Input lease start date (Enter to keep original): ");
        if (getchar() != '\n') {
            scanf(" %[^\n]", selectedApartment.leaseStart);
        }

        printf("Input lease end date (Enter to keep original): ");
        if (getchar() != '\n') {
            scanf(" %[^\n]", selectedApartment.leaseEnd);
        }

        printf("Input balance (Enter to keep original): ");
        if (getchar() != '\n') {
            scanf(" %d", &selectedApartment.balance);
        }
        fseek(file, apartmentNumber * sizeof(Apartment), SEEK_SET);
        fwrite(&selectedApartment, sizeof(Apartment), 1, file);

        printf("Apartment record updated successfully.\n");
    }
    else
    {
        printf("ERROR: apartment not found\n");
    }
    while (getchar() != '\n');
    fclose(file);
}

void deleteApt()
{
    FILE *file = fopen(FILENAME, "rb+");

    if (file == NULL)
    {
        printf("ERROR: Unable to open file for deleting.\n");
        return;
    }

    int apartmentNumber;
    printf("Enter the apartment number to delete: ");
    scanf("%d", &apartmentNumber);

    fseek(file, apartmentNumber * sizeof(Apartment), SEEK_SET);
    Apartment selectedApartment;
    fread(&selectedApartment, sizeof(Apartment), 1, file);

    if (strlen(selectedApartment.firstName) > 0)
    {
        selectedApartment.firstName[0] = '\0';

        fseek(file, apartmentNumber * sizeof(Apartment), SEEK_SET);
        fwrite(&selectedApartment, sizeof(Apartment), 1, file);

        printf("Record %d was successfully deleted.\n", apartmentNumber);
    }
    else
    {
        printf("ERROR: apartment not found\n");
    }
    while (getchar() != '\n');
    fclose(file);
}
