#include "functions.h"

/* main */
int main(int argc, char **argv)
{
    tTable finalTable;
    float totalCost;

    int j;

    finalTable.nHours = 0;

    createTable(&finalTable);

    printf("DATE       | TIME | USAGE\n");
    printf("==========================\n");
    for (j = 0; j < finalTable.nHours; j++)
    {
        printf("%s | %.2d   |%.3fkW = %.2f€\n", finalTable.hours[j].date, finalTable.hours[j].hour, finalTable.hours[j].usage, finalTable.hours[j].price);
    }

    totalCost = calculateTotalCost(finalTable.nHours, finalTable);

    printf("==================================\n");
    printf("TOTAL:                      %.2f€\n", totalCost);

    return 0;
}
