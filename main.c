#include <stdio.h>
#include <string.h>

int employeeCount = 3;
char employeeNames[50][50] = {"Matias Kalilo", "Ester Iikela", "Nelson Shikongo"};
float employeeSalaries[50] = {18500, 42000, 8500};
int budgetCount = 2;
char deptNames[50][50] = {"Finance", "IT"};
float allocatedBudget[50] = {500000, 300000};
float expenditure[50] = {420000, 310000};
int supplierCount = 2;
char supplierNames[50][50] = {"Windhoek Supplies", "NUST Tech"};
char supplierEmails[50][50] = {"info@ws.na", "sales@nust.na"};
char supplierTowns[50][50] = {"Windhoek", "Windhoek"};
int assetCount = 2;
char assetNames[50][50] = {"Toyota Hilux", "Dell Laptop"};

// fanctions  before main()
void employeeReport();
void budgetReport();
void supplierReport();
void assetReport();
void searchSupplierReport();
float calculateTotalSalary(float s[], int n);
float calculateVAT(float a);
float calculateAverageSalary(float total, int count);
float calculateBudgetBalance(float a, float b);

float calculateVAT(float amount){ return amount*0.15; }
float calculateTotalSalary(float salaries[], int count){ float t=0; for(int i=0;i<count;i++) t+=salaries[i]; return t; }
float calculateAverageSalary(float total, int count){ if(count==0) return 0; return total/count; }
float calculateBudgetBalance(float allocated, float spent){ return allocated-spent; }

void employeeReport(){
    float total=calculateTotalSalary(employeeSalaries,employeeCount);
    printf("\n----- Employee Report -----\nTotal:%d Total:N$%.2f Avg:N$%.2f VAT:%.2f\n",employeeCount,total,calculateAverageSalary(total,employeeCount),calculateVAT(total));
}
void budgetReport(){
    float alloc=0, spent=0; for(int i=0;i<budgetCount;i++){ alloc+=allocatedBudget[i]; spent+=expenditure[i]; }
    float remain=calculateBudgetBalance(alloc,spent);
    printf("\n----- Budget Report -----\nAlloc:%.2f Spent:%.2f Rem:%.2f\n",alloc,spent,remain);
}
void supplierReport(){
     printf("\n----- Supplier Report -----\n");
      for(int i=0;i<supplierCount;i++)
       printf("%d. %s - %s\n",i+1,supplierNames[i],supplierTowns[i]); }
void assetReport(){
     printf("\n----- Asset Report -----\n");
      for(int i=0;i<assetCount;i++) 
      printf("%d. %s\n",i+1,assetNames[i]); }
void searchSupplierReport(){
    char search[50]; 
    printf("Enter supplier name: ");
     fgets(search,50,stdin); 
     search[strcspn(search,"\n")]='\0';
    for(int i=0;i<supplierCount;i++) if(strcmp(supplierNames[i],search)==0){ 
        printf("Found: %s | %s\n",supplierNames[i],supplierEmails[i]); return; }
    printf("'%s' not found.\n",search);
}
// start of the fantion main
int main(){
    int choice;
    do{
        printf("\n--- REPORTS MENU ---\n1.Employee 2.Budget 3.Supplier 4.Asset 5.Search Supplier 6.Exit\nChoice: ");
        scanf("%d",&choice); 
        int c; while((c=getchar())!='\n' && c!=-1);
        if(choice==1) employeeReport();
        else if(choice==2) budgetReport();
        else if(choice==3) supplierReport();
        else if(choice==4) assetReport();
        else if(choice==5) searchSupplierReport();
        else if(choice==6) printf("Bye!\n");
        else printf("Invalid 1-6\n");
    }while(choice!=6);
    return 0;
}