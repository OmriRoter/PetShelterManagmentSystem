#ifndef DONATIONRECORD_H
#define DONATIONRECORD_H

#include "Date.h"
#include "stdio.h"
#include "Utility.h"

#define DONOR_NAME_SIZE 100


/**
 * @struct DonationRecord
 * @brief Represents a donation record.
 */
typedef struct {
    int recordId;           /**< Donation record ID */
    char* donorName;        /**< Name of the donor */
    double amount;          /**< Amount of the donation */
    Date donationDate;      /**< Date of the donation */
} DonationRecord;

/**
 * @brief Creates a new donation record with the given details.
 * @param recordId The donation record ID.
 * @param donorName The name of the donor.
 * @param amount The amount of the donation.
 * @param donationDate The date of the donation.
 * @return A pointer to the newly created donation record, or NULL if memory allocation fails.
 */
DonationRecord* createDonationRecord(int recordId, const char* donorName, double amount, Date donationDate);

/**
 * @brief Displays the details of a donation record.
 * @param record The donation record to display.
 */
void displayDonationRecord(const DonationRecord* record);

/**
 * @brief Frees the memory allocated for a donation record.
 * @param record The donation record to free.
 */
void freeDonationRecord(DonationRecord* record);
/**
 * @brief Creates a donation record from user input.
 * @return A pointer to the newly created donation record, or NULL if memory allocation fails or if the input is invalid.
 */
DonationRecord* createDonationRecordFromInput();

void saveDonationRecordToTextFile(const DonationRecord* record, FILE* file);
DonationRecord* loadDonationRecordFromTextFile(FILE* file);

void saveDonationRecordToBinaryFile(const DonationRecord* record, FILE* file);

DonationRecord* loadDonationRecordFromBinaryFile(FILE* file);


#endif // DONATIONRECORD_H