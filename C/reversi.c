/* 
 * "Reversi"
 *
 * Po uruchomieniu na ekranie wyświetla się początkowa wersja planszy.
 * Następuje tura ruchu gracza, w którym podaje on współrzędne pola,
 * na którym chce postawić swój pionek. Dane wejściowe możliwe są
 * w trzech formach - poprawne dane, poprzedzające ruch w danej
 * rundzie, znak '=', oznaczający rezygnację z ruchu, lub dane niepoprawne,
 * czyli wszystkie inne spoza wyżej opisanych. Poprawne dane składają się
 * z dwóch współrzędnych (x, y). Ruch jest legalny, więc też wykonywany,
 * jeśli spełnione są warunki: (1) na danym polu nie stoi inny pionek i
 * (2) idąc w jednym z ośmiu możliwych kierunków, zanim natrafimy na
 * kolejny 'swój' pionek, przejdziemy przez pionki przeciwnika oraz
 * nie znajdziemy żadnego pustego pola. Wykonany ruch w takim kierunku
 * spowoduje zmianę koloru pionków przeciwnika napotkanych na drodze
 * do naszego pionka. 
 * Następuje ruch komputera. Warunki do spełnienia w jego ruchu są
 * takie same, tyle że dodatkowo wiemy, że stawia on swoje pionki
 * zawsze w miejscu, w którym ilość obróconych pionków jego przeciwnika
 * (w tym wypadku gracza) będzie największa.
 * Gra toczy się do końca danych wejściowych.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*
 * Ustalona wielkość planszy
 */

#define WYS 8
#define SZER 8

/*
 * Współrzędne wektorów do poruszania się po planszy
 */
const int DX[] = {1, 1, 0, -1, -1, -1, 0, 1};
const int DY[] = {0, -1, -1, -1, 0, 1, 1, 1};

/*
 * Drukuje planszę na ekranie
 */
void WypiszPlansze(char tab[][SZER])
{
    for(int i = 0; i < WYS; i++)
    {
        for(int j = 0; j < SZER; j++)
        {
            printf("%c", tab[i][j]);
        }
    printf("%d\n", i+1);
    }
    for(char x = 'a'; x < 'i'; x++)
        printf("%c", x);
    putchar('\n');
}

/*
 * Zlicza pionki do legalnej zmiany w danym kierunku 
 */
int IleZmienieWKierunku(char tab[][SZER], int x, int y, int dx, int dy, bool czyBialy)
{
    char kolor, kolorPrzeciwnika;
    int przec = 0;
    if(czyBialy)
    {
        kolor = 'B';
        kolorPrzeciwnika = 'C';
    }
    else
    {
        kolor = 'C';
        kolorPrzeciwnika = 'B';
    }
    x += dx;
    y += dy;
    while(x < SZER && y < WYS && x >= 0 && y >= 0 && tab[y][x] != '-' && tab[y][x] != kolor)
    {
        if(tab[y][x] == kolorPrzeciwnika)
            przec++;
        x += dx;
        y += dy;        
    }
    if(tab[y][x] != kolor || x < 0 || x > 8 || y < 0 || y > 8)
        przec = 0;
    
    return przec;
}

/* 
 * W przypadku legalnego ruchu, zmienia kolory pionkow we wszystkich prawidłowych kierunkach
 */
void Zamien(char tab[][SZER], int x, int y, int dx, int dy, bool czyBialy)
{
    char kolor;

    if(czyBialy)
        kolor = 'B';
    else
        kolor = 'C';
    x += dx; 
    y += dy;
    
    while(x >= 0 && y >= 0 && x < 8 && y < 8 && tab[y][x] != kolor) 
    {
        tab[y][x] = kolor;
        x += dx;
        y += dy;
    }
}

/*
 * Zlicza wszystkie białe i czarne pionków na planszy
 */
void IlePionkow(char tab[][SZER], int *iloscCzarnych, int *iloscBialych)
{
    *iloscCzarnych = *iloscBialych = 0;
    for(int i = 0; i < SZER; i++)
    {
        for(int j = 0; j < WYS; j++)
        {
            if(tab[i][j] == 'B')
            {
                (*iloscBialych)++;
            }
            else if(tab[i][j] == 'C')
            {
                (*iloscCzarnych)++;
            }
        }
    }

}

/*
 * Dla zadanych współrzędnych początkowych, sprawdza czy ruch jest legalny w którymkolwiek kierunku
 */
bool CzyRuchJestLegalny(char tab[][SZER], int x, int y, bool czyBialy)
{
    int legalny = 0;
    if(tab[y][x] != '-')
        return legalny;

    for(int i = 0; i < 8; i++)
    {
        if(IleZmienieWKierunku(tab, x, y, DX[i], DY[i], czyBialy))
                   legalny++;
    }    
return legalny;
}


