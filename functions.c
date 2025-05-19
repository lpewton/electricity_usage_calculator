#include "functions.h"

void createTable(tTable *completeTable)
{
    FILE *fileToRead;
    char line[MAX_LINE];
    int i;
    int hour;
    float priceValue;
    tHour newLine;

    i = 0;

    fileToRead = fopen("readings.csv", "r");

    while (fgets(line, sizeof(line), fileToRead))
    {
        // Remove newline character if present
        line[strcspn(line, "\n")] = '\0';

        // Tokenize line using both space and comma as delimiters
        char *token = strtok(line, " ,");
        while (token != NULL)
        {
            if (i > 12)
            {
                if (i % 9 == 6) // Usage
                {
                    newLine.usage = strtof(token, NULL);
                }
                if (i % 9 == 2) // Date
                {
                    strcpy(newLine.date, token);
                }
                if (i % 9 == 3) // Time
                {
                    newLine.hour = atoi(&token[0]);
                    newLine.price = calculatePrice(newLine.usage, newLine.hour);

                    completeTable->hours[completeTable->nHours] = newLine;
                    completeTable->nHours += 1;
                }
            }

            token = strtok(NULL, " ,");
            i++;
        }
    }
    fclose(fileToRead);
}

float calculatePrice(float usage, int hour)
{
    float price;
    float priceValue;

    if (hour < 9 || hour > 22)
    {
        priceValue = 17.89;
    }
    else
    {
        priceValue = 36.15;
    }

    price = usage * priceValue;

    return price / 100;
}

float calculateTotalCost(int maxDays, tTable table)
{
    float totalCost;
    int i;

    totalCost = 0;

    for (i = 0; i < maxDays; i++)
    {
        totalCost += table.hours[i].price;
    }

    return totalCost;
}

void createFilteredTable(tTable completeTable, tTable *filteredTable, char chosenDay[11], int chosenParameter)
{
    int i;

    i = 0;

    filteredTable->nHours = 0;

    if (chosenParameter == 0)
    {
        printf("Heey");
        for (i = 0; i < completeTable.nHours; i++)
        {
            filteredTable->hours[filteredTable->nHours] = completeTable.hours[i];
            filteredTable->nHours += 1;
        }
    }
    else if (chosenParameter == 1)
    {
        for (i = 0; i < completeTable.nHours; i++)
        {
            if (strcmp(chosenDay, completeTable.hours[i].date) == 0)
            {
                filteredTable->hours[filteredTable->nHours] = completeTable.hours[i];
                filteredTable->nHours += 1;
            }
        }
    }
    else if (chosenParameter == 2)
    {
        while (strcmp(chosenDay, completeTable.hours[i].date) != 0)
        {
            filteredTable->hours[filteredTable->nHours] = completeTable.hours[i];
            filteredTable->nHours += 1;
            i++;
        }
    }
}

void printInformation(tTable filteredTable, float totalCost)
{
    int i;

    printf("DATE       | TIME | USAGE\n");
    printf("==========================\n");
    for (i = 0; i < filteredTable.nHours; i++)
    {
        {
            printf("%s | %.2dh   |%.3fkW = %.2f€\n", filteredTable.hours[i].date, filteredTable.hours[i].hour, filteredTable.hours[i].usage, filteredTable.hours[i].price);
            totalCost = calculateTotalCost(filteredTable.nHours, filteredTable);
        }
    }
    printf("==================================\n");
    printf("TOTAL:                      %.2f€\n", totalCost);
}
