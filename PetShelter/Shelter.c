// Shelter.c
#define _CRT_SECURE_NO_WARNINGS
#include "Shelter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//basics
Shelter* createShelter(const char* name, Address address) {
	Shelter* newShelter = (Shelter*)malloc(sizeof(Shelter));
	CHECK_ALLOCATION(newShelter);  

	newShelter->name = _strdup(name);
	newShelter->address = address;
	newShelter->availablePets = createLinkedList();
	newShelter->donationRecords = NULL;
	newShelter->donationCount = 0;
	newShelter->donationCapacity = INITIAL_DONATION_CAPACITY;
	newShelter->volunteers = NULL;
	newShelter->volunteerCount = 0;
	newShelter->volunteerCapacity = INITIAL_VOLUNTEER_CAPACITY;
	newShelter->adoptionRequests = createLinkedList();

	return newShelter;
}

void addDonationToShelter(Shelter* shelter, DonationRecord* donation) {
	if (!shelter || !donation) return;

	if (shelter->donationCount >= shelter->donationCapacity) {
		size_t newCapacity = shelter->donationCapacity == 0 ? 1 : shelter->donationCapacity * 2;
		DonationRecord** newRecords = realloc(shelter->donationRecords, newCapacity * sizeof(DonationRecord*));
		CHECK_ALLOCATION(newRecords);

		shelter->donationRecords = newRecords;
		shelter->donationCapacity = newCapacity;
	}

	shelter->donationRecords[shelter->donationCount++] = donation;
}

void addPetToShelter(Shelter* shelter, Pet* pet) {
	if (shelter && pet) {
		insertNode(shelter->availablePets, pet);
	}
}

int removePetFromShelter(Shelter* shelter, int petId) {
	if (shelter && shelter->availablePets) {
		Node* current = shelter->availablePets->head;
		while (current != NULL) {
			Pet* pet = (Pet*)current->data;
			if (pet && pet->id == petId) {
				deleteNode(shelter->availablePets, pet);
				return 1;  // Pet removed successfully
			}
			current = current->next;
		}
	}
	return 0;  // Pet not found
}

void addVolunteerToShelter(Shelter* shelter, Volunteer* volunteer) {
	if (!shelter || !volunteer) return;

	if (shelter->volunteerCount >= shelter->volunteerCapacity) {
		size_t newCapacity = shelter->volunteerCapacity == 0 ? 1 : shelter->volunteerCapacity * 2;
		Volunteer** newVolunteers = realloc(shelter->volunteers, newCapacity * sizeof(Volunteer*));
		CHECK_ALLOCATION(newVolunteers);

		shelter->volunteers = newVolunteers;
		shelter->volunteerCapacity = newCapacity;
	}

	shelter->volunteers[shelter->volunteerCount++] = volunteer;
}

void removeVolunteerFromShelter(Shelter* shelter) {
	if (!shelter || shelter->volunteerCount == 0) {
		printf("There are no volunteers in the shelter to remove.\n");
		return;
	}

	// Displaying all volunteers
	printf("List of Volunteers:\n");
	for (size_t i = 0; i < shelter->volunteerCount; i++) {
		printf("ID: %d, Name: %s\n", shelter->volunteers[i]->volunteerId, shelter->volunteers[i]->name);
	}

	// Prompting user to choose a volunteer to remove
	int volunteerId;
	printf("Enter the ID of the volunteer to remove: ");
	if (scanf("%d", &volunteerId) != 1) {
		printf("Invalid input. Please enter a valid volunteer ID.\n");
		while (getchar() != '\n');  // Clear input buffer
		return;
	}
	(void)getchar(); // Consume the newline character left by scanf and ignore the return value


	// Removing the selected volunteer
	for (size_t i = 0; i < shelter->volunteerCount; i++) {
		if (shelter->volunteers[i]->volunteerId == volunteerId) {
			freeVolunteer(shelter->volunteers[i]);  // Freeing the volunteer's memory

			// Shifting the remaining elements
			for (size_t j = i; j < shelter->volunteerCount - 1; j++) {
				shelter->volunteers[j] = shelter->volunteers[j + 1];
			}

			shelter->volunteerCount--;  // Decreasing the count of volunteers

			// Reallocating the array if the number of volunteers is much less than the capacity
			if (shelter->volunteerCount == 0) {
				free(shelter->volunteers);
				shelter->volunteers = NULL;
				shelter->volunteerCapacity = 0;
			}
			else if (shelter->volunteerCount <= shelter->volunteerCapacity / 4) {
				size_t newCapacity = shelter->volunteerCapacity / 2;
				Volunteer** newVolunteers = realloc(shelter->volunteers, newCapacity * sizeof(Volunteer*));
				if (newVolunteers) {
					shelter->volunteers = newVolunteers;
					shelter->volunteerCapacity = newCapacity;
				}  // If realloc fails, keep the original memory
			}

			printf("Volunteer with ID %d has been removed from the shelter.\n", volunteerId);
			return;
		}
	}

	// If the function reaches this point, the volunteer ID was not found
	printf("No volunteer with ID %d found in the shelter.\n", volunteerId);
}

