#include <stdio.h>
#include "reports.h"
#include "utils.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"

void employeeReport(void)
{
    int i;
    double total = 0.0, highest, lowest, gross;

    printf("\n===== EMPLOYEE REPORT =====\n");
    if (employeeCount == 0) {
        printf("No employees registered.\n");
        return;
    }

    highest = lowest = calculateGross(&employees[0]);
    for (i = 0; i < employeeCount; i++) {
        gross = calculateGross(&employees[i]);
        total += gross;
        if (gross > highest)
            highest = gross;
        if (gross < lowest)
            lowest = gross;
    }
    printf("Total Employees: %d\n", employeeCount);
    printf("Average Salary : N$%.2f\n", total / employeeCount);
    printf("Highest Salary : N$%.2f\n", highest);
    printf("Lowest Salary  : N$%.2f\n", lowest);
    printf("Total Payroll  : N$%.2f\n", total);
    printf("(Salary = gross: basic + housing + transport)\n");
}

void budgetReport(void)
{
    int i;
    double totalAllocated = 0.0, totalSpent = 0.0;

    printf("\n===== BUDGET REPORT =====\n");
    if (budgetCount == 0) {
        printf("No budgets registered.\n");
        return;
    }
    for (i = 0; i < budgetCount; i++) {
        totalAllocated += budgets[i].allocated;
        totalSpent += budgets[i].expenditure;
    }
    printf("Total allocated budget: N$%.2f\n", totalAllocated);
    printf("Total expenditure     : N$%.2f\n", totalSpent);
    printf("Remaining budget      : N$%.2f\n",
           calculateBudget(totalAllocated, totalSpent));
    displayExceededBudgets();
}

void supplierReport(void)
{
    printf("\n===== SUPPLIER REPORT =====");
    displaySuppliers();
}

void assetReport(void)
{
    printf("\n===== ASSET REPORT =====");
    displayAssets();
}

void displayReports(void)
{
    int choice;

    do {
        printf("\n===== REPORTS =====\n");
        printf("1. Employee report\n");
        printf("2. Budget report\n");
        printf("3. Supplier report\n");
        printf("4. Asset report\n");
        printf("5. Back to main menu\n");
        choice = readInt("Enter your choice: ", 1, 5);

        switch (choice) {
        case 1: employeeReport(); break;
        case 2: budgetReport(); break;
        case 3: supplierReport(); break;
        case 4: assetReport(); break;
        case 5: break;
        }
    } while (choice != 5);
}
