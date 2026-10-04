#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#include "utils.h"

#define MAX_SUPPLIERS 100

typedef struct {
    char id[MAX_TEXT];
    char name[MAX_NAME];
    char email[MAX_NAME];
    char phone[MAX_TEXT];
    char town[MAX_NAME];
} Supplier;

/* Data shared with the reports module */
extern Supplier suppliers[MAX_SUPPLIERS];
extern int supplierCount;

void supplierMenu(void);
void addSupplier(void);
void displaySuppliers(void);
void searchSuppliers(void);
int findSupplierById(const char *id);

#endif
