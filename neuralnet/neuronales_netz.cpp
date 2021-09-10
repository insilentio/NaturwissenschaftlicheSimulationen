/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@                                    @
@ Simulation eines neuronalen Netzes @
@ zur Mustererkennung                @
@                                    @ 
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

 Kompilationsbefehle:
 gcc neuronet.C -c -O2
 g77 -o neuronet neuronet.o -L/app/physik/pgplot -lcpgplot -lpgplot -lX11 -lgcc
-L/usr/X11R6/lib
 setenv PGPLOT_DIR /app/physik/pgplot
*/


#include <iostream.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
//#include "/app/physik/pgplot/cpgplot.h"


//using namespace std;



const int anzMuster = 10;
const int maxGewichte = 100;
/* Funktioniert fuer tanh(x) Aktivierungsfunktion
const int anzNeuronenHidden1 = 10;
const int anzNeuronenHidden2 = 10;
const int anzSchritt = 700;
const double eta =0.02;
const int anzNeuronenHidden1 = 5;
const int anzNeuronenHidden2 = 5;
const int anzSchritt = 2000;
const double eta =0.02;
*/
/* Funktioniert fuer 1/(1+exp(-x)) Aktivierungsfunktion
const int anzNeuronenHidden1 = 10;
const int anzNeuronenHidden2 = 10;
const int anzSchritt = 100;
const double eta =3;
*/

const int anzNeuronenHidden1 = 10;
const int anzNeuronenHidden2 = 10;
const int anzSchritt = 100;
const double eta =3;
const int matrixx=5,matrixy=7;

double referenzmuster[anzMuster][matrixy][matrixx] = {
    {
      {0,1,1,1,0},
      {1,0,0,0,1},
      {1,0,0,0,1},
      {1,0,0,0,1},
      {1,0,0,0,1},
      {1,0,0,0,1},
      {0,1,1,1,0},
    },
    {
      {0,0,1,0,0},
      {0,1,1,0,0},
      {1,0,1,0,0},
      {0,0,1,0,0},
      {0,0,1,0,0},
      {0,0,1,0,0},
      {0,0,1,0,0},
    },
    {
      {0,1,1,1,0},
      {1,0,0,0,1},
      {0,0,0,0,1},
      {0,0,0,0,1},
      {0,1,1,1,0},
      {1,0,0,0,0},
      {1,1,1,1,1},
    },
    {
      {0,1,1,1,0},
      {1,0,0,0,1},
      {0,0,0,0,1},
      {0,0,1,1,0},
      {0,0,0,0,1},
      {1,0,0,0,1},
      {0,1,1,1,0},
    },
    {
      {0,0,0,1,0},
      {0,0,1,1,0},
      {0,1,0,1,0},
      {1,1,1,1,1},
      {0,0,0,1,0},
      {0,0,0,1,0},
      {0,0,0,1,0},
    },
    {
      {1,1,1,1,0},
      {1,0,0,0,0},
      {1,1,1,0,0},
      {1,0,0,1,0},
      {0,0,0,1,0},
      {1,0,0,1,0},
      {0,1,1,0,0},
    },
    {
      {0,0,0,0,1},
      {0,0,0,1,0},
      {0,0,1,0,0},
      {0,1,1,1,0},
      {1,0,0,0,1},
      {1,0,0,0,1},
      {0,1,1,1,0},
    },
    {
      {1,1,1,1,1},
      {0,0,0,0,1},
      {0,0,0,1,0},
      {0,0,1,0,0},
      {0,1,0,0,0},
      {1,0,0,0,0},
      {0,0,0,0,0},
    },
    {
      {0,1,1,1,0},
      {1,0,0,0,1},
      {1,0,0,0,1},
      {0,1,1,1,0},
      {1,0,0,0,1},
      {1,0,0,0,1},
      {0,1,1,1,0},
    },
    {
      {0,1,1,1,0},
      {1,0,0,0,1},
      {1,0,0,0,1},
      {0,1,1,1,0},
      {0,0,1,0,0},
      {0,1,0,0,0},
      {1,0,0,0,0},
    },
};

