#define _CRT_SECURE_NO_WARNINGS

#include "Address.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Address createAddress(const char* street, const char* city, const char* state, const char* zipCode) {
    Address newAddress = { 0 }; // Initialize the newAddress to zero

    strncpy(newAddress.street, street, MAX_STREET_LENGTH - 1);
    strncpy(newAddress.city, city, MAX_CITY_LENGTH - 1);
    strncpy(newAddress.state, state, MAX_STATE_LENGTH - 1);
    strncpy(newAddress.zipCode, zipCode, MAX_ZIP_CODE_LENGTH - 1);

    return newAddress;
}


void displayAddress(const Address* address) {
    if (address != NULL) {
        UPPER_PRINT_DIVIDER(); // Add a divider for better readability
        printf("Address Details:\n");
        UPPER_PRINT_DIVIDER(); // Add another divider
        printf("Street: %s\nCity: %s\nState: %s\nZip Code: %s\n",
            address->street, address->city, address->state, address->zipCode);
        LOWER_PRINT_DIVIDER(); // Add a divider for better readability
    }
    else {
        UPPER_PRINT_DIVIDER(); // Add a divider for better readability
        printf("Error: No address to display. The address pointer is null.\n");
        LOWER_PRINT_DIVIDER(); // Add another divider
    }
}

Address createAddressFromInput(void) {
    char street[MAX_STREET_LENGTH], city[MAX_CITY_LENGTH], state[MAX_STATE_LENGTH], zipCode[MAX_ZIP_CODE_LENGTH];  // Ensure buffers are appropriately sized

    UPPER_PRINT_DIVIDER(); // Add a divider for better readability
    printf("Enter Address Details:\n");
    UPPER_PRINT_DIVIDER(); // Add another divider

    // Input for street with validation for alphabetic characters and spaces
    printf("Street and house number:\n");
    inputStringWithValidation(street, sizeof(street), isStringAlphaNumericSpace);

    // Input for city with validation for alphabetic characters and spaces
    printf("City (Letters Only):\n");
    inputStringWithValidation(city, sizeof(city), isStringAlpha);

    // Input for state with validation for alphabetic characters and spaces
    printf("State (Letters Only):\n");
    inputStringWithValidation(state, sizeof(state), isStringAlpha);

    // Input for zip code with validation for numeric characters
    printf("Zip Code (max 9 characters):\n");
    inputStringWithValidation(zipCode, sizeof(zipCode), isStringNumeric);

    LOWER_PRINT_DIVIDER(); // Add a divider for better readability

    return createAddress(street, city, state, zipCode); 
}

void saveAddressToTextFile(const Address* address, FILE* file) {
    if (address != NULL && file != NULL) {
        fprintf(file, "%s,%s,%s,%s\n", address->street, address->city, address->state, address->zipCode);
    }
}

Address loadAddressFromTextFile(FILE* file) {
    Address address = { 0 }; // Initialize address with an empty Address struct

    char line[INPUT_BUFFER_SIZE];
    if (file != NULL && fgets(line, sizeof(line), file) != NULL) {
        char* token = strtok(line, ",");
        if (token != NULL) {
            strncpy(address.street, token, sizeof(address.street));
            address.street[sizeof(address.street) - 1] = '\0';
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            strncpy(address.city, token, sizeof(address.city));
            address.city[sizeof(address.city) - 1] = '\0';
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            strncpy(address.state, token, sizeof(address.state));
            address.state[sizeof(address.state) - 1] = '\0';
        }

        token = strtok(NULL, ",\n");
        if (token != NULL) {
            strncpy(address.zipCode, token, sizeof(address.zipCode));
            address.zipCode[sizeof(address.zipCode) - 1] = '\0';
        }
    }

    return address;
}

void saveAddressToBinaryFile(const Address* address, FILE* file) {
    if (address != NULL && file != NULL) {
        fwrite(address, sizeof(Address), 1, file);
    }
}

Address loadAddressFromBinaryFile(FILE* file) {
    Address address;
    if (file != NULL && fread(&address, sizeof(Address), 1, file) == 1) {
        return address;
    }
    return (Address) { 0 }; // Return an empty address if read fails
}