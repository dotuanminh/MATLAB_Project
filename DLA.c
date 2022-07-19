#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define MAX 100
#define MAX_VALUE 10000

//Virus location structure
typedef struct VirusPlace{
    long x;
    long y;
} VirusPlace;

//Variable
//Row and column of the matrix
int row = 0,column = 0;
//Row and column of the first virus
int firstVirusRow = 0, firstVirusColumn = 0;
//The max number of virus
int MAX_NUMBER_OF_VIRUS = 10000;
// tham so hieu chinh, so mu virus phat trien
double w = 1.5;
double n = 1.2;

//Virus in the matrix
VirusPlace virus[MAX_VALUE];
int nVirus=0;
//Candidate(which can be virus) in the matrix
VirusPlace candidate[MAX_VALUE];
int nCandidate=0;
//food level
double c[MAX_VALUE][MAX_VALUE];
//Probability a location can turn into a virus
double chance[MAX_VALUE];
//boolean to check whether there is a virus in this location
bool grow[MAX_VALUE][MAX_VALUE];

//This function reads the file "inout.txt" 
void readFile(int i){
    FILE *f;
    char fileName[100];
    char name[] = "test_case\\test_case";
    char no[MAX];
    char format[] = "txt";
    sprintf(no, "%d", i);
    sprintf(fileName, "%s%s\\%s%s.%s", name, no,"input",no, format);
    f = fopen(fileName, "r");
    // f = fopen("input.txt", "r");
    if(f == NULL){
        printf("No file found!");
        exit(1);
    }
    fscanf(f, "%d%d", &row, &column);
    fscanf(f, "%d%d", &firstVirusRow, &firstVirusColumn);
    fscanf(f, "%d", &MAX_NUMBER_OF_VIRUS);
    fscanf(f, "%lf%lf", &w, &n);
    fclose(f);
}
/*
input.txt construct:
row column
firstVirusRow firstVirusColumn
MAX_NUMBER_OF_VIRUS
w n
*/


//This function writes the matrix c[i][j] to the file "output.txt"
void writeFile(int i){
    FILE *f;
    char fileName[100];
    char name[] = "test_case\\test_case";
    char no[MAX];
    char format[] = "txt";

    sprintf(no, "%d", i);
    sprintf(fileName, "%s%s\\%s%s.%s", name, no,"output",no, format);
    f = fopen(fileName, "w");
    
    if(f == NULL){
        printf("Error!");
        exit(1);
    }
    for(int i=0;i<row;++i){
        for(int j=0;j<column;++j){
            fprintf(f,"%.2f ", c[i][j]);
        }
        fprintf(f,"\n");
    }
    fclose(f);
}

//This function adds virus
void addVirus(int u,int v){
    //add virus to array virus
    virus[nVirus].x=u;
    virus[nVirus].y=v;
    nVirus++;
    //there is virus at (u,v) -> grow[u][v]=true
    grow[u][v]=true;
    //add neighbors of (u,v) to candidate.
    nCandidate=0;
    int a[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
    for(int j=0;j<nVirus;++j){
        for(int i=0;i<4;++i){
                int candidateRow=virus[j].x+a[i][0];
                int candidateColumn=virus[j].y+a[i][1];
                if(0<=candidateRow && candidateRow<row && 0<=candidateColumn && candidateColumn <column && grow[candidateRow][candidateColumn]==false){
                    candidate[nCandidate].x=candidateRow;
                    candidate[nCandidate].y=candidateColumn;
                    nCandidate++;
                }
        }
    }
}

//This function intiallizes the value of all variables
void init(){
    for(int i=0;i<row;++i){
        for(int j=0;j<column;++j){
            grow[i][j]=false;
            c[i][j]=1;
        }
    }
    //add the first virus to the matrix
    addVirus(firstVirusRow, firstVirusColumn);
}

//This functions calculates the food level (c[i][j])
void sor(){
    for(int i=0;i<row;++i){
        for(int j=0;j<column;++j){
            if(i==0 || i==row-1||j==0 || j==column-1) {
                c[i][j]=1;
            }else c[i][j]= w/4*(c[i+1][j]+c[i-1][j]+c[i][j+1]+c[i][j-1])+(1-w)*c[i][j];
        }
    }
}

//This functions makes the food level at a place which has virus to 0.
void eat(){
    for(int i=0;i<row;++i){
        for(int j=0;j<column;++j){
            if (grow[i][j]== true)  c[i][j]=0;
        }
    }
}

//This function calculates the probability
void computeProbality(){
    int sum=0;
    for (int i=0;i<nCandidate;++i){
        sum+=pow(c[candidate[i].x][candidate[i].y],n);
    }
    for(int i=0;i<nCandidate;++i){
        chance[i]=(double)pow(c[candidate[i].x][candidate[i].y],n)/sum;
    }
}

//This functions randomly pick a candidate to become virus
void growth(){
    //If the random number smaller than the chance in any cell, we will add it to the array virus
    for(int i=0;i<nCandidate;++i){
        float turnToVirusPercentage = n = (float)rand()/RAND_MAX;;
        if(turnToVirusPercentage<=(float)chance[i]){
            addVirus(candidate[i].x,candidate[i].y);
            if(nVirus==MAX_NUMBER_OF_VIRUS) break;
        }
    }
}

//This functions implements the process, until we get enough virus then sor()->eat()->computeProbality()->growth()
void solve(){
    while(nVirus<MAX_NUMBER_OF_VIRUS){
        sor();
        eat();
        computeProbality();
        growth();
    }
}

//main
int main(){
    
    readFile(10);
    init();
    solve();
    writeFile(10);
    printf("Done!");
    return 0;
}