double muster[anzMuster][matrixy][matrixx] = {
    {
      {0,1,1,1,0},
      {1,0,0,0,1},
      {1,0,0,0,1},
      {1,0,0,0,1},
      {1,0,0,0,1},
      {1,0,0,0,1},
      {0,1,1,1,0},
    },
    {
      {0,0,1,0,0},
      {0,1,1,0,0},
      {1,0,1,0,0},
      {0,0,1,0,0},
      {0,0,1,0,0},
      {0,0,1,0,0},
      {0,0,1,0,0},
    },
    {
      {0,1,1,1,0},
      {1,0,0,0,1},
      {0,0,0,0,1},
      {0,0,0,0,1},
      {0,1,1,1,0},
      {1,0,0,0,0},
      {1,1,1,1,1},
    },
    {
      {0,1,1,1,0},
      {1,0,0,0,1},
      {0,0,0,0,1},
      {0,0,1,1,0},
      {0,0,0,0,1},
      {1,0,0,0,1},
      {0,1,1,1,0},
    },
    {
      {0,0,0,1,0},
      {0,0,1,1,0},
      {0,1,0,1,0},
      {1,1,1,1,1},
      {0,0,0,1,0},
      {0,0,0,1,0},
      {0,0,0,1,0},
    },
    {
      {1,1,1,1,0},
      {1,0,0,0,0},
      {1,1,1,0,0},
      {1,0,0,1,0},
      {0,0,0,1,0},
      {1,0,0,1,0},
      {0,1,1,0,0},
    },
    {
      {0,0,0,0,1},
      {0,0,0,1,0},
      {0,0,1,0,0},
      {0,1,1,1,0},
      {1,0,0,0,1},
      {1,0,0,0,1},
      {0,1,1,1,0},
    },
    {
      {1,1,1,1,1},
      {1,1,1,1,1},
      {1,1,1,1,1},
      {1,1,1,1,1},
      {1,1,1,1,1},
      {1,1,1,1,1},
      {1,1,1,1,1},
    },
    {
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0},
    },
    {
      {0,1,1,1,0},
      {1,0,0,0,1},
      {1,0,0,0,1},
      {0,1,1,1,0},
      {0,0,1,0,0},
      {0,1,0,0,0},
      {1,0,0,0,0},
    },
};


//________________________________________________________________


class neuron
{
public:
  double delta;
  double gewicht[maxGewichte];
  double ausgang;
  double input[maxGewichte];

  void initGewichte ();
  void updateGewichte (double eta);
  void aktivierung (double eingang[], int laenge);
};

class layer1hidden
{
public:
  neuron n[anzNeuronenHidden1];  
};

class layer2hidden
{
public:
  neuron n[anzNeuronenHidden2];  
};

class layeroutput
{
public:
  neuron n[anzMuster];  
};

class netzwerk
{
public:
  layer1hidden l1;
  layer2hidden l2;
  layeroutput lo;
  void initGewichte();
  void aktivierung (double eingang[], int laenge);
  void backpropagation (double target[]);
  void gewichteUpdaten (double eta);
  void neuronenZeichnen ();
  void gewichteZeichnen(double schwelle, int farbe, int dicke);
};


//________________________________________________________________


void neuron::initGewichte ()
{
  for (int i = 0; i < maxGewichte; i++)
    //  gewicht[i] = 1.0 / maxGewichte;
    gewicht[i] = 2 * ((double)rand()/RAND_MAX - 0.5);    
}

void neuron::updateGewichte (double eta)
{
  double deltaW;
  for (int i = 0; i < maxGewichte; i++) {
    deltaW = eta * input[i] * delta;
    gewicht[i] += deltaW;
    //         printf ("%f\n", deltaW);
  }
}

void  neuron::aktivierung (double eingang[], int laenge)
{
  double sum = 0;
  for (int i = 0; i < laenge; i++) {
    sum += gewicht[i] * eingang[i];
    input[i] = eingang[i];
  }
  //   printf ("sum=%f\n", sum);
  //  ausgang = tanh(sum);
  ausgang = 1/(1+exp(-sum));

}