void freeShelter(Shelter* shelter) {
	if (!shelter) return;

	if (shelter->name) {
		free(shelter->name);
	}

	if (shelter->availablePets) {
		Node* current = shelter->availablePets->head;
		while (current != NULL) {
			if (current->data) {
				freePet((Pet*)current->data);
			}
			current = current->next;
		}
		freeLinkedList(shelter->availablePets);
	}

	if (shelter->donationRecords) {
		for (size_t i = 0; i < shelter->donationCount; i++) {
			if (shelter->donationRecords[i]) {
				freeDonationRecord(shelter->donationRecords[i]);
			}
		}
		free(shelter->donationRecords);
	}

	if (shelter->volunteers) {
		for (size_t i = 0; i < shelter->volunteerCount; i++) {
			if (shelter->volunteers[i]) {
				freeVolunteer(shelter->volunteers[i]);
			}
		}
		free(shelter->volunteers);
	}

	if (shelter->adoptionRequests) {
		Node* current = shelter->adoptionRequests->head;
		while (current != NULL) {
			if (current->data) {
				freeAdoptionRequest((AdoptionRequest*)current->data);
			}
			current = current->next;
		}
		freeLinkedList(shelter->adoptionRequests);
	}

	free(shelter);
}

void displayShelter(const Shelter* shelter) {
	if (!shelter) {
		printf("Shelter data is unavailable.\n");
		return;
	}

	UPPER_PRINT_DIVIDER();
	printf("Shelter Name: %s\n", shelter->name);
	printf("Address:\n");
	displayAddress(&shelter->address);

	printf("\nAvailable Pets:\n");
	UPPER_PRINT_DIVIDER();
	if (shelter->availablePets && shelter->availablePets->size > 0) {
		displayLinkedList(shelter->availablePets, (void (*)(void*))displayPetDetails);
	}
	else {
		printf("No available pets at the moment.\n");
	}
	LOWER_PRINT_DIVIDER();

	printf("\nVolunteers:\n");
	UPPER_PRINT_DIVIDER();
	if (shelter->volunteerCount > 0) {
		for (size_t i = 0; i < shelter->volunteerCount; ++i) {
			displayVolunteerInfo(shelter->volunteers[i]);
		}
	}
	else {
		printf("No volunteers registered.\n");
	}
	LOWER_PRINT_DIVIDER();

	printf("\nDonation Records:\n");
	UPPER_PRINT_DIVIDER();
	if (shelter->donationCount > 0) {
		for (size_t i = 0; i < shelter->donationCount; ++i) {
			displayDonationRecord(shelter->donationRecords[i]);
		}
	}
	else {
		printf("No donation records available.\n");
	}
	LOWER_PRINT_DIVIDER();

	printf("\nAdoption Requests:\n");
	UPPER_PRINT_DIVIDER();
	if (shelter->adoptionRequests && shelter->adoptionRequests->size > 0) {
		displayLinkedList(shelter->adoptionRequests, (void (*)(void*))displayAdoptionRequestDetails);
	}
	else {
		printf("No adoption requests available.\n");
	}
	LOWER_PRINT_DIVIDER();
}


