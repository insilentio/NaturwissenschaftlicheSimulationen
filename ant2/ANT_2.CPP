//ANT Colony Optimization

//#include "/app/physik/pgplot/cpgplot.h"
#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include <math.h>


//------------------------------------------------------------------------


const int anzhorz= 6;
const int anzvert= 5;
const int anzstaedte= anzhorz*anzvert;
const int gitterAbstand= 100;
const int Siedler=5;
const int anzameisen=anzstaedte*Siedler;
const double alpha=1;
const double beta=1; // Sichtbarkeit
const int durchlaeufe = 500;
const double verdampfungskoeffizient = 0.8;

class Ameise
{
public:
  int fertig;
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

void Ameise::setzen(int stadt)
{
	schritt=0;
	fertig = 0;
	tabu = 1<<stadt;
	weg [0]=stadt;
	stadtvorher =stadt;
	distanz=0;
}

int Ameise::tabulistevoll()
{
	for (int j=0; j<anzstaedte; j++)
		if (!(tabu & (1<<j)))
			return 0;
		if (!fertig)
		{
			fertig = 1;
			distanz += Distanz[weg[0]][weg[anzstaedte-1]];
		}
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

int city::ameisenuebrig()
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

void zeichneStaedteundWeg (city staedte[], /*int anzstaedte,*/ Ameise a1, Ameise a2)
{
	int i, s;
	float wegx[anzstaedte+1];
	float wegy[anzstaedte+1];

//	cpgeras ();
	
	// Staedte zeichnen
	
	for (i = 0; i < anzstaedte; i++)
	{
/*		cpgpt1 (staedte[i].x, staedte[i].y, 857); 
		if (i == a1.weg[0])
			cpgsci (6);
		else
			cpgsci (3);
		cpgcirc (staedte[i].x, staedte[i].y, 5); 
*/	}
	
	// Wege zeichnen
//	cpgsci (4);
	for (i = 0; i < anzstaedte; i++)
	{
		s = a1.weg[i];
		wegx[i] = staedte[s].x;
		wegy[i] = staedte[s].y;
	}
	s = a1.weg[0];
	wegx[i] = staedte[s].x;
	wegy[i] = staedte[s].y;

//	cpgline (anzstaedte+1, wegx, wegy);

//	cpgsci (1);
	
	for (i = 0; i < anzstaedte; i++)
	{
		s = a2.weg[i];
		wegx[i] = staedte[s].x+2;
		wegy[i] = staedte[s].y+2;
	}
	
	s = a2.weg[0];
	wegx[i] = staedte[s].x+2;
	wegy[i] = staedte[s].y+2;
//	cpgline (anzstaedte+1, wegx, wegy);
}

 
//____________________________________________________________


int main()
{
	int i,j;
	
/*	if(cpgbeg(0, "/XWIN", 1, 1) != 1)
		exit(EXIT_FAILURE);
	cpgask(1);
	cpgenv(-(double)gitterAbstand,(double)anzhorz*gitterAbstand, -(double)gitterAbstand,(double)anzvert*gitterAbstand,0, -2);
	cpglab(" ", " ", "Ant Colony Optimization");
*/	
	// Initialisierung
	srand (3/*getpid()*/);
	i=0;
	for (int x= 0; x< anzhorz; x++)
		for (int y=0; y< anzvert; y++)
      {
			double r1 = ((double)rand()/RAND_MAX*2 - 1);
			double r2 = ((double)rand()/RAND_MAX*2 - 1);
			staedte[i].x= (x+0.5*r1)*gitterAbstand;
			staedte[i].y= (y+0.5*r2)*gitterAbstand;
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
								if (!A.tabulistevoll()) //!: tabuliste nicht voll
								{
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
					
					for (i = 0; i < anzstaedte; i++)
						for (j = 0; j < anzstaedte; j++)
							tau[i][j] *= verdampfungskoeffizient;
						
						double minDist = kuerzesterweg(sieger);
						if (minDist < minDistanz)
						{
							minDistanz = minDist;
							zeichneStaedteundWeg (staedte, /*anzstaedte,*/ globalerSieger, sieger);
							globalerSieger = sieger;
						}
						
						for (i = 0; i < anzstaedte; i++)
							staedte[i].setzeAmeisenNeu ();
						
						printf ("%d: minimale Distanz = %f\n", n, minDistanz);
						globalerSieger.beschreibeWeg();
				}
				
//				cpgend();
				return EXIT_SUCCESS;
}