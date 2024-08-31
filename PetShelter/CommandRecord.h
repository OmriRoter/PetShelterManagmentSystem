#ifndef COMMAND_RECORD_H
#define COMMAND_RECORD_H

#include <stdint.h> // For fixed-width integer types
#include "Date.h"
#include "Utility.h"

#define DAY_MASK 0x1F    // Mask for extracting the day (5 bits)
#define MONTH_MASK 0x07  // Mask for extracting the month (3 bits)
#define MONTH_SHIFT 5    // Shift for encoding/decoding the month
#define BASE_YEAR 2000  // Base year used to reduce the storage size of the year in binary files
#define MAX_PROFICIENCY_LEVEL 7  // Maximum proficiency level for a command



/**
 * @struct CommandRecord
 * @brief Represents a record of a command learned by a pet.
 */
typedef struct {
    char* commandName;           /**< The name of the command */
    uint8_t learnedDate;         /**< Encodes day and month of the learned date */
    uint16_t learnedYear;        /**< The year the command was learned */
    uint8_t proficiencyLevel;    /**< The proficiency level of the pet in the command (0-7) */
} CommandRecord;


/**
 * @brief Saves a command record to a binary file.
 * @param record Pointer to the command record to save.
 * @param fileName The name of the file to save the record to.
 */
void saveCommandRecordToBinaryFile(const CommandRecord* record, FILE* file);

/**
 * @brief Loads a command record from a binary file.
 * @param fileName The name of the file to load the record from.
 * @return Pointer to the loaded command record, or NULL if loading fails.
 */
CommandRecord* loadCommandRecordFromBinaryFile(FILE* file);

/**
 * @brief Creates a command record with the given values.
 * @param commandName The name of the command.
 * @param day The day of the learned date (1-31).
 * @param month The month of the learned date (1-12).
 * @param learnedYear The learned year of the command.
 * @param proficiencyLevel The proficiency level of the command (0-7).
 * @return Pointer to the newly created command record, or NULL if memory allocation fails.
 */
CommandRecord* createCommandRecord(const char* commandName, uint8_t day, uint8_t month, uint16_t learnedYear, uint8_t proficiencyLevel);

/**
 * @brief Displays the details of a command record.
 * @param record Pointer to the command record to display.
 */
void displayCommandRecord(const CommandRecord* record);

/**
 * @brief Creates a command record from user input.
 * @return Pointer to the newly created command record, or NULL if memory allocation fails.
 */
CommandRecord* createCommandRecordFromInput();

void freeCommandRecord(CommandRecord* record);
/**
 * @brief Saves a command record to a text file.
 * @param record Pointer to the command record to save.
 * @param file Pointer to the FILE stream.
 */
void saveCommandRecordToTextFile(const CommandRecord* record, FILE* file);

/**
 * @brief Loads a command record from a text file.
 * @param file Pointer to the FILE stream.
 * @return Pointer to the loaded command record, or NULL if loading fails.
 */
CommandRecord* loadCommandRecordFromTextFile(FILE* file);

#endif // COMMAND_RECORD_H