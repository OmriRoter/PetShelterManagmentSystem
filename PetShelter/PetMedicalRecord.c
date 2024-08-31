#include "PetMedicalRecord.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

PetMedicalRecord* createPetMedicalRecord(Pet* pet, const char* vaccinations, const char* conditions, Date* lastVisit) {
    PetMedicalRecord* newRecord = (PetMedicalRecord*)malloc(sizeof(PetMedicalRecord));
    CHECK_ALLOCATION(newRecord);  // Check allocation with macro

    newRecord->pet = pet;  // Assuming the pet is managed elsewhere
    newRecord->vaccinations = vaccinations ? _strdup(vaccinations) : NULL;
    newRecord->medicalConditions = conditions ? _strdup(conditions) : NULL;
    // Allocate memory for lastVisit and copy the values
    newRecord->lastVisit = (Date*)malloc(sizeof(Date));
    CHECK_ALLOCATION(newRecord->lastVisit); // Check allocation for lastVisit
    if (newRecord->lastVisit && lastVisit) {
        *(newRecord->lastVisit) = *lastVisit;
    }

    return newRecord;
}

void updatePetMedicalRecord(PetMedicalRecord* record, const char* vaccinations, const char* conditions, Date* lastVisit) {
    if (!record) return;

    UPPER_PRINT_DIVIDER();
    printf("Updating Pet Medical Record...\n");

    // Vaccinations update logic
    if (vaccinations && strlen(vaccinations) > 0) {
        if (record->vaccinations && strlen(record->vaccinations) > 0) {
            size_t newLength = strlen(record->vaccinations) + strlen(vaccinations) + 2;
            char* updatedVaccinations = (char*)malloc(newLength + 1);
            if (updatedVaccinations) {
                snprintf(updatedVaccinations, newLength + 1, "%s, %s", record->vaccinations, vaccinations);
                free(record->vaccinations);
                record->vaccinations = updatedVaccinations;
                printf("Vaccinations updated.\n");
            }
        }
        else {
            record->vaccinations = _strdup(vaccinations);
            printf("Vaccinations set.\n");
        }
    }

    // Medical Conditions update logic
    if (conditions && strlen(conditions) > 0) {
        if (record->medicalConditions) {
            free(record->medicalConditions);
        }
        record->medicalConditions = _strdup(conditions);
        printf("Medical conditions updated.\n");
    }

    // Last Visit update logic
    if (lastVisit) {
        if (record->lastVisit) {
            *(record->lastVisit) = *lastVisit;
        }
        else {
            record->lastVisit = (Date*)malloc(sizeof(Date));
            if (record->lastVisit) {
                *(record->lastVisit) = *lastVisit;
                printf("Last visit date set.\n");
            }
        }
    }

    LOWER_PRINT_DIVIDER();
}

void displayPetMedicalRecordDetails(const PetMedicalRecord* record) {
    UPPER_PRINT_DIVIDER();
    if (!record) {
        printf("No Pet Medical Record to display.\n");
        LOWER_PRINT_DIVIDER();
        return;
    }

    printf("Pet Medical Record Details:\n");
    UPPER_PRINT_DIVIDER();
    if (record->pet) {
        printf("Pet Details:\n");
        displayPetDetails(record->pet); // Assuming a function to display Pet details
    }
    else {
        printf("Pet Details: N/A\n");
    }

    printf("Vaccinations: %s\n", record->vaccinations ? record->vaccinations : "N/A");
    printf("Medical Conditions: %s\n", record->medicalConditions ? record->medicalConditions : "N/A");

    if (record->lastVisit) {
        printf("Last Visit Date: ");
        displayDate(record->lastVisit); // Assuming a function to display Date
    }
    else {
        printf("Last Visit Date: N/A\n");
    }
    LOWER_PRINT_DIVIDER();
    
}

void freePetMedicalRecord(PetMedicalRecord* record) {
    if (record) {
        free(record->vaccinations);
        free(record->medicalConditions);
        free(record->lastVisit); // Free the allocated Date structure
        free(record);
    }
}

PetMedicalRecord* createPetMedicalRecordFromInput(Pet* pet) {
    char vaccinations[VACCINATIONS_SIZE], conditions[CONDITIONS_SIZE];
    Date lastVisit;

    UPPER_PRINT_DIVIDER();
    printf("Enter Pet Vaccinations (letters and spaces only): ");
    inputStringWithValidation(vaccinations, sizeof(vaccinations), isStringAlpha);

    UPPER_PRINT_DIVIDER();
    printf("Enter Pet Medical Conditions (letters and spaces only): ");
    inputStringWithValidation(conditions, sizeof(conditions), isStringAlpha);

    UPPER_PRINT_DIVIDER();
    printf("Enter Last Visit Date:\n");
    lastVisit = createDateFromInput();

    return createPetMedicalRecord(pet, vaccinations, conditions, &lastVisit);
}

