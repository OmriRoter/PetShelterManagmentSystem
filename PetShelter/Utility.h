#ifndef UTILITY_H
#define UTILITY_H

#include <stdlib.h> // For size_t
#include <stdio.h>
#include <stdbool.h>

#define INPUT_BUFFER_SIZE 256
#define NAME_SIZE 100



/**
 * @brief Counts the number of elements in an array that satisfy a given predicate.
 * @param array The array of void pointers.
 * @param count The number of elements in the array.
 * @param predicate The predicate function that takes a void pointer and returns an int.
 * @return The count of elements that satisfy the predicate.
 */
size_t countIf(void** array, size_t count, int (*predicate)(void*));

/**
 * @brief Macro to check memory allocation and exit with an error message if it fails.
 * @param ptr The pointer to check for NULL.
 */
#define CHECK_ALLOCATION(ptr) if ((ptr) == NULL) { \
    fprintf(stderr, "Memory allocation failed at %s:%d\n", __FILE__, __LINE__); \
    exit(EXIT_FAILURE); \
}

 /**
  * @brief Macro for old  pet that may require extra attention.
  */
#define MAX_PET_AGE 15

  /**
   * @brief Macro to print an upper divider line.
   */
#define UPPER_PRINT_DIVIDER() printf("-------------------------------------------------\n")
   /**
    * @brief Macro to print an lower divider line.
    */

#define LOWER_PRINT_DIVIDER() printf("-------------------------------------------------\n")


   /**
    * @brief Checks if a string contains only alphabetic characters and spaces.
    * @param str The string to check.
    * @return 1 if the string is alphabetic, 0 otherwise.
    */
int isStringAlpha(const char* str);

int isStringAlphaNumericSpace(const char* str);

/**
 * @brief Prompts the user for input and validates it using a provided validation function.
 * @param buffer The buffer to store the validated input.
 * @param bufferSize The size of the buffer.
 * @param validateFunc The validation function that takes a const char pointer and returns an int.
 */
void inputStringWithValidation(char* buffer, size_t bufferSize, int (*validateFunc)(const char*));

/**
 * @brief Clears the input buffer by consuming any remaining characters until a newline or EOF is encountered.
 */
void clearInputBuffer();

int isStringNumeric(const char* str);

void capitalizeFirstLetter(char* str);

#endif // UTILITY_H