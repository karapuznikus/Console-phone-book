# Console Phone Book (C)

## Description
A simple console application for managing a phone book. Users can add, remove, search, and view contacts. Data is persisted to a text file between sessions.

## Requirements
- **Compiler**: cmd.exe (+ GCC (GNU Compiler Collection) + VS code - if you want compile by yourself)
- **Operating System**: Windows
- **No external libraries required**

## Installation and Setup

### On Windows (just for start and use):
1. Install ENG version phonebook.exe(for avoid problems with cmd)
2. Place in any empty folder
3. Start phonebook.exe
### If you want compile program by yourself:
1. Download [MinGW-w64](https://www.mingw-w64.org/) to get `gcc`
2. Add the `bin` folder (e.g., `C:\mingw64\bin`) to your system `PATH`.
3. Verify installation:
   ```cmd
   gcc --version
4. Compile the program:
      **gcc -o phonebook.exe phonebook.c**
5. Use phonebook.exe
### Features:
   1. Add Contact: Enter first name, last name, phone, and email. The program checks for duplicate phone numbers.
   2. Remove Contact: Search by name or phone number, with confirmation before deletion.
   3. Search Contact: Find by first name, last name, or part of the phone number.
   4. View All Contacts: Displays all contacts. Offers optional sorting by first or last name.
   5. Save/Load: Contacts are saved to `contacts.txt` and loaded from it on startup. The file is created automatically on first save.
### File Structure:
   1. phonebook.c: Source code.
   2. phonebook.exe: Already ready to start
   2. contacts.txt: Data file (created automatically by the program).