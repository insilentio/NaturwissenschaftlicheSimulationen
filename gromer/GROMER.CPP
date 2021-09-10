//Gromer


#include <stdio.h>
#include <math.h>

int main ()
{
	double g, l, dt, theta, omega, t, omega_neu, q, F, Omega;
   
	g     = 9.81;
	l     = 1;
	dt    = 0.01;
	t     = 0;
	theta = 1;
	omega = 0.1;
	q     = 0.1;
	F     = 1;
	Omega = 1;
	
	do
	{
		t += dt;
		omega  = omega + dt * (-g / l*sin(theta) - q*omega + F*sin(Omega*t));
		theta += omega * dt;
		
		printf("%f %f %f\n",t,theta,omega);  
	}
	while(t <= 300);
	
	return 0;       
}