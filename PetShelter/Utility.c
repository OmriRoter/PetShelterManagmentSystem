#define _CRT_SECURE_NO_WARNINGS
#include "Utility.h"
#include <ctype.h>
#include <string.h>


size_t countIf(void** array, size_t count, int (*predicate)(void*)) {
    size_t elementsMeetingCondition = 0;
    for (size_t i = 0; i < count; ++i) {
        if (predicate(array[i])) {
            elementsMeetingCondition++;
        }
    }
    return elementsMeetingCondition;
}

int isStringAlpha(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i]) && str[i] != ' ') { // Allow spaces
            return 0; // Found a non-alphabetic character
        }
    }
    return 1; // String is all alphabetic characters
}

int isStringNumeric(const char* str) {
    if (str == NULL) {
        return 0;  // Equivalent to false
    }

    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;  // Equivalent to false
        }
    }

    return 1;  // Equivalent to true
}

int isStringAlphaNumericSpace(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalnum(str[i]) && str[i] != ' ') {
            return 0; // Found a character that is neither alphanumeric nor a space
        }
    }
    return 1; // String is valid, containing only alphanumeric characters and spaces
}

void inputStringWithValidation(char* buffer, size_t bufferSize, int (*validateFunc)(const char*)) {
    char input[INPUT_BUFFER_SIZE];
    int valid = 0;

    while (!valid) {
        printf("Enter input: ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            clearInputBuffer();
            printf("Error reading input. Please try again.\n");
            continue;
        }

        // Remove newline character
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }
        else {
            clearInputBuffer();
        }

        // Validate input
        if (validateFunc(input)) {
            valid = 1;
        }
        else {
            printf("Invalid input. Please try again.\n");
        }
    }

    // Capitalize first letter
    capitalizeFirstLetter(input);

    // Copy validated input to buffer
    strncpy(buffer, input, bufferSize - 1);
    buffer[bufferSize - 1] = '\0';
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}


void capitalizeFirstLetter(char* str) {
    if (str != NULL && islower(str[0])) {
        str[0] = toupper(str[0]);  // Convert first character to uppercase if it's lowercase
    }
}

