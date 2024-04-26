//Projekt 4 FILIP JABLONSKI
#include "ship.h"
#include <stdio.h>
#include <memory.h>

typedef enum { RIGHT, DOWN, UP, LEFT } move;

//=====
int Move( int** pTab, int nRow, int nCol, int nDepth,
  int move, int x, int y, int* px, int* py, int** pRoot )
{
  /* =================================================
  pTab - tablica okreslajaca glebokosc w kazdym kwadracie
   nRow, nCol - rozmiar pTab,
   nDepth - minimalna glebokosc aby statek przeplynal
   move - kierunek ruchu (wart typu wylicz)
   x, y - indeksy w tablicy skad wykonujemy kolejny ruch np. zaczynamy od 0,0
   px, py - adresy nowych wspolrzednych  (parametry WY)
   pRoot - tablica pamietajaca ruchy o rozm nRow, nCol
  ==================================================*/
  switch( move ) 
  {
  case RIGHT: *px = x + 1;  *py = y;   break;
  case LEFT: *px = x - 1;   *py = y;   break;
  case UP:  *py = y - 1;    *px = x;   break;
  case DOWN:  *py = y + 1;  *px = x;   break;
  }
  if( *px >= nRow || *px < 0 || *py >= nCol || *py < 0 || pRoot[*py][*px] || pTab[*py][*px] <= nDepth ) return 0;
  return 1;
}
//=====
int root( int** pTab, int nRow, int nCol, int nDepth,
  int x, int y, int** pRoot, int x_dest, int y_dest )
{
  static int Index = 1;
  /*=========================================
  pTab tabl glebokosci   o romiarze nRow  i nCol
    dDepth - glebokosc zanurzenia ststku
    x, y - wspolrzedne skad robimy kolejny ruch
    pRoot tablica kolejnych ruchow (w pole wstawia sie numer kolejnego ruchu)
    x_dest, y_dest - wsporzedne portu
  =========================================*/
  pRoot[y][x] = Index++;
  if( x == x_dest && y == y_dest ) return 1;
  
  int px = 0;
  int py = 0;
     
  for( int i = RIGHT; i <= LEFT; i++ ) // kolejno RIGHT DOWN UP LEFT
  {
    if( Move( pTab, nRow, nCol, nDepth, i, x, y, &px, &py, pRoot ) )
    {
      if( root( pTab, nRow, nCol, nDepth, px, py, pRoot, x_dest, y_dest ) ) return 1;
    }
  }
  pRoot[y][x] = -1; // statek nawraca i zostawia znak -1
  Index--;

  return 0;
}
//=====
void clearRoot( int** pTab, int nRow, int nCol )
{
  memset( *pTab, 0, sizeof( int ) * nRow * nCol );
}
//=====
int setTab( char* sFile, int** pTab, int nRow, int nCol )
{
  FILE* file_pointer = NULL;
  if( (file_pointer = fopen( sFile, "r" )) == NULL ) return 0;

  for( int i = 0; i < nRow; i++ )
  {
    int* v = *pTab++;
    for( int j = 0; j < nCol; j++ )
    {
      if( fscanf( file_pointer, "%d", v++ ) != 1 ) return 0;
    }
  }
  fclose( file_pointer );
  return 1;
  
}