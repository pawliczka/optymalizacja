/**
 * \file simplex_table.hh
 * 
 * To jest plik zawierający nagłówki biblioteki implemetującej algorytm
 * programowania liniowego simplex metodą tablic simplexowych.
 *
 * Version 1.2
 * Last mod: 08.04.13
 * Authors: StilL {yarpen_zigrin11@wp.pl}
 *			Vova {vovagorodok2@gmail.com}
 */

#ifndef __SIMPLEX_HEADER__
#define __SIMPLEX_HEADER__

#include "simplex_table.hpp"
#include "linprog.hpp"
#include <memory>

/*
 * Status algorytmu
 *
 *	1. STATUS_BUSY - algorytm jest w toku
 *	2. STATUS_WRONG_TABLE - tabela przekazana nie spelnia warunku dopuszczalnosci
 *  3. STATUS_SOLVED - algorytm zakonczyl dzialanie i zwrocił wynik
 *	4. STATUS_INITIALIZED - algorytm zostal poprawnie zainicjalizowany
 */
typedef enum SimplexStatus { STATUS_INITIALIZED , STATUS_BUSY ,
							 STATUS_WRONG_TABLE , STATUS_SOLVED };


/*! \brief Opisuje stan algorytmu
 *
 * Zawiera zmienne, ktore pozwalaja na stwierdzenie w jakim stanie znajduje
 * sie algorytm, ile ma rozwiazan i ile przeszedl juz petli.
 */
class SimplexState{

public:
	SimplexState();

	SimplexStatus Status;
	LinProblemCase Case;
	int LoopCnt1Phase;
	int LoopCnt2Phase;
};

/*! \brief Przeprowadza algorytm simplex w wersji prymalnej
 *
 * Przeprowadza algorytm simplex w wersji prymalnej dla danego problemu
 * liniowego.
 * Zasadnicza czescia algorytmu jest funkcja Solve, ktora rozwiazuje problem
 * i zwraca wskaznik na rozwiazanie lub NULL jesli rozwiazanie nie istnieje.
 */
class Simplex{
    SimplexTable Table;
	LinProblemSolution* Solution;
	OptimizeType Type;

	/*! \brief Sprawdza czy istnieja rozwiazania
	 *
	 * Sprawdza warunek, czy zadanie jest ograniczone czy nie. Jesli zadanie jest
	 * ograniczone to znaczy, ze posiada conajmniej jedno rozwiazanie.
	 * W przypadku algorytmu w wersji dualnej istnieje jeszcze mozliwosc rownan
	 * sprzecznych, tzn. nie obejmujacych rzadnych punktow wiekszych od 0.
	 */
	void CheckNoSolutions();

	/*! \brief Sprawdza problem jest sprzeczny
	 *
	 * ...
	 */
	void CheckInconsistent();

	/*! \brief Sprawdza czy liczba rozwiazan jest nieskonczona
	 *
	 * Analizujac postac tabeli simplexowej stwierdza czy istnieje nieskonczona
	 * liczba rozwiazan na zbiorze ograniczonym.
	 */
	void CheckInfSolutionsBounded();

	/*! \brief Sprawdza czy liczba rozwiazan jest nieskonczona
	 *
	 * Analizujac postac tabeli simplexowej stwierdza czy istnieje nieskonczona
	 * liczba rozwiazan na zbiorze nieograniczonym.
	 */
	void CheckInfSolutionsUnbounded();

	/*! \brief Sprawdza warunek dopuszczalności
	 *
	 * Sprawdza czy spelniony jest warunek dopuszczalności rozwiązania
	 * znajdującego się aktualnie w tablicy simplexowej. Kryterium
	 * polega na tym, że żadna liczba z pierwszej kolumny nie może być ujemna.
	 */
	int IsPermissible() const;

	/*! \brief Sprawdza warunek optymalności
	 * 
	 * Sprawdza czy spelniony jest warunek optymalności rozwiązania znajdującego się
	 * aktualnie w tabeli simnplexowej. Jeśli wszystkie liczby w pierwszym wierszu
	 * są nieujemne to znaczy, że rozwiązania nie da się już polepszyć a więc
	 * aktualne rozwiązanie jest optymalne.
	 */
	int IsOptimal() const;

