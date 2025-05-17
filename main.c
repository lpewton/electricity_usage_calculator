#include "functions.h"

/* main */
int main(int argc, char **argv)
{
    tTable completeTable;
    tTable filteredTable;
    float totalCost;
    int chosenParameter;
    char chosenPeriod[11];
    char temp[7];
    bool continues;

    int j;

    continues = false;

    completeTable.nHours = 0;

    createTable(&completeTable);
    printf("DO YOU WANT A SPECIFIC DAY (1) OR TO SEE FROM A SPECIFIC DAY (2)?\n");
    printf("PRESS 0 TO SEE ALL?\n");
    // do {
    scanf("%d", &chosenParameter);
    // } while (specificDay != 1 && specificDay != 0);

    if (chosenParameter == 1)
    {
        printf("ENTER DAY: (DD-MM-YYYY)\n");
        scanf("%s", chosenPeriod);
        createFilteredTable(completeTable, &filteredTable, chosenPeriod, continues);
    }
    else if (chosenParameter == 2)
    {
        printf("ENTER FROM DAY: (DD-MM-YYYY)\n");
        scanf("%s", chosenPeriod);
        continues = true;
        createFilteredTable(completeTable, &filteredTable, chosenPeriod, continues);
    }

    printf("DATE       | TIME | USAGE\n");
    printf("==========================\n");
    if (chosenParameter > 0)
    {
        for (j = 0; j < filteredTable.nHours; j++)
        {
            {
                printf("%s | %.2dh   |%.3fkW = %.2f€\n", filteredTable.hours[j].date, filteredTable.hours[j].hour, filteredTable.hours[j].usage, filteredTable.hours[j].price);
                totalCost = calculateTotalCost(filteredTable.nHours, filteredTable);
            }
        }
    }
    else
    {
        for (j = 0; j < completeTable.nHours; j++)
        {
            printf("%s | %.2dh   |%.3fkW = %.2f€\n", completeTable.hours[j].date, completeTable.hours[j].hour, completeTable.hours[j].usage, completeTable.hours[j].price);
            totalCost = calculateTotalCost(completeTable.nHours, completeTable);
        }
    }

    printf("==================================\n");
    printf("TOTAL:                      %.2f€\n", totalCost);
    return 0;
}
