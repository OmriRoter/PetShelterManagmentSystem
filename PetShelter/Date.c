// Date.c
#define _CRT_SECURE_NO_WARNINGS
#include "Date.h"
#include <stdio.h>
#include <time.h>

Date createDate(int day, int month, int year) {
    Date newDate = { 0 }; // Zero-initialize the newDate struct

    newDate.day = day;
    newDate.month = month;
    newDate.year = year;

    return newDate;
}

void displayDate(const Date* date) {
    if (date != NULL) {
        printf("Date: %02d/%02d/%04d\n", date->day, date->month, date->year);
    }
    else {
        UPPER_PRINT_DIVIDER();
        printf("Error: No date available.\n");
        LOWER_PRINT_DIVIDER();
    }
}

Date createDateFromInput(void) {
    int day, month, year;
    char input[INPUT_BUFFER_SIZE_FOR_DATE];

    UPPER_PRINT_DIVIDER();
    printf("Enter Date (DD/MM/YYYY) or '0' for today's date:\n");
    UPPER_PRINT_DIVIDER();

    while (1) {
        printf("> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error: Failed to read input. Please try again.\n");
            continue;
        }

        // Check if the user wants to use the current date
        if (input[0] == '0' && (input[1] == '\n' || input[1] == '\0')) {
            return getCurrentDate();
        }

        // Parse the input date
        if (sscanf(input, "%d/%d/%d", &day, &month, &year) == 3 && isValidDate(day, month, year)) {
            break;
        }
        else {
            printf("Invalid date format. Please enter a valid date in the format DD/MM/YYYY or '0' for today's date.\n");
        }
    }

    LOWER_PRINT_DIVIDER();
    return createDate(day, month, year);
}

int isValidDate(int day, int month, int year) {
    // Basic validation for date ranges
    if (year < MIN_YEAR || month < 1 || month > MAX_MONTHS_IN_YEAR || day < 1) return 0;

    int daysInMonth[] = { 31, 28 + isLeapYear(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    return day <= daysInMonth[month - 1];
}

int isLeapYear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

Date getCurrentDate() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    Date currentDate = { tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900 }; // struct tm month range is 0-11, hence +1; year since 1900, hence +1900
    return currentDate;
}

void saveDateToTextFile(const Date* date, FILE* file) {
    if (date != NULL && file != NULL) {
        fprintf(file, "%d,%d,%d\n", date->day, date->month, date->year);
    }
}

Date loadDateFromTextFile(FILE* file) {
    Date date = { 0 }; // Initialize date with zero values

    if (file != NULL) {
        int res = fscanf(file, "%d,%d,%d", &date.day, &date.month, &date.year);
        if (res != 3) {
            // Handle the case where fscanf failed to read all three values
            printf("Error: Failed to read date from file.\n");
            date.day = 0;
            date.month = 0;
            date.year = 0;
        }
    }

    return date;
}

void saveDateToBinaryFile(const Date* date, FILE* file) {
    if (date != NULL && file != NULL) {
        fwrite(date, sizeof(Date), 1, file);
    }
}

Date loadDateFromBinaryFile(FILE* file) {
    Date date;
    if (file != NULL && fread(&date, sizeof(Date), 1, file) == 1) {
        return date;
    }
    Date emptyDate = { 0, 0, 0 }; // Return an empty date if read fails
    return emptyDate;
}