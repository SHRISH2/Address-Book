

Address Book System
A robust, file-based Address Book Management System implemented in C. This project manages contact information using a modular approach, ensuring data persistence by storing entries in a structured text file.

🚀 Features
Create Contacts: Add new entries with name, phone number, and email.

Search Functionality: Quickly find contacts using specific attributes.

Edit & Update: Modify existing contact details with real-time file synchronization.

Delete Records: Remove outdated contacts from the database.

Data Persistence: All information is saved to contacts.txt, allowing data to stay intact after the program exits.

Input Validation: Basic checks for phone number formats and email structures.

🛠️ Technical Implementation
The project is structured into modular components to follow best practices in software engineering:

main.c: The entry point containing the menu-driven user interface.

contact.c / contact.h: Handles the core logic for contact manipulation and data structures.

file.c / file.h: Manages all file I/O operations (Loading from/Saving to disk).

contacts.txt: The flat-file database used for storing information.

💻 How to Run
Prerequisites
A C compiler (GCC recommended).

Standard Make tools (optional).

Compilation
Navigate to the project directory and compile using GCC:

Bash
gcc main.c contact.c file.c -o address_book
Execution
Run the compiled binary:

Bash
./address_book
📂 Project Structure
Plaintext
.
├── main.c          # UI and Menu Logic
├── contact.c       # Contact Management Logic
├── contact.h       # Contact Definitions & Prototypes
├── file.c          # File Handling Logic
├── file.h          # File Handling Prototypes
├── contacts.txt    # Data Storage File
└── .gitignore      # Git exclusion rules