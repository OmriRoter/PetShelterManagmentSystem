#define _CRT_SECURE_NO_WARNINGS
#include "Pet.h"
#include "TrainingTipsData.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Pet* createPet(int id, const char* name, const char* type, double age, const char* breed, Date addedDate) {
    Pet* newPet = (Pet*)malloc(sizeof(Pet));
    CHECK_ALLOCATION(newPet);  
    
    newPet->id = id;
    newPet->name = _strdup(name);
    strncpy(newPet->type, type, sizeof(newPet->type) - 1);
    newPet->age = age;
    strncpy(newPet->breed, breed, sizeof(newPet->breed) - 1);
    newPet->isAdopted = 0;
    newPet->addedDate = addedDate;
    newPet->commands = NULL;
    newPet->commandCount = 0;

    return newPet;
}

void setPetAdoptionStatus(Pet* pet, int adopted) {
    if (pet) {
        pet->isAdopted = adopted;
    }
}

void displayPetDetails(const Pet* pet) {
    UPPER_PRINT_DIVIDER();  // Use the macro to print a divider
    printf("Pet ID: %d, Name: %s, Type: %s, Age: %.1f\n", pet->id, pet->name, pet->type, pet->age);

    // Check if the pet's age is greater than or equal to MAX_PET_AGE
    if (pet->age >= MAX_PET_AGE) {
        printf("Note: This pet is %lf years old and may require extra attention!\n", pet->age);
    }

   LOWER_PRINT_DIVIDER();  // Use the macro again to print a divider
}

void freePet(Pet* pet) {
    if (pet == NULL) {
        return; // Early return if the pet pointer is null
    }

    // Free the dynamically allocated name string
    if (pet->name != NULL) {
        free(pet->name);
        pet->name = NULL; // Reset pointer to NULL after freeing
    }

    // Free each command record if commands are present
    if (pet->commands != NULL) {
        free(pet->commands);
        pet->commands = NULL; // Reset pointer to NULL after freeing
       pet->commandCount = 0; // Reset command count to zero
    }

    // Finally, free the pet structure itself
    free(pet);
    pet = NULL; // Reset the main structure pointer to NULL
}

// Comparison functions for qsort
int compareByName(const void* a, const void* b) {
    const Pet* petA = *(const Pet* const*)a;
    const Pet* petB = *(const Pet* const*)b;

    if (petA == NULL && petB == NULL) {
        return 0;
    }
    else if (petA == NULL) {
        return -1;
    }
    else if (petB == NULL) {
        return 1;
    }

    return strcmp(petA->name, petB->name);
}

int compareByType(const void* a, const void* b) {
    // Initialize petA and petB pointers to NULL
    Pet* petA = NULL;
    Pet* petB = NULL;

    // Safely assign values to petA and petB if a and b are not NULL
    if (a != NULL) {
        petA = *(Pet**)a;
    }
    if (b != NULL) {
        petB = *(Pet**)b;
    }

    // Handle cases where petA or petB are NULL
    if (petA == NULL && petB == NULL) {
        return 0; // Both are NULL, considered equal
    }
    else if (petA == NULL) {
        return -1; // Only petA is NULL, petB is considered greater
    }
    else if (petB == NULL) {
        return 1; // Only petB is NULL, petA is considered greater
    }

    // If neither petA nor petB is NULL, compare their types
    return strcmp(petA->type, petB->type);
}

int compareByAge(const void* a, const void* b) {
    const Pet* petA = *(const Pet**)a;
    const Pet* petB = *(const Pet**)b;
    if (petA->age < petB->age) return -1;
    if (petA->age > petB->age) return 1;
    return 0;
}

// Sorting functions
void sortPetsByName(LinkedList* petList) {
    if (petList == NULL || petList->size <= 1) {
        return;
    }

    Pet** petArray = (Pet**)malloc(petList->size * sizeof(Pet*));
    CHECK_ALLOCATION(petArray);


    Node* current = petList->head;
    for (size_t i = 0; i < petList->size; i++) {
        petArray[i] = (Pet*)current->data;
        current = current->next;
    }

    qsort(petArray, petList->size, sizeof(Pet*), compareByName);

    current = petList->head;
    for (size_t i = 0; i < petList->size; i++) {
        current->data = petArray[i];
        current = current->next;
    }

    free(petArray);
}