void savePetMedicalRecordToTextFile(const PetMedicalRecord* record, FILE* file) {
    if (!record || !file) {
        return;
    }

    if (record->pet) {
        savePetToTextFile(record->pet, file);
    }
    else {
        fprintf(file, "0\n");
    }

    if (record->vaccinations) {
        fprintf(file, "%s\n", record->vaccinations);
    }
    else {
        fprintf(file, "\n");
    }

    if (record->medicalConditions) {
        fprintf(file, "%s\n", record->medicalConditions);
    }
    else {
        fprintf(file, "\n");
    }

    if (record->lastVisit) {
        saveDateToTextFile(record->lastVisit, file);
    }
    else {
        fprintf(file, "0,0,0\n");
    }
}

PetMedicalRecord* loadPetMedicalRecordFromTextFile(FILE* file) {
    if (!file) {
        return NULL;
    }

    PetMedicalRecord* record = (PetMedicalRecord*)malloc(sizeof(PetMedicalRecord));
    CHECK_ALLOCATION(record); // Check allocation for lastVisit


    record->pet = loadPetFromTextFile(file);

    char buffer[INPUT_BUFFER_SIZE];
    fgets(buffer, sizeof(buffer), file);
    record->vaccinations = strlen(buffer) > 1 ? _strdup(buffer) : NULL;

    fgets(buffer, sizeof(buffer), file);
    record->medicalConditions = strlen(buffer) > 1 ? _strdup(buffer) : NULL;

    record->lastVisit = (Date*)malloc(sizeof(Date));
    CHECK_ALLOCATION(record->lastVisit); // Check allocation for lastVisit
    if (record->lastVisit) {
        *(record->lastVisit) = loadDateFromTextFile(file);
    }

    return record;
}

void savePetMedicalRecordToBinaryFile(const PetMedicalRecord* record, FILE* file) {
    if (!record || !file) {
        return;
    }

    int hasPet = (record->pet != NULL);
    fwrite(&hasPet, sizeof(int), 1, file);

    if (record->pet) {
        savePetToBinaryFile(record->pet, file);
    }

    int vaccinationsLength = record->vaccinations ? (int)(strlen(record->vaccinations) + 1) : 0;
    fwrite(&vaccinationsLength, sizeof(int), 1, file);

    if (vaccinationsLength > 0) {
        fwrite(record->vaccinations, sizeof(char), vaccinationsLength, file);
    }

    int conditionsLength = record->medicalConditions ? (int)(strlen(record->medicalConditions) + 1) : 0;
    fwrite(&conditionsLength, sizeof(int), 1, file);

    if (conditionsLength > 0) {
        fwrite(record->medicalConditions, sizeof(char), conditionsLength, file);
    }

    int hasLastVisit = (record->lastVisit != NULL);
    fwrite(&hasLastVisit, sizeof(int), 1, file);

    if (record->lastVisit) {
        saveDateToBinaryFile(record->lastVisit, file);
    }
}

PetMedicalRecord* loadPetMedicalRecordFromBinaryFile(FILE* file) {
    if (!file) {
        return NULL;
    }

    PetMedicalRecord* record = (PetMedicalRecord*)malloc(sizeof(PetMedicalRecord));
    CHECK_ALLOCATION(record); // Check allocation for lastVisit


    int hasPet;
    fread(&hasPet, sizeof(int), 1, file);

    if (hasPet) {
        record->pet = loadPetFromBinaryFile(file);
    }
    else {
        record->pet = NULL;
    }

    int vaccinationsLength;
    fread(&vaccinationsLength, sizeof(int), 1, file);

    if (vaccinationsLength > 0) {
        record->vaccinations = (char*)malloc(vaccinationsLength * sizeof(char));
        if (!record->vaccinations) {
            free(record);
            return NULL;
        }
        fread(record->vaccinations, sizeof(char), vaccinationsLength, file);
    }
    else {
        record->vaccinations = NULL;
    }

    int conditionsLength;
    fread(&conditionsLength, sizeof(int), 1, file);

    if (conditionsLength > 0) {
        record->medicalConditions = (char*)malloc(conditionsLength * sizeof(char));
        if (!record->medicalConditions) {
            free(record->vaccinations);
            free(record);
            return NULL;
        }
        fread(record->medicalConditions, sizeof(char), conditionsLength, file);
    }
    else {
        record->medicalConditions = NULL;
    }

    int hasLastVisit;
    fread(&hasLastVisit, sizeof(int), 1, file);

    if (hasLastVisit) {
        record->lastVisit = (Date*)malloc(sizeof(Date));
        if (!record->lastVisit) {
            free(record->medicalConditions);
            free(record->vaccinations);
            free(record);
            return NULL;
        }
        *(record->lastVisit) = loadDateFromBinaryFile(file);
    }
    else {
        record->lastVisit = NULL;
    }

    return record;
}