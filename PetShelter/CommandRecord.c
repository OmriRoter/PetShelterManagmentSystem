#define _CRT_SECURE_NO_WARNINGS

#include "CommandRecord.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void saveCommandRecordToBinaryFile(const CommandRecord* record, FILE* file) {
    if (record != NULL && file != NULL) {
        size_t nameLength = strlen(record->commandName);
        if (nameLength > UINT8_MAX) {
            fprintf(stderr, "Command name length exceeds the maximum value that can be stored in uint8_t.\n");
            return;
        }
        uint8_t compressedNameLength = (uint8_t)nameLength;
        fwrite(&compressedNameLength, sizeof(compressedNameLength), 1, file);
        fwrite(record->commandName, sizeof(char), nameLength, file);
        fwrite(&record->learnedDate, sizeof(record->learnedDate), 1, file);
        uint16_t compressedYear = record->learnedYear - BASE_YEAR;
        fwrite(&compressedYear, sizeof(compressedYear), 1, file);
        fwrite(&record->proficiencyLevel, sizeof(record->proficiencyLevel), 1, file);
    }
}

CommandRecord* loadCommandRecordFromBinaryFile(FILE* file) {
    if (file == NULL) return NULL;

    CommandRecord* record = (CommandRecord*)malloc(sizeof(CommandRecord));
    CHECK_ALLOCATION(record);

    uint8_t nameLength;
    fread(&nameLength, sizeof(nameLength), 1, file);
    record->commandName = (char*)malloc(nameLength + 1);
    if (record->commandName != NULL) {
        fread(record->commandName, sizeof(char), nameLength, file);
        record->commandName[nameLength] = '\0';
    }
    else {
        free(record);
        return NULL;
    }
    fread(&record->learnedDate, sizeof(record->learnedDate), 1, file);
    uint16_t compressedYear;
    fread(&compressedYear, sizeof(compressedYear), 1, file);
    record->learnedYear = compressedYear + BASE_YEAR;
    fread(&record->proficiencyLevel, sizeof(record->proficiencyLevel), 1, file);

    return record;
}

void displayCommandRecord(const CommandRecord* record) {
    if (!record) {
        printf("No Command Record to display.\n");
        return;
    }

    UPPER_PRINT_DIVIDER();
    printf("Command: %s\n", record->commandName);
    uint8_t day = record->learnedDate & DAY_MASK;  // First 5 bits for day
    uint8_t month = (record->learnedDate >> MONTH_SHIFT) & MONTH_MASK;  // Next 3 bits for month
    printf("Learned Date: %02d-%02d-%d\n", day, month, record->learnedYear);
    printf("Proficiency Level: %d\n", record->proficiencyLevel);
    LOWER_PRINT_DIVIDER();
}

CommandRecord* createCommandRecord(const char* commandName, uint8_t day, uint8_t month, uint16_t learnedYear, uint8_t proficiencyLevel) {
    CommandRecord* newCommand = (CommandRecord*)malloc(sizeof(CommandRecord));
    if (newCommand) {
        newCommand->commandName = _strdup(commandName);
        newCommand->learnedDate = (day & DAY_MASK) | ((month & MONTH_MASK) << MONTH_SHIFT);
        newCommand->learnedYear = learnedYear;
        newCommand->proficiencyLevel = proficiencyLevel;
    }
    else {
        printf("Failed to allocate memory for a new command record.\n");
    }
    return newCommand;
}

CommandRecord* createCommandRecordFromInput() {
    CommandRecord* newCommand = (CommandRecord*)malloc(sizeof(CommandRecord));
    CHECK_ALLOCATION(newCommand); // Check if the memory allocation was successful

    UPPER_PRINT_DIVIDER();
    char buffer[INPUT_BUFFER_SIZE];
    printf("Enter the command name: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';  // Remove trailing newline character
    newCommand->commandName = _strdup(buffer);

    printf("Enter the learned date:\n");
    Date learnedDate = createDateFromInput();
    newCommand->learnedDate = (learnedDate.day & DAY_MASK) | ((learnedDate.month & MONTH_MASK) << MONTH_SHIFT);
    newCommand->learnedYear = learnedDate.year;

    printf("Enter the proficiency level (0-7): ");
    fgets(buffer, sizeof(buffer), stdin);
    int proficiencyLevel;
    if (sscanf(buffer, "%d", &proficiencyLevel) != 1 || proficiencyLevel < 0 || proficiencyLevel > MAX_PROFICIENCY_LEVEL) {
        printf("Invalid proficiency level. Setting it to 0.\n");
        proficiencyLevel = 0;
    }
    newCommand->proficiencyLevel = (uint8_t)proficiencyLevel;
    LOWER_PRINT_DIVIDER();

    return newCommand;
}

void freeCommandRecord(CommandRecord* record) {
    if (record == NULL) {
        return; // Early return if the record pointer is null
    }

    // Free the command name if it is dynamically allocated
    if (record->commandName != NULL) {
        free(record->commandName);
        record->commandName = NULL; // Prevent dangling pointer by resetting to NULL
    }
    // Free the CommandRecord structure itself
    free(record);
    record = NULL; // Prevent dangling pointer by resetting to NULL
}

void saveCommandRecordToTextFile(const CommandRecord* record, FILE* file) {
    if (record != NULL && file != NULL) {
        fprintf(file, "%s,%d,%d,%d\n", record->commandName, record->learnedDate, record->learnedYear, record->proficiencyLevel);
    }
}

CommandRecord* loadCommandRecordFromTextFile(FILE* file) {
    CommandRecord* record = (CommandRecord*)malloc(sizeof(CommandRecord));
    CHECK_ALLOCATION(record);

    char buffer[INPUT_BUFFER_SIZE];
    if (fgets(buffer, sizeof(buffer), file) != NULL) {
        char* token = strtok(buffer, ",");
        if (token != NULL) {
            record->commandName = _strdup(token);  // Use _strdup instead of strdup
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            record->learnedDate = (uint8_t)atoi(token);
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            record->learnedYear = (uint16_t)atoi(token);
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            record->proficiencyLevel = (uint8_t)atoi(token);
        }
    }

    return record;
}