	/*! \brief Aktualizuje rozwiązanie
	 *
	 * Wypełnia strukturę Solution odpowiedniomi wartościami zmiennych decyzyjnych
	 * i wartością funkcji celu wyciągniętymi z tabeli simplexowej.
	 */
	void UpdateSolution();

	/*! \brief Wybiera jedną ze zmiennych niebazowych do usunięcia
	 *
	 * Wybiera zmienną o najbardziej ujemnym współczynniku spośród wyrazów pierwszego
	 * wiersza tabeli.
	 * W wersji z numerem wiersza jest wykorzystywana w alorytmie dwufazowym do
	 * znalezienia zmiennej usuwanej z bazy z wybranego wiersza.
	 *
	 * \return Indeks wybranej zmiennej niebazowej do usunięcia
	 */
	int ChooseNewBaseVar() const;
	int ChooseNewBaseVar( int numRow ) const;

	/*! \brief Wybiera jedną ze zmiennych bazy do usuniecia
	 *
	 * Wybiera zmienną ze zmiennych bazowych w ten sposób, że dzieli
	 * współczynnik stojący przy danej zmiennej przez współczynnik z tego
	 * samego wiersza i z kolumny zmiennej wprowdzanej do bazy.
	 *
	 * W przypadku wersji dla fazy pierwszej wymagane jest aby iloczyn
	 * y_i0/y_ik był większy od zera.
	 *
	 * \return Indeks zmiennej usunietej z bazy
	 */
	int ChooseFromBase2Delete( int BaseVarIndex ) const;
	int ChooseFromBase2Delete1Phase( int BaseVarIndex ) const;

	/*! \brief Wybiera jeden z wierszy jako tymczasowa funkcje celu
	 *
	 * Wybiera ten z wierszy jako tymczasowa funkcje celu, ktorego wspolczynnik
	 * w pierwszej kolumnie jest najmniejszy.
	 */
	int ChooseTempObjFunc() const;

	/*! \brief Aktualizuje tabelę simpleksową po zmianie zmiennych w bazie
	 *
	 * Aktualizuje tabelę simpleksową po zmianie zmiennych w bazie zgodnie ze
	 * schematem:
	 *
	 *		PRZED:
	 *
	 *     |     ... -xj ... -xk
	 * --------------------------
	 * x0  | y00 ... y0j ... y0k
	 *     |     ...
	 * xBi | yi0 ... yij ... yik
	 *     |     ...
	 * xBr | yr0 ... yrj ... yrk
	 *     |     ...
	 * xBm | ym0 ... ymj ... ymk
	 * --------------------------
	 *
	 *		PO:
	 *
	 *     |                   ... -xj               ... -xBr
	 * -----------------------------------------------------------
	 * x0  | y00-(y0k*yr0/yrk) ... y0j-(y0k*yrj/yrk) ... -y0k/yrk
	 *     |                   ...
	 * xBi | yi0-(yik*yr0/yrk) ... yij-(yik*yrj/yrk) ... -yik/yrk
	 *     |                   ...
	 * xk  | yr0/yrk           ... yrj/yrk           ... 1/yrk
	 * -----------------------------------------------------------
	 *
	 *	Gdzie:
	 *		k - indeks zmiennej usuwanej z bazy
	 *		r - indeks zmiennej wprowadzanej do bazy
	 *		yrk - element centralny
	 */
	void UpdateTable( int k , int r );

	/*! \brief Wprowadza zaburzenie do problemu
	 * 
	 * Wprowadza takie zaburzenie do tabeli aby została wybrana inna
	 * funkcja zastępcza w następnym kroku 1szej fazy algorytmu simplex.
	 */
	void DisturbTable();

public:
	SimplexState State;

	Simplex( LinProblem& Problem );
	Simplex( LinProblem* Problem );
	~Simplex();

	LinProblemSolution* Solve();
	LinProblemSolution* Solve1Phase();
	LinProblemSolution* Solve2Phase();
	
};

#endif /* __SIMPLEX_HEADER__ */
