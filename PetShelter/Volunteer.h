#ifndef VOLUNTEER_H
#define VOLUNTEER_H

#include "stdio.h"
#include "Utility.h"

#define ROLE_SIZE 100


/**
 * @struct Volunteer
 * @brief Represents a volunteer at the shelter.
 */
typedef struct {
    int volunteerId;     /**< Unique identifier for the volunteer */
    char* name;          /**< Name of the volunteer */
    char* role;          /**< Role of the volunteer at the shelter */
    int hoursPerMonth;   /**< The number of hours the volunteer commits per month */
} Volunteer;

/**
 * @brief Creates a new volunteer with the given details.
 * @param volunteerId The unique identifier for the volunteer.
 * @param name The name of the volunteer.
 * @param role The role of the volunteer at the shelter.
 * @param hoursPerMonth The number of hours the volunteer commits per month.
 * @return A pointer to the newly created Volunteer, or NULL if memory allocation fails.
 */
Volunteer* createVolunteer(int volunteerId, const char* name, const char* role, int hoursPerMonth);

/**
 * @brief Displays the information of a volunteer.
 * @param volunteer A pointer to the Volunteer to display.
 */
void displayVolunteerInfo(const Volunteer* volunteer);

/**
 * @brief Creates a new volunteer from user input.
 * @return A pointer to the newly created Volunteer, or NULL if memory allocation fails.
 */
Volunteer* createVolunteerFromInput(void);

/**
 * @brief Frees the memory allocated for a volunteer.
 * @param volunteer A pointer to the Volunteer to free.
 */
void freeVolunteer(Volunteer* volunteer);

/**
 * @brief Saves a volunteer to a text file.
 * @param volunteer Pointer to the volunteer.
 * @param file Pointer to the FILE stream.
 */
void saveVolunteerToTextFile(const Volunteer* volunteer, FILE* file);

/**
 * @brief Loads a volunteer from a text file.
 * @param file Pointer to the FILE stream.
 * @return Pointer to the loaded volunteer, or NULL if loading fails.
 */
Volunteer* loadVolunteerFromTextFile(FILE* file);

/**
 * @brief Saves a volunteer to a binary file.
 * @param volunteer Pointer to the volunteer.
 * @param file Pointer to the FILE stream.
 */
void saveVolunteerToBinaryFile(const Volunteer* volunteer, FILE* file);

/**
 * @brief Loads a volunteer from a binary file.
 * @param file Pointer to the FILE stream.
 * @return Pointer to the loaded volunteer, or NULL if loading fails.
 */
Volunteer* loadVolunteerFromBinaryFile(FILE* file);


#endif // VOLUNTEER_H