void processAdoptionRequest(struct Shelter* shelter, AdoptionRequest* request) {
	if (shelter == NULL || request == NULL || request->requestedPet == NULL || request->requester == NULL) {
		printf("Invalid parameters for adoption request.\n");
		return;
	}

	UPPER_PRINT_DIVIDER();
	// Remove the requested pet from the shelter's available pets list
	if (removePetFromShelter(shelter, request->requestedPet->id)) {
		// Pet found and removed from the shelter, proceed with adoption
		addPetToOwner(request->requester, request->requestedPet);
		setPetAdoptionStatus(request->requestedPet, 1); // Mark the pet as adopted
		addAdoptionRequestToShelter(shelter, request); // Add the adoption request to the shelter
		printf("Pet ID %d has been successfully adopted by %s.\n", request->requestedPet->id, request->requester->name);
		printf("The pet has been removed from the shelter's available pets and added to the pet owner's list of pets.\n");
	}
	else {
		printf("Pet ID %d not found in the shelter.\n", request->requestedPet->id);
	}
	LOWER_PRINT_DIVIDER();
}

Shelter* createShelterFromInput(void) {
	char name[NAME_SIZE];
	Address address;

	UPPER_PRINT_DIVIDER();
	printf("Enter Shelter Name: ");
	fgets(name, sizeof(name), stdin);
	name[strcspn(name, "\n")] = 0;  // Remove trailing newline character

	address = createAddressFromInput();

	LOWER_PRINT_DIVIDER();

	return createShelter(name, address);
}

void displayAvailablePets(const Shelter* shelter) {
	if (!shelter || !shelter->availablePets || shelter->availablePets->size == 0) {
		printf("No available pets in the shelter.\n");
		return;
	}

	printf("Available Pets:\n");
	Node* current = shelter->availablePets->head;
	while (current != NULL) {
		Pet* pet = (Pet*)current->data;
		printf("ID: %d, Name: %s\n", pet->id, pet->name);  // Adjust this line if you want to display more details
		current = current->next;
	}
}


void addAdoptionRequestToShelter(Shelter* shelter, AdoptionRequest* adoptionRequest) {
	if (!shelter || !adoptionRequest) return;

	insertNode(shelter->adoptionRequests, adoptionRequest);
}

PetOwner* findPetOwnerByIdFromAdoptionRequests(Shelter* shelter, int ownerId) {
	if (shelter == NULL || shelter->adoptionRequests == NULL) {
		return NULL;
	}

	Node* current = shelter->adoptionRequests->head;
	while (current != NULL) {
		AdoptionRequest* request = (AdoptionRequest*)current->data;
		if (request->requester != NULL && request->requester->id == ownerId) {
			return request->requester;
		}
		current = current->next;
	}

	return NULL;
}


void addTrainingCommand(Shelter* shelter) {
	if (shelter) {
		Pet* selectedPet = selectPetFromShelter(shelter);
		if (selectedPet) {
			CommandRecord* newCommand = createCommandRecordFromInput();
			if (newCommand) {
				addCommandToPet(selectedPet, newCommand);
				free(newCommand);  // Free the dynamically allocated command record
			}
			else {
				printf("Failed to create a new command record.\n");
			}
		}
		else {
			printf("No pet selected.\n");
		}
	}
	else {
		printf("Invalid shelter pointer.\n");
	}
}

void showTrainingCommands(Shelter* shelter) {
	if (shelter) {
		Pet* selectedPet = selectPetFromShelter(shelter);
		if (selectedPet) {
			displayPetCommands(selectedPet);
		}
		else {
			printf("No pet selected.\n");
		}
	}
	else {
		printf("Invalid shelter pointer.\n");
	}
}

