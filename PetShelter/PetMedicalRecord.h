#ifndef PETMEDICALRECORD_H
#define PETMEDICALRECORD_H

#include "Pet.h"
#include "Date.h"

#define VACCINATIONS_SIZE 256
#define CONDITIONS_SIZE 256

/**
 * @struct PetMedicalRecord
 * @brief Represents a pet's medical record.
 */
typedef struct {
    Pet* pet;                /**< Pointer to the associated Pet object */
    char* vaccinations;      /**< String containing the pet's vaccinations */
    char* medicalConditions; /**< String containing the pet's medical conditions */
    Date* lastVisit;         /**< Pointer to the Date object representing the pet's last visit */
} PetMedicalRecord;

/**
 * @brief Creates a new pet medical record with the given details.
 * @param pet Pointer to the associated Pet object.
 * @param vaccinations String containing the pet's vaccinations.
 * @param conditions String containing the pet's medical conditions.
 * @param lastVisit Pointer to the Date object representing the pet's last visit.
 * @return Pointer to the newly created PetMedicalRecord, or NULL if memory allocation fails.
 */
PetMedicalRecord* createPetMedicalRecord(Pet* pet, const char* vaccinations, const char* conditions, Date* lastVisit);

/**
 * @brief Updates an existing pet medical record with new details.
 * @param record Pointer to the PetMedicalRecord to update.
 * @param vaccinations String containing the updated vaccinations (optional).
 * @param conditions String containing the updated medical conditions (optional).
 * @param lastVisit Pointer to the Date object representing the updated last visit (optional).
 */
void updatePetMedicalRecord(PetMedicalRecord* record, const char* vaccinations, const char* conditions, Date* lastVisit);

/**
 * @brief Displays the details of a pet medical record.
 * @param record Pointer to the PetMedicalRecord to display.
 */
void displayPetMedicalRecordDetails(const PetMedicalRecord* record);

/**
 * @brief Frees the memory allocated for a pet medical record.
 * @param record Pointer to the PetMedicalRecord to free.
 */
void freePetMedicalRecord(PetMedicalRecord* record);

/**
 * @brief Creates a new pet medical record from user input.
 * @param pet Pointer to the associated Pet object.
 * @return Pointer to the newly created PetMedicalRecord, or NULL if memory allocation fails.
 */
PetMedicalRecord* createPetMedicalRecordFromInput(Pet* pet);

/**
 * @brief Saves a PetMedicalRecord to a text file.
 * @param record Pointer to the PetMedicalRecord to save.
 * @param file Pointer to the already open FILE to write to.
 */
void savePetMedicalRecordToTextFile(const PetMedicalRecord* record, FILE* file);

/**
 * @brief Loads a PetMedicalRecord from a text file.
 * @param file Pointer to the already open FILE to read from.
 * @return Pointer to the loaded PetMedicalRecord, or NULL if an error occurred.
 */
PetMedicalRecord* loadPetMedicalRecordFromTextFile(FILE* file);

/**
 * @brief Saves a PetMedicalRecord to a binary file.
 * @param record Pointer to the PetMedicalRecord to save.
 * @param file Pointer to the already open FILE to write to.
 */
void savePetMedicalRecordToBinaryFile(const PetMedicalRecord* record, FILE* file);

/**
 * @brief Loads a PetMedicalRecord from a binary file.
 * @param file Pointer to the already open FILE to read from.
 * @return Pointer to the loaded PetMedicalRecord, or NULL if an error occurred.
 */
PetMedicalRecord* loadPetMedicalRecordFromBinaryFile(FILE* file);

#endif // PETMEDICALRECORD_H