//Oszillator mit Verlet-Methode inkl. Daempfung


#include <stdio.h>
#include <math.h>

int main ()
{
	double omega,omega_1,omega_neu,theta,theta_1,theta_neu,g,l,dt,t,q;
	
	//Startwerte
	omega_1=0;
	theta_1=1;
	g=9.81;
	l=1;
	dt=0.001;
	t=0;
	q=0.1;
	//F=10;
	//Omega=PI;

	//Euler
	omega = omega_1 - g / l * sin(theta_1) * dt;
	theta = theta_1 + omega_1 * dt;

	do
	{
		//Gleichungen
		omega_neu=2*omega-omega_1-dt*dt*(g/l*cos(theta)*omega+q*(-g/l*sin(theta)-q*omega));
		theta_neu=2*theta-theta_1-dt*dt*(g/l*sin(theta)+q*omega);
		
		//loop
		omega_1=omega;
		omega=omega_neu;
		theta_1=theta;
		theta=theta_neu;
		t+=dt;
		
		printf("%f %f %f\n",t,omega_neu,theta_neu);
	}
	while(t<=100);
	
	return 0;
}