void showTrainingTip(Shelter* shelter) {
	if (shelter) {
		Pet* selectedPet = selectPetFromShelter(shelter);
		if (selectedPet) {
			displayPetTrainingTips(selectedPet);
		}
		else {
			printf("No pet selected.\n");
		}
	}
	else {
		printf("Invalid shelter pointer.\n");
	}
}

void searchByName(Shelter* shelter) {
	char name[NAME_SIZE];
	printf("Enter the name of the pet to search for: ");
	if (scanf("%s", name) != 1) {
		printf("Invalid input. Please enter a valid pet name.\n");
		while (getchar() != '\n');  // Clear input buffer
		return;
	}

	Pet* pet = searchPetByName(shelter->availablePets, name);
	if (pet != NULL) {
		printf("Pet found:\n");
		displayPetDetails(pet);
	}
	else {
		printf("Pet with name '%s' not found.\n", name);
	}
}

void searchByType(Shelter* shelter) {
	char type[TYPE_SIZE];
	printf("Enter the type of the pet to search for: ");
	if (scanf("%s", type) != 1) {
		printf("Invalid input. Please enter a valid pet type.\n");
		while (getchar() != '\n');  // Clear input buffer
		return;
	}

	Pet* pet = searchPetByType(shelter->availablePets, type);
	if (pet != NULL) {
		printf("Pet found:\n");
		displayPetDetails(pet);
	}
	else {
		printf("Pet with type '%s' not found.\n", type);
	}
}

void searchByAge(Shelter* shelter) {
	int age;
	printf("Enter the age of the pet to search for: ");
	if (scanf("%d", &age) != 1) {
		printf("Invalid input. Please enter a valid pet age.\n");
		while (getchar() != '\n');  // Clear input buffer
		return;
	}

	Pet* pet = searchPetByAge(shelter->availablePets, age);
	if (pet != NULL) {
		printf("Pet found:\n");
		displayPetDetails(pet);
	}
	else {
		printf("Pet with age %d not found.\n", age);
	}
}

void saveShelterToTextFile(const Shelter* shelter, const char* filename) {
	if (!shelter || !filename) return;

	FILE* file = fopen(filename, "w");
	if (!file) return;

	fprintf(file, "%s,", shelter->name);
	saveAddressToTextFile(&shelter->address, file);

	fprintf(file, "%d\n", shelter->availablePets->size);
	Node* petNode = shelter->availablePets->head;
	while (petNode) {
		savePetToTextFile((Pet*)petNode->data, file);
		petNode = petNode->next;
	}

	fprintf(file, "%zu\n", shelter->donationCount);
	for (size_t i = 0; i < shelter->donationCount; i++) {
		saveDonationRecordToTextFile(shelter->donationRecords[i], file);
	}

	fprintf(file, "%zu\n", shelter->volunteerCount);
	for (size_t i = 0; i < shelter->volunteerCount; i++) {
		saveVolunteerToTextFile(shelter->volunteers[i], file);
	}

	fprintf(file, "%d\n", shelter->adoptionRequests->size);
	Node* requestNode = shelter->adoptionRequests->head;
	while (requestNode) {
		saveAdoptionRequestToTextFile((AdoptionRequest*)requestNode->data, file);
		requestNode = requestNode->next;
	}

	fclose(file);
}

