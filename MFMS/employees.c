#include <stdio.h>
#include <string.h>
#include "employees.h"

Employee employees[MAX_EMPLOYEES];
int employeeCount = 0;

/* Returns index of employee with this ID, or -1 if not found. */
int findEmployeeById(const char *id)
{
    int i;
    for (i = 0; i < employeeCount; i++) {
        if (strcmp(employees[i].id, id) == 0)
            return i;
    }
    return -1;
}

/* Gross salary = basic + housing + transport. */
double calculateGross(const Employee *e)
{
    return e->basicSalary + e->housingAllowance + e->transportAllowance;
}

/* Simplified illustrative tax bands (NOT the official tax tables). */
double calculateTax(double gross)
{
    if (gross <= 5000.0)
        return 0.0;
    else if (gross <= 15000.0)
        return (gross - 5000.0) * 0.10;
    else if (gross <= 30000.0)
        return 1000.0 + (gross - 15000.0) * 0.20;
    else
        return 4000.0 + (gross - 30000.0) * 0.30;
}

static void printEmployeeRow(const Employee *e)
{
    printf("%-8s %-20s %-15s %-15s N$%9.2f N$%9.2f\n",
           e->id, e->name, e->department, e->position,
           e->basicSalary, calculateGross(e));
}

void addEmployee(void)
{
    Employee e;
    char id[MAX_TEXT];

    if (employeeCount >= MAX_EMPLOYEES) {
        printf("Employee list is full (%d).\n", MAX_EMPLOYEES);
        return;
    }

    printf("\n--- Add Employee ---\n");
    while (1) {
        readNonEmpty("Employee ID (e.g. E001): ", id, sizeof(id));
        if (findEmployeeById(id) != -1)
            printf("  Error: an employee with ID '%s' already exists.\n", id);
        else
            break;
    }
    strcpy(e.id, id);
    readNonEmpty("Full name: ", e.name, sizeof(e.name));
    readNonEmpty("Department: ", e.department, sizeof(e.department));
    readNonEmpty("Position/Job title: ", e.position, sizeof(e.position));
    e.basicSalary = readDouble("Basic salary (N$): ", 0.01);
    e.housingAllowance = readDouble("Housing allowance (N$): ", 0.0);
    e.transportAllowance = readDouble("Transport allowance (N$): ", 0.0);

    employees[employeeCount++] = e;
    printf("Employee '%s' added successfully.\n", e.name);
}

void displayEmployees(void)
{
    int i;

    printf("\n--- Employee List ---\n");
    if (employeeCount == 0) {
        printf("No employees registered yet.\n");
        return;
    }
    printf("%-8s %-20s %-15s %-15s %12s %12s\n",
           "ID", "Name", "Department", "Position", "Basic", "Gross");
    printLine('-', 88);
    for (i = 0; i < employeeCount; i++)
        printEmployeeRow(&employees[i]);
    printf("\nTotal employees: %d\n", employeeCount);
}

void searchEmployee(void)
{
    char term[MAX_NAME];
    int choice, i, found = 0;

    printf("\n--- Search Employee ---\n");
    printf("1. Search by ID (exact)\n");
    printf("2. Search by name (partial match)\n");
    printf("3. Search by department\n");
    choice = readInt("Choice: ", 1, 3);
    readNonEmpty("Search term: ", term, sizeof(term));

    printf("\n%-8s %-20s %-15s %-15s %12s %12s\n",
           "ID", "Name", "Department", "Position", "Basic", "Gross");
    printLine('-', 88);
    for (i = 0; i < employeeCount; i++) {
        int match = 0;
        switch (choice) {
        case 1:
            match = (strcmp(employees[i].id, term) == 0);
            break;
        case 2:
            match = containsIgnoreCase(employees[i].name, term);
            break;
        case 3:
            match = containsIgnoreCase(employees[i].department, term);
            break;
        }
        if (match) {
            printEmployeeRow(&employees[i]);
            found++;
        }
    }
    if (found == 0)
        printf("No matching employee found.\n");
    else
        printf("\n%d employee(s) found.\n", found);
}

void calculateSalary(void)
{
    char id[MAX_TEXT];
    int idx;
    double gross, tax, pension, net;

    printf("\n--- Salary Calculation ---\n");
    readNonEmpty("Enter employee ID: ", id, sizeof(id));
    idx = findEmployeeById(id);
    if (idx == -1) {
        printf("Employee not found.\n");
        return;
    }

    gross = calculateGross(&employees[idx]);
    tax = calculateTax(gross);
    pension = employees[idx].basicSalary * 0.05; /* 5% of basic */
    net = gross - tax - pension;

    printf("\nPayslip for %s (%s)\n", employees[idx].name, employees[idx].id);
    printLine('-', 40);
    printf("Basic salary       : N$%10.2f\n", employees[idx].basicSalary);
    printf("Housing allowance  : N$%10.2f\n", employees[idx].housingAllowance);
    printf("Transport allowance: N$%10.2f\n", employees[idx].transportAllowance);
    printf("Gross salary       : N$%10.2f\n", gross);
    printf("Tax (simplified)   : N$%10.2f\n", tax);
    printf("Pension (5%% basic) : N$%10.2f\n", pension);
    printf("NET SALARY         : N$%10.2f\n", net);
}

void employeeMenu(void)
{
    int choice;

    do {
        printf("\n===== EMPLOYEE MANAGEMENT =====\n");
        printf("1. Add employee\n");
        printf("2. Display employees\n");
        printf("3. Search employee\n");
        printf("4. Calculate salary\n");
        printf("5. Back to main menu\n");
        choice = readInt("Enter your choice: ", 1, 5);

        switch (choice) {
        case 1: addEmployee(); break;
        case 2: displayEmployees(); break;
        case 3: searchEmployee(); break;
        case 4: calculateSalary(); break;
        case 5: break;
        }
    } while (choice != 5);
}
