#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#define MAX_VALUE 10000
#include <stdlib.h>


typedef struct VirusPlace{
    long x;
    long y;
} VirusPlace;

//Variable
//row and column of the matrix
int row,column;
//row and column of the first virus
int firstVirusRow, firstVirusColumn;
//the max number of virus
int MAX_NUMBER_OF_VIRUS ;
// tham so hieu chinh, so mu virus phat trien
double w;
double n;


//intialize the aray of virus
VirusPlace virus[MAX_VALUE];
int nVirus=0;
VirusPlace candidate[MAX_VALUE];
int nCandidate=0;
double c[MAX_VALUE][MAX_VALUE];
double chance[MAX_VALUE];
bool grow[MAX_VALUE][MAX_VALUE];


void readFile(){
    FILE *f;
    char fileName[100];

    f = fopen("test_case\\test_case3\\input3.txt", "r");
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



void writeFile(){
    FILE *f;
    f = fopen("test_case\\test_case3\\output3.txt","w");
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

void addVirus(int u,int v){
    virus[nVirus].x=u;
    virus[nVirus].y=v;
    nVirus++;
    grow[u][v]=true;
    nCandidate=0;
    //add o xung quanh (u,v) to candidate.
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
//    for(int i=0;i<nVirus;++i){
//        printf("%d %d \n",virus[i].x,virus[i].y);
//    }
//    printf("+++++++++++++++++++++++++++++++++++++++++\n");
//    for (int i=0;i<nCandidate;++i){
//        printf("%d %d \n",candidate[i].x,candidate[i].y);
//
//    }
//    printf("--------------------------------------------\n");
}

void init(){
    for(int i=0;i<row;++i){
        for(int j=0;j<column;++j){
            grow[i][j]=false;
            c[i][j]=1;
        }
    }
    addVirus(firstVirusRow, firstVirusColumn);

}

void sor(){
    for(int i=0;i<row;++i){
        for(int j=0;j<column;++j){
            if(i==0 || i==row-1||j==0 || j==column-1) {
                c[i][j]=1;
            }else c[i][j]= w/4*(c[i+1][j]+c[i-1][j]+c[i][j+1]+c[i][j-1])+(1-w)*c[i][j];
        }
    }
}

void eat(){
    for(int i=0;i<row;++i){
        for(int j=0;j<column;++j){
            if (grow[i][j]== true)  c[i][j]=0;
        }
    }
}

void computeProbality(){
    int sum=0;
    for (int i=0;i<nCandidate;++i){
        sum+=pow(c[candidate[i].x][candidate[i].y],n);
    }
    for(int i=0;i<nCandidate;++i){
        chance[i]=(double)pow(c[candidate[i].x][candidate[i].y],n)/sum;
    }
}

void growth(){
    int max=chance[0];
    int index=0;
    for(int i=0;i<nCandidate;++i){
        for(int j=i+1;j<nCandidate;++j){
            if(chance[i]>chance[j]){
                float tmp=chance[i];
                chance[i]=chance[j];
                chance[j]=tmp;
            }
        }
    }

    addVirus(candidate[0].x,candidate[0].y);
    addVirus(candidate[1].x,candidate[1].y);
    addVirus(candidate[2].x,candidate[2].y);
    addVirus(candidate[3].x,candidate[3].y);
}

void solve(){
    while(nVirus<MAX_NUMBER_OF_VIRUS){
        sor();
        eat();
        computeProbality();
        growth();
    }
}

int main(){
    init();
    readFile();
    solve();
//    printf("--------------------------------------------\n");
//    for(int i=0;i<row;++i){
//        for(int j=0;j<column;++j){
//            printf("%.2f ", c[i][j]);
//        }
//        printf("\n");
//    }
    writeFile();
    return 0;
}