Shelter* loadShelterFromTextFile(const char* filename) {
	if (!filename) return NULL;

	FILE* file = fopen(filename, "r");
	if (!file) return NULL;

	Shelter* shelter = (Shelter*)malloc(sizeof(Shelter));
	if (!shelter) {
		fclose(file);
		return NULL;
	}

	shelter->name = (char*)malloc(100 * sizeof(char));
	if (!shelter->name) {
		free(shelter);
		fclose(file);
		return NULL;
	}

	if (fscanf(file, "%[^,],", shelter->name) != 1) {
		free(shelter->name);
		free(shelter);
		fclose(file);
		return NULL;
	}

	shelter->address = loadAddressFromTextFile(file);

	int availablePetsCount;
	if (fscanf(file, "%d\n", &availablePetsCount) != 1) {
		free(shelter->name);
		free(shelter);
		fclose(file);
		return NULL;
	}

	shelter->availablePets = createLinkedList();
	for (int i = 0; i < availablePetsCount; i++) {
		Pet* pet = loadPetFromTextFile(file);
		if (!pet) {
			freeShelter(shelter);
			fclose(file);
			return NULL;
		}
		insertNode(shelter->availablePets, pet);
	}

	if (fscanf(file, "%zu\n", &shelter->donationCount) != 1) {
		freeShelter(shelter);
		fclose(file);
		return NULL;
	}

	shelter->donationCapacity = shelter->donationCount;
	if (shelter->donationCount > 0) {
		shelter->donationRecords = (DonationRecord**)malloc(shelter->donationCount * sizeof(DonationRecord*));
		if (!shelter->donationRecords) {
			printf("Failed to allocate memory for donation records.\n");
			freeShelter(shelter);
			fclose(file);
			return NULL;
		}
	}
	else {
		shelter->donationRecords = NULL;
	}

	for (size_t i = 0; i < shelter->donationCount; i++) {
		shelter->donationRecords[i] = loadDonationRecordFromTextFile(file);
		if (!shelter->donationRecords[i]) {
			for (size_t j = 0; j < i; j++) {
				freeDonationRecord(shelter->donationRecords[j]);
			}
			free(shelter->donationRecords);
			freeShelter(shelter);
			fclose(file);
			return NULL;
		}
	}

	if (fscanf(file, "%zu\n", &shelter->volunteerCount) != 1) {
		freeShelter(shelter);
		fclose(file);
		return NULL;
	}

	shelter->volunteerCapacity = shelter->volunteerCount;
	shelter->volunteers = (Volunteer**)malloc(shelter->volunteerCapacity * sizeof(Volunteer*));
	if (!shelter->volunteers) {
		freeShelter(shelter);
		fclose(file);
		return NULL;
	}

	for (size_t i = 0; i < shelter->volunteerCount; i++) {
		shelter->volunteers[i] = loadVolunteerFromTextFile(file);
		if (!shelter->volunteers[i]) {
			for (size_t j = 0; j < i; j++) {
				freeVolunteer(shelter->volunteers[j]);
			}
			free(shelter->volunteers);
			freeShelter(shelter);
			fclose(file);
			return NULL;
		}
	}

	int adoptionRequestsCount;
	if (fscanf(file, "%d\n", &adoptionRequestsCount) != 1) {
		freeShelter(shelter);
		fclose(file);
		return NULL;
	}

	shelter->adoptionRequests = createLinkedList();
	for (int i = 0; i < adoptionRequestsCount; i++) {
		AdoptionRequest* request = loadAdoptionRequestFromTextFile(file);
		if (!request) {
			freeShelter(shelter);
			fclose(file);
			return NULL;
		}
		insertNode(shelter->adoptionRequests, request);
	}

	fclose(file);

	return shelter;
}

void saveShelterToBinaryFile(const Shelter* shelter, const char* filename) {
	if (!shelter || !filename) return;

	FILE* file = fopen(filename, "wb");
	if (!file) return;

	size_t nameLength = strlen(shelter->name) + 1;
	fwrite(&nameLength, sizeof(nameLength), 1, file);
	fwrite(shelter->name, sizeof(char), nameLength, file);

	saveAddressToBinaryFile(&shelter->address, file);

	fwrite(&shelter->availablePets->size, sizeof(shelter->availablePets->size), 1, file);
	Node* petNode = shelter->availablePets->head;
	while (petNode) {
		savePetToBinaryFile((Pet*)petNode->data, file);
		petNode = petNode->next;
	}

	fwrite(&shelter->donationCount, sizeof(shelter->donationCount), 1, file);
	for (size_t i = 0; i < shelter->donationCount; i++) {
		saveDonationRecordToBinaryFile(shelter->donationRecords[i], file);
	}

	fwrite(&shelter->volunteerCount, sizeof(shelter->volunteerCount), 1, file);
	for (size_t i = 0; i < shelter->volunteerCount; i++) {
		saveVolunteerToBinaryFile(shelter->volunteers[i], file);
	}

	fwrite(&shelter->adoptionRequests->size, sizeof(shelter->adoptionRequests->size), 1, file);
	Node* requestNode = shelter->adoptionRequests->head;
	while (requestNode) {
		saveAdoptionRequestToBinaryFile((AdoptionRequest*)requestNode->data, file);
		requestNode = requestNode->next;
	}

	fclose(file);
}

