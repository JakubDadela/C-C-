#define DEBUG
#include <stdio.h>
#include "Matrix.h"
#include <iostream>

using namespace std;
void ReadData( FILE* f, double** Tab, double* b, int Size );

int main( int argc, char* argv[] )
{

	if ( argc < 2 ) 
	{
		printf( "write: %s input file", argv[0] );
		return 0;
	}
	FILE* f = fopen( argv[1], "r" ); 
	if (!f) //sprawdzamy czy podallismy dobry plik
	{
		perror( "Blad odczytu pliku\n\n" );
		return 0;
	}

	int Size; 
	fscanf_s( f, "%d", &Size ); 
	double** Tab = NULL; 
	double* vector = NULL; // do wektora wyrazow wolnych
#ifdef _DEBUG_
	printf("Tab %d x %d\n", Size, Size);
	CreateMatrix(&Tab, Size);
#endif
	if ( !CreateMatrix( &Tab, Size ) )
	{
		perror("Blad alokacji pamieci \n\n"); 
		return 0;
	}
	
	vector = ( double* )malloc( sizeof( double ) * Size); 
	if ( !vector ) {
		perror( "Blad alokacji pamieci \n\n" );
		return 0; // sprawdzam czy alokacja sie powiodla
	}
	memset( vector, 0, sizeof( double ) * Size ); 
	ReadData( f, Tab, vector, Size );
	//PrintMatrix(Tab, Size);
	fclose(f);
	if ( fabs(Det( Tab, Size ) )< 1e-14)
	{
		printf("Wyznacznik wynosi zero, nie mozemy obliczyc macierzy odwrotnej\n\n");
		return 0;
	}
	double* roz = NULL;
	roz = ( double* )malloc( sizeof( double ) * Size );
	if ( !roz )
	{
		perror( "Blad alokacji pamieci \n\n" );
		return 0;
	}
	memset( roz, 0, sizeof(double) * Size );
	double** Odw = NULL;
	CreateMatrix( &Odw, Size );
	if(!CreateMatrix(&Odw,Size))
	{
		perror("Blad alokacji pamieci \n\n");
		return 0;
	}
	InverseMatrix( Odw, Tab, Size ); 
	DeleteMatrix( &Tab, Size );
	LayoutEqu( Odw, vector, roz, Size ); 
	free( vector );
	DeleteMatrix( &Odw, Size );
	double* v = roz;
	for ( int i = 0; i < Size; i++ ) {
		printf( "%f\n", *v++ );
	}
	free(roz);
	
	return 0;

}


void ReadData( FILE* f, double** Tab, double* b, int Size )
{
	
	for ( int i = 0;  i < Size;  i++ )
	{
		double* col = *Tab++; // ustawienie wskaźnika na bierzącej kolumnie i przejscie do nastepnego wiersza
		for ( int j = 0;  j < Size;  j++ )
		{
			fscanf_s( f, "%lf", col++ ); 
			
		}
		fscanf_s( f, "%lf", b++ ); // zostanje nam wektor wyrazow wolnych b++ zwiekszamy

							
	}
}

