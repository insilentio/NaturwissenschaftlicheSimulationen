//Ferromagnet mit Temperaturanstieg


//#include "/app/physik/pgplot/cpgplot.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif

const int up=1;
const int down=-1;
const int L=22;      //totale gittergroesse, gitter geht von 0 bis L-1 !
const int N=100000;     //echtes gitter geht von 1 bis L-2
const int D=16;        //anzahl Temperaturen
const int s=5;        //Temperaturschritte=1/s, Tmax=D/s     

int wald[L][L];
int wald2[L][L];


//________________________________________________________________


int main(int argc, char *argv[])
{
	double p,MM,M,r,rho;
	int i,j,k,x,y,E1,E2,E,t;
	float vMM[D],vT[D],T,Tmax; 
	
/*	if(cpgbeg(0, "/XWIN", 1, 1) != 1)
		exit(EXIT_FAILURE);
	
	cpgask(1);
	cpgenv(1.0, (L-2), 1.0,(L-2), 0, -2);
	cpglab(" ", " ", "PGPLOT Ferromagnet");
*/	
	//printf ("Dichte=");
	//scanf("%lf\n", &rho);
	rho = atof(argv[1]);           //rho: anteil spin up
	M=0; 
	
	for(i=1; i<L-1; i++)
	{
		for(j=1; j<L-1; j++)
		{
			r =(double)rand()/RAND_MAX;
			
			if(r>rho)
			{
				wald[i][j]=down;
				M=M-1;
//				cpgsci (3);              //spin down=gruener Pfeil
//				cpgpt1 (i,j,2262);
			}
			else
			{
				wald[i][j]=up;
				M=M+1;
//				cpgsci (2);              //spin up=roter Pfeil
//				cpgpt1 (i,j,2264);
			}
		}
	}
	
	for(i=0; i<L; i++)        //per. rand setzen, wird nicht dargestellt  
	{
		wald[i][0] =wald[i][L-2];
		wald[i][L-1] =wald[i][1];
		wald[0][i] =wald[L-2][i];
		wald[L-1][i] =wald[1][i];
	}
	
	for(t=0;t<D;t++)
	{
		MM=0;
		
		for(k=0;k<N;k++)
		{
			x=int(1+(L-2)*(double)rand()/RAND_MAX);
			y=int(1+(L-2)*(double)rand()/RAND_MAX);
			wald2[x][y]=-wald[x][y];
			E1=-(wald[x-1][y] + wald[x][y-1] + wald[x][y+1] + wald[x+1][y])*wald[x][y];
			E2=-(wald[x-1][y] + wald[x][y-1] + wald[x][y+1] + wald[x+1][y])*wald2[x][y];
			E=E2-E1;
			r =(double)rand()/RAND_MAX;
			T =(double)t/double(s);
			p =exp(-(double)E/T);  
			
			if(p > r)
			{
				wald[x][y]=wald2[x][y];
				if(wald[x][y]==up)
				{
/*					cpgsci (0);
					cpgpt1 (x,y,2262);
					cpgsci (0);
					cpgpt1 (x,y,2264);
					cpgsci (2);
					cpgpt1 (x,y,2262);
*/					M=M+2;
				}
				else
				{
					M=M-2;
/*					cpgsci (0);
					cpgpt1 (x,y,2262);
					cpgsci (0);
					cpgpt1 (x,y,2264);
					cpgsci (3);
					cpgpt1 (x,y,2264);
*/				}
			}
			
			MM=MM+M;
			
			for(i=0; i<L; i++)              //per. rand updaten, wird nicht dargestellt  
			{
				wald[i][0] =wald[i][L-2];
				wald[i][L-1] =wald[i][1];
				wald[0][i] =wald[L-2][i];
				wald[L-1][i] =wald[1][i];
			}
		}
		
		MM=MM/(N*(L-2)*(L-2));
		printf("M=%f\n",MM); 
		vMM[t]=MM;
		vT[t]=T;
	}
	
	Tmax=float(D)/float(s);
/*	cpgsci (1);
	cpgenv(0.0, Tmax, -1.0, 1.0, 0, 0);
	cpglab("T", "<m>", "PGPLOT Ferromagnet");
	cpgpt(D,vT,vMM,227);
	
	cpgend();
*/	return EXIT_SUCCESS;
}