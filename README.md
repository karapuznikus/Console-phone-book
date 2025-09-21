# Console Phone Book (C)

## Description
A simple console application for managing a phone book. Users can add, remove, search, and view contacts. Data is persisted to a text file between sessions.

## Requirements
- **Compiler**: GCC (GNU Compiler Collection)
- **Operating System**: Windows, Linux(don't tested run), or macOS(don't tested run)
- **No external libraries required**

## Installation and Setup

### On Windows:
1. Install [MinGW-w64](https://www.mingw-w64.org/) to get `gcc`.
2. Add the `bin` folder (e.g., `C:\mingw64\bin`) to your system `PATH`.
3. Verify installation:
   ```cmd
   gcc --version
### On Linux (Ubuntu/Debian):
   sudo apt update && sudo apt install gcc
### On MacOS:
   Install Xcode Command Line Tools:
      xcode-select --install
### How to Run:
   1. Clone or download this repository.
   2. Open a terminal in the project directory.
   3. Compile the program:
      **gcc -o phonebook phonebook.c** (**gcc -o phonebook.exe phonebook.c**(For surely start))
   4. Windows:
        1. open cmd.exe
        2. chcp 65001 (sets the console encoding to UTF-8, ensuring correct display of Cyrillic characters.)
        3. cd /d "Путь к phonebook.exe"
        4. phonebook.exe 
      Linux/MacOS:
        1. open terminal/console
        2. ./phonebook
### Features:
   1. Add Contact: Enter first name, last name, phone, and email. The program checks for duplicate phone numbers.
   2. Remove Contact: Search by name or phone number, with confirmation before deletion.
   3. Search Contact: Find by first name, last name, or part of the phone number.
   4. View All Contacts: Displays all contacts. Offers optional sorting by first or last name.
   5. Save/Load: Contacts are saved to contacts.txt and loaded from it on startup. The file is created automatically on first save.
### File Structure:
   1. phonebook.c: Source code.
   2. contacts.txt: Data file (created automatically by the program).