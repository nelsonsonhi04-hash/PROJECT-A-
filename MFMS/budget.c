#include <stdio.h>
#include <string.h>
#include "budget.h"

Budget budgets[MAX_BUDGETS];
int budgetCount = 0;

/* Remaining budget (negative means overspent). */
double calculateBudget(double allocated, double expenditure)
{
    return allocated - expenditure;
}

/* 1 if spending is within (or equal to) the allocation. */
int isWithinBudget(double allocated, double expenditure)
{
    return expenditure <= allocated;
}

/* Case-insensitive lookup so "finance" matches "Finance". */
int findBudgetByDepartment(const char *department)
{
    int i;
    for (i = 0; i < budgetCount; i++) {
        if (strlen(budgets[i].department) == strlen(department) &&
            containsIgnoreCase(budgets[i].department, department))
            return i;
    }
    return -1;
}

static void printBudget(const Budget *b)
{
    double remaining = calculateBudget(b->allocated, b->expenditure);

    printf("Department      : %s\n", b->department);
    printf("Allocated Budget: N$%.2f\n", b->allocated);
    printf("Expenditure     : N$%.2f\n", b->expenditure);
    printf("Remaining Budget: N$%.2f\n", remaining);
    printf("Status          : %s\n",
           isWithinBudget(b->allocated, b->expenditure)
               ? "WITHIN BUDGET" : "EXCEEDED BUDGET");
    printLine('-', 40);
}

void addBudget(void)
{
    Budget b;

    if (budgetCount >= MAX_BUDGETS) {
        printf("Budget list is full.\n");
        return;
    }

    printf("\n--- Enter Departmental Budget ---\n");
    while (1) {
        readNonEmpty("Department name: ", b.department, sizeof(b.department));
        if (findBudgetByDepartment(b.department) != -1)
            printf("  Error: a budget for this department already exists.\n");
        else
            break;
    }
    b.allocated = readDouble("Allocated budget (N$): ", 0.01);
    b.expenditure = 0.0;

    budgets[budgetCount++] = b;
    printf("Budget saved for %s.\n", b.department);
}

void recordExpenditure(void)
{
    char dept[MAX_NAME];
    int idx;
    double amount;

    printf("\n--- Record Expenditure ---\n");
    if (budgetCount == 0) {
        printf("No budgets exist yet. Add a budget first.\n");
        return;
    }
    readNonEmpty("Department name: ", dept, sizeof(dept));
    idx = findBudgetByDepartment(dept);
    if (idx == -1) {
        printf("Department not found.\n");
        return;
    }
    amount = readDouble("Expenditure amount (N$): ", 0.0);
    budgets[idx].expenditure += amount;

    printf("\nUpdated budget:\n");
    printBudget(&budgets[idx]);
    if (!isWithinBudget(budgets[idx].allocated, budgets[idx].expenditure))
        printf("WARNING: %s has exceeded its budget!\n", budgets[idx].department);
}

void displayBudgets(void)
{
    int i;

    printf("\n--- Budget Information ---\n");
    if (budgetCount == 0) {
        printf("No budgets registered yet.\n");
        return;
    }
    for (i = 0; i < budgetCount; i++)
        printBudget(&budgets[i]);
}

void displayExceededBudgets(void)
{
    int i, count = 0;

    printf("\n--- Departments Over Budget ---\n");
    for (i = 0; i < budgetCount; i++) {
        if (!isWithinBudget(budgets[i].allocated, budgets[i].expenditure)) {
            printf("%-20s over by N$%.2f\n", budgets[i].department,
                   -calculateBudget(budgets[i].allocated, budgets[i].expenditure));
            count++;
        }
    }
    if (count == 0)
        printf("No department has exceeded its budget.\n");
}

void budgetMenu(void)
{
    int choice;

    do {
        printf("\n===== BUDGET MANAGEMENT =====\n");
        printf("1. Enter departmental budget\n");
        printf("2. Record expenditure\n");
        printf("3. Display budget information\n");
        printf("4. Show departments over budget\n");
        printf("5. Back to main menu\n");
        choice = readInt("Enter your choice: ", 1, 5);

        switch (choice) {
        case 1: addBudget(); break;
        case 2: recordExpenditure(); break;
        case 3: displayBudgets(); break;
        case 4: displayExceededBudgets(); break;
        case 5: break;
        }
    } while (choice != 5);
}