//________________________________________________________________


void netzwerk::initGewichte ()
{
  int i;
  for (i = 0; i < anzNeuronenHidden1; i++)
    l1.n[i].initGewichte();

  for (i = 0; i < anzNeuronenHidden2; i++)
    l2.n[i].initGewichte();

  for (i = 0; i < anzMuster; i++)
    lo.n[i].initGewichte();
}


void netzwerk::aktivierung (double eingang[], int laenge)
{
  int i;
  double hidden1[anzNeuronenHidden1];
  double hidden2[anzNeuronenHidden2];
  for (i = 0; i < anzNeuronenHidden1; i++) {
    l1.n[i].aktivierung(eingang, laenge);
    hidden1[i] = l1.n[i].ausgang;
  }
  for (i = 0; i < anzNeuronenHidden2; i++) {
    l2.n[i].aktivierung(hidden1, anzNeuronenHidden1);
    hidden2[i] = l2.n[i].ausgang;
  }
  for (i = 0; i < anzMuster; i++)
    lo.n[i].aktivierung(hidden2, anzNeuronenHidden2);

}


void netzwerk::backpropagation (double target[])
{
  int i, j;
  double f, sum;
  for (i = 0; i < anzMuster; i++) {
    f = lo.n[i].ausgang;
    lo.n[i].delta = f*(1-f) * (target[i] - f);
  } 
  
  for (i = 0; i < anzNeuronenHidden2; i++) {
    f = l2.n[i].ausgang;
    sum = 0;
    for (j = 0; j < anzMuster; j++)
      sum += lo.n[j].gewicht[i] * lo.n[j].delta;
    l2.n[i].delta = f*(1-f) * sum;
  } 

  for (i = 0; i < anzNeuronenHidden1; i++) {
    f = l1.n[i].ausgang;
    sum = 0;
    for (j = 0; j < anzMuster; j++)
      sum += l2.n[j].gewicht[i] * l2.n[j].delta;
    l1.n[i].delta = f*(1-f) * sum;
  } 

}


void netzwerk::gewichteUpdaten (double eta)
{
 int i;
  for (i = 0; i < anzNeuronenHidden1; i++)
    l1.n[i].updateGewichte(eta);

  for (i = 0; i < anzNeuronenHidden2; i++)
    l2.n[i].updateGewichte(eta);

  for (i = 0; i < anzMuster; i++)
    lo.n[i].updateGewichte(eta);
}

void netzwerk::neuronenZeichnen()
{
  const int anzLayer = 4;
  int i;
  double x, y;

  double radius;
  double breite;
  double layerHoehe;

  layerHoehe = 1.0/anzLayer;

  breite = 1.0/(matrixx*matrixy);
  radius = breite/3;
  x = breite/2;
  y = layerHoehe/2;
  for (i = 0; i < matrixx*matrixy; i++) {
//    cpgcirc (x, y, radius);
    x += breite;
  } 

  breite = 1.0/anzNeuronenHidden1;
  radius = breite/3;
  x = breite/2;
  y += layerHoehe;
  for (i = 0; i < anzNeuronenHidden1; i++) {
//    cpgcirc (x, y, radius);
    x += breite;
  } 

  breite = 1.0/anzNeuronenHidden2;
  radius = breite/3;
  x = breite/2;
  y += layerHoehe;
  for (i = 0; i < anzNeuronenHidden2; i++){
//    cpgcirc (x, y, radius);
    x += breite;
  }

  breite = 1.0/anzMuster;
  radius = breite/3;
  x = breite/2;
  y += layerHoehe;
  for (i = 0; i < anzMuster; i++){
//    cpgcirc (x, y, radius);
    x += breite;
  }  
}

