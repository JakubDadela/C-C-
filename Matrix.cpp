
#include "Matrix.h"



 
int CreateMatrix( double*** Tab, int Size ) 
{
	*Tab = ( double** )malloc( sizeof( double* ) * Size ); //tworzymy tablice wskaŸników(tablice tablic)
	if ( !*Tab ) return 0;
	else memset( *Tab,  NULL,  sizeof( double* ) * Size ); 

	double** c = *Tab;
	for ( int i = 0;  i < Size;  i++ )
	{
		*c = ( double* )malloc( sizeof( double ) * Size ); // alokujemy pamiec kolejno dla kazdej "komorki" tablicy
		if ( !*c ) return 0;
		else memset( *c++, 0, sizeof( double ) * Size );
	}
	return 1;
}
void DeleteMatrix( double*** Tab, int Size ) 
{
	double** d = *Tab; 
	int i = 0;
	while ( i < Size )
	{
		free( *d++ ); //zwalniamy poszczegolne komorki w tablicah
		i++;
	}
	free( *Tab ); // zwalniamy pamiec dla tablicy wskaznikow(tablicy tablic)
	*Tab = NULL; 
}
void TransMatrix( double** Tab, int Size ) 
{
	double temp;
	double* c=NULL; 
	double** r = Tab; 
	for ( int i = 0;  i < Size - 1;  i++ )
	{
		c = *r++ + i + 1; //nie tykamy przek¹tnej
		for ( int j = i + 1;  j < Size;  j++ )
		{
			 temp = *c;
			*c++ = Tab[j][i]; 
			Tab[j][i] = temp; 
		}
	}
}

void InverseMatrix( double** Inv, double** Tab, int Size )
{
	//macierz odwrotn¹ liczymy z wzoru
	ComplMatrix( Inv, Tab, Size ); 
	TransMatrix( Inv, Size ); 
	double* s = NULL; //wskaznik pomocniczy
	for ( int i = 0;  i < Size;  i++ )
	{
		s = *Inv++; // ustawiamy wskaznik kolumnie
		for ( int j = 0;  j < Size;  j++ )
		*s++ /= Det( Tab ,Size ); // przechodzimy po kolumnie
	
	}
}
double Det( double** Tab, int Size ) 
{
	if ( Size == 0 ) return 0;
	else if ( Size == 1 ) return Tab[0][0];
	else if ( Size == 2 ) return ( Tab[0][0] * Tab[1][1] ) - ( Tab[0][1] * Tab[1][0] );
	
		double** d = NULL;
		CreateMatrix( &d, Size - 1 ); 
		double w = 0;
		double* f = *Tab; // element wzgledem którego bedziemy liczyc La'placea
		int sign = 1; //zaczynamy wzgledem 0(1) wiersza i kolumny to znak = + bo(0+0)1+1=2 czyli liczba parzysta
		for ( int i = 0;  i < Size;  i++ )
		{
			Complement( d, Tab, 0, i, Size ); // liczymy rozwiniecie wedlug pierwszego (zerowego) wiersza
			w += *f++ * sign * Det( d, Size - 1 ); 
			sign = -sign; 

		}
		DeleteMatrix( &d, Size - 1 ); 
		return w; 

}

void LayoutEqu( double** Tab, double* B, double* w, int Size )
{
	double* o = NULL; //wskaznik do macierzy odwrotnej
	double* v = NULL; // wskaznik do wektora wyrazow wolnych
	for ( int i = 0;  i < Size;  i++ )
	{
		o = *Tab++; // ustawiamy wskaznik pomocniczy na odpowiedniej kolumnie 
		v = B; //poczatek wektora wyrazon wolnych
		for ( int j = 0; j < Size; j++ ) 
		*w += *o++ * *v++;
		w++; 
	}
}
void PrintMatrix( double** Tab, int Size )
{
	double* p = NULL; 
	for ( int i = 0;  i < Size;  i++ )
	{
	p = *Tab++; //ustawiamy wskaznik na wierszu
	for  ( int j = 0;  j < Size;  j++ )
			printf( "%f ", *p++ ); //przechodzimy po poszczególnych komórkach(kolumnach) w wierszu
		printf("\n");
	}
}


void Complement( double** Tab0, double** Tab1, int Row, int Col, int Size )
{
	double* z = NULL; //kolumnacy macierzy z ktorej wycinamy
	double* d = NULL; //kolumny macierzy do ktorej wczytujemy wycieta macierz
	for ( int i = 0;  i < Size;  i++ )
	{
		z = *Tab1; // ustawienie wskaznikow na odpowiednich kolumnach
		d = *Tab0;
		if ( i == Row ) 
		{
			Tab1++; //pomijamy wiersz i przechodzimy dalej
			continue;

		} 
		for ( int j = 0; j < Size; j++ )
		{
			if ( j == Col )	 // pomijamy konkretna komorke
			{
				z++;
				continue;
			}

			*d++ = *z++; // przechodzimy po kolumnach i kopiujemy dane
		}
		Tab0++; // przechodzimy do nastepnych wierszy
		Tab1++; 
	}
}
void ComplMatrix( double** Tab0, double** Tab1, int Size ) 
{
	double sign = 1;
	double* M1 = NULL; 
	double** M2 = NULL; //wskaznik do ktorego bedziemy wpisywac Wycieta macierz
	CreateMatrix( &M2, Size - 1 ); 
	for ( int i = 0; i < Size;  i++ )
	{
		M1 = *Tab0++; // ustawiamy na kolumnie
		sign = (i % 2)? -1 : 1;
		for ( int j = 0;  j < Size;  j++ )
		{
			Complement(  M2,  Tab1,  i,  j,  Size ); 
			*M1++ = sign * Det( M2, Size - 1 ); 
			sign = -sign;
	
		}
	
	}
	DeleteMatrix( &M2, Size - 1 ); 
}
