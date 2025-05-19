#include "functions.h"

/* main */
int main(int argc, char **argv)
{
    tTable completeTable;
    tTable filteredTable;
    float totalCost;
    int chosenParameter;
    char chosenPeriod[11];
    int i;

    completeTable.nHours = 0;

    createTable(&completeTable);
    printf("DO YOU WANT TO SEE: \n");
    printf("0: ALL SPENDING UNTIL TODAY\n");
    printf("1: A SPECIFIC DAY\n");
    printf("2: TOTAL SPENGING FROM A SPECIFIC DAY (INPUT THE DAY THAT YOU DO NOT WANT TO SEE))\n");

    do {
        printf("PICK FROM 0 TO 2\n");
        scanf("%d", &chosenParameter);
    } while (chosenParameter < 0 || chosenParameter > 3);

    if (chosenParameter > 0)
    {
        printf("ENTER DAY: (DD-MM-YYYY)\n");
        scanf("%s", chosenPeriod);
    }

    createFilteredTable(completeTable, &filteredTable, chosenPeriod, chosenParameter);
    printInformation(filteredTable, totalCost);
   
    return 0;
}
