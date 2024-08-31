#ifndef SHELTER_H
#define SHELTER_H

#include "Pet.h"
#include "LinkedList.h"
#include "Address.h"
#include "Volunteer.h"
#include "AdoptionRequest.h"
#include "DonationRecord.h"
#include "Utility.h"

#define INITIAL_DONATION_CAPACITY 0
#define INITIAL_VOLUNTEER_CAPACITY 0



/**
 * @struct Shelter
 * @brief Represents an animal shelter.
 */
typedef struct Shelter {
    char* name;                   /**< Name of the shelter */
    Address address;              /**< Address of the shelter */
    LinkedList* availablePets;    /**< Linked list of available pets in the shelter */
    DonationRecord** donationRecords;  /**< Array of donation records */
    size_t donationCount;         /**< Number of donation records */
    size_t donationCapacity;      /**< Capacity of the donation records array */
    Volunteer** volunteers;       /**< Array of volunteers */
    size_t volunteerCount;        /**< Number of volunteers */
    size_t volunteerCapacity;     /**< Capacity of the volunteers array */
    LinkedList* adoptionRequests; /**< Linked list of adoption requests */
} Shelter;

/**
 * @brief Creates a new shelter with the given name and address.
 * @param name The name of the shelter.
 * @param address The address of the shelter.
 * @return A pointer to the newly created shelter, or NULL if memory allocation fails.
 */
Shelter* createShelter(const char* name, Address address);

/**
 * @brief Adds a pet to the shelter.
 * @param shelter The shelter to add the pet to.
 * @param pet The pet to be added to the shelter.
 */
void addPetToShelter(Shelter* shelter, Pet* pet);

/**
 * @brief Removes a pet from the shelter based on the pet ID.
 * @param shelter The shelter to remove the pet from.
 * @param petId The ID of the pet to be removed.
 * @return 1 if the pet is successfully removed, 0 otherwise.
 */
int removePetFromShelter(Shelter* shelter, int petId);

/**
 * @brief Adds a volunteer to the shelter.
 * @param shelter The shelter to add the volunteer to.
 * @param volunteer The volunteer to be added to the shelter.
 */
void addVolunteerToShelter(Shelter* shelter, Volunteer* volunteer);

/**
 * @brief Removes a volunteer from the shelter based on user input.
 * @param shelter The shelter to remove the volunteer from.
 */
void removeVolunteerFromShelter(Shelter* shelter);

/**
 * @brief Adds a donation record to the shelter.
 * @param shelter The shelter to add the donation record to.
 * @param donation The donation record to be added to the shelter.
 */
void addDonationToShelter(Shelter* shelter, DonationRecord* donation);

/**
 * @brief Selects a pet from the shelter based on user input.
 * @param shelter The shelter to select the pet from.
 * @return A pointer to the selected pet, or NULL if no pet is selected.
 */
Pet* selectPetFromShelter(Shelter* shelter);

/**
 * @brief Frees the memory allocated for a shelter and its associated data.
 * @param shelter The shelter to be freed.
 */
void freeShelter(Shelter* shelter);

/**
 * @brief Displays the details of a shelter.
 * @param shelter The shelter to display the details of.
 */
void displayShelter(const Shelter* shelter);


// * @brief Saves a shelter to a text file.
// * @param shelter The shelter to be saved.
// * @param filename The name of the file to save the shelter to.
// */
void saveShelterToTextFile(const Shelter* shelter, const char* filename);
/**
 * @brief Loads a shelter from a text file.
 * @param filename The name of the file to load the shelter from.
 * @return A pointer to the loaded shelter, or NULL if loading fails.
 */
Shelter* loadShelterFromTextFile(const char* filename);

/**
 * @brief Saves a shelter to a binary file.
 * @param shelter The shelter to be saved.
 * @param filename The name of the file to save the shelter to.
 */
void saveShelterToBinaryFile(const Shelter* shelter, const char* filename);

/**
 * @brief Loads a shelter from a binary file.
 * @param filename The name of the file to load the shelter from.
 * @return A pointer to the loaded shelter, or NULL if loading fails.
 */
Shelter* loadShelterFromBinaryFile(const char* filename);
/**
 * @brief Processes an adoption request for a pet in the shelter.
 * @param shelter The shelter to process the adoption request in.
 * @param request The adoption request to be processed.
 */
void processAdoptionRequest(struct Shelter* shelter, AdoptionRequest* request);

/**
 * @brief Creates a shelter from user input.
 * @return A pointer to the newly created shelter, or NULL if memory allocation fails.
 */
Shelter* createShelterFromInput(void);

/**
 * @brief Displays the available pets in the shelter.
 * @param shelter The shelter to display the available pets of.
 */
