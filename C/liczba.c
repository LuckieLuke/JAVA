/*
Przedstawianie liczb i działań w postaci kabanosów w systemie BBR NAF.

Autor: Łukasz Laskowski
*/

#include <stdio.h>
#include <stdlib.h>
#include "liczba.h"
#define MAX 2147483647

/*
Struktura prezentująca liczby
*/
struct liczba {
  int c;
  int nr;
  struct liczba *nast;
};
typedef struct liczba *Liczba;

/*
Funkcja konwertująca liczby z systemu dziesiętnego na kabanosy.
*/
Liczba reprezentacja(int n)
{
  if(n == 0)
    return NULL;
  Liczba l = NULL;
  Liczba pom = NULL;
  while(n != 0)
  {
    pom = (Liczba)malloc(sizeof(struct liczba));
    pom->nast = NULL;
    if(n % 2 == 0)
      pom->c = 0;
    else if((n - 1) % 4 == 0)
      pom->c = 1;
    else
      pom->c = -1;

    n = (n-pom->c)/2;
    pom->nast = l;
    l = pom;
  }
/* Odwracanie listy */
  Liczba poprz = NULL;
  Liczba biez = l;
  Liczba temp = NULL;
  while(biez != NULL)
  {
    temp = biez->nast;
    biez->nast = poprz;
    poprz = biez;
    biez = temp;
  }
  l = poprz;
  Liczba pocz = l;
  int i = 0;

  while(l != NULL)
  {
    l->nr = i;
    i++;
    l = l->nast;
  }

/* Usuwanie zerowych elementów. */
  l = pocz;
  Liczba atrapa = (Liczba)malloc(sizeof(struct liczba));
  atrapa->nast = l;
  l = atrapa;
  Liczba help = NULL;
  while(l->nast != NULL)
  {
    if(l->nast->c != 0)
      l = l->nast;
    else
    {
      help = l->nast->nast;
      free(l->nast);
      l->nast = help;
    }
  }
  l = atrapa->nast;
  free(atrapa);

/* Nadawanie elementom odpowiednich wartości. */
  pocz = l;
  while(l != NULL)
  {
    if(l->c == -1)
      l->c = (-1)*(l->nr + 1);
    else if(l->c == 1)
      l->c = l->nr;

    l = l->nast;
  }

  l = pocz;

  return l;
}

/*
Funkcja wypisująca kabanosową reprezentację liczb.
*/
void pisz(Liczba a)
{
  Liczba pocza = a;
  while(a != NULL)
  {
    if(a->c >= 0)
      printf("+%d", a->c);
    else
      printf("%d", a->c);
    a = a->nast;
  }
  putchar(';');
  a = pocza;
}

/*
Funkcja określająca znak liczby (-1 dla ujemnych, 0 dla zera i 1 dla dodatnich).
*/
int znak(Liczba a)
{
  if(a == NULL)
    return 0;
  while(a->nast != NULL)
    a = a->nast;

  if(a->c < 0)
    return -1;
  else if(a->c >= 0)
    return 1;

  return 0;
}

/*
Funkcja obliczająca wartość liczby w systemie dziesiętnym.
(zwraca 0, gdy wykracza poza zakres INT)
*/
int wartosc(Liczba a)
{
  long long int suma = 0;
  long long int dod = 1;
  while(a != NULL)
  {
    for(int i = 1; i <= a->nr; i++)
    {
      if(MAX - dod < dod || -MAX - dod > dod)
        return 0;
      else
        dod *= 2;
    }

    if(suma > MAX - dod || suma < (-1)*MAX - dod)
      return 0;

    if(a->c >= 0)
      suma += dod;
    else
      suma -= dod;

    a = a->nast;
    dod = 1;
  }
  if(suma > MAX  || suma < (-1)*MAX)
    return 0;

  return suma;
}

/*
Funkcja tworząca kopię reprezentacji liczby w postaci kabanosa.
*/
Liczba kopiuj(Liczba a) {
  if (a == NULL) return NULL;
  Liczba l = (Liczba)malloc(sizeof(struct liczba));
  l->c = a->c;
  l->nr = a->nr;
  l->nast = kopiuj(a->nast);
  return l;
}