void sortPetsByType(LinkedList* petList) {
    if (petList == NULL || petList->size <= 1) {
        return;
    }

    Pet** petArray = (Pet**)malloc(petList->size * sizeof(Pet*));
    CHECK_ALLOCATION(petArray);


    Node* current = petList->head;
    for (size_t i = 0; i < petList->size; i++) {
        petArray[i] = (Pet*)current->data;
        current = current->next;
    }

    qsort(petArray, petList->size, sizeof(Pet*), compareByType);

    current = petList->head;
    for (size_t i = 0; i < petList->size; i++) {
        current->data = petArray[i];
        current = current->next;
    }

    free(petArray);
}

void sortPetsByAge(LinkedList* petList) {
    if (petList == NULL || petList->size <= 1) {
        return;
    }

    Pet** petArray = (Pet**)malloc(petList->size * sizeof(Pet*));
    CHECK_ALLOCATION(petArray);

    Node* current = petList->head;
    for (size_t i = 0; i < petList->size; i++) {
        petArray[i] = (Pet*)current->data;
        current = current->next;
    }

    qsort(petArray, petList->size, sizeof(Pet*), compareByAge);

    current = petList->head;
    for (size_t i = 0; i < petList->size; i++) {
        current->data = petArray[i];
        current = current->next;
    }

    free(petArray);
}

// Binary search for pet by name
Pet* searchPetByName(LinkedList* petList, const char* name) {
    if (petList == NULL || name == NULL) {
        return NULL;
    }

    Pet** petArray = (Pet**)malloc(petList->size * sizeof(Pet*));
    CHECK_ALLOCATION(petArray);

    Node* current = petList->head;
    for (size_t i = 0; i < petList->size; i++) {
        petArray[i] = (Pet*)current->data;
        current = current->next;
    }

    qsort(petArray, petList->size, sizeof(Pet*), compareByName);

    Pet key = { .name = (char*)name };
    Pet* keyPtr = &key;
    Pet** result = (Pet**)bsearch(&keyPtr, petArray, petList->size, sizeof(Pet*), compareByName);

    Pet* foundPet = result != NULL ? *result : NULL;

    free(petArray);

    return foundPet;
}// Binary search for pet by type
// Binary search for pet by type
Pet* searchPetByType(LinkedList* petList, const char* type) {
    if (petList == NULL || type == NULL || petList->size == 0) {
        return NULL; // Early return for null or empty list
    }

    Pet** petArray = (Pet**)malloc(petList->size * sizeof(Pet*));
    CHECK_ALLOCATION(petArray);

    Node* current = petList->head;
    for (size_t i = 0; current != NULL && i < petList->size; i++, current = current->next) {
        petArray[i] = (Pet*)current->data; // Populate the array
    }

    qsort(petArray, petList->size, sizeof(Pet*), compareByType);

    Pet key = { 0 }; // Initialize the key Pet structure
    strncpy(key.type, type, sizeof(key.type) - 1); // Safely copy the type
    key.type[sizeof(key.type) - 1] = '\0'; // Ensure null-termination

    Pet* keyPtr = &key;
    Pet** result = (Pet**)bsearch(&keyPtr, petArray, petList->size, sizeof(Pet*), compareByType);

    Pet* foundPet = result != NULL ? *result : NULL;

    free(petArray); // Don't forget to free the allocated memory

    return foundPet;
}
// Binary search for pet by age
Pet* searchPetByAge(LinkedList* petList, double age) {
    if (petList == NULL) {
        return NULL;
    }

    Pet** petArray = (Pet**)malloc(petList->size * sizeof(Pet*));
    CHECK_ALLOCATION(petArray);

    Node* current = petList->head;
    for (size_t i = 0; i < petList->size; i++) {
        petArray[i] = (Pet*)current->data;
        current = current->next;
    }

    qsort(petArray, petList->size, sizeof(Pet*), compareByAge);

    Pet key = { .age = age };
    Pet* keyPtr = &key;
    Pet** result = (Pet**)bsearch(&keyPtr, petArray, petList->size, sizeof(Pet*), compareByAge);

    Pet* foundPet = result != NULL ? *result : NULL;

    free(petArray);

    return foundPet;
}

