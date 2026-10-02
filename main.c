#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employees.h"

static int readMenuChoice(void)
{
    char line[32];
    char *end;
    long value;

    if (fgets(line, sizeof(line), stdin) == NULL)
        return 0;

    value = strtol(line, &end, 10);
    if (end == line)
        return -1;
    return (int)value;
}

int main(void)
{
    int choice;

    loadEmployees();

    do {
        printf("\n=========================================\n");
        printf("        EMPLOYEE MANAGEMENT SYSTEM\n");
        printf("=========================================\n");
        printf("1. Add an employee\n");
        printf("2. Display employees\n");
        printf("3. Search for an employee\n");
        printf("4. Calculate employee salary\n");
        printf("0. Exit\n");
        printf("-----------------------------------------\n");
        printf("Enter your choice: ");

        choice = readMenuChoice();

        switch (choice) {
            case 1: addEmployee();      break;
            case 2: displayEmployees(); break;
            case 3: searchEmployee();   break;
            case 4: calculateSalary();  break;
            case 0: printf("\nGoodbye!\n"); break;
            default: printf("\nInvalid choice. Try again.\n");
        }
    } while (choice != 0);

    return 0;
}