Shelter* loadShelterFromBinaryFile(const char* filename){
	if (!filename) return NULL;

	FILE* file = fopen(filename, "rb");
	if (!file) return NULL;

	Shelter* shelter = (Shelter*)malloc(sizeof(Shelter));
	if (!shelter) {
		fclose(file);
		return NULL;
	}

	size_t nameLength;
	fread(&nameLength, sizeof(nameLength), 1, file);
	shelter->name = (char*)malloc(nameLength);
	fread(shelter->name, sizeof(char), nameLength, file);

	shelter->address = loadAddressFromBinaryFile(file);

	int availablePetsCount;
	fread(&availablePetsCount, sizeof(availablePetsCount), 1, file);

	shelter->availablePets = createLinkedList();
	for (int i = 0; i < availablePetsCount; i++) {
		Pet* pet = loadPetFromBinaryFile(file);
		if (!pet) {
			freeShelter(shelter);
			fclose(file);
			return NULL;
		}
		insertNode(shelter->availablePets, pet);
	}

	fread(&shelter->donationCount, sizeof(shelter->donationCount), 1, file);

	shelter->donationCapacity = shelter->donationCount;
	shelter->donationRecords = (DonationRecord**)malloc(shelter->donationCount * sizeof(DonationRecord*));
	if (!shelter->donationRecords) {
		printf("Failed to allocate memory for donation records.\n");
		freeShelter(shelter);
		fclose(file);
		return NULL;
	}

	for (size_t i = 0; i < shelter->donationCount; i++) {
		shelter->donationRecords[i] = loadDonationRecordFromBinaryFile(file);
		if (!shelter->donationRecords[i]) {
			for (size_t j = 0; j < i; j++) {
				freeDonationRecord(shelter->donationRecords[j]);
			}
			free(shelter->donationRecords);
			freeShelter(shelter);
			fclose(file);
			return NULL;
		}
	}

	fread(&shelter->volunteerCount, sizeof(shelter->volunteerCount), 1, file);

	shelter->volunteerCapacity = shelter->volunteerCount;
	shelter->volunteers = (Volunteer**)malloc(shelter->volunteerCapacity * sizeof(Volunteer*));
	if (!shelter->volunteers) {
		freeShelter(shelter);
		fclose(file);
		return NULL;
	}

	for (size_t i = 0; i < shelter->volunteerCount; i++) {
		shelter->volunteers[i] = loadVolunteerFromBinaryFile(file);
		if (!shelter->volunteers[i]) {
			for (size_t j = 0; j < i; j++) {
				freeVolunteer(shelter->volunteers[j]);
			}
			free(shelter->volunteers);
			freeShelter(shelter);
			fclose(file);
			return NULL;
		}
	}

	int adoptionRequestsCount;
	fread(&adoptionRequestsCount, sizeof(adoptionRequestsCount), 1, file);

	shelter->adoptionRequests = createLinkedList();
	for (int i = 0; i < adoptionRequestsCount; i++) {
		AdoptionRequest* request = loadAdoptionRequestFromBinaryFile(file);
		if (!request) {
			freeShelter(shelter);
			fclose(file);
			return NULL;
		}
		insertNode(shelter->adoptionRequests, request);
	}

	fclose(file);

	return shelter;
}

