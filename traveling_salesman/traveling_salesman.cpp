//traveling salesman problem


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



const int N=10000;          //anz. durchlaeufe
const int S=100;            //anz. staedte
const int TS=10;            //anz. temperaturen
const double Pstart=0.001;  //wahrsch. fuer annahme unguenstigen wechsels

int ort[S+1];               //momentaner ort auf der route
float koord[S][2];          //matrix mit staedtekoordinaten
float XK[S+1];              //X-koordinaten der route
float YK[S+1];              //Y-koordinaten der route
float XKmin[S+1];           //X-koordinaten der momentan besten route
float YKmin[S+1];           //Y-koordinaten der momentan bestenroute



int main()
{
  double r1,r2,deltar,rmin,w,z,P,xk,yk;
  int x,y,a,b,v,t;
  P=Pstart;

  //Start- und Zielort bei Stadt 0
  ort[0]=0;          
  ort[S]=0;
  
/*  if(cpgbeg(0, "/XWIN", 1, 1) != 1)
    exit(EXIT_FAILURE);
  cpgask(1);
  cpgenv(0.0,1.0,0.0,1.0, 0, -2);
  cpglab(" ", " ", "TRAVELING SALESMAN");
*/  
  for(x=0; x<S; x++)
  {
    for(y=0; y<2; y++)
	 {
      koord[x][y]=(float)rand()/RAND_MAX;   //ortskoordinaten zufaellig zuordnen
    }
    XK[x]=koord[x][0];
    YK[x]=koord[x][1];
//    cpgsci (3);
//    cpgpt1 (koord[x][0],koord[x][1],857);
  }
  
  //nehme stadt 0, dann gehe der reihe nach weiter
  XK[S]=koord[0][0];
  YK[S]=koord[0][1];
  
  for(x=1;x<S;x++)
    ort[x]=x;
  r1=0;                     //weglaenge
  
  for(y=0;y<S;y++)
    r1=r1+pow(XK[y]-XK[y+1],2)+pow(YK[y]-YK[y+1],2);
  rmin=r1;
  
  for(t=0;t<TS;t++)
  {
    P=Pstart-t*Pstart/TS;
    
	 for(x=0;x<N;x++)
	 {
      a=1+(S-1)*(double)rand()/RAND_MAX;
      b=1+(S-1)*(double)rand()/RAND_MAX;
      
		if(a>b)
		{
        v=a;
        a=b;
        b=v;
      }
		
		r2=r1+pow(XK[a-1]-XK[b],2)+pow(YK[a-1]-YK[b],2)+pow(XK[b+1]-XK[a],2)+pow(YK[b+1]-YK[a],2)-pow(XK[a-1]-XK[a],2)-pow(YK[a-1]-YK[a],2)-pow(XK[b+1]-XK[b],2)-pow(YK[b+1]-YK[b],2);
      deltar=sqrt(r2)-sqrt(r1);           //wegunterschied
      z=(double)rand()/RAND_MAX;
      w=exp(-(double)deltar/P);
      
		if(w>z)
		{
        while(b>a)
		  {
          xk=XK[a];
          XK[a]=XK[b];
          XK[b]=xk;
          yk=YK[a];
          YK[a]=YK[b];
          YK[b]=yk;
          a=a+1;
          b=b-1;
        }

/*        cpgeras();
        cpgsci(3);
        for(y=0;y<S;y++)
          cpgpt1 (koord[y][0],koord[y][1],857);
        cpgsci (4);
        cpgline(S+1,XK,YK);
*/        if(r2<rmin)
		  {
          rmin=r2;
        
			 for(y=0;y<S+1;y++)
			 {
            XKmin[y]=XK[y];
            YKmin[y]=YK[y];
          }
        }
        
		  printf("r=%f P=%f\n\n",r1,P);
        //      printf("P=%f\n\n",P);
        r1=r2;
      }
    }
  }
  
  printf("rmin=%f\n",rmin);
/*  cpgenv(0.0,1.0,0.0,1.0, 0, -2);
  cpgsci(6);
  cpglab(" "," ","TRAVELING SALESMAN, optimaler Weg");
  
  for(y=0;y<S;y++)
  {
    cpgsci (3);
    cpgpt1 (koord[y][0],koord[y][1],857);
  }
  
  cpgsci (4);
  cpgline(S+1,XKmin,YKmin);
  cpgend();
*/  
  return EXIT_SUCCESS;
}