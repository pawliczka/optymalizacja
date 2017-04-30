/**
 * \file simplex_table.hh
 * 
 * To jest plik zawierający nagłówki biblioteki implemetującej struktury danych
 * wykorzystywanych w metodach programowania liniowego simplex, m.in. tabele
 * simplexowe.
 *
 * Version 1.2
 * Last mod: 08.04.13
 * Authors: StilL {yarpen_zigrin11@wp.pl}
 *			Vova {vovagorodok2@gmail.com}
 */

#ifndef __SIMPLEX_TABLE_HEADER__
#define __SIMPLEX_TABLE_HEADER__

#include "linprog.hpp"
#include <iostream>
#include <string>
#include <vector>

class SimplexTable {
	int numBaseVars;
	int numAdditionalVars;
	int numCols;
	int numRows;
    std::vector<std::vector<double>> Tab;
    int* ColIndex;
	int* RowIndex;

	/*
	 * Alokuje tablicę dynamiczną dwuwymiarową o rozmiarze numCols x numRows.
	 */
	void AllocTable();

	/*
	 * Wstawia funkcję celu do pierwszego wiersza tabeli simplexowej.
	 * Jest używana we wstępnym przetwarzanie liniowego problemu optymalizacji
	 * do postaci tabeli.
	 *
	 * Działanie:
	 *	- Pierwszy element ustawiany na 0 co oznacza, że funkcja celu na
	 *	  początku jest w srodku ukladu wspolrzednych (dla problemu gdzie
	 *	  x>0)
	 *  - Kolejne elementy wiersza to kolejne wspolczynniki rzeczywiste funkcji
	 *    celu wziete z przeciwnym znakiem.
	 */
    void ObjFuncTo1stRow( Equation& ObjFunc );

	/*
	 * Wstawia ograniczenie do podanego wiersza tabeli simplexowej.
	 * Jest uzywana we wstepnym przetwarzanie liniowego problemu optymalizacji
	 * do postaci tabeli.
	 *
	 * Dzialanie:
	 *	 - pierwszy element to wyraz wolny ograniczenia
	 *	 - kolejne elementy wiersza to wspolczynniki rzeczywiste ograniczenia
	 */
    void ConstrToRow(  Equation Constr , int Row );

	/*
	 * Ustawiaja indeksy zmiennych odpowiadajacych za poszczegolne wiersze i
	 * kolumny tabeli simplexowej.
	 */
	void SetupColIndexes();
	void SetupRowIndexes();

public:
	SimplexTable() {}
    SimplexTable(const SimplexTable& CpyTab );
    SimplexTable( LinProblem& problem );
	SimplexTable( LinProblem* problem );
	~SimplexTable();

	void print() const;
	double rowMax( int Row ) const;
	double rowMin( int Row ) const;
	double colMax( int Col ) const;
	double colMin( int Col ) const;
	int colNegative( int Col ) const;
	int rowMinIndex( int Col ) const;
	int colMinIndex( int Col ) const;

	inline int getnumBaseVars() const { return numBaseVars; }
	inline int getnumAdditionalVars() const { return numAdditionalVars; }
	inline int getnumCols() const { return numCols; }
	inline int getnumRows() const { return numRows; }
	inline double getTabElem( int row , int col ) const { return Tab[row][col]; }
	inline int getColIndex( int num ) const { return ColIndex[num]; }
	inline int getRowIndex( int num ) const { return RowIndex[num]; }
	//void setColIndex( int num , int value ) { ColIndex[num]=value; }
	//void setRowIndex( int num , int value ) { RowIndex[num]=value; }
	void swapRowColIndexes( int col , int row ) ;
	void setTabElem( int row , int col , double val ) { Tab[row][col] = val; }


};

#endif /* __SIMPLEX_TABLE_HEADER__ */