int main(void)
{    
    int x, y, a, b, c, i, j, suma = 0;
    char plansza[WYS][SZER];
    bool ruchBialego = 0; // 0 - czarny, 1 - biały
    int iloscBialych = 2;
    int iloscCzarnych = 2;
    int xKomp, yKomp;
    int maxSuma;

    for(i = 0; i < WYS; i++)
    {
        for(j = 0; j < SZER; j++)
        {
            plansza[i][j] = '-';
        }
    }
/*
 * Początkowy stan planszy
 */
    plansza[3][3] = plansza[4][4] = 'B';
    plansza[3][4] = plansza[4][3] = 'C';

    WypiszPlansze(plansza);
/*
 * Wczytywanie danych wejściowych do końca pliku
 */ 
        c = getchar();
    while(c != EOF)
    {
        if(c == '=')
        {
            c = getchar();
                if(c == '\n') // wczytane znaki to '=' i '\n'
                {
                    maxSuma = 0;
                    ruchBialego = !ruchBialego;
                    for(a = 0; a < WYS; a++)
                    {
                        for(b = 0; b < SZER; b++)
                        {    
                            suma = 0;
                            if(CzyRuchJestLegalny(plansza, b, a, ruchBialego)) // dla każdego legalnego ruchu sprawdzam, ile pionków zostanie obróconych
                            {
                                for(i = 0; i < 8; i++)
                                {
                                    suma += IleZmienieWKierunku(plansza, b, a, DX[i], DY[i], ruchBialego);
                                }
                                if(maxSuma < suma)
                                {    
                                    maxSuma = suma;
                                    yKomp = a;
                                    xKomp = b;
                                }
                            }
                        }
                    }
                    if(maxSuma != 0) // jeśli istnieje legalny ruch komputera
                    {
                        for(i = 0; i < 8; i++)
                        {
                            if(IleZmienieWKierunku(plansza, xKomp, yKomp, DX[i], DY[i], ruchBialego))
                                Zamien(plansza, xKomp, yKomp, DX[i], DY[i], ruchBialego);
                        }
                        plansza[yKomp][xKomp] = 'B';                            
                        printf("= %c%c", xKomp + 'a', yKomp + '1');
                    } // komputer nie ma legalnych ruchów
                    else
                        printf("= =");

                    IlePionkow(plansza, &iloscCzarnych, &iloscBialych);
                    printf(" %d\n", iloscCzarnych - iloscBialych);
                    
                } //niepoprawne dane
                else
                {
                    putchar('?');
                    IlePionkow(plansza, &iloscCzarnych, &iloscBialych);
                    printf(" %d\n", iloscCzarnych - iloscBialych);
                }
                ruchBialego = !ruchBialego;
        }
        else if(c >= 'a' && c <= 'h')
        {
            x = c - 'a';
            c = getchar();
            if(c >= '1' && c <= '8')
            {
                y = c - '1';
                c = getchar();
                if(c == '\n') //poprawne dane (wspolrzedne (x, y))
                {
                    if(CzyRuchJestLegalny(plansza, x, y, ruchBialego))
                    {
                        for(i = 0; i < 8; i++)
                        {
                            if(IleZmienieWKierunku(plansza, x, y, DX[i], DY[i], ruchBialego))
                            {
                                Zamien(plansza, x, y, DX[i], DY[i], ruchBialego);
                            }
                        }
                        plansza[y][x] = 'C';
                        ruchBialego = !ruchBialego;
                        maxSuma = 0; 
                        for(a = 0; a < WYS; a++) // ruch komputera
                        {
                            for(b = 0; b < SZER; b++)
                            {
                                suma = 0;
                                if(CzyRuchJestLegalny(plansza, b, a, ruchBialego))
                                {
                                    for(i = 0; i < 8; i++)
                                    {
                                        suma += IleZmienieWKierunku(plansza, b, a, DX[i], DY[i], ruchBialego);
                                    }    
                                    if(maxSuma < suma)
                                    {    
                                        maxSuma = suma;
                                        yKomp = a;
                                        xKomp = b;
                                    }
                                }
                            }
                        }
                        if(maxSuma != 0) //komputer nie ma poprawnych ruchów
                        {
                            for(i = 0; i < 8; i++)
                            {
                                if(IleZmienieWKierunku(plansza, xKomp, yKomp, DX[i], DY[i], ruchBialego))
                                    Zamien(plansza, xKomp, yKomp, DX[i], DY[i], ruchBialego);
                            }
                            plansza[yKomp][xKomp] = 'B';
                        
                        printf("%c%c %c%c", x + 'a', y + '1', xKomp + 'a', yKomp + '1');
                        }
                        else 
                            printf("%c%c =", x + 'a', y + '1');

                        IlePionkow(plansza, &iloscCzarnych, &iloscBialych);
                        printf(" %d\n", iloscCzarnych - iloscBialych);
                        ruchBialego = !ruchBialego;
                    

                    } 
                    else //dane są poprawne, ale sam ruch jest nielegalny
                    {
                        putchar('?');
                        IlePionkow(plansza, &iloscCzarnych, &iloscBialych);
                        printf(" %d\n", iloscCzarnych - iloscBialych);
                    }
                }
                else //wczytane dane mają więcej niż 2 znaki, czyli są niepoprawne
                {
                    while(c != '\n')
                        c = getchar();

                    putchar('?');
                    IlePionkow(plansza, &iloscCzarnych, &iloscBialych);
                    printf(" %d", iloscCzarnych - iloscBialych);
                    putchar('\n');
                }
            }
            else //pierwsza współrzędna jest poprawna, ale druga nie
            {
                while(c != '\n')
                    c = getchar();

                putchar('?');
                IlePionkow(plansza, &iloscCzarnych, &iloscBialych);
                printf(" %d", iloscCzarnych - iloscBialych);
                putchar('\n');
            }
        }
        else //niepoprawne dane
        {
            while(c != '\n')
                c = getchar();

            putchar('?');
            IlePionkow(plansza, &iloscCzarnych, &iloscBialych);
            printf(" %d", iloscCzarnych - iloscBialych);
            putchar('\n');
        }
    IlePionkow(plansza, &iloscCzarnych, &iloscBialych);
    WypiszPlansze(plansza);
    c = getchar();
    }
    return 0;
}
