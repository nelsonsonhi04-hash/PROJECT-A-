#ifndef ASSETS_H
#define ASSETS_H

#include "utils.h"

#define MAX_ASSETS 200

typedef struct {
    char id[MAX_TEXT];
    char name[MAX_NAME];
    char type[MAX_TEXT];
    double purchaseValue;
    char department[MAX_NAME];
    char condition[MAX_TEXT];
} Asset;

/* Data shared with the reports module */
extern Asset assets[MAX_ASSETS];
extern int assetCount;

void assetMenu(void);
void addAsset(void);
void displayAssets(void);
void searchAssets(void);
int findAssetById(const char *id);

#endif
