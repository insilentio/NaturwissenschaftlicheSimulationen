//ANT Colony Optimization

//#include "/app/physik/pgplot/cpgplot.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//____________________________________________________________


const int anzhorz       = 5;
const int anzvert       = 5;
const int anzstaedte    = anzhorz*anzvert;
const int gitterAbstand = 100;
const int Siedler       = 20;
const int anzameisen    = anzstaedte*Siedler;
const double alpha      = 1;
const double beta       = 1;
const int durchlaeufe   = 50;


//____________________________________________________________


class Ameise
{
public:
  int tabu;
  int schritt;
  int weg [anzstaedte];
  double distanz;
  int stadtvorher;
  void tabuEintrag(int stadt);
  void wegEintrag(int stadt);
  int dejavu(int stadt);
  int tabulistevoll();
  Ameise();
  void setzen (int stadt);
  void beschreibeWeg ();
};

class city
{
public:
  double x;
  double y;
  int name;
  int AmeisenAnwesend;
  Ameise Besucher[anzameisen];
  city();
  void ameisehinzufuegen (Ameise A);
  Ameise ameisewegnehmen ();
  int ameisenuebrig ();
  int unterwegs();
  void setzeAmeisenNeu();
};


//____________________________________________________________


Ameise ameisePopulation[anzameisen];
city staedte[anzstaedte];
double Distanz[anzstaedte][anzstaedte]; 
double Sichtbarkeit[anzstaedte][anzstaedte]; 
double deltatau[anzstaedte][anzstaedte]; 
double tau[anzstaedte][anzstaedte];


//____________________________________________________________


void Ameise::tabuEintrag(int stadt)
{
	tabu|=1<<stadt;
}

Ameise::Ameise() 
{
	tabu=0;
	schritt=0;
	distanz=0;
	stadtvorher=0;
	for (int i=0;i<anzstaedte;i++)
		weg [i]=0;
}

void Ameise::wegEintrag(int stadt)
{
	schritt++;
	weg [schritt]=stadt;
	distanz += Distanz [stadtvorher] [stadt];
	stadtvorher = stadt;
}

void Ameise ::setzen(int stadt)
{
	schritt = 0;
	tabu = 1<<stadt;
	weg [0] = stadt;
	stadtvorher = stadt;
	distanz = 0;
}

int Ameise::tabulistevoll()
{
	for (int j=0; j<anzstaedte; j++)
		if (!(tabu & (1<<j)))
			return 0;
		return 1;
}

int Ameise::dejavu(int stadt)
{
	if (tabu & (1<<stadt))
      return 1;
	return 0;
}

void Ameise::beschreibeWeg ()
{
	printf ("Weg: ");
	for (int i = 0; i < anzstaedte; i++)
		printf ("%d ", weg[i]);
	printf ("\n");
}


//____________________________________________________________


city::city()
{
	AmeisenAnwesend= 0;
}

void city::ameisehinzufuegen (Ameise A)
{
	Besucher [AmeisenAnwesend]= A;
	AmeisenAnwesend++;
	// printf ("ameisehinzufuegen: %d\n",AmeisenAnwesend);
}

Ameise city::ameisewegnehmen ()
{
	int i, j;
	Ameise A =  Besucher[0];
	
	for (j=0; j<AmeisenAnwesend; j++)
		if (!(A = Besucher[j]).tabulistevoll())
			break;
		
		for (i = j; i < AmeisenAnwesend; i++)
			Besucher[i] = Besucher[i+1];
		
		AmeisenAnwesend--;
		return A;
}

int city::ameisenuebrig ()
{
	int ok = 0;
	for (int j=0; j<AmeisenAnwesend; j++)
		if (!Besucher[j].tabulistevoll())
			ok++;
		return ok > 0;
}

int city::unterwegs()
{
	for (int j=0; j<AmeisenAnwesend; j++)
		if (!Besucher[j].tabulistevoll())
			return 1;
		return 0;
}

void city::setzeAmeisenNeu()
{
	for (int j=0; j<AmeisenAnwesend; j++)
		Besucher[j].setzen (name);
}


