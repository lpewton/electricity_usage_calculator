#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 300

typedef struct
{
    int hour;
    char date[11];
    float usage;
    float price;
} tHour;

typedef struct
{
    tHour hours[35040];
    int nHours;
} tTable;



void createTable(tTable *finalTable);

float calculatePrice(float usage, int hour);

float calculateTotalCost(int maxDays, tTable table);
