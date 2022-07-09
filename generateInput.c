#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
const long MAX_ROW = 50;
const long MAX_COLUMN = 50;

int intRandom(const long min, const long max)
{
    return min + rand() % (max + 1 - min);
}

double doubleRandom(double min, double max)
{
    double scale = rand() / (double)RAND_MAX; /* [0, 1.0] */
    return min + scale * (max - min);         /* [min, max] */
}

void generateInput()
{
    FILE *f;
    for (int i = 1; i < 101; i++){
        char name[] = "test_case\\test_case";
        char no[MAX];
        char format[] = "txt";
        char fileName[MAX];
        sprintf(no, "%d", i);
        sprintf(fileName, "%s%s\\%s%s.%s", name, no,"input",no, format);
        f = fopen(fileName, "w");
        if (f == NULL)
        {
            printf("Error!");
            exit(1);
        }
        // row, column belongs to [20; 50]
        int row = intRandom(20, MAX_ROW);
        int column = intRandom(20, MAX_COLUMN);

        // Location of the first virus
        // firstRow belongs to [1, the number of row]
        int firstRow = intRandom(1, row);
        // firstColumn belongs to [1, the number of column]
        int firstColumn = intRandom(1, column);
        int MAX_NUMBER_OF_VIRUS = intRandom(row*column/4, row*column/2);
        double w = 1.5;
        double n = doubleRandom(0.5, 2);

        /*
        input.txt construct:
        row column
        firstVirusRow firstVirusColumn
        MAX_NUMBER_OF_VIRUS
        w n
        */
        fprintf(f, "%d %d\n", row, column);
        fprintf(f, "%d %d\n", firstRow, firstColumn);
        fprintf(f, "%d\n", MAX_NUMBER_OF_VIRUS);
        fprintf(f, "%.1lf %.2lf\n", w, n);
        fclose(f);
    }
}

int main()
{
    generateInput();
}
