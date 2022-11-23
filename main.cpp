#define ID_PRZYCISK1 501
#define ID_PRZYCISK2 502
#define ID_PRZYCISKA 503
#define ID_PRZYCISKB 504
#define ID_PRZYCISKC 505
#define ID_PRZYCISKD 506

#include <windows.h>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

int aktualne_zad = 0;
char * odp = NULL;
char * odp_Usera =NULL;
int global_position = 1; //jesli nacisniemy next to pobierze kolejen linie z quizu
MSG Komunikat; //wiem ¿e nie elegancko ale co zrobiæ do obsługi komunikatówl
char * Bufor =NULL;
int punkty = 0;
HWND zadanie;
HWND tresc;
HWND odpA;
HWND odpB;
HWND odpC;
HWND odpD;


HWND hButton1;
HWND hButtonA;
HWND hButtonB;
HWND hButtonC;
HWND hButtonD;
HWND hButtonNext;
HWND Licznik;
HWND Licznik_Tekst;




LPSTR nazwaKlasyOkna = (LPSTR)"Moje Okienko";

HWND przycisk;//globalny uchywt do przycisku
void sprawdzanie(HWND hwnd);
void open_file(HWND hwnd);
void UpdateGraph(HWND hwnd, HDC dc);
LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);//funkcja do obs³ugi zdarzeñ
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
   LPSTR nazwaKlasyOkna = (LPSTR)L"Moje Okienko";

   WNDCLASSEX wc; //zeby utworzyc klase okna musimy wypelnic ta strukture której nadajemy  nazwe wc ponoc od "Window Class"

   wc.cbSize = sizeof(WNDCLASSEX); //Rozmiar struktury w bajtach
   wc.style =  CS_DBLCLKS;//potrzebne jest to zeby wykrywac podwójne klikniecia
   wc.lpfnWndProc = WndProc;//wskaznik do struktury obslugujacej zdarzenia w oknie
   wc.cbClsExtra = 0;
   wc.cbWndExtra = 0;
   wc.hInstance = hInstance;//instancja okna
    //dodatkowe bajty Pamiêci dla okna
   wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);//ikonka aplikacji
   wc.hCursor = LoadCursor(NULL,IDC_ARROW);//wyœwietli na ekranie kursor myszki
   wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1) ;//Kolor okna domyslny
   wc.lpszMenuName = NULL;// Nie chcemy Menu
   wc.lpszClassName =nazwaKlasyOkna;
   wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);//ma³a ikonka naszej aplikacji

   if( !RegisterClassEx( & wc ) )//obs³uga b³êdów
    {
    MessageBox( NULL, "Nie powiod³o siê utworzenie okna", "ERROR",
    MB_ICONEXCLAMATION | MB_OK );
    return 1;
    }
   HWND hwnd;

   hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,//styl okna
   nazwaKlasyOkna,//nazwa klasy okna
   "Moje Okienko",//napis na pasku tytu³owym okna
    WS_OVERLAPPEDWINDOW,  //najczêstrze flagi sytlu okna
    CW_USEDEFAULT,//pozycje okna i jego rozmiar ustawiamy na domyœlny
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    NULL,//uchwyt dla okna rodzicielkiego jak ma to na NULL
    NULL,//nie chcemy menu
    hInstance,//instanacja naszego okna
    NULL);
    if( hwnd == NULL )//obs³uga b³edów
    {
    MessageBox( NULL, "Error przy tworzenu Okna!", "Ups coœ posz³o nie tak :(", MB_ICONEXCLAMATION );
    return 1;
    }

    HWND hButton1 = CreateWindowEx( WS_EX_CLIENTEDGE, "BUTTON", "Rozpocznij Gre", WS_CHILD | WS_VISIBLE |WS_BORDER, 50, 50, 150, 30, hwnd,( HMENU ) ID_PRZYCISK1, hInstance, NULL );
    HWND hButtonA = CreateWindowEx( WS_EX_CLIENTEDGE, "BUTTON", "A", WS_CHILD | WS_VISIBLE |WS_BORDER, 290, 350, 150, 30, hwnd,( HMENU ) ID_PRZYCISKA, hInstance, NULL );
    HWND hButtonB = CreateWindowEx( WS_EX_CLIENTEDGE, "BUTTON", "B", WS_CHILD | WS_VISIBLE |WS_BORDER, 440, 350, 150, 30, hwnd,( HMENU ) ID_PRZYCISKB, hInstance, NULL );
    HWND hButtonC = CreateWindowEx( WS_EX_CLIENTEDGE, "BUTTON", "C", WS_CHILD | WS_VISIBLE |WS_BORDER, 590, 350, 150, 30, hwnd,( HMENU ) ID_PRZYCISKC, hInstance, NULL );
    HWND hButtonD = CreateWindowEx( WS_EX_CLIENTEDGE, "BUTTON", "D", WS_CHILD | WS_VISIBLE |WS_BORDER, 740, 350, 150, 30, hwnd,( HMENU ) ID_PRZYCISKD, hInstance, NULL );
    HWND hButtonNext = CreateWindowEx( WS_EX_CLIENTEDGE, "BUTTON", "SPRAWDZ", WS_CHILD | WS_VISIBLE |WS_BORDER, 50, 100, 150, 30, hwnd,( HMENU ) ID_PRZYCISK2, NULL, NULL );
    Licznik_Tekst = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |SS_CENTER, 50, 150, 70, 20, hwnd, NULL, hInstance, NULL );
    Licznik = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |SS_CENTER, 130, 150, 70, 20, hwnd, NULL, hInstance, NULL );
    SetWindowText( Licznik_Tekst, "Licznik:" );
     char wynik[2];
    sprintf(wynik, "%d", punkty);
    SetWindowText( Licznik, wynik);
    zadanie = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |SS_LEFT, 350, 50, 300, 20, hwnd, NULL, NULL, NULL );
    tresc = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |SS_LEFT, 350,100 , 300, 20, hwnd, NULL, NULL, NULL );
    odpA = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |SS_LEFT, 350, 150, 100, 20, hwnd, NULL, NULL, NULL );
    odpB = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |SS_LEFT, 350, 200, 100, 20, hwnd, NULL, NULL, NULL );
    odpC = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |SS_LEFT, 350, 250, 100, 20, hwnd, NULL, NULL, NULL );
    odpD = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |SS_LEFT, 350, 300, 100, 20, hwnd, NULL, NULL, NULL );

     ShowWindow(hwnd,nCmdShow);
     UpdateWindow(hwnd);




   while(GetMessage(&Komunikat,NULL,0,0))//obs³uga komunikatów przychodz¹cych do okna pêtla dzia³a póki nie bêdzie 0 czyli komunikatu o zamkniêciu okna
   {

       TranslateMessage(&Komunikat);//wstêpne przetworzenie komunikatu
       DispatchMessage(&Komunikat);//wys³anie komunikatu gdzie trzeba

   }
   return Komunikat.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
    switch(msg)
    {
    case WM_CLOSE:
        {
             DestroyWindow(hwnd);
                break;
        }//naciœniêcie zamkniêcia okna spowoduje wyslanie WM_CLOSE i wywolamy wtedy komunikat Destroy Window

    case WM_DESTROY:
        {
            //Wtedy na komunikat WM_DESTROY zamykamy okno
            PostQuitMessage(0);
            break;
        }

    case WM_COMMAND://komunika po nacisnieciu przycisku
        {
            switch(wParam)
            {
                  case ID_PRZYCISK1:
                        {
                 open_file(hwnd);




                break;
                        }
            case ID_PRZYCISK2:
                            {
                                sprawdzanie(hwnd);
                                open_file(hwnd);

                                break;
                            }
            case ID_PRZYCISKA:
                {
                    odp_Usera ="A";
                   break;
                }

            case ID_PRZYCISKB:
                {
                    odp_Usera ="B";
                   break;
                }

            case ID_PRZYCISKC:
                {
                    odp_Usera ="C";
                   break;
                }

            case ID_PRZYCISKD:
                {
                    odp_Usera ="D";
                   break;
                }
            }



            break;
        }

   default:
         return DefWindowProc( hwnd, msg, wParam, lParam );//domyœlna obsluga zdarzen których my nie obslugujemy
    }
    return 0;
}

