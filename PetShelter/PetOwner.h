#ifndef PETOWNER_H
#define PETOWNER_H

#include "Pet.h"
#include "Address.h"


/**
 * @struct PetOwner
 * @brief Represents a pet owner.
 */
typedef struct {
    int id;            /**< Pet owner ID */
    char* name;        /**< Pet owner name */
    Address address;   /**< Pet owner address */
    Pet** pets;        /**< Array of pets owned by the pet owner */
    int numPets;       /**< Number of pets owned by the pet owner */
} PetOwner;

/**
 * @brief Creates a new pet owner with the given ID, name, and address.
 * @param id The pet owner ID.
 * @param name The pet owner name.
 * @param address The pet owner address.
 * @return A pointer to the newly created pet owner, or NULL if memory allocation fails.
 */
PetOwner* createPetOwner(int id, const char* name, Address address);

/**
 * @brief Adds a pet to a pet owner.
 * @param owner The pet owner to add the pet to.
 * @param pet The pet to add to the pet owner.
 */
void addPetToOwner(PetOwner* owner, Pet* pet);

/**
 * @brief Displays the details of a pet owner.
 * @param owner The pet owner to display the details of.
 */
void displayPetOwnerDetails(const PetOwner* owner);

/**
 * @brief Removes a pet from a pet owner.
 * @param owner The pet owner to remove the pet from.
 * @param pet The pet to remove from the pet owner.
 */
void removePetFromOwner(PetOwner* owner, Pet* pet);

/**
 * @brief Frees the memory allocated for a pet owner and its associated pets.
 * @param owner The pet owner to free.
 */
void freePetOwner(PetOwner* owner);

/**
 * @brief Creates a pet owner from user input.
 * @return A pointer to the newly created pet owner, or NULL if memory allocation fails.
 */
PetOwner* createPetOwnerFromInput(void);

/**
 * @brief Saves a pet owner to a text file.
 * @param owner Pointer to the pet owner.
 * @param file Pointer to the FILE stream.
 */
void savePetOwnerToTextFile(const PetOwner* owner, FILE* file);

/**
 * @brief Loads a pet owner from a text file.
 * @param file Pointer to the FILE stream.
 * @return Pointer to the loaded pet owner, or NULL if loading fails.
 */
PetOwner* loadPetOwnerFromTextFile(FILE* file);

/**
 * @brief Saves a pet owner to a binary file.
 * @param owner Pointer to the pet owner.
 * @param file Pointer to the FILE stream.
 */
void savePetOwnerToBinaryFile(const PetOwner* owner, FILE* file);

/**
 * @brief Loads a pet owner from a binary file.
 * @param file Pointer to the FILE stream.
 * @return Pointer to the loaded pet owner, or NULL if loading fails.
 */
PetOwner* loadPetOwnerFromBinaryFile(FILE* file);


#endif // PETOWNER_H