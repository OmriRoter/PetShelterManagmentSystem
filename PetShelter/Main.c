#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC

#include <crtdbg.h>
#include <time.h>
#include <string.h>
#include<direct.h>
#include <time.h>
#include <errno.h>



#include "PetMedicalRecord.h"
#include "Shelter.h"


void updatePetMedicalRecordIfShelterExists(Shelter* myShelter);
Shelter* loadProjectFromTextFile(const char* filename);
Shelter* loadProjectFromBinaryFile(const char* filename);
void SaveProject(Shelter* shelter);
void displayMenu();
void displayLoadProjectMenu(Shelter** shelter, const char* textFilename, const char* binFilename);



int main() {
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    Shelter* myShelter = NULL;
    const char* myShelterFilenameText = "shelter.txt";
    const char* myShelterFilenameBin = "shelter.bin";

    int choice;
    do {
        displayMenu();
        int numScanned = scanf("%d", &choice);
        if (numScanned != 1) {
            fprintf(stderr, "Failed to read an integer.\n");
            while (getchar() != '\n');  // Clear the input buffer
            continue;  // Go to the next iteration of the loop or handle error differently
        }
        (void)getchar(); // To consume the newline character left by scanf
        printf("\n");

        switch (choice) {
        case 1:
            displayLoadProjectMenu(&myShelter, myShelterFilenameText, myShelterFilenameBin);
            break;
        case 2:
            createNewShelter(&myShelter);
            break;
        case 3:
            addPetToShelterIfExists(myShelter);
            break;
        case 4:
            removePetFromShelterIfExists(myShelter);
            break;
        case 5:
            addDonationToShelterIfExists(myShelter);
            break;
        case 6:
            addVolunteerToShelterIfExists(myShelter);
            break;
        case 7:
            removeVolunteerFromShelterIfExists(myShelter);
        break;
        case 8:
            updatePetMedicalRecordIfShelterExists(myShelter);
            break;
        case 9:
            addTrainingCommandIfShelterExists(myShelter);
            break;
        case 10:
            showTrainingCommandsIfShelterExists(myShelter);
            break;
        case 11:
            showTrainingTipIfShelterExists(myShelter);
            break;
        case 12:
            showSortMenuIfShelterExists(myShelter);
            break;
        case 13:
            showSearchMenuIfShelterExists(myShelter);
            break;
        case 14:
            displayShelterIfExists(myShelter);
            break;
        case 15:
            processAdoptionRequestIfShelterExists(myShelter);
            break;
        case 16:
            SaveProject(myShelter);
            printf("Exsiting... goodbye...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 16);

    // Cleanup before exiting
    if (myShelter) {
        freeShelter(myShelter);
    }
    printf("before dump\n");
    _CrtDumpMemoryLeaks();

    return 0;
}

Shelter* loadProjectFromTextFile(const char* filename) {
    Shelter* loadedShelter = loadShelterFromTextFile(filename);
    if (loadedShelter == NULL) {
        printf("Failed to load the shelter from '%s'.\n", filename);
    }
    else {
        printf("Shelter loaded successfully from '%s'.\n", filename);
    }
    return loadedShelter;
}

Shelter* loadProjectFromBinaryFile(const char* filename) {
    Shelter* loadedShelter = loadShelterFromBinaryFile(filename);
    if (loadedShelter == NULL) {
        printf("Failed to load the shelter from '%s'.\n", filename);
    }
    else {
        printf("Shelter loaded successfully from '%s'.\n", filename);
    }
    return loadedShelter;
}

void SaveProject(Shelter* shelter) {
    if (shelter == NULL) {
        printf("No shelter data available to save.\n");
        return;
    }

    const char* shelterFilename = "shelter.txt";
    saveShelterToTextFile(shelter, shelterFilename);
    printf("Shelter saved successfully to text file '%s'.\n", shelterFilename);

    const char* binaryShelterFilename = "shelter.bin";
    saveShelterToBinaryFile(shelter, binaryShelterFilename);
    printf("Shelter saved successfully to binary file '%s'.\n", binaryShelterFilename);
}

void displayMenu() {
    printf("\nPet Shelter Management System\n");
    printf("1. Load the project from files\n");
    printf("2. Create a new shelter\n");
    printf("3. Add a pet to the shelter\n");
    printf("4. Remove a pet from the shelter\n");
    printf("5. Add a donation to the shelter\n");
    printf("6. Add a volunteer to the shelter\n");
    printf("7. Remove a volunteer from the shelter\n");
    printf("8. Add/update a pet's medical condition\n");
    printf("9. Add a training command for a certain pet\n");
    printf("10. Show the commands that a pet knows how to perform\n");
    printf("11. Show a training tip for a particular pet\n");
    printf("12. Sorting\n");
    printf("13. Searching\n");
    printf("14. Show shelter details\n");
    printf("15. Process an adoption request\n");
    printf("16. Exit\n");
    printf("Enter your choice:");
}

void displayLoadProjectMenu(Shelter** shelter, const char* textFilename, const char* binfilename) {
    int choice;
    printf("Choose file format:\n");
    printf("1. Text file\n");
    printf("2. Binary file\n");
    printf("Enter your choice: ");

    int numScanned = scanf("%d", &choice);
    if (numScanned != 1) {
        fprintf(stderr, "Failed to read an integer.\n");
        while (getchar() != '\n');  // Clear the input buffer
        return;  // Return without loading anything
    }
    (void)getchar(); // To consume the newline character left by scanf

    switch (choice) {
    case 1:
        *shelter = loadProjectFromTextFile(textFilename);
        break;
    case 2:
        *shelter = loadProjectFromBinaryFile(binfilename);
        break;
    default:
        printf("Invalid file format choice.\n");
    }
}

void updatePetMedicalRecordIfShelterExists(Shelter* myShelter) {
    if (myShelter) {
        Pet* selectedPet = selectPetFromShelter(myShelter);
        if (selectedPet) {
            PetMedicalRecord* petMedRecord = createPetMedicalRecordFromInput(selectedPet);
            if (petMedRecord) {
                printf("Pet medical record updated successfully.\n");
                displayPetMedicalRecordDetails(petMedRecord);

                // Create a folder for the pet's ID if it doesn't exist
                char folderName[100];
                snprintf(folderName, sizeof(folderName), "pet_%d", selectedPet->id);

                // Adjusting mkdir based on platform
#ifdef _WIN32
                int result = _mkdir(folderName);  // Use _mkdir for Windows which takes only the path
#else
                int result = mkdir(folderName, 0777);  // Use mkdir with mode on Unix/Linux
#endif

                if (result == 0 || errno == EEXIST) {
                    // Generate a unique filename for the medical record
                    char filename[100];
                    snprintf(filename, sizeof(filename), "%s/medical_record_%d.txt", folderName, (int)time(NULL));

                    FILE* file = fopen(filename, "w");
                    if (file) {
                        savePetMedicalRecordToTextFile(petMedRecord, file);
                        fclose(file);
                        printf("Pet medical record saved to file: %s\n", filename);
                    }
                    else {
                        printf("Failed to open file for saving pet medical record.\n");
                    }
                }
                else {
                    printf("Failed to create folder for pet medical records. Error: %s\n", strerror(errno));
                }

                freePetMedicalRecord(petMedRecord); // Free the memory
            }
            else {
                printf("Failed to update pet medical record.\n");
            }
        }
    }
    else {
        printf("No shelter exists. Please create a shelter first.\n");
    }
}