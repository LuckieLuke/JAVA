/*
 * Program rozwiązuje problem dokładnego pokrycia. Robi to metodą prób i błędów,
 * zagłębiając się rekurencyjnie w wieszach danych i wypisując rozwiązania
 * zgodnie ze stane pierwszej wczytanej linii, gdzie znajduje się filtr.
 *
 * Autor: Łukasz Laskowski
 */

#include <stdio.h>
#include <stdlib.h>

#define ROZMIAR_POCZ 2
#define MNOZNIK 3
#define DZIELNIK 2

/*
 * Funkcja wczytuje wszystkie dane do jednowymiarowej tablicy
 */

void WczytajDane(char **a, int *dlugosc, int *ileWierszy)
{
  char *s;
  int rozmiar = ROZMIAR_POCZ;
  int i = 0;
  int c;

  s = malloc(rozmiar * sizeof *s);
  while((c = getchar()) != EOF)
  {
    if(c == '\n')
      (*ileWierszy)++;
    if(i + 1 == rozmiar)
    {
      rozmiar = rozmiar * MNOZNIK / DZIELNIK;
      char *t = realloc(s, rozmiar * sizeof *t);
      s = t;
    }
    s[i] = c;
    i++;
  }
  *a = s;
  *dlugosc = (i / (*ileWierszy)) - 1;
}

/*
 * Dane są przepisywane z jednowymiarowej tablicy do specjalnie utworzonej na nie
 * dwuwymiarowej tablicy o wymiarach (dlugosc wiersza)x(ilosc wierszy)
 */

void PrzepiszDane(char **wszystko, char **dane, int dlugosc, int wiersze)
{
  int przesuniecie = dlugosc + 1;
  for(int w = 0; w < wiersze; w++)
  {
    for(int k = 0; k < dlugosc; k++)
    {
      dane[w][k] = (*wszystko)[przesuniecie];
      przesuniecie++;
    }
    przesuniecie++;
  }
  char *t = realloc(*wszystko, dlugosc * sizeof *t);
  *wszystko = t;
}

/*
 * Po uzupelnieniu wynikowej tablicy, dane sa wypisywane na ekran zgodnie z filtrem
 */

void Wypisz(char *wynik, int dlugosc, char *filtr)
{
  for(int i = 0; i < dlugosc; i++)
  {
    if(filtr[i] == '+')
      printf("%c", wynik[i]);
  }
  putchar('\n');
}

/*
 * Funkcja ma za zadanie wybrac wszystkie poprawne kombinacje wierszy,
 * rekursywnie wpisujac ich zawartosci do tablicy wynikowej
 */
void Wybierz(char **dane, char *filtr, int dlugosc, int ileWierszy, int ile, char *wynik)
{
  while(ile < dlugosc && wynik[ile] != '_')
    ile++;

  if(ile == dlugosc)
    Wypisz(wynik, dlugosc, filtr);

  else
  {
    for(int w = 0; w < ileWierszy; w++)
    {
      if(dane[w][ile] != '_')
      {
        int ileok = 0;
        for(int i = 0; i < dlugosc; i++)
        {
          if(dane[w][i] == '_' || wynik[i] == '_')
            ileok++;
        }
        if(ileok == dlugosc)
        {
          for(int i = ile; i < dlugosc; i++)
          {
            if(dane[w][i] != '_')
              wynik[i] = dane[w][i];
          }
          Wybierz(dane, filtr, dlugosc, ileWierszy, ile, wynik);
          for(int i = ile; i < dlugosc; i++)
          {
            if(dane[w][i] != '_')
                wynik[i] = '_';
          }
        }
      }
    }
  }
}

int main(void)
{
  char *filtr;
  int dlugosc;
  int ileWierszy = 0;

  WczytajDane(&filtr, &dlugosc, &ileWierszy);
/*
 * Zmniejszam ilosc wierszy, bo w tablicy znajduje sie takze filtr,
 * ktorego nie chce przepisywac do dwuwymiarowej tablicy
 */
  ileWierszy--;
  char **dane = (char**)malloc(ileWierszy * sizeof(char*));
  for(int i = 0; i < ileWierszy; i++)
  {
    dane[i] = (char*)malloc(dlugosc * sizeof(char));
  }
  char *wynik = (char*)malloc(dlugosc * sizeof(char));

  for(int i = 0; i < dlugosc; i++)
    wynik[i] = '_';

  PrzepiszDane(&filtr, dane, dlugosc, ileWierszy);
  Wybierz(dane, filtr, dlugosc, ileWierszy, 0, wynik);

  for(int i = 0; i < ileWierszy; i++)
    free(dane[i]);

  free(dane);
  free(filtr);
  free(wynik);
  return 0;
}
