//Simulation eines Waldbrands

#include <stdlib.h>
#include <stdio.h>
#include <math.h>


void Ausgabe();
int wald[100][100];	//Definition des Arrays
int i,j;
const int keinBaum=0;
const int Baum=1;
const int Baumbrennt=2;
const int Abgebrannt=3;

int main(){

double r,p=0.63;


//Wald aufbauen, p ist vorgegeben

 for (i=0;i<=99;i++)
   for (j=0;j<=99;j++){
     r= (double)rand()/RAND_MAX;
     if (r<p)
       wald[i][j]=Baum;
     else
       wald[i][j]=keinBaum;
   }

//Anzuenden
  for(j=0;j<=99;j++)
    if (wald[0][j]==Baum)
      wald[0][j]=Baumbrennt;
  

//Abbrennen lasse
  
  int brenntNoch=1;
  while (brenntNoch){
    brenntNoch=0;
    for (i=1;i<=99;i++)
      for(j=1;j<=99;j++)
        if(wald[i-1][j]==Baumbrennt||
           wald[i][j-1]==Baumbrennt){
          if (wald[i][j]==Baum){
            wald[i][j]=Baumbrennt;
            brenntNoch=1;
          }
        }
    // if (wald[i-1][j]==Baumbrennt)
    //  wald [i-1][j]=Abgebrannt;
    //if (wald[i][j-1]==Baumbrennt)
    // wald [i][j-1]=Abgebrannt;
    Ausgabe();
  }
}



void Ausgabe(){
  int i,j;
  for(i=0;i<=99;i++){
    for (j=0;j<=99;j++)
      switch (wald[i][j]){
      case Baum:
        printf("B");
        break;
      case keinBaum:
        printf(" ");
        break;
      case Baumbrennt:
        printf("*");
        break;
      case Abgebrannt:
        printf(".");
        break;
      } 
    printf("\n");
  }
}