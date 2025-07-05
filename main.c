#include "functions.h"

/* main */
int main(int argc, char **argv)
{
    // Check if enough arguments are provided
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <csv_file> <chosenParameter> [chosenDay] [chosenPeriod]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    tTable completeTable;
    tTable filteredTable;
    float totalCost = 0.0;
    int chosenPeriod = 0;
    char chosenDay[11] = ""; // optional
    int chosenParameter = atoi(argv[2]); // convert string to int

    completeTable.nHours = 0;
    completeTable.nDays = 0;

    const char *filename = argv[1];  // first argument is the CSV file name

    // If param is 1 or 2, we expect a chosenDay
    if (chosenParameter > 0 && argc > 3) {
        strncpy(chosenDay, argv[3], sizeof(chosenDay));
    }

    // If param is 0, we expect a period
    if (chosenParameter == 0 && argc > 4) {
        chosenPeriod = atoi(argv[4]);
    }

    // Now we can call the rest as usual
    createTable(&completeTable, filename);
    createFilteredTable(completeTable, &filteredTable, chosenDay, chosenParameter);
    printInformation(filteredTable, totalCost, chosenPeriod);

    return 0;
}