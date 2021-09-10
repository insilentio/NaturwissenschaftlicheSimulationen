//Ferromagnet nach Montecarlo-Verfahren


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

const int up = 1;
const int down = -1;
const int N=50;
const int H=100000;
const int J=1;
const double T=1;
const int k=1;

int magnet1[N][N];
int magnet2[N][N];
int Ealt[N][N];
int Eneu[N][N];
int deltaE[N][N];
int M[N][N];
int Mag[N][N];


//________________________________________________________________


int main(int argc, char *argv[])
{
  double y,r,r2,rho,Mag;
  int i,j,x,M;

/*  if(cpgbeg(0, "/XWIN", 1, 1) != 1)
    exit(EXIT_FAILURE);
  cpgask(1);
  cpgenv(0.0, N, 0.0, N, 0, -2);
  cpglab(" ", " ", "PGPLOT q2s");
*/
  
  //printf ("Dichte=");
  //scanf("%lf\n", &rho);
  rho = atof(argv[1]);

  M = 0;
  for(i=0; i<N; i++)
  {
    for(j=0; j<N; j++)
	 {
      r =(double)rand()/RAND_MAX;
      if(r<rho) 
		{
			magnet1[i][j] = down;
			M=M-1;
//			cpgsci (3);
//			cpgpt1 (i,j,2264);
      }
      else
		{
			magnet1[i][j] = up;
			M=M+1;
//			cpgsci (2);
//			cpgpt1 (i,j,2262);
      }
    }
  }

  Mag = 0;
  
  for (x=0; x<H;x++)
  {
	  //Auswaehlen eines Magneten zufaellig;
	  i=(int)(N*(double)rand()/RAND_MAX);
	  j=(int)(N*(double)rand()/RAND_MAX);
	  //delta E berechnen
	  
	  Ealt[i][j]=-J*((magnet1[i][j])*(magnet1[i-1][j]+magnet1[i+1][j]+magnet1[i][j-1]+magnet1[i][j+1]));
	  deltaE[i][j]=-2*Ealt[i][j];
	  
	  //erzeugen einer Zufallszahl zwischen [0,1]
	  r2=(double)rand()/RAND_MAX;
	  
	  if(exp(-deltaE[i][j]/(k*T))>r2)
	  {
		  M=M-2*magnet1[i][j];
		  magnet1[i][j]=-magnet1[i][j];
		  if (magnet1[i][j]==up)
		  {
/*			  cpgsci (0);
			  cpgpt1 (i,j,2262);
			  cpgpt1 (i,j,2264);
			  cpgsci (2);
			  cpgpt1 (i,j,2262);
*/		  }
		  else
		  {
/*			  cpgsci (0);
			  cpgpt1 (i,j,2262);
			  cpgpt1 (i,j,2264);
			  cpgsci (3);
			  cpgpt1 (i,j,2264);
*/		  }
	  }
	  
	  Mag=Mag+M;
  }
  
  Mag=Mag/(H*N*N);
  printf("Magnetisierung=%f\n",Mag);

  
//  cpgend();
  return EXIT_SUCCESS;
}