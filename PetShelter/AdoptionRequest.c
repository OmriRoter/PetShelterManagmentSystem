// AdoptionRequest.c
#define _CRT_SECURE_NO_WARNINGS
#include "AdoptionRequest.h"
#include "Shelter.h"
#include <stdlib.h>

AdoptionRequest* createAdoptionRequest(int requestId, PetOwner* requester, Pet* requestedPet, Date requestDate) {
    AdoptionRequest* newRequest = (AdoptionRequest*)malloc(sizeof(AdoptionRequest));
    CHECK_ALLOCATION(newRequest);

    newRequest->requestId = requestId;
    newRequest->requester = requester;
    newRequest->requestedPet = requestedPet;
    newRequest->requestDate = requestDate;

    return newRequest;
}

void displayAdoptionRequestDetails(const AdoptionRequest* request) {
    if (!request) {
        printf("No Adoption Request details to display.\n");
        return;
    }

    printf("Adoption Request ID: %d\n", request->requestId);

    // Display Requester (PetOwner) details
    printf("Requester Details:\n");
    if (request->requester) {
        displayPetOwnerDetails(request->requester);  // Display PetOwner details
    }
    else {
        printf("Requester information is not available.\n");
    }

    // Display Requested Pet details
    printf("Requested Pet Details:\n");
    if (request->requestedPet) {
        displayPetDetails(request->requestedPet);  // Display Pet details
    }
    else {
        printf("Requested Pet information is not available.\n");
    }

    // Display Request Date
    printf("Request Date: ");
    displayDate(&(request->requestDate)); // Use existing function to display Date

}

void freeAdoptionRequest(AdoptionRequest* request) {
    if (request) {
        //freePetOwner(request->requester);
        free(request);
    }
}

void saveAdoptionRequestToTextFile(const AdoptionRequest* request, FILE* file) {
    if (!request || !file) return;

    fprintf(file, "%d,", request->requestId);
    savePetOwnerToTextFile(request->requester, file);
    savePetToTextFile(request->requestedPet, file);
    saveDateToTextFile(&request->requestDate, file);
    fprintf(file, "\n");
}

AdoptionRequest* loadAdoptionRequestFromTextFile(FILE* file) {
    if (!file) return NULL;

    AdoptionRequest* request = (AdoptionRequest*)malloc(sizeof(AdoptionRequest));
    CHECK_ALLOCATION(request); // Check if the memory allocation was successful

    if (fscanf(file, "%d,", &request->requestId) != 1) {
        free(request);
        return NULL;
    }

    request->requester = loadPetOwnerFromTextFile(file);
    request->requestedPet = loadPetFromTextFile(file);
    request->requestDate = loadDateFromTextFile(file);

    if (!request->requester || !request->requestedPet) {
        freeAdoptionRequest(request);
        return NULL;
    }

    return request;
}

void saveAdoptionRequestToBinaryFile(const AdoptionRequest* request, FILE* file) {
    if (!request || !file) return;

    fwrite(&request->requestId, sizeof(request->requestId), 1, file);
    savePetOwnerToBinaryFile(request->requester, file);
    savePetToBinaryFile(request->requestedPet, file);
    saveDateToBinaryFile(&request->requestDate, file);
}

AdoptionRequest* loadAdoptionRequestFromBinaryFile(FILE* file) {
    if (!file) return NULL;

    AdoptionRequest* request = (AdoptionRequest*)malloc(sizeof(AdoptionRequest));
    CHECK_ALLOCATION(request); // Check if the memory allocation was successful

    fread(&request->requestId, sizeof(request->requestId), 1, file);

    request->requester = loadPetOwnerFromBinaryFile(file);
    request->requestedPet = loadPetFromBinaryFile(file);
    request->requestDate = loadDateFromBinaryFile(file);

    if (!request->requester || !request->requestedPet) {
        freeAdoptionRequest(request);
        return NULL;
    }

    return request;
}

AdoptionRequest* createAdoptionRequestFromInput(void) {
    int requestId;
    char inputBuffer[256]; // Buffer for numeric inputs

    // Request ID input with validation for numbers only
    do {
        printf("Enter Adoption Request ID (numbers only): ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
    } while (sscanf(inputBuffer, "%d", &requestId) != 1);

    // In a full application, you would also need to input/fetch the PetOwner and Pet details here.
    // For simplicity, we'll use placeholders since fetching real PetOwner and Pet requires database or similar storage access.

    PetOwner* requester = NULL; // Placeholder - in a real app, fetch the PetOwner using the entered ID
    Pet* requestedPet = NULL;   // Placeholder - similarly, fetch the Pet using the entered ID

    printf("Note: Requester and Requested Pet are placeholders in this example.\n");

    Date requestDate = createDateFromInput(); // Use the previously defined function for date input

    return createAdoptionRequest(requestId, requester, requestedPet, requestDate);
}