void open_file(HWND hwnd)//Funkcja która będzie odczytywać z pliku
{
    FILE * ptr;
    ptr = fopen("test.txt","rb");
    size_t len = 0;
    ssize_t read;


    int i = 0;
    int j = 0;
    while ((read = getline(&Bufor, &len, ptr)) != -1) {

        if(i!=global_position-1)//zeby przeskoczyc do interesujacego nas miejsca w pliku tyle razy przeskakujemy petle
        {
            i++;

            continue;
        }


        switch(j)
        {
        case 0:
            {
                SetWindowText( zadanie, Bufor);
                j++;
                break;
            }
        case 1:
            {
                SetWindowText(tresc, Bufor);
                j++;
                break;
            }
        case 2:
            {
                SetWindowText( odpA, Bufor);
                j++;
                break;
            }
        case 3:
            {
                SetWindowText( odpB, Bufor);
                j++;
                break;
            }
        case 4:
            {
                SetWindowText( odpC, Bufor);
                j++;
                break;
            }
       case 5:
            {
                SetWindowText( odpD, Bufor);
                j++;
                break;
            }
       case 6:
            {


                odp = Bufor;
                j++;
                break;
            }
        }
        if(j == 7)
        {
            break;
        }



    }

  global_position +=j;


    fclose(ptr);
}

void sprawdzanie(HWND hwnd)
{
    int result = strcmp(odp,odp_Usera);
    if(odp[0]==odp_Usera[0])
    {
          MessageBox( NULL, "Super Udalo ci sie", "Gratki", MB_ICONEXCLAMATION );
          punkty++;

    }else{
        MessageBox( NULL, "Nie udalo ci sie", "Porazka", MB_ICONEXCLAMATION );

    }
    char wynik[2];
    sprintf(wynik, "%d", punkty);
    SetWindowText( Licznik, wynik);
}
