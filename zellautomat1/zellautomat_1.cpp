//Zellautomat


#include <stdio.h>
//#include <math.h>
//#include <stdlib.h>

void Ausgabe();
int durchlauf, i;
int zeile1[100], zeile2[100];
const int zelletot  = 0;
const int zellelebt = 1;
int l,r;


//________________________________________________________________


int main()
{
	
	//double r;

	//Randbedingungen
	
	//erste Zeile
	
	for (i=0;i<=99;i++)
		zeile1[i]=zelletot;
	zeile1[50]=zellelebt;
	zeile1[51]=zellelebt;
	zeile1[52]=zellelebt;
	
	//naechste zeile berechnen
	
	for(durchlauf=0;durchlauf<=100;durchlauf++)
	{
		for (i=0;i<=99;i++)
		{ 
			if(i==0)
				l=99;
			else
				l=i-1;
			if(i==99)
				r=0;
			else
				r=i+1;
			if (zeile1[l]==zeile1[r])
				zeile2[i]=zelletot;
			else 
				zeile2[i]=zellelebt;
		}
		
		for (i=0;i<=99;i++) 
			zeile1[i]=zeile2[i];
		Ausgabe();
	}
}


//________________________________________________________________


void Ausgabe()
{
	int i;
	for (i=0;i<=99;i++)
	{
		switch (zeile1[i])
		{
		case zelletot:
			printf(" ");
			break;
		case zellelebt:
			printf("@");
			break;
		}
	}
	printf ("\n"); 
}