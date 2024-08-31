#ifndef DATE_H
#define DATE_H

#include "stdio.h"
#include "utility.h"

// Define constants for date ranges and input sizes
#define MIN_YEAR 0
#define MAX_DAYS_IN_MONTH 31
#define MAX_MONTHS_IN_YEAR 12
#define INPUT_BUFFER_SIZE_FOR_DATE 20

/**
 * @struct Date
 * @brief Represents a date.
 */
typedef struct {
    int day;   /**< Day of the month (1-31) */
    int month; /**< Month of the year (1-12) */
    int year;  /**< Year */
} Date;

/**
 * @brief Creates a Date object with the given day, month, and year.
 * @param day The day of the month (1-31).
 * @param month The month of the year (1-12).
 * @param year The year.
 * @return The created Date object.
 */
Date createDate(int day, int month, int year);

/**
 * @brief Displays the date in the format "DD/MM/YYYY".
 * @param date A pointer to the Date object.
 */
void displayDate(const Date* date);

/**
 * @brief Saves a Date object to a text file.
 * @param date A pointer to the Date object.
 * @param file A pointer to the FILE stream.
 */
void saveDateToTextFile(const Date* date, FILE* file);

/**
 * @brief Loads a Date object from a text file.
 * @param file A pointer to the FILE stream.
 * @return The loaded Date object.
 */
Date loadDateFromTextFile(FILE* file);

//
///**
// * @brief Saves a Date object to a binary file.
// * @param date A pointer to the Date object.
// * @param filename The name of the file to save the date to.
// */
void saveDateToBinaryFile(const Date* date, FILE* file);

///**
// * @brief Loads a Date object from a binary file.
// * @param file to load the date from.
// * @return The loaded Date object.
// */
Date loadDateFromBinaryFile(FILE* file);

/**
 * @brief Creates a Date object from user input.
 * @return The created Date object.
 */
Date createDateFromInput(void);

/**
 * @brief Checks if a given date is valid.
 * @param day The day of the month (1-31).
 * @param month The month of the year (1-12).
 * @param year The year.
 * @return 1 if the date is valid, 0 otherwise.
 */
int isValidDate(int day, int month, int year);

/**
 * @brief Checks if a given year is a leap year.
 * @param year The year to check.
 * @return 1 if the year is a leap year, 0 otherwise.
 */
int isLeapYear(int year);

/**
 * @brief Gets the current date.
 * @return The current date as a Date object.
 */
Date getCurrentDate();

#endif // DATE_H