//Simulation einer Proteinfaltung

// gcc proteinfolding.C -c -O2
// g77 -o proteinfolding proteinfolding.o -L/app/physik/pgplot -lcpgplot -lpgplot -lX11 -lgcc -L/usr/X11R6/lib
// setenv PGPLOT_DIR /app/physik/pgplot

//#include "/app/physik/pgplot/cpgplot.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int anzAS=25, TypAS=20;
const int N=2*anzAS;
const int AnzMontecarlostep=1000;


//________________________________________________________________


class AS
{
public:
  int x,y,identitaet;
  AS(int typ, int x, int y);
  AS() {};
};

class protein
{
public:
  int laenge;
  AS *kette[anzAS];
  void ASbestimmen(int x, int y);
  protein();
  void ASauswaehlen(AS **links, AS **mitte, AS **rechts);
  double Energie (AS *mitte);
  void zeichnen ();
};

class gitter
{
  int g[N][N];
public:
  int Platz_besetzt(int i,int j);
  void setzen (int i, int j);
  void loeschen (int i, int j);
  void neuerPlatzRand (AS *a, int& x, int& y);
  void neuerPlatzMitte (AS *l, AS *m, AS *r, int& x, int& y);
};

class Wechselwirkung
{
public:
  double J[TypAS][TypAS];
  Wechselwirkung(); //Konstruktor (fuer Ausgangswert)
};

Wechselwirkung ww;


//________________________________________________________________


int gitter:: Platz_besetzt (int i, int j){
  return g[i] [j];
}

void gitter:: setzen (int i, int j){
  g[i][j] = 1;
}

void gitter:: loeschen (int i, int j){
  g[i][j] = 0;
}

void gitter:: neuerPlatzRand (AS *a, int& x, int& y) {
  int xKandidat[4];
  int yKandidat[4];
  int n = 0;
  if (!Platz_besetzt(a->x-1, a->y)) {
    xKandidat[n] = a->x-1;
    yKandidat[n] = a->y;
    n++;
  }
  if (!Platz_besetzt(a->x+1, a->y)) {
    xKandidat[n] = a->x+1;
    yKandidat[n] = a->y;
    n++;
  } 
  if (!Platz_besetzt(a->x, a->y-1)) {
    xKandidat[n] = a->x;
    yKandidat[n] = a->y-1;
    n++;
  }
  if (!Platz_besetzt(a->x, a->y+1)) {
    xKandidat[n] = a->x;
    yKandidat[n] = a->y+1;
    n++;
  }
  if (n == 0) {
    x = a->x;
    y = a->y;
  } else {
    double r= (double)rand()/RAND_MAX;
    int i = (int)(n*r);
    x= xKandidat[i];
    y= yKandidat[i];
  }
}

void gitter:: neuerPlatzMitte (AS *l, AS *m, AS *r, int& x, int& y) {
  if (l->x == r->x || l->y == r->y) { // linear
    x = m->x;
    y = m->y;
  } else if (l->x == m->x) {
    x = r->x;
    y = l->y;
    if (Platz_besetzt (x, y)) {
      x = m->x;
      y = m->y;
    }
  } else if (r->x == m->x) {
    x = l->x;
    y = r->y;
    if (Platz_besetzt (x, y)) {
      x = m->x;
      y = m->y;
    }
  }
}


//________________________________________________________________


void protein:: ASbestimmen (int x, int y){
  double r= (double)rand()/RAND_MAX;
  kette[laenge]=new AS(TypAS*r, x, y);
  laenge++;
}

void protein:: ASauswaehlen(AS **links, AS **mitte, AS **rechts){
  double r= (double)rand()/RAND_MAX;
  int i= (int)(r*laenge);
  *mitte = kette [i];
  if (i==0) {
    *links = NULL;
    *rechts = kette [i+1];
  } else  if (i==laenge-1) {
    *rechts = NULL;
    *links = kette [i-1];
  } else {
    *rechts = kette [i+1];
    *links = kette [i-1];
  }
}

