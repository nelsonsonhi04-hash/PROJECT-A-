#include <stdio.h>
#include <string.h>
#include "suppliers.h"

Supplier suppliers[MAX_SUPPLIERS];
int supplierCount = 0;

int findSupplierById(const char *id)
{
    int i;
    for (i = 0; i < supplierCount; i++) {
        if (strcmp(suppliers[i].id, id) == 0)
            return i;
    }
    return -1;
}

static void printSupplierRow(const Supplier *s)
{
    printf("%-8s %-22s %-26s %-14s %-12s\n",
           s->id, s->name, s->email, s->phone, s->town);
}

void addSupplier(void)
{
    Supplier s;
    char id[MAX_TEXT];

    if (supplierCount >= MAX_SUPPLIERS) {
        printf("Supplier list is full.\n");
        return;
    }

    printf("\n--- Add Supplier ---\n");
    while (1) {
        readNonEmpty("Supplier ID (e.g. S001): ", id, sizeof(id));
        if (findSupplierById(id) != -1)
            printf("  Error: supplier ID already exists.\n");
        else
            break;
    }
    strcpy(s.id, id);
    readNonEmpty("Supplier name: ", s.name, sizeof(s.name));

    while (1) {
        readNonEmpty("Email: ", s.email, sizeof(s.email));
        if (isValidEmail(s.email))
            break;
        printf("  Error: invalid email (example: name@company.com).\n");
    }
    while (1) {
        readNonEmpty("Telephone number: ", s.phone, sizeof(s.phone));
        if (isValidPhone(s.phone))
            break;
        printf("  Error: phone must be 7-15 digits (optional leading +).\n");
    }
    readNonEmpty("Town/Location: ", s.town, sizeof(s.town));

    suppliers[supplierCount++] = s;
    printf("Supplier '%s' added successfully.\n", s.name);
}

void displaySuppliers(void)
{
    int i;

    printf("\n--- Supplier List ---\n");
    if (supplierCount == 0) {
        printf("No suppliers registered yet.\n");
        return;
    }
    printf("%-8s %-22s %-26s %-14s %-12s\n",
           "ID", "Name", "Email", "Phone", "Town");
    printLine('-', 86);
    for (i = 0; i < supplierCount; i++)
        printSupplierRow(&suppliers[i]);
    printf("\nTotal suppliers: %d\n", supplierCount);
}

/* Search (and so compare) suppliers by ID, name or town. */
void searchSuppliers(void)
{
    char term[MAX_NAME];
    int choice, i, found = 0;

    printf("\n--- Search Suppliers ---\n");
    printf("1. By ID (exact)\n");
    printf("2. By name (partial)\n");
    printf("3. By town/location (partial) - compare suppliers in an area\n");
    choice = readInt("Choice: ", 1, 3);
    readNonEmpty("Search term: ", term, sizeof(term));

    printf("\n%-8s %-22s %-26s %-14s %-12s\n",
           "ID", "Name", "Email", "Phone", "Town");
    printLine('-', 86);
    for (i = 0; i < supplierCount; i++) {
        int match = 0;
        switch (choice) {
        case 1: match = (strcmp(suppliers[i].id, term) == 0); break;
        case 2: match = containsIgnoreCase(suppliers[i].name, term); break;
        case 3: match = containsIgnoreCase(suppliers[i].town, term); break;
        }
        if (match) {
            printSupplierRow(&suppliers[i]);
            found++;
        }
    }
    if (found == 0)
        printf("No matching supplier found.\n");
    else
        printf("\n%d supplier(s) found.\n", found);
}

void supplierMenu(void)
{
    int choice;

    do {
        printf("\n===== SUPPLIER MANAGEMENT =====\n");
        printf("1. Add supplier\n");
        printf("2. Display suppliers\n");
        printf("3. Search / compare suppliers\n");
        printf("4. Back to main menu\n");
        choice = readInt("Enter your choice: ", 1, 4);

        switch (choice) {
        case 1: addSupplier(); break;
        case 2: displaySuppliers(); break;
        case 3: searchSuppliers(); break;
        case 4: break;
        }
    } while (choice != 4);
}
