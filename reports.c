#include <stdio.h>
#include "reports.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"

// total salaries
float totalSalary(float salaries[], int count) {
    float total = 0;
    for(int i = 0; i < count; i++) {
        total = total + salaries[i];
    }
    return total;
}

// average salary
float averageSalary(float total, int count) {
    if(count == 0) {
        return 0;
    }
    return total / count;
}

// balance Budgeted 
float budgetBalance(float allocated, float spent) {
    return allocated - spent;
}

// VAT Calculations
float VAT(float amount) {
    return amount * 0.15;
}

// Employee reports
void employeeReport() {
    float total = calculateTotalSalary(employeeSalaries, employeeCount);
    float avg = calculateAverageSalary(total, employeeCount);

    printf("\n--- Employee Report ---\n");
    printf("Number of employees: %d\n", employeeCount);
    printf("Total salary: %.2f\n", total);
    printf("Average salary: %.2f\n", avg);
    printf("VAT: %.2f\n", calculateVAT(total));

    for(int i = 0; i < employeeCount; i++) {
        printf("%d. %s - %.2f\n", i+1, employeeNames[i], employeeSalaries[i]);
    }
}

// Our  budget reports
void budgetReport() {
    float alloc = 0;
    float spent = 0;
    for(int i = 0; i < budgetCount; i++) {
        alloc = alloc + allocatedBudget[i];
        spent = spent + expenditure[i];
    }
    printf("\n--- Budget Report ---\n");
    printf("Total Allocated: %.2f\n", alloc);
    printf("Total Spent: %.2f\n", spent);
    printf("Remaining: %.2f\n", calculateBudgetBalance(alloc, spent));
}

// Reports about our suppliers
void supplierReport() {
    printf("\n--- Supplier Report ---\n");
    for(int i = 0; i < supplierCount; i++) {
        printf("%d. %s - %s\n", i+1, supplierNames[i], supplierTowns[i]);
    }
}

//  Reports about the assets
void assetReport() {
    printf("\n--- Asset Report ---\n");
    for(int i = 0; i < assetCount; i++) {
        printf("%d. %s\n", i+1, assetNames[i]);
    }
}