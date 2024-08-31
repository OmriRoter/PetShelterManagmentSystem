#ifndef ADOPTIONREQUEST_H
#define ADOPTIONREQUEST_H

#include "PetOwner.h"
#include "Pet.h"
#include "Date.h"

// Forward declaration of Shelter to avoid circular dependency
struct Shelter;

/**
 * @struct AdoptionRequest
 * @brief Represents an adoption request made by a pet owner for a specific pet.
 */
typedef struct AdoptionRequest {
    int requestId;         /**< Unique identifier for the adoption request */
    PetOwner* requester;   /**< Pointer to the pet owner making the request */
    Pet* requestedPet;     /**< Pointer to the pet being requested for adoption */
    Date requestDate;      /**< Date of the adoption request */
} AdoptionRequest;

/**
 * @brief Creates a new adoption request with the given details.
 * @param requestId The unique identifier for the adoption request.
 * @param requester Pointer to the pet owner making the request.
 * @param requestedPet Pointer to the pet being requested for adoption.
 * @param requestDate The date of the adoption request.
 * @return Pointer to the newly created AdoptionRequest, or NULL if memory allocation fails.
 */
AdoptionRequest* createAdoptionRequest(int requestId, PetOwner* requester, Pet* requestedPet, Date requestDate);

/**
 * @brief Frees the memory allocated for an adoption request.
 * @param request Pointer to the AdoptionRequest to be freed.
 */
void freeAdoptionRequest(AdoptionRequest* request);

///**
// * @brief Saves an adoption request to a text file.
// * @param request Pointer to the AdoptionRequest to be saved.
// * @param filename The name of the file to save the adoption request to.
// */
void saveAdoptionRequestToTextFile(const AdoptionRequest* request, FILE* file);

///**
// * @brief Loads an adoption request from a text file.
// * @param  The file to load the adoption request from.
// * @return Pointer to the loaded AdoptionRequest, or NULL if loading fails.
// */
AdoptionRequest* loadAdoptionRequestFromTextFile(FILE* file);

/**
 * @brief Saves an adoption request to a binary file.
 * @param request Pointer to the AdoptionRequest to be saved.
 * @param file Pointer to the FILE stream.
 */
void saveAdoptionRequestToBinaryFile(const AdoptionRequest* request, FILE* file);

/**
 * @brief Loads an adoption request from a binary file.
 * @param file Pointer to the FILE stream.
 * @return Pointer to the loaded AdoptionRequest, or NULL if loading fails.
 */
AdoptionRequest* loadAdoptionRequestFromBinaryFile(FILE* file);


/**
 * @brief Creates a new adoption request from user input.
 * @return Pointer to the newly created AdoptionRequest, or NULL if memory allocation fails.
 */
AdoptionRequest* createAdoptionRequestFromInput(void);

/**
 * @brief Displays the details of an adoption request.
 * @param request Pointer to the AdoptionRequest to be displayed.
 */
void displayAdoptionRequestDetails(const AdoptionRequest* request);

#endif // ADOPTIONREQUEST_H