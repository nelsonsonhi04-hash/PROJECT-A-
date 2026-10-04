#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#include "utils.h"

#define MAX_EMPLOYEES 100

typedef struct {
    char id[MAX_TEXT];
    char name[MAX_NAME];
    char department[MAX_NAME];
    char position[MAX_NAME];
    double basicSalary;
    double housingAllowance;
    double transportAllowance;
} Employee;

/* Data shared with the reports module */
extern Employee employees[MAX_EMPLOYEES];
extern int employeeCount;

void employeeMenu(void);
void addEmployee(void);
void displayEmployees(void);
void searchEmployee(void);
void calculateSalary(void);

double calculateGross(const Employee *e);
double calculateTax(double gross);
int findEmployeeById(const char *id);

#endif
