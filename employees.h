#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#define MAX_EMPLOYEES 100
#define NAME_LEN 50
#define DEPT_LEN 30
#define PHONE_LEN 20
#define DATA_FILE "employees.txt"
#define TAX_RATE 0.10

typedef struct {
    int id;
    char name[NAME_LEN];
    char department[DEPT_LEN];
    char phone[PHONE_LEN];
    double basicSalary;
    double housingAllowance;
    double transportAllowance;
    double otherAllowance;
} Employee;

void loadEmployees(void);
void saveEmployees(void);
void addEmployee(void);
void displayEmployees(void);
void searchEmployee(void);
void calculateSalary(void);

#endif