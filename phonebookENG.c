#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CONTACTS 100

typedef struct {
    char firstName[50];
    char lastName[50];
    char phone[20];
    char email[50];
} Contact;

Contact contacts[MAX_CONTACTS];
int contactCount = 0;

// Прототипы функций (объявления)
void add_contact();
void remove_contact();
void search_contact();
void print_contacts();
void save_contacts_to_file();
void load_contacts_from_file();
void show_menu();

// Функции сравнения
int compareByName(const void *a, const void *b) {
    Contact *contactA = (Contact *)a;
    Contact *contactB = (Contact *)b;
    return strcmp(contactA->firstName, contactB->firstName);
}

int compareByLastName(const void *a, const void *b) {
    Contact *contactA = (Contact *)a;
    Contact *contactB = (Contact *)b;
    return strcmp(contactA->lastName, contactB->lastName);
}

int main() {
    // Загружаем контакты из файла при запуске
    load_contacts_from_file();

    int choice;
    do {
        show_menu();
        printf("Enter the action number: ");
        scanf("%d", &choice);
        getchar(); // Очищаем буфер после scanf

        switch (choice) {
            case 1:
                add_contact();
                break;
            case 2:
                remove_contact();
                break;
            case 3:
                search_contact();
                break;
            case 4:
                print_contacts();
                break;
            case 5:
                save_contacts_to_file();
                break;
            case 6:
                load_contacts_from_file();
                break;
            case 0:
                printf("Goodbye!\n");
                break;
            default:
                printf("Wrong choice. Try again.\n");
        }
    } while (choice != 0);

    return 0;
}

void show_menu() {
    printf("\n=== Phone Book ===\n");
    printf("1 — Add a contact\n");
    printf("2 — Delete a contact\n");
    printf("3 — Find a contact\n");
    printf("4 — View all contacts\n");
    printf("5 — Save Contacts\n");
    printf("6 — Upload Contacts\n");
    printf("0 — Exit\n");
    printf("========================\n");
}

void add_contact() {
    if (contactCount >= MAX_CONTACTS) {
        printf("The phone book is full! You can't add more contacts.\n");
        return;
    }

    Contact newContact;

    printf("Enter name: ");
    fgets(newContact.firstName, sizeof(newContact.firstName), stdin);
    newContact.firstName[strcspn(newContact.firstName, "\n")] = 0; // Удаляем символ новой строки

    printf("Enter last name: ");
    fgets(newContact.lastName, sizeof(newContact.lastName), stdin);
    newContact.lastName[strcspn(newContact.lastName, "\n")] = 0;

    printf("Enter phone number: ");
    fgets(newContact.phone, sizeof(newContact.phone), stdin);
    newContact.phone[strcspn(newContact.phone, "\n")] = 0;

    printf("Enter email address: ");
    fgets(newContact.email, sizeof(newContact.email), stdin);
    newContact.email[strcspn(newContact.email, "\n")] = 0;

    // Проверка на дубликат по номеру телефона
    for (int i = 0; i < contactCount; i++) {
        if (strcmp(contacts[i].phone, newContact.phone) == 0) {
            printf("Error: A contact with this phone number already exists!\n");
            return;
        }
    }

    // Добавляем контакт
    contacts[contactCount] = newContact;
    contactCount++;
    printf("The contact has been added successfully!\n");
}

