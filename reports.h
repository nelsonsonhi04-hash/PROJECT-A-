#ifndef REPORTS_H
#define REPORTS_H

float calculateTotalSalary(float salaries[], int count);
float calculateAverageSalary(float total, int count);
float calculateBudgetBalance(float allocated, float spent);
float calculateVAT(float amount);

void employeeReport();
void budgetReport();
void supplierReport();
void assetReport();

#endif