double protein:: Energie(AS *mitte) {
  double e = 0;
  for (int i=0; i<laenge; i++){
    if (kette[i]->x == mitte->x && kette[i]->y == mitte->y-1)
      e += ww.J[kette[i]->identitaet][mitte->identitaet];
    else if (kette[i]->x == mitte->x && kette[i]->y == mitte->y+1)
      e += ww.J[kette[i]->identitaet][mitte->identitaet];
    else if (kette[i]->x == mitte->x-1 && kette[i]->y == mitte->y)
      e += ww.J[kette[i]->identitaet][mitte->identitaet];
    else if (kette[i]->x == mitte->x+1 && kette[i]->y == mitte->y)
      e += ww.J[kette[i]->identitaet][mitte->identitaet];
  }
  return e;
}

void protein::zeichnen ()
{
/*  float x[laenge];
  float y[laenge];
  cpgeras();
  for (int i = 0; i < laenge; i++) {
    cpgsci (kette[i]->identitaet + 1);
    cpgcirc (kette[i]->x, kette[i]->y, 0.3);
    x[i] = kette[i]->x;
    y[i] = kette[i]->y;
  }
  cpgsci (4);
  cpgline (laenge, x, y);
*/}

AS::AS(int typ, int x, int y) {
  this->x=x; //pointer auf Objekt selbst
  this->y=y;
  identitaet=typ;
}

protein::protein(){
  laenge=0;
}

Wechselwirkung::Wechselwirkung() {
  int i, j;
  double r;
  for (i=0; i<TypAS;i++){
    for (j=0; j <TypAS;j++){
      r= (double)rand()/RAND_MAX;
      J[i][j]=-4*r;
    } 
  }
}


//________________________________________________________________


gitter g;
protein p;

int main(){
  int x, y, xv, yv;
  AS *l,*m,*r,*a;
  double Evorher, Enachher, dE;
  y=anzAS;
  for (x=anzAS/2; x<anzAS/2+anzAS; x++){
    g.setzen(x,y);
    p.ASbestimmen(x, y);  
  }

/*  if(cpgbeg(0, "/XWIN", 1, 1) != 1)
    exit(EXIT_FAILURE);
  cpgask(1);
  cpgenv(0.0, (double)N, 0.0, (double)N, 0, -2);
  cpglab(" ", " ", "Protein Folding");
*/
  p.zeichnen();

  for (double T = 2; T > 0.5; T *= 0.98) {
    printf ("T = %g\n", T);
    for (int i=0; i<AnzMontecarlostep; i++){
      p.ASauswaehlen(&l,&m,&r);
      if (l == NULL) {
        a = m;
        xv = m->x;
        yv = m->y;
        Evorher = p.Energie (m);
        g.neuerPlatzRand(r, x, y);
        //printf ("l == NULL: xv = %d, yv = %d, x = %d, y = %d\n", xv, yv, x, y);
        m->x = x;
        m->y = y;
        Enachher = p.Energie (m);
      } else if (r == NULL) {
        a = m;
        xv = m->x;
        yv = m->y;
        Evorher = p.Energie (m);
        g.neuerPlatzRand(l, x, y);
        //printf ("r == NULL: xv = %d, yv = %d, x = %d, y = %d\n", xv, yv, x, y);
        m->x = x;
        m->y = y;
        Enachher = p.Energie (m);
      } else {
        a = m;
        xv = m->x;
        yv = m->y;
        Evorher = p.Energie (m);
        g.neuerPlatzMitte (l, m, r, x, y);
        //printf ("xv = %d, yv = %d, x = %d, y = %d\n", xv, yv, x, y);
        m->x = x;
        m->y = y;
        Enachher = p.Energie (m);
      }
      dE = Enachher - Evorher;
      //      printf ("dE = %g\n", dE);
      double R= (double)rand()/RAND_MAX;
      if (exp (-dE/T) <= R) { // verschobene Aminosaeure zurueckschieben
        a->x = xv;
        a->y = yv;
      } else {
        if (x != xv || y != yv)
          p.zeichnen();
        g.loeschen (xv, yv);
        g.setzen (x, y);
      }
      //      char c = getchar();
    }  
  }
//  cpgend();
  return 0;
}