// Volunteer.c
#define _CRT_SECURE_NO_WARNINGS
#include "Volunteer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Volunteer* createVolunteer(int volunteerId, const char* name, const char* role, int hoursPerMonth) {
    Volunteer* newVolunteer = (Volunteer*)malloc(sizeof(Volunteer));
    CHECK_ALLOCATION(newVolunteer);  // Use the macro for memory allocation check

    newVolunteer->volunteerId = volunteerId;
    newVolunteer->name = _strdup(name);
    newVolunteer->role = _strdup(role);
    newVolunteer->hoursPerMonth = hoursPerMonth;

    return newVolunteer;
}

void displayVolunteerInfo(const Volunteer* volunteer) {
    if (!volunteer) {
        UPPER_PRINT_DIVIDER();
        printf("No volunteer data available.\n");
        LOWER_PRINT_DIVIDER();
        return;
    }

    UPPER_PRINT_DIVIDER();
    printf("Volunteer Information:\n");
    UPPER_PRINT_DIVIDER();
    printf("Volunteer ID: %d\n", volunteer->volunteerId);
    printf("Name: %s\n", volunteer->name);
    printf("Role: %s\n", volunteer->role);
    printf("Hours per Month: %d\n", volunteer->hoursPerMonth);
    LOWER_PRINT_DIVIDER();
}

void freeVolunteer(Volunteer* volunteer) {
    if (volunteer) {
        if (volunteer->name) {
            free(volunteer->name);
        }
        if (volunteer->role) {
            free(volunteer->role);
        }
        free(volunteer);
    }
}

Volunteer* createVolunteerFromInput(void) {
    int volunteerId, hoursPerMonth;
    char name[NAME_SIZE], role[ROLE_SIZE], inputBuffer[INPUT_BUFFER_SIZE];

    UPPER_PRINT_DIVIDER();
    printf("Volunteer Registration\n");
    UPPER_PRINT_DIVIDER();

    // Volunteer ID input with validation for numbers only
    while (1) {
        printf("Enter Volunteer ID (numbers only): ");
        if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL || sscanf(inputBuffer, "%d", &volunteerId) != 1) {
            printf("Invalid input. Please enter numbers only.\n");
            continue;
        }
        break;
    }

    UPPER_PRINT_DIVIDER();
    printf("Enter Volunteer Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; // Remove trailing newline
    if (strlen(name) == 0) {
        printf("Name cannot be empty. Please enter a valid name.\n");
        return NULL;
    }

    UPPER_PRINT_DIVIDER();
    printf("Enter Volunteer Role: ");
    fgets(role, sizeof(role), stdin);
    role[strcspn(role, "\n")] = 0; // Remove trailing newline
    if (strlen(role) == 0) {
        printf("Role cannot be empty. Please enter a valid role.\n");
        return NULL;
    }

    UPPER_PRINT_DIVIDER();
    // Hours per month input with validation for numbers only
    while (1) {
        printf("Enter Hours Per Month (numbers only): ");
        if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL || sscanf(inputBuffer, "%d", &hoursPerMonth) != 1) {
            printf("Invalid input. Please enter numbers only.\n");
            continue;
        }
        break;
    }

    UPPER_PRINT_DIVIDER();
    printf("Thank you for entering the information.\n");
    LOWER_PRINT_DIVIDER();

    return createVolunteer(volunteerId, name, role, hoursPerMonth);
}

void saveVolunteerToTextFile(const Volunteer* volunteer, FILE* file) {
    if (!volunteer || !file) return;

    fprintf(file, "%d,%s,%s,%d\n", volunteer->volunteerId, volunteer->name, volunteer->role, volunteer->hoursPerMonth);
}

Volunteer* loadVolunteerFromTextFile(FILE* file) {
    if (!file) return NULL;

    Volunteer* volunteer = (Volunteer*)malloc(sizeof(Volunteer));
    CHECK_ALLOCATION(volunteer);

    char nameBuffer[NAME_SIZE] = { 0 };  // Initialize with zeros to ensure it's null-terminated
    char roleBuffer[ROLE_SIZE] = { 0 };  // Initialize with zeros to ensure it's null-terminated

    int readItems = fscanf(file, "%d,%99[^,],%99[^,],%d\n",
        &volunteer->volunteerId, nameBuffer, roleBuffer,
        &volunteer->hoursPerMonth);
    if (readItems != 4) { // Check if all items were read successfully
        free(volunteer);
        return NULL;
    }

    // Ensure strings are null-terminated
    nameBuffer[sizeof(nameBuffer) - 1] = '\0';
    roleBuffer[sizeof(roleBuffer) - 1] = '\0';

    volunteer->name = (char*)malloc((strlen(nameBuffer) + 1) * sizeof(char));
    CHECK_ALLOCATION(volunteer->name);  // Use the macro instead of manual check
    strcpy(volunteer->name, nameBuffer);

    volunteer->role = (char*)malloc((strlen(roleBuffer) + 1) * sizeof(char));
    CHECK_ALLOCATION(volunteer->role);  // Use the macro instead of manual check
    strcpy(volunteer->role, roleBuffer);

    return volunteer;
}

void saveVolunteerToBinaryFile(const Volunteer* volunteer, FILE* file) {
    if (volunteer != NULL && file != NULL) {
        fwrite(&volunteer->volunteerId, sizeof(int), 1, file);

        int nameLen = (int)(strlen(volunteer->name) + 1);
        fwrite(&nameLen, sizeof(int), 1, file);
        fwrite(volunteer->name, sizeof(char), nameLen, file);

        int roleLen = (int)(strlen(volunteer->role) + 1);
        fwrite(&roleLen, sizeof(int), 1, file);
        fwrite(volunteer->role, sizeof(char), roleLen, file);

        fwrite(&volunteer->hoursPerMonth, sizeof(int), 1, file);
    }
}

Volunteer* loadVolunteerFromBinaryFile(FILE* file) {
    if (file == NULL) return NULL;

    Volunteer* volunteer = (Volunteer*)malloc(sizeof(Volunteer));
    CHECK_ALLOCATION(volunteer);

    if (fread(&volunteer->volunteerId, sizeof(int), 1, file) != 1) {
        free(volunteer);
        return NULL;
    }

    int nameLen = 0;
    if (fread(&nameLen, sizeof(int), 1, file) != 1) {
        free(volunteer);
        return NULL;
    }

    volunteer->name = (char*)malloc(nameLen * sizeof(char));
    if (volunteer->name == NULL) {
        free(volunteer);
        return NULL;
    }

    if (fread(volunteer->name, sizeof(char), nameLen, file) != nameLen) {
        free(volunteer->name);
        free(volunteer);
        return NULL;
    }

    int roleLen = 0;
    if (fread(&roleLen, sizeof(int), 1, file) != 1) {
        free(volunteer->name);
        free(volunteer);
        return NULL;
    }

    volunteer->role = (char*)malloc(roleLen * sizeof(char));
    if (volunteer->role == NULL) {
        free(volunteer->name);
        free(volunteer);
        return NULL;
    }

    if (fread(volunteer->role, sizeof(char), roleLen, file) != roleLen) {
        free(volunteer->name);
        free(volunteer->role);
        free(volunteer);
        return NULL;
    }

    if (fread(&volunteer->hoursPerMonth, sizeof(int), 1, file) != 1) {
        free(volunteer->name);
        free(volunteer->role);
        free(volunteer);
        return NULL;
    }

    return volunteer;
}
