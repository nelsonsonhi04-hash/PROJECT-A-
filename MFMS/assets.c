#include <stdio.h>
#include <string.h>
#include "assets.h"

Asset assets[MAX_ASSETS];
int assetCount = 0;

int findAssetById(const char *id)
{
    int i;
    for (i = 0; i < assetCount; i++) {
        if (strcmp(assets[i].id, id) == 0)
            return i;
    }
    return -1;
}

static void printAssetRow(const Asset *a)
{
    printf("%-8s %-20s %-12s N$%11.2f %-15s %-10s\n",
           a->id, a->name, a->type, a->purchaseValue,
           a->department, a->condition);
}

static void chooseAssetType(char *dest)
{
    int choice;

    printf("Asset type:\n");
    printf("  1. Vehicle\n  2. Computer\n  3. Building\n");
    printf("  4. Equipment\n  5. Furniture\n");
    choice = readInt("Choose type (1-5): ", 1, 5);

    switch (choice) {
    case 1: strcpy(dest, "Vehicle"); break;
    case 2: strcpy(dest, "Computer"); break;
    case 3: strcpy(dest, "Building"); break;
    case 4: strcpy(dest, "Equipment"); break;
    default: strcpy(dest, "Furniture"); break;
    }
}

static void chooseCondition(char *dest)
{
    int choice;

    printf("Condition:\n  1. Good\n  2. Fair\n  3. Poor\n");
    choice = readInt("Choose condition (1-3): ", 1, 3);

    if (choice == 1)
        strcpy(dest, "Good");
    else if (choice == 2)
        strcpy(dest, "Fair");
    else
        strcpy(dest, "Poor");
}

void addAsset(void)
{
    Asset a;
    char id[MAX_TEXT];

    if (assetCount >= MAX_ASSETS) {
        printf("Asset register is full.\n");
        return;
    }

    printf("\n--- Add Asset ---\n");
    while (1) {
        readNonEmpty("Asset ID (e.g. A001): ", id, sizeof(id));
        if (findAssetById(id) != -1)
            printf("  Error: asset ID already exists.\n");
        else
            break;
    }
    strcpy(a.id, id);
    readNonEmpty("Asset name: ", a.name, sizeof(a.name));
    chooseAssetType(a.type);
    a.purchaseValue = readDouble("Purchase value (N$): ", 0.01);
    readNonEmpty("Department: ", a.department, sizeof(a.department));
    chooseCondition(a.condition);

    assets[assetCount++] = a;
    printf("Asset '%s' registered successfully.\n", a.name);
}

void displayAssets(void)
{
    int i;
    double total = 0.0;

    printf("\n--- Asset Register ---\n");
    if (assetCount == 0) {
        printf("No assets registered yet.\n");
        return;
    }
    printf("%-8s %-20s %-12s %14s %-15s %-10s\n",
           "ID", "Name", "Type", "Value", "Department", "Condition");
    printLine('-', 86);
    for (i = 0; i < assetCount; i++) {
        printAssetRow(&assets[i]);
        total += assets[i].purchaseValue;
    }
    printf("\nTotal assets: %d   Total value: N$%.2f\n", assetCount, total);
}

void searchAssets(void)
{
    char term[MAX_NAME];
    int choice, i, found = 0;

    printf("\n--- Search Assets ---\n");
    printf("1. By ID (exact)\n2. By name (partial)\n");
    printf("3. By type (partial)\n4. By department (partial)\n");
    choice = readInt("Choice: ", 1, 4);
    readNonEmpty("Search term: ", term, sizeof(term));

    printf("\n%-8s %-20s %-12s %14s %-15s %-10s\n",
           "ID", "Name", "Type", "Value", "Department", "Condition");
    printLine('-', 86);
    for (i = 0; i < assetCount; i++) {
        int match = 0;
        switch (choice) {
        case 1: match = (strcmp(assets[i].id, term) == 0); break;
        case 2: match = containsIgnoreCase(assets[i].name, term); break;
        case 3: match = containsIgnoreCase(assets[i].type, term); break;
        case 4: match = containsIgnoreCase(assets[i].department, term); break;
        }
        if (match) {
            printAssetRow(&assets[i]);
            found++;
        }
    }
    if (found == 0)
        printf("No matching asset found.\n");
    else
        printf("\n%d asset(s) found.\n", found);
}

void assetMenu(void)
{
    int choice;

    do {
        printf("\n===== ASSET MANAGEMENT =====\n");
        printf("1. Add asset\n");
        printf("2. Display assets\n");
        printf("3. Search assets\n");
        printf("4. Back to main menu\n");
        choice = readInt("Enter your choice: ", 1, 4);

        switch (choice) {
        case 1: addAsset(); break;
        case 2: displayAssets(); break;
        case 3: searchAssets(); break;
        case 4: break;
        }
    } while (choice != 4);
}
