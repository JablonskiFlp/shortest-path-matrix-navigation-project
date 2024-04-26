//Projekt 4 FILIP JABLONSKI
#include "ship.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define DEPTH 5
#define ROWS 7
#define COLS 7

int** CreateTab2D( int nCol, int nRow );
void PrintMatrix( int** pTab, int nRow, int nCol );
void DelTab( int*** pTab );

int main( int argc, char* argv[] )
{
  if( argc != 2 )
  {
    printf( "usage: %s <tab/size> \n", argv[0] );
    return 1;
  } // sprawdzam czy zalaczony jest plik

  int** pTab = CreateTab2D( ROWS, COLS );
  if( !pTab ) 
  {
    perror( "pTabAlocationError\n" );
    return 2;
  } // kreuje tablice pTab i wypelniam zerami

  int** pRoot = CreateTab2D( ROWS, COLS );
  if( !pRoot )
  {
    perror( "pRootAlocationError\n" );
    return 3;
  } // kreuje tablice pRoot i wypelniam zerami

  if( !setTab( argv[1], pTab, ROWS, COLS ) )
  {
    printf( "error reading %s \n", argv[1]);
    return 4;
  } // wypelniam tablice pTab danymi z pliku

  PrintMatrix( pTab, ROWS, COLS ); // wypisuje macierz pTab
  
  if( !root( pTab, ROWS, COLS, DEPTH, 0, 0, pRoot, COLS-1, ROWS-1 ) )
  {
    printf( "**Nie ma mozliwosci doplynac do portu!!\n\n" );
  }
  else
  {
    printf( "\nDroga do celu\n" );
    PrintMatrix( pRoot, ROWS, COLS );
  }

  DelTab( &pTab );
  DelTab( &pRoot );
  return 0;
}
//=====
int** CreateTab2D( int nRow, int nCol ) 
{
  int** pTab = (int**)malloc( sizeof( int* ) * nRow ); 
  if( !pTab ) return NULL;
  memset( pTab, 0, sizeof( int* ) * nRow );

  *pTab = (int*)malloc( sizeof( int ) * nRow * nCol ); 
  if( !*pTab ) return NULL;
  memset( *pTab, 0, sizeof( int ) * nRow * nCol );

  int** v = pTab + 1;
  int* p = *pTab + nCol;

  for( int i = 1; i < nRow; i++, p += nCol ) *v++ = p;
  return pTab;
}
//=====
void PrintMatrix( int** pTab, int nRow, int nCol ) 
{
  for( int i = 0; i < nRow; i++ ) 
  {
    int* p = *pTab++;
    for( int j = 0; j < nCol; j++ ) 
    {
      printf( "%2d ", *p++ );
    }
    printf( "\n" );
  }
}
//=====
void DelTab( int*** tab )
{
  free( **tab );
  free( *tab );
  *tab = NULL;
}