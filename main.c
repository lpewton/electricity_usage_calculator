#include "functions.h"

/* main */
int main(int argc, char **argv)
{
    // Check if enough arguments are provided
    if (argc < 5) {
        fprintf(stderr, "Usage: %s <csv_file> <chosenParameter> [chosenDay] [chosenPeriod] [chosenStartDay] [chosenEndDay] \n", argv[0]);
        exit(EXIT_FAILURE);
    }

    tTable completeTable;
    tTable filteredTable;
    float totalCost = 0.0;
    int chosenPeriod = 0;
    char chosenDay[11] = ""; // optional
    char chosenStartDay[11] = ""; // optional
    char chosenEndDay[11] = ""; // optional
    int chosenParameter = atoi(argv[2]); // convert string to int

    completeTable.nHours = 0;
    completeTable.nDays = 0;

    const char *filename = argv[1];  // first argument is the CSV file name

    // If param is 0, we expect a period
    if (chosenParameter == 0 && argc > 4) {
        chosenPeriod = atoi(argv[4]);
    }

    // If param is 1 we expect a chosenDay
    if (chosenParameter == 1 && argc > 3) {
        strncpy(chosenDay, argv[3], sizeof(chosenDay));
    }

    // If param is 2 we expect a chosenStartDay and chosenEndDay
    if (chosenParameter == 2 && argc > 5) {
        strncpy(chosenStartDay, argv[5], sizeof(chosenStartDay));
        strncpy(chosenEndDay, argv[6], sizeof(chosenEndDay));
    }

    createTable(&completeTable, filename);
    createFilteredTable(completeTable, &filteredTable, chosenDay, chosenParameter, chosenStartDay, chosenEndDay);
    printInformation(filteredTable, totalCost, chosenPeriod);

    return 0;
}