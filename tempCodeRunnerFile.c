#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

int intRandom(int min, int max)
{
    return min + rand() % (max + 1 - min);
}

double doubleRandom(double min, double max)
{
    double scale = rand() / (double)RAND_MAX; /* [0, 1.0] */
    return min + scale * (max - min);         /* [min, max] */
}

void writeFile()
{
    FILE *f;
    chdir("test_case");
    for (int i = 1; i < 101; i++)
    {
        char name[] = "input";
        char no[MAX];
        char format[] = "txt";
        char fileName[MAX];
        sprintf(no, "%d", i);
        sprintf(fileName, "%s%s.%s", name, no, format);
        // printf("%s\n", fileName);
        f = fopen(fileName, "w");
        if (f == NULL)
        {
            printf("Error!");
            exit(1);
        }
        // row, column belongs to [100; 500]
        int row = intRandom(100, 500);
        int column = intRandom(100, 500);

        // Location of the first virus
        // firstRow belongs to [1, the number of row]
        int firstRow = intRandom(1, row);
        // firstColumn belongs to [1, the number of column]
        int firstColumn = intRandom(1, column);
        int MAX_NUMBER_OF_VIRUS = intRandom(100 * 100, row * column);
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
void generateInput(){
    FILE *f;
    char filename[MAX];
    char no[MAX];
    for (int i = 1; i <= 100; i++)
    {
        
        snprintf(filename, MAX, "input%d", i);
        printf("%s\n", filename);
        f = fopen ("input", "r");
        fprintf(f,"hello");
    }
    fclose(f);
    
}

int main()
{
    // writeFile();
    generateInput();
}