void sortMenu(Shelter* shelter) {
	int sortChoice;
	do {
		printf("Sort by:\n");
		printf("1. Name\n");
		printf("2. Type\n");
		printf("3. Age\n");
		printf("Enter your choice for sorting: ");
		if (scanf("%d", &sortChoice) != 1) {
			// Clear the input buffer if scanf fails
			while (getchar() != '\n');
			sortChoice = 0; // Set an invalid value to trigger the loop
		}
	} while (sortChoice < 1 || sortChoice > 3);

	switch (sortChoice) {
	case 1:
		sortPetsByName(shelter->availablePets);
		break;
	case 2:
		sortPetsByType(shelter->availablePets);
		break;
	case 3:
		sortPetsByAge(shelter->availablePets);
		break;
	default:
		printf("Invalid sort choice.\n");
		break;
	}
}

void searchMenu(Shelter* shelter) {
	int searchChoice;
	printf("Search by:\n");
	printf("1. Name\n");
	printf("2. Type\n");
	printf("3. Age\n");
	printf("Enter your choice for searching: ");
	int numScanned = scanf("%d", &searchChoice);
	if (numScanned != 1) {
		fprintf(stderr, "Failed to read an integer.\n");
		while (getchar() != '\n');  // Clear the input buffer
	}


	switch (searchChoice) {
	case 1: searchByName(shelter); break;
	case 2: searchByType(shelter); break;
	case 3: searchByAge(shelter); break;
	default:
		printf("Invalid choice. Please try again.\n");
		searchMenu(shelter);
		break;
	}
}

void addPetToShelterIfExists(Shelter* myShelter) {
	if (myShelter) {
		Pet* newPet = createPetFromInput(); // Assume this function exists
		addPetToShelter(myShelter, newPet);
	}
	else {
		printf("Please create a shelter first.\n");
	}
}

void removePetFromShelterIfExists(Shelter* myShelter) {
	if (myShelter) {
		displayAvailablePets(myShelter);

		printf("Enter the ID of the pet to remove: ");
		int petId;
		int numScanned = scanf("%d", &petId);

		if (numScanned != 1) {
			fprintf(stderr, "Failed to read an integer for pet ID.\n");
			while (getchar() != '\n'); // Clear the input buffer
			return; // Or handle error differently
		}

		(void)getchar(); // Consume the newline character left by scanf

		int result = removePetFromShelter(myShelter, petId);

		if (result) {
			printf("Pet with ID %d has been removed from the shelter.\n", petId);
		}
		else {
			printf("No pet with ID %d found in the shelter.\n", petId);
		}
	}
	else {
		printf("No shelter exists. Please create a shelter first.\n");
	}
}

void createNewShelter(Shelter** myShelter) {
	if (*myShelter != NULL) {
		freeShelter(*myShelter); // Free the existing shelter before creating a new one
		*myShelter = NULL;
	}
	*myShelter = createShelterFromInput(); // Now, the shelter is kept for further operations
}

void addDonationToShelterIfExists(Shelter* myShelter) {
	if (myShelter) {
		DonationRecord* newDonation = createDonationRecordFromInput();
		addDonationToShelter(myShelter, newDonation);
		printf("Donation added successfully to the shelter.\n");
	}
	else {
		printf("No shelter exists. Please create a shelter first.\n");
	}
}

void addVolunteerToShelterIfExists(Shelter* myShelter) {
	if (myShelter) {
		Volunteer* newVolunteer = createVolunteerFromInput();
		if (newVolunteer) {
			addVolunteerToShelter(myShelter, newVolunteer);
			printf("Volunteer '%s' added successfully to the shelter.\n", newVolunteer->name);
		}
		else {
			printf("Failed to add the volunteer.\n");
		}
	}
	else {
		printf("No shelter exists. Please create a shelter first.\n");
	}
}

