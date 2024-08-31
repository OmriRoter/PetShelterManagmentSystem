#ifndef ADDRESS_H
#define ADDRESS_H

#include "Utility.h"

// Constants for address field sizes
#define MAX_STREET_LENGTH 50
#define MAX_CITY_LENGTH 30
#define MAX_STATE_LENGTH 30
#define MAX_ZIP_CODE_LENGTH 10


/**
 * @struct Address
 * @brief Represents an address.
 */
typedef struct {
    char street[MAX_STREET_LENGTH]; /**< Street name */
    char city[MAX_CITY_LENGTH];   /**< City name */
    char state[MAX_STATE_LENGTH];  /**< State name */
    char zipCode[MAX_ZIP_CODE_LENGTH]; /**< Zip code */
} Address;

/**
 * @brief Creates an Address object with the given details.
 * @param street The street name.
 * @param city The city name.
 * @param state The state name.
 * @param zipCode The zip code.
 * @return The created Address object.
 */
Address createAddress(const char* street, const char* city, const char* state, const char* zipCode);

/**
 * @brief Displays the details of an Address object.
 * @param address A pointer to the Address object.
 */
void displayAddress(const Address* address);

/**
 * @brief Saves an Address object to a text file.
 * @param address A pointer to the Address object.
 * @param file A pointer to the FILE stream.
 */
void saveAddressToTextFile(const Address* address, FILE* file);

/**
 * @brief Loads an Address object from a text file.
 * @param file A pointer to the FILE stream.
 * @return The loaded Address object.
 */
Address loadAddressFromTextFile(FILE* file);

/**
 * @brief Creates an Address object from user input.
 * @return The created Address object.
 */
Address createAddressFromInput(void);

Address loadAddressFromBinaryFile(FILE* file);

void saveAddressToBinaryFile(const Address* address, FILE* file);

Address createAddressFromInput(void);


#endif // ADDRESS_H