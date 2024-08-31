#pragma once
#ifndef MAIN_H
#define MAIN_H

#include "Date.h"
#include "Address.h"
#include "LinkedList.h"
#include "Pet.h"
#include "PetOwner.h"
#include "Shelter.h"
#include "AdoptionRequest.h"
#include "DonationRecord.h"
#include "Volunteer.h"
#include "PetMedicalRecord.h"
#include "Utility.h"
#include "CommandRecord.h"
#include "LinkedList.h"

#include <crtdbg.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <direct.h> // Include for Windows
#define mkdir(path) _mkdir(path) // Redefine mkdir to use _mkdir for Windows
#else
#include <sys/stat.h> // Include for Unix/Linux
#define mkdir(path, mode) mkdir(path, mode) // Use standard mkdir with mode for Unix/Linux
#endif


void updatePetMedicalRecordIfShelterExists(Shelter* myShelter);
Shelter* loadProjectFromTextFile(const char* filename);
Shelter* loadProjectFromBinaryFile(const char* filename);
void SaveProject(Shelter* shelter);
void displayMenu();
void displayLoadProjectMenu(Shelter** shelter, const char* textFilename, const char* binFilename);

#endif