void savePetToTextFile(const Pet* pet, FILE* file) {
    if (!pet || !file) {
        return;
    }

    fprintf(file, "%d,%s,%s,%lf,%s,%d,", pet->id, pet->name, pet->type, pet->age, pet->breed, pet->isAdopted);
    saveDateToTextFile(&pet->addedDate, file);
    fprintf(file, ",%d\n", pet->commandCount);

    for (int i = 0; i < pet->commandCount; i++) {
        saveCommandRecordToTextFile(&pet->commands[i], file);
    }
}

Pet* loadPetFromTextFile(FILE* file) {
    if (!file) return NULL;

    Pet* pet = (Pet*)malloc(sizeof(Pet));
    CHECK_ALLOCATION(pet);

    char nameBuffer[NAME_SIZE];

    int result = fscanf(file, "%d,%[^,],%[^,],%lf,%[^,],%d,", &pet->id, nameBuffer, pet->type, &pet->age, pet->breed, &pet->isAdopted);
    if (result != 6) {
        free(pet);
        return NULL;
    }

    // Ensure null-termination of nameBuffer
    nameBuffer[NAME_SIZE - 1] = '\0';

    pet->name = (char*)malloc((strlen(nameBuffer) + 1) * sizeof(char));
    if (!pet->name) {
        free(pet);
        return NULL;
    }

    strcpy(pet->name, nameBuffer);

    pet->addedDate = loadDateFromTextFile(file);

    // Check if commandCount can be read successfully
    int scanResult = fscanf(file, "\n,%d\n", &pet->commandCount);
    if (scanResult == EOF) {
        // Reached end of file, assume commandCount is 0
        pet->commandCount = 0;
        pet->commands = NULL;
    }
    else if (scanResult != 1) {
        // Error reading commandCount
        free(pet->name);
        free(pet);
        return NULL;
    }
    else {
        // Allocate memory for commands
        pet->commands = (CommandRecord*)malloc(pet->commandCount * sizeof(CommandRecord));
        if (!pet->commands) {
            freePet(pet);
            return NULL;
        }

        for (int i = 0; i < pet->commandCount; i++) {
            CommandRecord* command = loadCommandRecordFromTextFile(file);
            if (!command) {
                freePet(pet);
                return NULL;
            }
            pet->commands[i] = *command;
            free(command);
        }
    }

    return pet;
}

void savePetToBinaryFile(const Pet* pet, FILE* file) {
    if (!pet || !file) return;

    fwrite(&pet->id, sizeof(pet->id), 1, file);

    int nameLength = (int)(strlen(pet->name) + 1);
    fwrite(&nameLength, sizeof(nameLength), 1, file);
    fwrite(pet->name, sizeof(char), nameLength, file);

    int typeLength = (int)(strlen(pet->type) + 1);
    fwrite(&typeLength, sizeof(typeLength), 1, file);
    fwrite(pet->type, sizeof(char), typeLength, file);

    fwrite(&pet->age, sizeof(pet->age), 1, file);

    int breedLength = (int)(strlen(pet->breed) + 1);
    fwrite(&breedLength, sizeof(breedLength), 1, file);
    fwrite(pet->breed, sizeof(char), breedLength, file);

    fwrite(&pet->isAdopted, sizeof(pet->isAdopted), 1, file);

    saveDateToBinaryFile(&pet->addedDate, file);

    fwrite(&pet->commandCount, sizeof(pet->commandCount), 1, file);

    for (int i = 0; i < pet->commandCount; i++) {
        saveCommandRecordToBinaryFile(&pet->commands[i], file);
    }
}

