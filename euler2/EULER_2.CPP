//evt. eine Version von Euler
#include <stdio.h>


int main ()
{
	double dt,p,v,ca,rho,m,vend,t,tend;
	
	t=0;
	v=4;
	dt=0.1;
	p=400;
	m=70;
	ca=0.5*0.33;
	vend=14;
	rho=0.9;
	tend=100;

   do
	{
      t+=dt;
      v=v+p/(m*v)*dt-(ca*rho*v*v)/m*dt;

      printf("%f %f\n",t,v);

   }
	while(t<=tend);
	
	return 0;

}