//Magnete

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
const int N=40;

int wald[N][N];
int wald2[N][N];

int main(int argc, char *argv[])
{
  double T,x,y,r,rho;
  int i,j,brenntNoch;
  brenntNoch = 1;

/*  if(cpgbeg(0, "/XWIN", 1, 1) != 1)
    exit(EXIT_FAILURE);

  cpgask(1);
  cpgenv(0.0, N, 0.0, N, 0, -2);
  cpglab(" ", " ", "PGPLOT q2s");
*/
  
  //printf ("Dichte=");
  //scanf("%lf\n", &rho);
  rho = atof(argv[1]);

  for(i=0; i<N; i++)
  {
    for(j=0; j<N; j++)
	 {
      r =(double)rand()/RAND_MAX;
      
		if(r<rho)
		{
        wald[i][j] = down;
//        cpgsci (3);
//        cpgpt1 (i,j,254);
      }
      
		else
		{
        wald[i][j] = up;
//        cpgsci (2);
//        cpgpt1 (i,j,254);
      }
    }
  }


  //getchar();  
  while(brenntNoch==1)
  {
    brenntNoch=0;
    for(i=0; i<N; i++)
	 {
      for(j=0; j<N; j++)
		{
        wald2[i][j] = wald[i][j];
      
		  if(wald[i-1][j] + wald[i][j-1] + wald[i][j+1] + wald[i+1][j]==0)
		  {
          wald2[i][j]=-wald[i][j];
          brenntNoch=1;
          if(wald[i][j]==up) 
			 {
//            cpgsci (2);
            //        cpgpt1(i , j, 2262);
//            cpgpt1 (i,j,254);
          }
			 else 
			 {
//            cpgsci (3);
            //        cpgpt1(i , j, 2264);}
//            cpgpt1 (i,j,254);
          }
        }
      }
    }
    
	 for(i=0; i<N; i++)
	 {
      for(j=0; j<N; j++)
			wald[i][j] = wald2[i][j];
	 }
    
	 //    usleep(200000);
    //getchar();  
  }  
  
//  cpgend();
  return EXIT_SUCCESS;
}