Pet* loadPetFromBinaryFile(FILE* file) {
    if (!file) return NULL;

    Pet* pet = (Pet*)malloc(sizeof(Pet));
    if (!pet) return NULL;
    pet->commands = NULL;

    fread(&pet->id, sizeof(pet->id), 1, file);

    int nameLength;
    fread(&nameLength, sizeof(nameLength), 1, file);
    pet->name = (char*)malloc(nameLength);
    if (pet->name) {
        fread(pet->name, sizeof(char), nameLength, file);
    }

    int typeLength;
    fread(&typeLength, sizeof(typeLength), 1, file);
    char* typeBuffer = (char*)malloc(typeLength);
    if (typeBuffer) {
        fread(typeBuffer, sizeof(char), typeLength, file);
        strncpy(pet->type, typeBuffer, TYPE_SIZE - 1);
        pet->type[TYPE_SIZE - 1] = '\0'; // Ensure null-termination
        free(typeBuffer); // Free the temporary buffer
    }

    fread(&pet->age, sizeof(pet->age), 1, file);

    int breedLength;
    fread(&breedLength, sizeof(breedLength), 1, file);
    char* breedBuffer = (char*)malloc(breedLength);
    if (breedBuffer) {
        fread(breedBuffer, sizeof(char), breedLength, file);
        strncpy(pet->breed, breedBuffer, BREED_SIZE - 1);
        pet->breed[BREED_SIZE - 1] = '\0'; // Ensure null-termination
        free(breedBuffer); // Free the temporary buffer
    }

    fread(&pet->isAdopted, sizeof(pet->isAdopted), 1, file);

    pet->addedDate = loadDateFromBinaryFile(file);

    fread(&pet->commandCount, sizeof(pet->commandCount), 1, file);

    if (pet->commandCount > 0) {
        pet->commands = (CommandRecord*)malloc(pet->commandCount * sizeof(CommandRecord));
        if (pet->commands) {
            for (int i = 0; i < pet->commandCount; i++) {
                CommandRecord* command = loadCommandRecordFromBinaryFile(file);
                if (!command) {
                    freePet(pet);
                    return NULL;
                }
                pet->commands[i] = *command;
                free(command);
            }
        }
    }

    return pet;
}

