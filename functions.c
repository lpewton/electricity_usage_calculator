#include "functions.h"

void createTable(tTable *completeTable, const char *filename)
{

    FILE *fileToRead;
    char line[MAX_LINE];
    char currentDate[11];
    int i;
    int hour;
    float priceValue;
    tHour newHour;
    tDay newDay;

    i = 0;
    currentDate[0] = '\0';

    fileToRead = fopen(filename, "r");

    if (fileToRead == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
    }

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
                    newHour.usage = strtof(token, NULL);
                }
                if (i % 9 == 2) // Date
                {
                    strcpy(newHour.date, token);
                }
                if (i % 9 == 3) // Time
                {
                    newHour.hour = atoi(&token[0]);
                    newHour.price = calculatePrice(newHour.usage, newHour.hour);

                    if (strcmp(currentDate, newHour.date) != 0) {
                        completeTable->days[completeTable->nDays] = newDay;
                        strcpy(currentDate, newHour.date);
                        newDay.usage = newHour.usage;
                        newDay.price = newHour.price;
                        strcpy(newDay.date, newHour.date);
                        completeTable->nDays += 1;
                    } else {
                        newDay.usage += newHour.usage;
                        newDay.price += newHour.price;
                    }

                    completeTable->hours[completeTable->nHours] = newHour;
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
        priceValue = 0.1789;
    }
    else
    {
        priceValue = 0.3615;
    }

    price = usage * priceValue;

    return price;
}

float calculateTotalCost(int maxDays, tTable filteredTable, int chosenPeriod)
{
    float totalCost;
    float standingCharge;
    int i;

    totalCost = 0;

    for (i = 0; i < maxDays; i++)
    {
        if (chosenPeriod == 0)
        {
            totalCost += filteredTable.hours[i].price;
        }
        else
        {
            totalCost += filteredTable.days[i].price;
        }
    }

    standingCharge = filteredTable.nDays * 0.7223;

    return totalCost + standingCharge;
}

void createFilteredTable(tTable completeTable, tTable *filteredTable, char chosenDay[11], int chosenParameter)
{
    int i;

    filteredTable->nHours = 0;

    if (chosenParameter == 0)
    {
        for (i = 0; i < completeTable.nDays; i++) {
            filteredTable->days[filteredTable->nDays] = completeTable.days[i];
            filteredTable->nDays += 1;
        }
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
    i = 0;
        while (strcmp(chosenDay, completeTable.hours[i].date) != 0)
        {
            filteredTable->hours[filteredTable->nHours] = completeTable.hours[i];
            filteredTable->nHours += 1;
            i++;
        }
    }
}

void printInformation(tTable filteredTable, float totalCost, int chosenPeriod)
{
    int i;

    if (chosenPeriod == 0) { // Print by hour
    for (i = 0; i < filteredTable.nHours; i++)
        {
            printf("%s - %.2dh - %.3fkW = %.2f€\n", filteredTable.hours[i].date, filteredTable.hours[i].hour, filteredTable.hours[i].usage, filteredTable.hours[i].price);
            totalCost = calculateTotalCost(filteredTable.nHours, filteredTable, chosenPeriod);
        }
    } else { // Print by day
    for (i = 1; i < filteredTable.nDays; i++)
        {
            printf("%s - %.3fkW = %.2f€\n", filteredTable.days[i].date, filteredTable.days[i].usage, filteredTable.days[i].price);
            totalCost = calculateTotalCost(filteredTable.nDays, filteredTable, chosenPeriod);
    }
    }
    printf(": %.2f€\n", totalCost);
}