void removeVolunteerFromShelterIfExists(Shelter* myShelter) {
	if (myShelter) {
		if (myShelter->volunteerCount > 0) {
			removeVolunteerFromShelter(myShelter);
		}
		else {
			printf("There are currently no volunteers in the shelter to remove.\n");
		}
	}
	else {
		printf("No shelter exists. Please create a shelter first.\n");
	}
}


void addTrainingCommandIfShelterExists(Shelter* myShelter) {
	if (myShelter) {
		addTrainingCommand(myShelter);
	}
	else {
		printf("No shelter exists. Please create a shelter first.\n");
	}
}

void showTrainingCommandsIfShelterExists(Shelter* myShelter) {
	if (myShelter) {
		showTrainingCommands(myShelter);
	}
	else {
		printf("No shelter exists. Please create a shelter first.\n");
	}
}

void showTrainingTipIfShelterExists(Shelter* myShelter) {
	if (myShelter) {
		showTrainingTip(myShelter);
	}
	else {
		printf("No shelter exists. Please create a shelter first.\n");
	}
}

void showSortMenuIfShelterExists(Shelter* myShelter) {
	if (myShelter) {
		sortMenu(myShelter);
	}
	else {
		printf("No shelter exists. Please create a shelter first.\n");
	}
}

void showSearchMenuIfShelterExists(Shelter* myShelter) {
	if (myShelter) {
		searchMenu(myShelter);
	}
	else {
		printf("No shelter exists. Please create a shelter first.\n");
	}
}

void displayShelterIfExists(Shelter* myShelter) {
	if (myShelter) {
		displayShelter(myShelter);
	}
	else {
		printf("No shelter exists. Please create a shelter first.\n");
	}
}

void processAdoptionRequestIfShelterExists(Shelter* myShelter) {
	if (myShelter) {
		printf("Enter Pet Owner ID (numbers only): ");
		int ownerId;
		int numScanned = scanf("%d", &ownerId);
		if (numScanned != 1) {
			fprintf(stderr, "Failed to read an integer for owner ID.\n");
			while (getchar() != '\n'); // Clear the input buffer
			return; // Or handle error differently
		}
		(void)getchar(); // Consume the newline character

		PetOwner* foundOwner = findPetOwnerByIdFromAdoptionRequests(myShelter, ownerId);
		if (foundOwner != NULL) {
			printf("Pet owner found:\n");
			displayPetOwnerDetails(foundOwner);
		}
		else {
			printf("Pet owner with ID %d not found in adoption requests.\n", ownerId);
			printf("Registering as a new pet owner...\n");
			foundOwner = createPetOwnerFromInput();
		}

		Pet* selectedPet = selectPetFromShelter(myShelter);
		if (selectedPet != NULL) {
			printf("Selected pet:\n");
			displayPetDetails(selectedPet);

			// Generate a unique request ID (you can use a different approach if needed)
			int requestId = myShelter->adoptionRequests->size + 1;

			// Get the current date
			Date currentDate = getCurrentDate();

			// Create a new AdoptionRequest
			AdoptionRequest* newRequest = createAdoptionRequest(requestId, foundOwner, selectedPet, currentDate);
			processAdoptionRequest(myShelter, newRequest);
		}
		else {
			printf("No pet selected for adoption.\n");
		}
	}
	else {
		printf("No shelter exists. Please create a shelter first.\n");
	}
}

Pet* selectPetFromShelter(Shelter* shelter) {
	if (shelter && shelter->availablePets && shelter->availablePets->head) {
		displayAvailablePets(shelter);

		printf("Enter the ID of the pet you want to select: ");
		int petId;
		if (scanf("%d", &petId) != 1) {
			printf("Invalid input. Please enter a valid pet ID.\n");
			while (getchar() != '\n');  // Clear input buffer
			return NULL;
		}
		(void)getchar(); // Consume the newline character left by scanf and ignore the return value

		Node* current = shelter->availablePets->head;
		while (current != NULL) {
			Pet* pet = (Pet*)current->data;
			if (pet->id == petId) {
				return pet;
			}
			current = current->next;
		}
	}
	printf("Pet not found.\n");
	return NULL;
}
