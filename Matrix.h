#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <stdio.h>

int CreateMatrix( double*** Tab, int Size ); // !!! - error 1 -ok alokuje pamiec dla nowej macierzy
void DeleteMatrix( double*** Tab, int Size ); // *pTab==NULL;
void TransMatrix( double** Tab, int Size ); // transponowanie macierzy
void InverseMatrix( double** Inv, double** Tab, int Size ); // odwraca macierz
double Det( double** Tab, int Size ); // rozw wzg 0 wiersza rekurencyjnie
void LayoutEqu( double** Tab, double* B, double* w, int Size ); //rozwiazuje rowananie
void PrintMatrix( double** Tab, int Size ); 
void Complement( double** Tab0, double** Tab1, int Row, int Col, int Size );
void ComplMatrix( double** Tab0, double** Tab1, int Size );

#endif
