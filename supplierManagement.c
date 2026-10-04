#include <stdio.h>
#include <string.h>
#include "supplierManagement.h"

int  supplierCount = 0;
int  supplierIDs[MAX_SUPPLIERS];
char supplierNames[MAX_SUPPLIERS][50];
char supplierEmails[MAX_SUPPLIERS][50];
char supplierPhones[MAX_SUPPLIERS][50];
char supplierTowns[MAX_SUPPLIERS][50];

void addSupplier(){
    if(supplierCount>=MAX_SUPPLIERS){
        printf("\nSupplier list is full.\n");
        return;
    }

    int id, c;
    printf("\nEnter Supplier ID: ");
    scanf("%d",&id);
    while((c=getchar())!='\n' && c!=-1);

    for(int i=0;i<supplierCount;i++){
        if(supplierIDs[i]==id){
            printf("A supplier with ID %d already exists.\n",id);
            return;
        }
    }

    char name[50], email[50], phone[50], town[50];

    printf("Enter Supplier Name: ");
    fgets(name,50,stdin); name[strcspn(name,"\n")]='\0';
    if(strlen(name)==0){
        printf("Supplier name cannot be empty.\n");
        return;
    }

    printf("Enter Email: ");
    fgets(email,50,stdin); email[strcspn(email,"\n")]='\0';

    printf("Enter Telephone Number: ");
    fgets(phone,50,stdin); phone[strcspn(phone,"\n")]='\0';

    printf("Enter Town/Location: ");
    fgets(town,50,stdin); town[strcspn(town,"\n")]='\0';

    supplierIDs[supplierCount]=id;
    strcpy(supplierNames[supplierCount],name);
    strcpy(supplierEmails[supplierCount],email);
    strcpy(supplierPhones[supplierCount],phone);
    strcpy(supplierTowns[supplierCount],town);
    supplierCount++;

    printf("Supplier added successfully.\n");
}

void displaySuppliers(){
    if(supplierCount==0){
        printf("\nNo suppliers have been captured yet.\n");
        return;
    }

    printf("\n%-5s %-20s %-25s %-15s %-15s\n","ID","Name","Email","Phone","Town");
    for(int i=0;i<supplierCount;i++)
        printf("%-5d %-20s %-25s %-15s %-15s\n",
               supplierIDs[i],supplierNames[i],supplierEmails[i],supplierPhones[i],supplierTowns[i]);
}

void searchSupplier(){
    if(supplierCount==0){
        printf("\nNo suppliers have been captured yet.\n");
        return;
    }

    int choice, c;
    printf("\nSearch by:\n1. Supplier ID\n2. Supplier Name\nEnter your choice: ");
    scanf("%d",&choice);
    while((c=getchar())!='\n' && c!=-1);

    int found=0;

    if(choice==1){
        int id;
        printf("Enter Supplier ID: ");
        scanf("%d",&id);
        while((c=getchar())!='\n' && c!=-1);

        for(int i=0;i<supplierCount;i++){
            if(supplierIDs[i]==id){
                found=1;
                printf("\nSupplier Found:\nID: %d\nName: %s\nEmail: %s\nPhone: %s\nTown: %s\n",
                       supplierIDs[i],supplierNames[i],supplierEmails[i],supplierPhones[i],supplierTowns[i]);
                break;
            }
        }
    } else if(choice==2){
        char name[50];
        printf("Enter Supplier Name: ");
        fgets(name,50,stdin); name[strcspn(name,"\n")]='\0';

        for(int i=0;i<supplierCount;i++){
            if(strcmp(supplierNames[i],name)==0){
                found=1;
                printf("\nSupplier Found:\nID: %d\nName: %s\nEmail: %s\nPhone: %s\nTown: %s\n",
                       supplierIDs[i],supplierNames[i],supplierEmails[i],supplierPhones[i],supplierTowns[i]);
                break;
            }
        }
    } else {
        printf("Invalid choice.\n");
        return;
    }

    if(!found) printf("No matching supplier was found.\n");
}

void supplierReport(){
    printf("\n--- Supplier Report ---\n");
    if(supplierCount==0){
        printf("No suppliers have been captured yet.\n");
        return;
    }
    printf("Total Suppliers: %d\n",supplierCount);
    displaySuppliers();
}

void supplierMenu(){
    int choice, c;
    do{
        printf("\n---- SUPPLIER MANAGEMENT ----\n1. Add Supplier\n2. Display Suppliers\n3. Search Supplier\n4. Back to Main Menu\nEnter your choice: ");
        scanf("%d",&choice);
        while((c=getchar())!='\n' && c!=-1);

        if(choice==1) addSupplier();
        else if(choice==2) displaySuppliers();
        else if(choice==3) searchSupplier();
        else if(choice==4) printf("Returning to main menu...\n");
        else printf("Invalid choice. Please try again.\n");
    } while(choice!=4);
}
   