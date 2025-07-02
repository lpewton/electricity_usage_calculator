#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fnmatch.h>

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
    char date[11];
    float usage;
    float price;
} tDay;

typedef struct
{
    tDay days[730];
    tHour hours[35040];
    int nHours;
    int nDays;
} tTable;



void createTable(tTable *completeTable, const char *filename);

float calculatePrice(float usage, int hour);

float calculateTotalCost(int maxDays, tTable filteredTable, int chosenPeriod);

void createFilteredTable(tTable completeTable, tTable *filteredTable, char chosenDay[11], int chosenParameter);

void printInformation(tTable filteredTable, float totalCost, int chosenPeriod);

void createDailyTable(tTable completeTable, tTable *dailyTable);