Pet* createPetFromInput(void) {
    int id;
    double age;

    char name[NAME_SIZE], type[TYPE_SIZE], breed[BREED_SIZE];
    char inputBuffer[INPUT_BUFFER_SIZE]; 

    // ID input with validation for numbers only
    do {
        printf("Enter Pet ID (numbers only): ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
    } while (sscanf(inputBuffer, "%d", &id) != 1);

    // Name input with validation for letters only
    do {
        printf("Enter Pet Name (letters only): ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;  // Remove newline character
        capitalizeFirstLetter(name);  // Ensure the first letter is capitalized
    } while (!isStringAlpha(name));

    // Type input with validation for letters only
    do {
        printf("Enter Pet Type (letters only): ");
        fgets(type, sizeof(type), stdin);
        type[strcspn(type, "\n")] = 0; // Remove newline character
        capitalizeFirstLetter(type);  // Ensure the first letter is capitalized
    } while (!isStringAlpha(type));

    // Age input with validation for numbers only
    do {
        printf("Enter Pet Age (numbers only): ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
    } while (sscanf(inputBuffer, "%lf", &age) != 1);

    // Breed input with validation for letters only
    do {
        printf("Enter Pet Breed (letters only): ");
        fgets(breed, sizeof(breed), stdin);
        breed[strcspn(breed, "\n")] = 0; // Remove newline character
        capitalizeFirstLetter(breed);  // Ensure the first letter is capitalized
    } while (!isStringAlpha(breed));

    printf("Enter Added Date:\n");
    Date addedDate = createDateFromInput();

    return createPet(id, name, type, age, breed, addedDate);
}

void addCommandToPet(Pet* pet, CommandRecord* command) {
    if (pet && command) {
        pet->commandCount++;
        CommandRecord* newCommands = (CommandRecord*)realloc(pet->commands, pet->commandCount * sizeof(CommandRecord));
        if (newCommands) {
            pet->commands = newCommands;
            pet->commands[pet->commandCount - 1] = *command;
            printf("Command added successfully to the pet.\n");
        }
        else {
            printf("Failed to allocate memory for the command.\n");
            pet->commandCount--;
        }
    }
    else {
        printf("Invalid pet or command.\n");
    }
}

void removeCommandFromPet(Pet* pet, int commandIndex) {
    if (commandIndex >= 0 && commandIndex < pet->commandCount) {
        for (int i = commandIndex; i < pet->commandCount - 1; i++) {
            pet->commands[i] = pet->commands[i + 1];
        }
        pet->commandCount--;
        CommandRecord* newCommands = (CommandRecord*)realloc(pet->commands, pet->commandCount * sizeof(CommandRecord));
        if (newCommands || pet->commandCount == 0) {
            pet->commands = newCommands;
        }
        else {
            printf("Failed to reallocate memory for commands.\n");
        }
    }
}

void displayPetCommands(const Pet* pet) {
    if (pet) {
        printf("Commands for Pet: %s\n", pet->name);
        if (pet->commandCount > 0) {
            for (int i = 0; i < pet->commandCount; i++) {
                printf("Command %d:\n", i + 1);
                displayCommandRecord(&(pet->commands[i]));
                printf("\n");
            }
        }
        else {
            printf("No commands found for this pet.\n");
        }
    }
    else {
        printf("Invalid pet pointer.\n");
    }
}

void displayPetTrainingTips(const Pet* pet) {
    if (!pet) {
        printf("Invalid pet pointer.\n");
        return;
    }

    const TrainingTip* tipsArray;
    size_t tipsCount;

    if (strcmp(pet->type, "Dog") == 0) {
        tipsArray = dogTrainingTips;
        tipsCount = sizeof(dogTrainingTips) / sizeof(dogTrainingTips[0]);
    }
    else if (strcmp(pet->type, "Cat") == 0) {
        tipsArray = catTrainingTips;
        tipsCount = sizeof(catTrainingTips) / sizeof(catTrainingTips[0]);
    }
    else {
        UPPER_PRINT_DIVIDER();
        printf("| Training tips for '%s' are not available.                 |\n", pet->type);
        printf("| General Training Tip:                                      |\n");
        printf("| Ensure regular exercise, a balanced diet, and plenty of    |\n");
        printf("| love and attention for your pet.                           |\n");
        LOWER_PRINT_DIVIDER();
        return;
    }

    const char* ageCategory = pet->age <= 1 ? "Puppy" : (pet->age <= 3 ? "Young" : "Adult");

    const TrainingTip* bestMatch = NULL;
    int maxMatchScore = 0;

    for (size_t i = 0; i < tipsCount; ++i) {
        int matchScore = 0;

        if (strcmp(tipsArray[i].breed, pet->breed) == 0) {
            matchScore += 2;
        }

        if (strcmp(tipsArray[i].ageCategory, ageCategory) == 0) {
            matchScore += 1;
        }

        if (matchScore > maxMatchScore) {
            maxMatchScore = matchScore;
            bestMatch = &tipsArray[i];
        }
    }

    UPPER_PRINT_DIVIDER();
    if (bestMatch) {
        printf("| Training Tips for %s (%s, %s)                       |\n", pet->name, bestMatch->breed, bestMatch->ageCategory);
        LOWER_PRINT_DIVIDER();
        printf("| %s|\n", bestMatch->tips);
    }
    else {
        printf("| No specific training tips available for %s (%s).     |\n", pet->name, pet->breed);
        printf("| General Training Tip:                                      |\n");
        printf("| Ensure regular exercise, a balanced diet, and plenty of    |\n");
        printf("| love and attention for your pet.                           |\n");
    }
    LOWER_PRINT_DIVIDER();
}