void displayAvailablePets(const Shelter* shelter);

/**
 * @brief Adds an adoption request to the shelter.
 * @param shelter The shelter to add the adoption request to.
 * @param adoptionRequest The adoption request to be added to the shelter.
 */
void addAdoptionRequestToShelter(Shelter* shelter, AdoptionRequest* adoptionRequest);

/**
 * @brief Finds a pet owner by ID from the adoption requests in the shelter.
 * @param shelter The shelter to search for the pet owner in.
 * @param ownerId The ID of the pet owner to find.
 * @return A pointer to the found pet owner, or NULL if not found.
 */
PetOwner* findPetOwnerByIdFromAdoptionRequests(Shelter* shelter, int ownerId);

/**
 * @brief Adds a training command to a selected pet in the shelter.
 * @param shelter The shelter to add the training command in.
 */
void addTrainingCommand(Shelter* shelter);

/**
 * @brief Shows the training commands of a selected pet in the shelter.
 * @param shelter The shelter to show the training commands in.
 */
void showTrainingCommands(Shelter* shelter);

/**
 * @brief Shows a training tip for a selected pet in the shelter.
 * @param shelter The shelter to show the training tip in.
 */
void showTrainingTip(Shelter* shelter);

/**
 * @brief Searches for a pet in the shelter by name.
 * @param shelter The shelter to search for the pet in.
 */
void searchByName(Shelter* shelter);

/**
 * @brief Searches for a pet in the shelter by type.
 * @param shelter The shelter to search for the pet in.
 */
void searchByType(Shelter* shelter);

/**
 * @brief Searches for a pet in the shelter by age.
 * @param shelter The shelter to search for the pet in.
 */
void searchByAge(Shelter* shelter);

/**
 * @brief Creates a new shelter if one doesn't exist, otherwise frees the existing shelter and creates a new one.
 * @param myShelter Double pointer to the Shelter object.
 */
void createNewShelter(Shelter** myShelter);

/**
 * @brief Adds a new pet to the shelter if the shelter exists.
 * @param myShelter Pointer to the Shelter object.
 */
void addPetToShelterIfExists(Shelter* myShelter);

/**
 * @brief Removes a pet from the shelter if the shelter exists.
 * @param myShelter Pointer to the Shelter object.
 */
void removePetFromShelterIfExists(Shelter* myShelter);

/**
 * @brief Adds a donation to the shelter if the shelter exists.
 * @param myShelter Pointer to the Shelter object.
 */
void addDonationToShelterIfExists(Shelter* myShelter);

/**
 * @brief Adds a volunteer to the shelter if the shelter exists.
 * @param myShelter Pointer to the Shelter object.
 */
void addVolunteerToShelterIfExists(Shelter* myShelter);

/**
 * @brief Removes a volunteer from the shelter if the shelter exists and has volunteers.
 * @param myShelter Pointer to the Shelter object.
 */
void removeVolunteerFromShelterIfExists(Shelter* myShelter);

/**
 * @brief Adds a training command to the shelter if the shelter exists.
 * @param myShelter Pointer to the Shelter object.
 */
void addTrainingCommandIfShelterExists(Shelter* myShelter);

/**
 * @brief Shows the training commands if the shelter exists.
 * @param myShelter Pointer to the Shelter object.
 */
void showTrainingCommandsIfShelterExists(Shelter* myShelter);

/**
 * @brief Shows a training tip if the shelter exists.
 * @param myShelter Pointer to the Shelter object.
 */
void showTrainingTipIfShelterExists(Shelter* myShelter);

/**
 * @brief Shows the sort menu if the shelter exists.
 * @param myShelter Pointer to the Shelter object.
 */
void showSortMenuIfShelterExists(Shelter* myShelter);

/**
 * @brief Shows the search menu if the shelter exists.
 * @param myShelter Pointer to the Shelter object.
 */
void showSearchMenuIfShelterExists(Shelter* myShelter);

/**
 * @brief Displays the shelter details if the shelter exists.
 * @param myShelter Pointer to the Shelter object.
 */
void displayShelterIfExists(Shelter* myShelter);

/**
 * @brief Processes an adoption request if the shelter exists.
 * @param myShelter Pointer to the Shelter object.
 */
void processAdoptionRequestIfShelterExists(Shelter* myShelter);

/**
 * @brief Displays the sort menu and performs the sorting operation based on user input.
 * @param shelter Pointer to the Shelter object.
 */
void sortMenu(Shelter* shelter);

/**
 * @brief Displays the search menu and performs the search operation based on user input.
 * @param shelter Pointer to the Shelter object.
 */
void searchMenu(Shelter* shelter);


#endif // SHELTER_H