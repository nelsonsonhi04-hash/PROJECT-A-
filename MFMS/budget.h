#ifndef BUDGET_H
#define BUDGET_H

#include "utils.h"

#define MAX_BUDGETS 30

typedef struct {
    char department[MAX_NAME];
    double allocated;
    double expenditure;
} Budget;

/* Data shared with the reports module */
extern Budget budgets[MAX_BUDGETS];
extern int budgetCount;

void budgetMenu(void);
void addBudget(void);
void recordExpenditure(void);
void displayBudgets(void);
void displayExceededBudgets(void);

double calculateBudget(double allocated, double expenditure); /* remaining */
int isWithinBudget(double allocated, double expenditure);
int findBudgetByDepartment(const char *department);

#endif
