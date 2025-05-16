#include "functions.h"

/* main */
int main(int argc, char **argv)
{
    tTable completeTable;
    tTable filteredTable;
    float totalCost;
    bool specificDay;
    char chosenDay[11];

    int j;

    completeTable.nHours = 0;

    createTable(&completeTable);
    printf("DO YOU WANT A SPECIFIC DAY (YES-1, NO-0)\n");
    scanf("%d", &specificDay);

    if (specificDay)
    {
        printf("ENTER DAY: (DD-MM-YYYY)\n");
        scanf("%s", chosenDay);
        createFilteredTable(completeTable, &filteredTable, chosenDay);
    }

    printf("DATE       | TIME | USAGE\n");
    printf("==========================\n");
    if (specificDay == true)
    {
        for (j = 0; j < filteredTable.nHours; j++)
        {
            {
                printf("%s | %.2d   |%.3fkW = %.2f€\n", filteredTable.hours[j].date, filteredTable.hours[j].hour, filteredTable.hours[j].usage, filteredTable.hours[j].price);
                totalCost = calculateTotalCost(filteredTable.nHours, filteredTable);
            }
        }
    }
    else
    {
        for (j = 0; j < completeTable.nHours; j++)
        {

            {
                printf("%s | %.2d   |%.3fkW = %.2f€\n", completeTable.hours[j].date, completeTable.hours[j].hour, completeTable.hours[j].usage, completeTable.hours[j].price);
                totalCost = calculateTotalCost(completeTable.nHours, completeTable);
            }
        }
    }

    printf("==================================\n");
    printf("TOTAL:                      %.2f€\n", totalCost);

    return 0;
}
