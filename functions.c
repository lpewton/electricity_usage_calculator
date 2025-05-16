#include "functions.h"

void createTable(tTable *finalTable)
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

                    finalTable->hours[finalTable->nHours] = newLine;
                    finalTable->nHours += 1;
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