void remove_contact() {
    if (contactCount == 0) {
        printf("The phone book is empty.\n");
        return;
    }

    char searchKey[50];
    printf("Enter the name or phone number of the contact to delete: ");
    fgets(searchKey, sizeof(searchKey), stdin);
    searchKey[strcspn(searchKey, "\n")] = 0;

    int index = -1;
    // Ищем контакт
    for (int i = 0; i < contactCount; i++) {
        if (strcmp(contacts[i].firstName, searchKey) == 0 ||
            strcmp(contacts[i].phone, searchKey) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("The contact was not found.\n");
        return;
    }

    // Подтверждение удаления
    printf("Do you really want to delete the contact: %s %s? (y/n): ",
           contacts[index].firstName, contacts[index].lastName);
    char confirm;
    scanf(" %c", &confirm); // Пробел перед %c пропускает пробельные символы
    getchar(); // Очищаем буфер

    if (confirm == 'y' || confirm == 'Y') {
        // Сдвигаем все элементы на один влево
        for (int i = index; i < contactCount - 1; i++) {
            contacts[i] = contacts[i + 1];
        }
        contactCount--;
        printf("The contact was successfully deleted.\n");
    } else {
        printf("Deletion has been canceled.\n");
    }
}

void search_contact() {
    if (contactCount == 0) {
        printf("The phone book is empty.\n");
        return;
    }

    char query[50];
    printf("Enter the first name, last name, or part of the phone number to search: ");
    fgets(query, sizeof(query), stdin);
    query[strcspn(query, "\n")] = 0; // Удаляем '\n'

    int found = 0;
    printf("\n--- Search Results ---\n");
    for (int i = 0; i < contactCount; i++) {
        if (strstr(contacts[i].firstName, query) != NULL ||
            strstr(contacts[i].lastName, query) != NULL ||
            strstr(contacts[i].phone, query) != NULL) {
            printf("%d. %s %s | Телефон: %s | Email: %s\n",
                   i + 1,
                   contacts[i].firstName,
                   contacts[i].lastName,
                   contacts[i].phone,
                   contacts[i].email);
            found = 1;
        }
    }

    if (!found) {
        printf("No contacts found.\n");
    }
    printf("------------------------\n");
}

void print_contacts() {
    if (contactCount == 0) {
        printf("The phone book is empty.\n");
        return;
    }

    int sortChoice;
    printf("Sort by: 1 - First name, 2 - Last Name, 0 - Without sorting: ");
    scanf("%d", &sortChoice);
    getchar(); // Очищаем буфер после scanf

    // Создаем временную копию массива для сортировки
    Contact tempContacts[MAX_CONTACTS];
    for (int i = 0; i < contactCount; i++) {
        tempContacts[i] = contacts[i];
    }

    if (sortChoice == 1) {
        qsort(tempContacts, contactCount, sizeof(Contact), compareByName);
    } else if (sortChoice == 2) {
        qsort(tempContacts, contactCount, sizeof(Contact), compareByLastName);
    }

    printf("\n--- All contacts ---\n");
    for (int i = 0; i < contactCount; i++) {
        printf("%d. %s %s | Telephone: %s | Email: %s\n",
               i + 1,
               tempContacts[i].firstName,
               tempContacts[i].lastName,
               tempContacts[i].phone,
               tempContacts[i].email);
    }
    printf("--------------------\n");
}

void save_contacts_to_file() {
    FILE *file = fopen("contacts.txt", "w");
    if (file == NULL) {
        printf("Error: The file could not be opened for writing.\n");
        return;
    }

    fprintf(file, "%d\n", contactCount); // Сохраняем количество контактов

    for (int i = 0; i < contactCount; i++) {
        fprintf(file, "%s\n", contacts[i].firstName);
        fprintf(file, "%s\n", contacts[i].lastName);
        fprintf(file, "%s\n", contacts[i].phone);
        fprintf(file, "%s\n", contacts[i].email);
    }

    fclose(file);
    printf("Contacts have been successfully saved to a file 'contacts.txt '.\n");
}

void load_contacts_from_file() {
    FILE *file = fopen("contacts.txt", "r");
    if (file == NULL) {
        printf("The file 'contacts.txt' not found. A new phone book is being created.\n");
        contactCount = 0;
        return;
    }

    fscanf(file, "%d\n", &contactCount); // Читаем количество контактов

    for (int i = 0; i < contactCount; i++) {
        fgets(contacts[i].firstName, sizeof(contacts[i].firstName), file);
        contacts[i].firstName[strcspn(contacts[i].firstName, "\n")] = 0;

        fgets(contacts[i].lastName, sizeof(contacts[i].lastName), file);
        contacts[i].lastName[strcspn(contacts[i].lastName, "\n")] = 0;

        fgets(contacts[i].phone, sizeof(contacts[i].phone), file);
        contacts[i].phone[strcspn(contacts[i].phone, "\n")] = 0;

        fgets(contacts[i].email, sizeof(contacts[i].email), file);
        contacts[i].email[strcspn(contacts[i].email, "\n")] = 0;
    }

    fclose(file);
    printf("Contacts have been successfully uploaded from the file 'contacts.txt'.\n");
}