/*
Funkcja sumująca dwa kabanosy.
*/
Liczba suma(Liczba a, Liczba b)
{
  Liczba w = kopiuj(a);
  Liczba z = kopiuj(b);
  Liczba wyn;
  Liczba c;
  wyn = (Liczba)malloc(sizeof(struct liczba));
  Liczba ost = wyn;
  wyn->nast = NULL;

/* Scalenie obu liczb w porządku niemalejących modułów wartości. */
  if(z == NULL && w == NULL)
  {
    free(wyn);
    return NULL;
  }
  else if(z == NULL)
    c = w;
  else if(w == NULL)
    c = z;

  while(w != NULL && z != NULL)
  {
    if(w->nr < z->nr)
    {
      ost->nast = w;
      ost = ost->nast;
      w = w->nast;
    }
    else
    {
      ost->nast = z;
      ost = ost->nast;
      z = z->nast;
    }
  }
    if(w == NULL)
      ost->nast = z;
    else
      ost->nast = w;

/* Odśmiecenie ewentualnych dwóch liczb na tej samej pozycji. */
  c = wyn->nast;
  if(!c)
    return NULL;

  while(c->nast)
  {
    if(c->nr == c->nast->nr && c->c == c->nast->c)
    {
      (c->nast->nr)++;
      if(c->nast->c >= 0)
        c->nast->c = c->nast->nr;
      else
        c->nast->c = (-1)*((c->nast->nr)+1);
      c->nr = -2;
      c = c->nast;
    }
    else if(c->nr == c->nast->nr && c->c != c->nast->c)
    {
      c->nr = -2;
      c->nast->nr = -2;
      c = c->nast;
    }
    else
      c = c->nast;
  }
  c = wyn;

  if(!(c->nast))
    return NULL;

  while(c->nast)
  {
    if(c->nast->nr != -2)
      c = c->nast;
    else
    {
      Liczba pom = NULL;
      pom = c->nast->nast;
      free(c->nast);
      c->nast = pom;
    }
  }
  c = wyn->nast;
  if(!c)
    return NULL;

/* Konwersja już scalonej liczby na NAF. */
  int ile = c->nr;
  while(c != NULL && c->nast != NULL)
  {
    if(ile == (c->nast->nr) - 1 || c->nr == (c->nast->nr) - 1)
    {
      if(c->c >= 0 && c->nast->c >= 0)
      {
        c->c = -((c->nr) + 1);
        c = c->nast;
        while(c->nast != NULL && c->nr == (c->nast->nr) - 1 && c->c >= 0 && c->nast->c >= 0)
        {
          c->nr = -2;
          c = c->nast;
        }
        ile = c->nr;
        c->nr = -2;

        if(c->nast && ile == (c->nast->nr) - 1 && c->nast->c < 0)
          c->nast->nr = -2;
        else
        {
          Liczba pom = (Liczba)malloc(sizeof(struct liczba));
          pom->nast = c->nast;
          c->nast = pom;
          pom->nr = ile + 1;
          pom->c = pom->nr;
        }
        c = c->nast;
      }
      else if(c->c < 0 && c->nast->c < 0)
      {
        c->c = c->nr;
        c = c->nast;
        while(c->nast != NULL && c->nr == (c->nast->nr) - 1 && c->c < 0 && c->nast->c < 0)
        {
          c->nr = -2;
          c = c->nast;
        }
        ile = c->nr;
        c->nr = -2;
        if(c->nast && ile == (c->nast->nr) - 1 && c->nast->c >= 0)
          c->nast->nr = -2;
        else
        {
          Liczba pom = (Liczba)malloc(sizeof(struct liczba));
          pom->nast = c->nast;
          c->nast = pom;
          pom->nr = ile + 1;
          pom->c = -(pom->nr + 1);
        }
        c = c->nast;
      }
      else if(c->c >= 0 && c->nast->c < 0)
      {
        c->c = -(c->nr + 1);
        c->nast->nr = -2;
        c = c->nast;
      }
      else if(c->c < 0 && c->nast->c >= 0)
      {
        c->c = c->nr;
        c->nast->nr = -2;
        c = c->nast;
      }
      else
        c = c->nast;
    }
    else
      c = c->nast;
  }
  c = wyn->nast;
  while(c->nast != NULL)
  {
    if(c->nast->nr != -2)
      c = c->nast;
    else
    {
      Liczba pom = NULL;
      pom = c->nast->nast;
      free(c->nast);
      c->nast = pom;
    }
  }
  c = wyn->nast;
  free(wyn);

  return c;
}

/*
Funkcja odejmująca dwie liczby od siebie.
*/
Liczba roznica(Liczba a, Liczba b)
{
  Liczba u = kopiuj(b);
  Liczba poczu = u;
  while(u)
  {
    if(u->c >= 0)
      u->c = -(u->nr + 1);
    else
      u->c = u->nr;

    u = u->nast;
  }
  u = poczu;
  Liczba d = suma(a, u);
  usun(u);
  return d;
}

/*
Funkcja podająca wynik mnożenia dwóch kabanosów.
*/
Liczba iloczyn(Liczba a, Liczba b)
{
  if(!a || !b)
    return NULL;
  Liczba wz_a = kopiuj(a);
  Liczba wz_b = kopiuj(b);
  Liczba pocz_a = wz_a;
  Liczba pocz_b = wz_b;
  Liczba wynik = NULL;
  Liczba podwynik = NULL;

  while(wz_b)
  {
    Liczba pom = kopiuj(wz_a);
    Liczba pocz_pom = pom;
    while(pom)
    {
      pom->nr += wz_b->nr;

      if(pom->c >= 0)
        pom->c = pom->nr;
      else
        pom->c = -(pom->nr + 1);

      pom = pom->nast;
    }
    pom = pocz_pom;
    podwynik = wynik;
    if(wz_b->c >= 0)
      wynik = suma(podwynik, pom);
    else
      wynik = roznica(podwynik, pom);

    usun(podwynik);
    usun(pom);
    wz_b = wz_b->nast;
  }
  wz_b = pocz_b;
  wz_a = pocz_a;
  usun(wz_a);
  usun(wz_b);
  return wynik;
}

/*
Funkcja czytająca z wejścia tekstową reprezentację kabanosa.
*/
Liczba czytaj(void)
{
  char z;
  int n;
  Liczba l = (Liczba)malloc(sizeof(struct liczba));
  Liczba ost = NULL;
  Liczba pocz = l;
  while(~scanf(" %c", &z) && z != ';')
  {
    scanf("%d", &n);
    ost = (Liczba)malloc(sizeof(struct liczba));
    ost->nast = NULL;
    l->nast = ost;

    if(z == '+')
    {
      ost->c = n;
      ost->nr = n;
    }
    else
    {
      ost->c = -n;
      ost->nr = n-1;
    }
    l = l->nast;
  }
  l = pocz;
  Liczba zwr = l->nast;
  free(pocz);
  return zwr;
}

/*
Funkcja czyszcząca pamięć po kabanosie.
*/
void usun(Liczba l)
{
  Liczba akt = l;
  Liczba next = NULL;
  if(akt == NULL)
    return;

  while(akt)
  {
    next = akt->nast;
    free(akt);
    akt = next;
  }
}
