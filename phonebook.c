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
        printf("Введите номер действия: ");
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
                printf("До свидания!\n");
                break;
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 0);

    return 0;
}

void show_menu() {
    printf("\n=== Телефонная книга ===\n");
    printf("1 — Добавить контакт\n");
    printf("2 — Удалить контакт\n");
    printf("3 — Найти контакт\n");
    printf("4 — Просмотреть все контакты\n");
    printf("5 — Сохранить контакты\n");
    printf("6 — Загрузить контакты\n");
    printf("0 — Выход\n");
    printf("========================\n");
}

void add_contact() {
    if (contactCount >= MAX_CONTACTS) {
        printf("Телефонная книга заполнена! Нельзя добавить больше контактов.\n");
        return;
    }

    Contact newContact;

    printf("Введите имя: ");
    fgets(newContact.firstName, sizeof(newContact.firstName), stdin);
    newContact.firstName[strcspn(newContact.firstName, "\n")] = 0; // Удаляем символ новой строки

    printf("Введите фамилию: ");
    fgets(newContact.lastName, sizeof(newContact.lastName), stdin);
    newContact.lastName[strcspn(newContact.lastName, "\n")] = 0;

    printf("Введите номер телефона: ");
    fgets(newContact.phone, sizeof(newContact.phone), stdin);
    newContact.phone[strcspn(newContact.phone, "\n")] = 0;

    printf("Введите email: ");
    fgets(newContact.email, sizeof(newContact.email), stdin);
    newContact.email[strcspn(newContact.email, "\n")] = 0;

    // Проверка на дубликат по номеру телефона
    for (int i = 0; i < contactCount; i++) {
        if (strcmp(contacts[i].phone, newContact.phone) == 0) {
            printf("Ошибка: Контакт с таким номером телефона уже существует!\n");
            return;
        }
    }

    // Добавляем контакт
    contacts[contactCount] = newContact;
    contactCount++;
    printf("Контакт успешно добавлен!\n");
}

void remove_contact() {
    if (contactCount == 0) {
        printf("Телефонная книга пуста.\n");
        return;
    }

    char searchKey[50];
    printf("Введите имя или номер телефона контакта для удаления: ");
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
        printf("Контакт не найден.\n");
        return;
    }

    // Подтверждение удаления
    printf("Вы действительно хотите удалить контакт: %s %s? (y/n): ",
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
        printf("Контакт успешно удален.\n");
    } else {
        printf("Удаление отменено.\n");
    }
}

void search_contact() {
    if (contactCount == 0) {
        printf("Телефонная книга пуста.\n");
        return;
    }

    char query[50];
    printf("Введите имя, фамилию или часть номера телефона для поиска: ");
    fgets(query, sizeof(query), stdin);
    query[strcspn(query, "\n")] = 0; // Удаляем '\n'

    int found = 0;
    printf("\n--- Результаты поиска ---\n");
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
        printf("Контакты не найдены.\n");
    }
    printf("------------------------\n");
}

void print_contacts() {
    if (contactCount == 0) {
        printf("Телефонная книга пуста.\n");
        return;
    }

    int sortChoice;
    printf("Отсортировать по: 1 - Имени, 2 - Фамилии, 0 - Без сортировки: ");
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

    printf("\n--- Все контакты ---\n");
    for (int i = 0; i < contactCount; i++) {
        printf("%d. %s %s | Телефон: %s | Email: %s\n",
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
        printf("Ошибка: Не удалось открыть файл для записи.\n");
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
    printf("Контакты успешно сохранены в файл 'contacts.txt'.\n");
}

void load_contacts_from_file() {
    FILE *file = fopen("contacts.txt", "r");
    if (file == NULL) {
        printf("Файл 'contacts.txt' не найден. Создается новая телефонная книга.\n");
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
    printf("Контакты успешно загружены из файла 'contacts.txt'.\n");
}