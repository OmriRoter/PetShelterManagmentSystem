// PetOwner.c
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "PetOwner.h"
#include "Address.h"


PetOwner* createPetOwner(int id, const char* name, Address address) {
    PetOwner* newOwner = (PetOwner*)malloc(sizeof(PetOwner));
    CHECK_ALLOCATION(newOwner);

    newOwner->id = id;
    newOwner->name = _strdup(name);
    newOwner->address = address;
    newOwner->pets = NULL;
    newOwner->numPets = 0;

    return newOwner;
}

void addPetToOwner(PetOwner* owner, Pet* pet) {
    if (!owner || !pet) return;

    // Use a temporary pointer for realloc to avoid memory leaks
    Pet** temp = realloc(owner->pets, (owner->numPets + 1) * sizeof(Pet*));
    if (!temp) {
        printf("Failed to allocate memory for adding new pet.\n");
        // Handle memory allocation failure; temp is NULL, owner->pets is still valid
        return;
    }

    owner->pets = temp; // Update owner->pets only after successful realloc
    owner->pets[owner->numPets] = pet;
    owner->numPets++;
}

void removePetFromOwner(PetOwner* owner, Pet* pet) {
    if (!owner || !pet || owner->numPets == 0) return;

    for (int i = 0; i < owner->numPets; i++) {
        if (owner->pets[i] == pet) {
            for (int j = i; j < owner->numPets - 1; j++) {
                owner->pets[j] = owner->pets[j + 1];
            }
            owner->numPets--;

            // Use a temporary pointer for realloc to avoid memory leaks
            Pet** temp = realloc(owner->pets, owner->numPets * sizeof(Pet*));
            if (!temp && owner->numPets > 0) {
                printf("Failed to reallocate memory after removing pet.\n");
                // Handle reallocation failure; temp is NULL but owner->pets still valid
                return;
            }

            owner->pets = temp; // Update owner->pets only after successful realloc
            break;
        }
    }
}

void displayPetOwnerDetails(const PetOwner* owner) {
    UPPER_PRINT_DIVIDER();
    if (!owner) {
        printf("No Pet Owner details to display.\n");
        LOWER_PRINT_DIVIDER();
        return;
    }

    printf("Pet Owner Details:\n");
    printf("Pet Owner ID: %d\n", owner->id);
    printf("Pet Owner Name: %s\n", owner->name ? owner->name : "N/A");
    printf("Address:\n");
    displayAddress(&(owner->address)); // Use existing function to display Address
    LOWER_PRINT_DIVIDER();
}

void freePetOwner(PetOwner* owner) {
    if (!owner) return;

    free(owner->name);
    for (int i = 0; i < owner->numPets; i++) {
        freePet(owner->pets[i]);
    }
    free(owner->pets);
    free(owner);
}

PetOwner* createPetOwnerFromInput(void) {
    int id;
    char name[NAME_SIZE]; // Use defined constant
    char inputBuffer[INPUT_BUFFER_SIZE]; // Use defined constant

    UPPER_PRINT_DIVIDER();
    printf("Creating New Pet Owner\n");

    // ID input with validation for numbers only
    do {
        printf("Enter Pet Owner ID (numbers only): ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
    } while (sscanf(inputBuffer, "%d", &id) != 1);

    // Name input with validation for letters only
    do {
        printf("Enter Pet Owner Name (letters and spaces only): ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0; // Remove newline character
    } while (!isStringAlpha(name));

    // Address input with a detailed introduction
    printf("Enter Address Details:\n");
    Address address = createAddressFromInput(); // Assuming this function is structured for user input

    LOWER_PRINT_DIVIDER();
    return createPetOwner(id, name, address);
}

void savePetOwnerToTextFile(const PetOwner* owner, FILE* file) {
    if (!owner || !file) return;

    fprintf(file, "%d,%s,", owner->id, owner->name);
    saveAddressToTextFile(&owner->address, file);
    fprintf(file, ",%d\n", owner->numPets);

    for (int i = 0; i < owner->numPets; i++) {
        savePetToTextFile(owner->pets[i], file);
    }
}

PetOwner* loadPetOwnerFromTextFile(FILE* file) {
    if (!file) return NULL;

    PetOwner* owner = (PetOwner*)malloc(sizeof(PetOwner));
    CHECK_ALLOCATION(owner);

    owner->name = (char*)malloc(100 * sizeof(char)); // Adjust size as needed
    if (!owner->name) {
        free(owner);
        return NULL;
    }

    if (fscanf(file, "%d,%[^,],", &owner->id, owner->name) != 2) {
        free(owner->name);
        free(owner);
        return NULL;
    }

    owner->address = loadAddressFromTextFile(file);

    if (fscanf(file, ",%d\n", &owner->numPets) != 1) {
        free(owner->name);
        free(owner);
        return NULL;
    }

    owner->pets = (Pet**)malloc(owner->numPets * sizeof(Pet*));
    if (!owner->pets) {
        free(owner->name);
        free(owner);
        return NULL;
    }

    for (int i = 0; i < owner->numPets; i++) {
        owner->pets[i] = loadPetFromTextFile(file);
        if (!owner->pets[i]) {
            for (int j = 0; j < i; j++) {
                freePet(owner->pets[j]);
            }
            free(owner->pets);
            free(owner->name);
            free(owner);
            return NULL;
        }
    }

    return owner;
}

void savePetOwnerToBinaryFile(const PetOwner* owner, FILE* file) {
    if (!owner || !file) return;

    fwrite(&owner->id, sizeof(owner->id), 1, file);

    size_t nameLength = strlen(owner->name) + 1; // Use size_t instead of int
    fwrite(&nameLength, sizeof(nameLength), 1, file);
    fwrite(owner->name, sizeof(char), nameLength, file);

    saveAddressToBinaryFile(&owner->address, file);

    fwrite(&owner->numPets, sizeof(owner->numPets), 1, file);

    for (int i = 0; i < owner->numPets; i++) {
        savePetToBinaryFile(owner->pets[i], file);
    }
}

PetOwner* loadPetOwnerFromBinaryFile(FILE* file) {
    if (!file) return NULL;

    PetOwner* owner = (PetOwner*)malloc(sizeof(PetOwner));
    CHECK_ALLOCATION(owner);

    fread(&owner->id, sizeof(owner->id), 1, file);

    size_t nameLength;
    fread(&nameLength, sizeof(nameLength), 1, file);

    owner->name = (char*)malloc(nameLength);
    if (owner->name) {
        fread(owner->name, sizeof(char), nameLength, file);
    }

    owner->address = loadAddressFromBinaryFile(file);

    fread(&owner->numPets, sizeof(owner->numPets), 1, file);

    owner->pets = (Pet**)malloc(owner->numPets * sizeof(Pet*));
    if (!owner->pets) {
        free(owner->name);
        free(owner);
        return NULL;
    }

    for (int i = 0; i < owner->numPets; i++) {
        owner->pets[i] = loadPetFromBinaryFile(file);
        if (!owner->pets[i]) {
            for (int j = 0; j < i; j++) {
                freePet(owner->pets[j]);
            }
            free(owner->pets);
            free(owner->name);
            free(owner);
            return NULL;
        }
    }

    return owner;
}