//____________________________________________________________


int unterwegs()
{
	for (int j=0; j< anzstaedte; j++)
		if (staedte[j].unterwegs())
			return 1;
		return 0;
}

double kuerzesterweg(Ameise& wer)
{
	double minDistanz = 1e100;
	for (int j=0; j< anzstaedte; j++)
	{
		city c = staedte[j];
		//    printf ("AmeisenAnwesend = %d\n", c.AmeisenAnwesend);
		for (int i = 0; i < c.AmeisenAnwesend; i++)
			if (c.Besucher[i].distanz < minDistanz)
			{
				minDistanz = c.Besucher[i].distanz;
				wer = c.Besucher[i];
			}
	}
	
	return minDistanz;
} 


//____________________________________________________________


int main ()
{
	int i,j;
	// Initialisierung
	i=0;
	for (int x= 0; x< anzhorz; x++)
		for (int y=0; y< anzvert; y++)
      {
			staedte[i].x= x*gitterAbstand;
			staedte[i].y= y*gitterAbstand;
			staedte[i].name = i;
			i++;
      }
		for (i= 0; i< anzstaedte; i++)
			for (j=0; j< anzstaedte; j++)
			{
				double dx= staedte[i].x- staedte[j].x;
				double dy= staedte[i].y- staedte[j].y;
				Distanz [i][j]= sqrt(dx*dx+dy*dy);
				if (i != j)
					Sichtbarkeit [i][j]= 1/ Distanz [i][j];
				else
					Sichtbarkeit[i][j] = 0;
				tau[i][j]=0.01;
				deltatau[i][j]= 0.01;
			}
			
			int k=0;
			for (i= 0; i< anzstaedte; i++)
				for (j=0; j< Siedler; j++)
				{
					ameisePopulation[k].setzen(i);
					staedte[i].ameisehinzufuegen (ameisePopulation[k]);
					k++;
				}
				
				//____________________________________________________________
				
				double minDistanz = 1e100;
				Ameise sieger, globalerSieger;
				
				for (int n=0;n<durchlaeufe;n++)
				{
					do
					{
						for (i= 0; i< anzstaedte; i++)
						{
							while (staedte[i].ameisenuebrig())
							{
								Ameise A= staedte[i].ameisewegnehmen();
								if (!A.tabulistevoll()){ //!: tabuliste nicht voll
									double p[anzstaedte];
									for (j=0; j<anzstaedte; j++)
										p[j]=pow (tau[i][j],alpha)* pow (Sichtbarkeit[i][j], beta);
									double sigma=0;
									for (j=0; j<anzstaedte; j++)
										sigma+=p[j];
									for (j=0; j<anzstaedte; j++)
										p[j]/=sigma;
									do
									{
										double zufall=(double)rand()/RAND_MAX;
										sigma=0;
										for (j=0; j<anzstaedte; j++)
										{
											sigma+=p[j];
											if (sigma>zufall)
												break;
										}
										//                      printf ("sigma=%f, zufall=%f\n", sigma, zufall);
										
									}
									while (A.dejavu(j));
									
									//    printf ("n = %d: von %d nach %d, tabu = %04x\n", n, i, j, A.tabu);
									
									A.wegEintrag(j);
									A.tabuEintrag(j);
									staedte[j].ameisehinzufuegen (A);
									tau[i][j]+=deltatau[i][j];
								}
								else
									staedte[i].ameisehinzufuegen (A);
							}
						}
					}
					while (unterwegs());
					
					
					double minDist = kuerzesterweg(sieger);
					if (minDist < minDistanz)
					{
						minDistanz = minDist;
						globalerSieger = sieger;
					}
					
					for (i = 0; i < anzstaedte; i++)
						staedte[i].setzeAmeisenNeu ();
					
					//printf ("minimale Distanz = %f\n", minDist);
					//sieger.beschreibeWeg();
					printf ("Durchgang %d: minimale Distanz = %f\n", n+1, minDistanz);
					globalerSieger.beschreibeWeg();
					//printf ("durchlaeufe = %n\n", durchlaeufe);
				}
				return 0;
}