void netzwerk::gewichteZeichnen(double schwelle, int farbe, int dicke)
{
  const int anzLayer = 4;
  int i, j;
  float x[2], y[2];

  double radius;
  double breite;
  double radius2;
  double breite2;
  double layerHoehe;

  layerHoehe = 1.0/anzLayer;

//  cpgsci(farbe);
//  cpgslw(dicke);
  breite2 = 1.0/anzNeuronenHidden1;
  radius2 = breite2/3;
  x[1] = breite2/2;
  y[1] = 3*layerHoehe/2;
  for (j = 0; j < 1/*anzNeuronenHidden1*/; j++) {
    breite = 1.0/(matrixx*matrixy);
    radius = breite/3;
    x[0] = breite/2;
    y[0] = layerHoehe/2;
    for (i = 0; i < matrixx*matrixy; i++) {
      if (lo.n[j].gewicht[i] > schwelle)
//        cpgline (2, x, y);
      x[0] += breite;
    }
    x[1] += breite2;
  }

  breite2 = 1.0/anzNeuronenHidden2;
  radius2 = breite2/3;
  x[1] = breite2/2;
  y[1] = 5*layerHoehe/2;
  for (j = 0; j < anzNeuronenHidden2; j++) {
    breite = 1.0/anzNeuronenHidden1;
    radius = breite/3;
    x[0] = breite/2;
    y[0] = 3*layerHoehe/2;
    for (i = 0; i < anzNeuronenHidden1; i++) {
      if (l2.n[j].gewicht[i] > schwelle)
//        cpgline (2, x, y);
      x[0] += breite;
    }
    x[1] += breite2;
  }

  breite2 = 1.0/anzMuster;
  radius2 = breite2/3;
  x[1] = breite2/2;
  y[1] = 7*layerHoehe/2;
  for (j = 0; j < 1/*anzMuster*/; j++) {
    breite = 1.0/anzNeuronenHidden2;
    radius = breite/3;
    x[0] = breite/2;
    y[0] = 5*layerHoehe/2;
    for (i = 0; i < anzNeuronenHidden2; i++) {
      if (l1.n[j].gewicht[i] > schwelle)
//        cpgline (2, x, y);
      x[0] += breite;
    }
    x[1] += breite2;
  }

}


//________________________________________________________________


int main()
{
  int i,j, lernschritt, m;
  double target[anzMuster];
  netzwerk nw;

/*  if(cpgbeg(0, "/XWIN", 1, 1) != 1)
    exit(EXIT_FAILURE);
  cpgask(1);
  cpgenv(0, 1.0,
         0, 1.0,
         0, -2);
  cpglab(" ", " ", "Neuronales Netzwerk");
*/
  nw.neuronenZeichnen();
  nw.initGewichte();
  double schwelle = -1;
  int dicke;
  for (dicke = 0; dicke < 10; dicke++) {
    nw.gewichteZeichnen(schwelle, 2, dicke);
    schwelle += 0.2;
  }

  for (lernschritt = 0; lernschritt < anzSchritt*anzMuster; lernschritt++) {

    i = (int)(anzMuster*(double)rand()/RAND_MAX);
    nw.aktivierung(&referenzmuster[i][0][0], matrixx * matrixy);
    for (j = 0; j < anzMuster; j++)
      target[j] = 0;
    target[i] = +1;
    nw.backpropagation(target);
    nw.gewichteUpdaten(eta);

  }

  schwelle = -1;
  for (dicke = 0; dicke < 10; dicke++) {
    nw.gewichteZeichnen(schwelle, 3, dicke);
    schwelle += 0.2;
  }

  for (i = 0; i < anzMuster; i++) {
    nw.aktivierung(&muster[i][0][0], matrixx * matrixy);
 
    printf ("Ausgangsaktivitaet fuer Muster %d:\n", i);
    for (j = 0; j < anzMuster; j++)
      printf ("Ausgang %d: %f\n", j, nw.lo.n[j].ausgang);
   
    double max=-2;
    for (j = 0; j < anzMuster; j++) {
      double o = nw.lo.n[j].ausgang;
      if (o > max) {
        max = o;
        m = j;
      }
    }
    printf ("Erkannt %d, Eingang war %d\n", m, i);
  }

//  cpgend();
  return(0);
}