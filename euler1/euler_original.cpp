//Euler (mein allererstes Programm!!)


#include <stdio.h>
int main ()
{
	double t, dt, N, tau, tend;
	
	//Initialisieren: Startwerte und Parameter
	
	t    = 0;
	dt   = 0.001;
	N    = 1;
	tau  = 1;
	tend = 3*tau;
	
	//Schritt 2 und 3: Euler-Algorithmus
	do
	{
		t += dt;
		N -= dt*N / tau;
		printf("%f %f\n",t,N);
	}
	while(t <= tend);
	
	return 0;
}