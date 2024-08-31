# Pet Shelter Management System

## Project Overview
The **Pet Shelter Management System** is a software application designed to efficiently manage various operations within a pet shelter. This system includes modules for handling animal records, adoption processes, volunteer management, and more. It is built using C and provides a robust command-line interface for shelter administrators to manage their operations effectively.

## Features
- **Animal Management**: 
  - **Pet Module (`Pet.c`, `Pet.h`)**: Manage pet details such as species, breed, age, and medical records.
  - **Pet Medical Records (`PetMedicalRecord.c`, `PetMedicalRecord.h`)**: Maintain a detailed medical history for each pet.
  - **Pet Owner Management (`PetOwner.c`, `PetOwner.h`)**: Manage information related to pet owners.

- **Adoption Management**:
  - **Adoption Request Module (`AdoptionRequest.c`, `AdoptionRequest.h`)**: Handle the processing and tracking of adoption requests.

- **Volunteer Management**:
  - **Volunteer Module (`Volunteer.c`, `Volunteer.h`)**: Record and manage volunteer details and contributions.

- **Shelter Operations**:
  - **Shelter Module (`Shelter.c`, `Shelter.h`)**: Oversee the general management of the shelter's activities.
  - **Inventory and Donations (`DonationRecord.c`, `DonationRecord.h`)**: Track donations and inventory related to the shelter.
  - **Address Management (`Address.c`, `Address.h`)**: Maintain and handle address-related data.
  - **Command History (`CommandRecord.c`, `CommandRecord.h`)**: Keep a record of commands executed within the system.

- **Utility Functions**:
  - **Date Handling (`Date.c`, `Date.h`)**: Manage date-related operations.
  - **Linked List Implementation (`LinkedList.c`, `LinkedList.h`)**: A custom linked list data structure used within the application.
  - **Miscellaneous Utilities (`Utility.c`, `Utility.h`)**: General utility functions used throughout the project.

- **Training and Tips**:
  - **Training Tips Module (`TrainingTips.c`, `TrainingTipsData.h`)**: Provide training tips and guidance within the system.

## Technologies Used
- **Programming Language**: C
- **Development Environment**: Visual Studio (Project files: `PetShelter.vcxproj`, `PetShelter.vcxproj.filters`, etc.)
- **Data Storage**: Binary files (`shelter.bin`) and text files (`shelter.txt`).

## Installation and Setup

### Prerequisites
- Ensure you have a C compiler installed.
- The project is developed using Visual Studio; it is recommended to use the same or compatible IDE for the best experience.

### Setup Steps

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/OmriRoter/PetShelterManagmentSystem.git
   ```

2. **Open the Project in Visual Studio**:
   - Open the `.vcxproj` file in Visual Studio.

3. **Build the Project**:
   - Build the solution to compile all the source files.

4. **Run the Application**:
   - Execute the built binary through Visual Studio's debugger or directly from the command line.

## Usage
The Pet Shelter Management System can be run from the command line or through the Visual Studio environment. The system allows you to perform tasks such as:

- Adding and managing pet records.
- Processing adoption requests.
- Tracking volunteer contributions.
- Managing inventory and donations.
- Generating reports and accessing training tips.

## Project Structure

- **Source Files**: Located in the root directory, includes all the C files implementing the core functionality.
- **Headers**: Header files defining structures and functions are paired with their respective source files.
- **Data Files**: Binary and text files used for storing persistent data (e.g., `shelter.bin`, `shelter.txt`).
- **Visual Studio Files**: Project and build configuration files (`.vcxproj`, `.filters`, `.user`).

## Contributing
Contributions to the Pet Shelter Management System are welcome. Please follow these steps to contribute:

1. Fork the repository.
2. Create a new branch for your feature or bug fix:
   ```bash
   git checkout -b feature-branch-name
   ```
3. Implement your changes.
4. Commit your changes with descriptive messages:
   ```bash
   git commit -m "Add feature/fix bug: description"
   ```
5. Push your branch to GitHub:
   ```bash
   git push origin feature-branch-name
   ```
6. Open a pull request on GitHub.

## License
This project is licensed under the MIT License. Please see the `LICENSE` file for more details.

## Contact
For any inquiries or further information, please contact Omri Roter at Omri99Roter@gmail.com.
