//Zellautomat



#include <stdio.h>
#include <stdlib.h>

void Ausgabe();
int durchlauf, i, l, r;
int zeile1[100], zeile2[100];
const int zelletot  = 0;
const int zellelebt = 1;
double zufall;


//________________________________________________________________


int main()
{
	//erste Zeile
	
	for (i=0;i<=99;i++)
	{
		zufall=(double)rand()/RAND_MAX; 
		if (zufall<1.9)
			zeile1[i]=zellelebt;
		else
			zeile1[i]=zelletot;
	}
	
	Ausgabe();  
	
	//naechste zeile berechnen
	
	for(durchlauf=0;durchlauf<=100;durchlauf++)
	{
		for (i=0;i<=99;i++)
		{
			//Randbedingungen     
			
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

	return 0;
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