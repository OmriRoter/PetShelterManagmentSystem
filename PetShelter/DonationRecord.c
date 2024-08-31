// DonationRecord.c
#define _CRT_SECURE_NO_WARNINGS
#include "DonationRecord.h"
#include "Utility.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

DonationRecord* createDonationRecord(int recordId, const char* donorName, double amount, Date donationDate) {
    DonationRecord* newRecord = (DonationRecord*)malloc(sizeof(DonationRecord));
    CHECK_ALLOCATION(newRecord);

    newRecord->recordId = recordId;
    newRecord->donorName = _strdup(donorName);
    newRecord->amount = amount;
    newRecord->donationDate = donationDate;

    return newRecord;
}

void displayDonationRecord(const DonationRecord* record) {
    if (!record) {
        UPPER_PRINT_DIVIDER();
        printf("No Donation Record Available.\n");
        LOWER_PRINT_DIVIDER();
        return;
    }

    UPPER_PRINT_DIVIDER();
    printf("Donation Record Details:\n");
    UPPER_PRINT_DIVIDER();    printf("Donation Record ID: %d\n", record->recordId);
    printf("Donor Name: %s\n", record->donorName);
    printf("Donation Amount: $%.2f\n", record->amount);
    printf("Donation Date: %d-%d-%d\n", record->donationDate.day, record->donationDate.month, record->donationDate.year);
    LOWER_PRINT_DIVIDER();
}

void freeDonationRecord(DonationRecord* record) {
    if (record) {
        free(record->donorName);
        free(record);
    }
}

DonationRecord* createDonationRecordFromInput() {
    int recordId;
    char donorName[DONOR_NAME_SIZE];
    double amount;
    Date donationDate;

    UPPER_PRINT_DIVIDER();
    printf("New Donation Record Entry\n");
    UPPER_PRINT_DIVIDER();

    printf("Enter Donation Record ID: ");
    if (scanf("%d", &recordId) != 1) {
        printf("Invalid input for Donation Record ID.\n");
        return NULL;
    }
    clearInputBuffer(); // Clear the input buffer after reading the record ID

    UPPER_PRINT_DIVIDER();
    printf("Enter Donor Name: ");
    fgets(donorName, sizeof(donorName), stdin);
    donorName[strcspn(donorName, "\n")] = 0; // Remove the newline character

    UPPER_PRINT_DIVIDER();
    printf("Enter Donation Amount: ");
    if (scanf("%lf", &amount) != 1) {
        printf("Invalid input for Donation Amount.\n");
        return NULL;
    }
    clearInputBuffer(); // Clear the input buffer after reading the donation amount

    UPPER_PRINT_DIVIDER();
    printf("Enter Donation Date:\n");
    donationDate = createDateFromInput();  // Assuming this function is also structured for user input

    UPPER_PRINT_DIVIDER();
    printf("Thank you for entering the donation details.\n");
    LOWER_PRINT_DIVIDER();

    return createDonationRecord(recordId, donorName, amount, donationDate);
}

void saveDonationRecordToTextFile(const DonationRecord* record, FILE* file) {
    if (!record || !file) return;

    fprintf(file, "%d,%s,%lf,", record->recordId, record->donorName, record->amount);
    saveDateToTextFile(&record->donationDate, file);
    fprintf(file, "\n");
}

DonationRecord* loadDonationRecordFromTextFile(FILE* file) {
    if (!file) return NULL;

    DonationRecord* record = (DonationRecord*)malloc(sizeof(DonationRecord));
    CHECK_ALLOCATION(record);

    record->donorName = (char*)malloc(DONOR_NAME_SIZE * sizeof(char)); // Adjust size as needed
    if (!record->donorName) {
        free(record);
        return NULL;
    }

    if (fscanf(file, "%d,%[^,],%lf,", &record->recordId, record->donorName, &record->amount) != 3) {
        free(record->donorName);
        free(record);
        return NULL;
    }

    record->donationDate = loadDateFromTextFile(file);

    return record;
}

void saveDonationRecordToBinaryFile(const DonationRecord* record, FILE* file) {
    if (!record || !file) return;

    fwrite(&record->recordId, sizeof(record->recordId), 1, file);

    int nameLength = (int)(strlen(record->donorName) + 1);
    fwrite(&nameLength, sizeof(nameLength), 1, file);
    fwrite(record->donorName, sizeof(char), nameLength, file);

    fwrite(&record->amount, sizeof(record->amount), 1, file);
    saveDateToBinaryFile(&record->donationDate, file);
}

DonationRecord* loadDonationRecordFromBinaryFile(FILE* file) {
    if (!file) return NULL;

    DonationRecord* record = (DonationRecord*)malloc(sizeof(DonationRecord));
    if (!record) return NULL;

    fread(&record->recordId, sizeof(record->recordId), 1, file);

    int nameLength;
    fread(&nameLength, sizeof(nameLength), 1, file);

    record->donorName = (char*)malloc(nameLength);
    if (!record->donorName) {
        free(record);
        return NULL;
    }

    fread(record->donorName, sizeof(char), nameLength, file);

    fread(&record->amount, sizeof(record->amount), 1, file);

    record->donationDate = loadDateFromBinaryFile(file);

    return record;
}

