//Euler-Variante

#include <stdio.h>

int main ()
{
   double g,l,dt,fi,w,t;
   
   g=9.81;
   l=1;
   dt=0.04;
   t=0;
   fi=1;
   w=0;
   
	do
	{
		t += dt;
		w -= g / l * fi * dt;
		fi += w * dt;
		
		printf("%f %f\n",t,fi);  
	}
	while(t<=2);
        
  return 0;     
}