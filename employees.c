#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "employees.h"

static Employee employees[MAX_EMPLOYEES];
static int employeeCount = 0;

static void readLine(const char *prompt, char *buffer, int size)
{
    printf("%s", prompt);
    if (fgets(buffer, size, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    buffer[strcspn(buffer, "\n")] = '\0';
}

static int readInt(const char *prompt)
{
    char line[64];
    char *end;
    long value;

    while (1) {
        readLine(prompt, line, sizeof(line));
        value = strtol(line, &end, 10);
        if (end != line && *end == '\0' && value > 0)
            return (int)value;
        printf("Invalid input. Enter a positive whole number.\n");
    }
}

static double readDouble(const char *prompt)
{
    char line[64];
    char *end;
    double value;

    while (1) {
        readLine(prompt, line, sizeof(line));
        value = strtod(line, &end);
        if (end != line && *end == '\0' && value >= 0)
            return value;
        printf("Invalid input. Enter a number (0 or more).\n");
    }
}

static void readNonEmpty(const char *prompt, char *buffer, int size)
{
    do {
        readLine(prompt, buffer, size);
        if (buffer[0] == '\0')
            printf("This field cannot be empty.\n");
    } while (buffer[0] == '\0');
}

static int findIndexById(int id)
{
    int i;
    for (i = 0; i < employeeCount; i++) {
        if (employees[i].id == id)
            return i;
    }
    return -1;
}

static int containsIgnoreCase(const char *text, const char *pattern)
{
    size_t i, j, tl = strlen(text), pl = strlen(pattern);

    if (pl == 0)
        return 1;
    if (pl > tl)
        return 0;

    for (i = 0; i + pl <= tl; i++) {
        for (j = 0; j < pl; j++) {
            if (tolower((unsigned char)text[i + j]) !=
                tolower((unsigned char)pattern[j]))
                break;
        }
        if (j == pl)
            return 1;
    }
    return 0;
}

static void printEmployeeDetails(const Employee *e)
{
    printf("\n----------------------------------------\n");
    printf("Employee ID        : %d\n", e->id);
    printf("Name               : %s\n", e->name);
    printf("Department         : %s\n", e->department);
    printf("Phone              : %s\n", e->phone);
    printf("Basic Salary       : %.2f\n", e->basicSalary);
    printf("Housing Allowance  : %.2f\n", e->housingAllowance);
    printf("Transport Allowance: %.2f\n", e->transportAllowance);
    printf("Other Allowance    : %.2f\n", e->otherAllowance);
    printf("----------------------------------------\n");
}

static void printSalaryDetails(const Employee *e)
{
    double gross = e->basicSalary + e->housingAllowance +
                   e->transportAllowance + e->otherAllowance;
    double tax = gross * TAX_RATE;
    double net = gross - tax;

    printf("\n========== SALARY INFORMATION ==========\n");
    printf("Employee ID        : %d\n", e->id);
    printf("Name               : %s\n", e->name);
    printf("Department         : %s\n", e->department);
    printf("----------------------------------------\n");
    printf("Basic Salary       : %10.2f\n", e->basicSalary);
    printf("Housing Allowance  : %10.2f\n", e->housingAllowance);
    printf("Transport Allowance: %10.2f\n", e->transportAllowance);
    printf("Other Allowance    : %10.2f\n", e->otherAllowance);
    printf("Gross Salary       : %10.2f\n", gross);
    printf("Tax (%.0f%%)         : %10.2f\n", TAX_RATE * 100, tax);
    printf("Net Salary         : %10.2f\n", net);
    printf("========================================\n");
}

void saveEmployees(void)
{
    FILE *fp = fopen(DATA_FILE, "w");
    int i;

    if (fp == NULL) {
        printf("Error: could not save data to %s\n", DATA_FILE);
        return;
    }

    for (i = 0; i < employeeCount; i++) {
        fprintf(fp, "%d|%s|%s|%s|%.2f|%.2f|%.2f|%.2f\n",
                employees[i].id,
                employees[i].name,
                employees[i].department,
                employees[i].phone,
                employees[i].basicSalary,
                employees[i].housingAllowance,
                employees[i].transportAllowance,
                employees[i].otherAllowance);
    }
    fclose(fp);
}

void loadEmployees(void)
{
    FILE *fp = fopen(DATA_FILE, "r");
    char line[256];

    if (fp == NULL)
        return;

    while (employeeCount < MAX_EMPLOYEES &&
           fgets(line, sizeof(line), fp) != NULL) {
        Employee e;
        int n = sscanf(line, "%d|%49[^|]|%29[^|]|%19[^|]|%lf|%lf|%lf|%lf",
                       &e.id, e.name, e.department, e.phone,
                       &e.basicSalary, &e.housingAllowance,
                       &e.transportAllowance, &e.otherAllowance);
        if (n == 8)
            employees[employeeCount++] = e;
    }
    fclose(fp);
}

void addEmployee(void)
{
    Employee e;

    if (employeeCount >= MAX_EMPLOYEES) {
        printf("Employee list is full.\n");
        return;
    }

    printf("\n--- Add Employee ---\n");

    while (1) {
        e.id = readInt("Employee ID: ");
        if (findIndexById(e.id) == -1)
            break;
        printf("An employee with this ID already exists.\n");
    }

    readNonEmpty("Name: ", e.name, NAME_LEN);
    readNonEmpty("Department: ", e.department, DEPT_LEN);
    readNonEmpty("Phone: ", e.phone, PHONE_LEN);
    e.basicSalary = readDouble("Basic salary: ");
    e.housingAllowance = readDouble("Housing allowance: ");
    e.transportAllowance = readDouble("Transport allowance: ");
    e.otherAllowance = readDouble("Other allowance: ");

    employees[employeeCount++] = e;
    saveEmployees();
    printf("\nEmployee added successfully.\n");
}

void displayEmployees(void)
{
    int i;

    if (employeeCount == 0) {
        printf("\nNo employees to display.\n");
        return;
    }

    printf("\n%-6s %-20s %-15s %-12s %-10s %-10s %-10s %-10s\n",
           "ID", "Name", "Department", "Phone",
           "Basic", "Housing", "Transport", "Other");
    printf("-----------------------------------------------------------"
           "-----------------------------\n");

    for (i = 0; i < employeeCount; i++) {
        printf("%-6d %-20s %-15s %-12s %-10.2f %-10.2f %-10.2f %-10.2f\n",
               employees[i].id,
               employees[i].name,
               employees[i].department,
               employees[i].phone,
               employees[i].basicSalary,
               employees[i].housingAllowance,
               employees[i].transportAllowance,
               employees[i].otherAllowance);
    }
    printf("\nTotal employees: %d\n", employeeCount);
}

void searchEmployee(void)
{
    int choice, i, found = 0;

    printf("\n--- Search Employee ---\n");
    printf("1. Search by ID\n");
    printf("2. Search by Name\n");
    choice = readInt("Choice: ");

    if (choice == 1) {
        int id = readInt("Enter Employee ID: ");
        int idx = findIndexById(id);
        if (idx == -1)
            printf("Employee not found.\n");
        else
            printEmployeeDetails(&employees[idx]);
    } else if (choice == 2) {
        char name[NAME_LEN];
        readNonEmpty("Enter name (or part of it): ", name, NAME_LEN);
        for (i = 0; i < employeeCount; i++) {
            if (containsIgnoreCase(employees[i].name, name)) {
                printEmployeeDetails(&employees[i]);
                found = 1;
            }
        }
        if (!found)
            printf("No employee found with that name.\n");
    } else {
        printf("Invalid choice.\n");
    }
}

void calculateSalary(void)
{
    int id, idx;

    if (employeeCount == 0) {
        printf("\nNo employees available.\n");
        return;
    }

    id = readInt("\nEnter Employee ID to calculate salary: ");
    idx = findIndexById(id);

    if (idx == -1)
        printf("Employee not found.\n");
    else
        printSalaryDetails(&employees[idx]);
}