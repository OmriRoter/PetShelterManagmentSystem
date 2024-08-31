#ifndef PET_H
#define PET_H

#include "Date.h"
#include "CommandRecord.h"
#include "Utility.h"
#include "LinkedList.h"




#include <stdlib.h>

#define TYPE_SIZE 20
#define BREED_SIZE 30

/**
 * @struct Pet
 * @brief Represents a pet.
 */
typedef struct {
    int id;                    /**< Pet ID */
    char* name;                /**< Dynamically allocated string for pet name */
    char type[TYPE_SIZE];      /**< Fixed-size char array for pet type */
    double age;                   /**< Pet age */
    char breed[BREED_SIZE];    /**< Fixed-size char array for pet breed */
    int isAdopted;             /**< Adoption status of the pet */
    Date addedDate;            /**< Date when the pet was added */
    CommandRecord* commands;   /**< Array of command records */
    int commandCount;          /**< Number of commands the pet has */
} Pet;

/**
 * @brief Creates a new pet with the given details.
 * @param id The pet ID.
 * @param name The name of the pet.
 * @param type The type of the pet.
 * @param age The age of the pet.
 * @param breed The breed of the pet.
 * @param addedDate The date when the pet was added.
 * @return A pointer to the newly created pet.
 */
Pet* createPet(int id, const char* name, const char* type, double age, const char* breed, Date addedDate);
/**
 * @brief Sets the adoption status of a pet.
 * @param pet Pointer to the pet.
 * @param adopted The adoption status (1 for adopted, 0 for not adopted).
 */
void setPetAdoptionStatus(Pet* pet, int adopted);

/**
 * @brief Displays the details of a pet.
 * @param pet Pointer to the pet.
 */
void displayPetDetails(const Pet* pet);

/**
 * @brief Frees the memory allocated for a pet.
 * @param pet Pointer to the pet.
 */
void freePet(Pet* pet);

/**
 * @brief Sorts a linked list of pets by name.
 * @param petList Pointer to the linked list of pets.
 */
void sortPetsByName(LinkedList* petList);

/**
 * @brief Sorts a linked list of pets by type.
 * @param petList Pointer to the linked list of pets.
 */
void sortPetsByType(LinkedList* petList);

/**
 * @brief Sorts a linked list of pets by age.
 * @param petList Pointer to the linked list of pets.
 */
void sortPetsByAge(LinkedList* petList);

/**
 * @brief Searches for a pet by name in a linked list of pets.
 * @param petList Pointer to the linked list of pets.
 * @param name The name to search for.
 * @return Pointer to the found pet, or NULL if not found.
 */
Pet* searchPetByName(LinkedList* petList, const char* name);

/**
 * @brief Searches for a pet by type in a linked list of pets.
 * @param petList Pointer to the linked list of pets.
 * @param type The type to search for.
 * @return Pointer to the found pet, or NULL if not found.
 */
Pet* searchPetByType(LinkedList* petList, const char* type);

/**
 * @brief Searches for a pet by age in a linked list of pets.
 * @param petList Pointer to the linked list of pets.
 * @param age The age to search for.
 * @return Pointer to the found pet, or NULL if not found.
 */
Pet* searchPetByAge(LinkedList* petList, double age);

/**
 * @brief Saves a pet to a text file.
 * @param pet Pointer to the pet.
 * @param file Pointer to the FILE stream.
 */
void savePetToTextFile(const Pet* pet, FILE* file);

/**
 * @brief Loads a pet from a text file.
 * @param file Pointer to the FILE stream.
 * @return Pointer to the loaded pet, or NULL if loading fails.
 */
Pet* loadPetFromTextFile(FILE* file);

///**
// * @brief Saves a pet to a binary file.
// * @param pet Pointer to the pet.
// * @param binary file to save the pet to.
// * @return 1 if the save is successful, 0 otherwise.
// */
void savePetToBinaryFile(const Pet* pet, FILE* file);

///**
// * @brief Loads a pet from a binary file.
// * @param binary file to load the pet from.
// * @return Pointer to the loaded pet, or NULL if loading fails.
// */
Pet* loadPetFromBinaryFile(FILE* file);

/**
 * @brief Creates a pet from user input.
 * @return Pointer to the newly created pet.
 */
Pet* createPetFromInput(void);

/**
 * @brief Adds a command to a pet.
 * @param pet Pointer to the pet.
 * @param command Pointer to the command record to add.
 */
void addCommandToPet(Pet* pet, CommandRecord* command);

/**
 * @brief Removes a command from a pet.
 * @param pet Pointer to the pet.
 * @param commandIndex The index of the command to remove.
 */
void removeCommandFromPet(Pet* pet, int commandIndex);

void displayPetCommands(const Pet* pet);

/**
 * @brief Displays training tips for a given pet based on its breed and age category.
 * @param pet A pointer to the Pet object.
 */
void displayPetTrainingTips(const Pet* pet);

#endif // PET_H