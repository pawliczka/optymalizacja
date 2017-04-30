/**
 * \file linprog.hh
 *
 * To jest plik zawierający nagłowki biblioteki implemetującej obiekty
 * wykorzystywane w problematyce programowania liniowego.
 *
 * Version 1.2
 * Last mod: 08.04.13
 * Authors: StilL {yarpen_zigrin11@wp.pl}
 *			Vova {vovagorodok2@gmail.com}
 */

/***** TODO
    1. Konstruktor kopiujący
*****/

#ifndef __LINEAR_PROGRAMMING_HEADER__
#define __LINEAR_PROGRAMMING_HEADER__

//#ifdef QT_VERSION
//	#define string QString
//	#define vector QVector
//#endif

#include <vector>
#include <string>
#include "Equation.hpp"

/**
 * Typ ograniczeń:
 *	EQU - równościowe
 *	LE - mniejsze lub równe
 *  GE - większe lub równe
 */
enum ConstrType { EQU , LE , GE };

/**
 * Typ optymalizacji:
 *	MAX - maksymalizowanie funkcji celu (np. zysk)
 *	MIN - minimalizowanie funkcji celu (np. koszty)
 */
enum OptimizeType { MAX , MIN };

/*
 * Przypadek problemu
 *
 *	1. ONE_SOLUTION - podstawowa forma, istnieje jedno rozwiazanie optymalne w
 *					  jednym z wierzcholkow
 *	2. NO_SOLUTIONS - zadanie jest nieograniczone przez co nie istnieje
 *					  rozwiazanie optymalne
 *  3. INCONSISTENT - zadanie jest sprzeczne i nie ma rozwiazan
 *	4. INF_SOLUTIONS_BOUND - zadanie ma nieskończona liczbe rozwiazan na
 *					  ograniczonym obszarze
 *	5. INF_SOLUTIONS_UNBOUND - zadanie ma nieskonczona liczba rozwiazan na
 *					  nieograniczonym obszarze
 *  6. UNKNOWN -	  domyslnie: nieznany stan
 */
enum LinProblemCase { ONE_SOLUTION , NO_SOLUTIONS , INCONSISTENT ,
                      INF_SOLUTIONS_BOUND , INF_SOLUTIONS_UNBOUND ,
                      UNKNOWN };


/**
 * Zamienia ciąg znaków na typ ograniczenia.
 */
ConstrType StrToConstrType( std::string& _type );

/**
 * \brief Modeluje ogranienie
 *
 * Modeluje ograniczenie postaci:
 *		transp(a) * x <= b	, lub
 *		transp(a) * x >= b  , lub
 *		transp(a) * x = b	, gdzie
 *		a = { a_1 , a_2 , ... , a_n } - współczynniki przy zmiennych decyzyjnych
 *		x = { x_1 , x_2 , ... , x_n } - zmienne decyzyjne problemu
 *		b \in R	- wyraz wolny ograniczenia
 *
 */
class Constraint {
    /**
     * \brief Ilość zmiennych decyzyjnych do których zastosowano ograniczenie
     */
    int n;

    /**
     * \brief Współczynniki rzeczywiste przy zmiennych decyzyjnych
     */
    std::vector<double> a;

    /**
     * \brief Wyraz wolny ograniczenia
     */
    double b;

    /**
     * \brief Typ ograniczenia
     */
    ConstrType type;

public:
    Constraint();
    Constraint( int _n , double _a[] , double _b , ConstrType _type );
    ~Constraint() {}

    void print() const;
    ConstrType getType() const { return type; }
    double geta( int coeffNum ) const;
    inline double getb() const { return b; }

};

/**
 * \brief Modeluje funkcję celu
 *
 * Modeluje funkcję celu postaci:
 *	(max/min) z = c_1 * x_1 + c_2 * x_2 + ... + c_n * x_n
 *	= (max/min) sum{i=1..n}( transp(c_i)*x_i )
 */
class ObjectiveFunc {
    /**
     * \brief Ilość zmiennych decyzyjnych w funkcji celu
     */
    int n;

    /**
     * \brief Współczynniki rzeczywiste przy zmiennych decyzyjnych
     */
    std::vector<double> c;

public:
    ObjectiveFunc();
    ObjectiveFunc( int _n , double _c[] );
    ~ObjectiveFunc() {}

    void print() const;
    double getc( int coeffNum ) const;

};


/**
 * \brief Modeluje problem liniowy optymalizacji
 *
 * Problem składa się z funkcji celu oraz z dowolnej liczby ograniczeń.
 * W tej wersji zakładamy, że rzadna ze zmiennych decyzyjnych x_1 .. x_n nie
 * może być ujemna.
 */
class LinProblem {
    /**
     * \brief Ilość zmiennych decyzyjnych w funkcji celu
     */
    int n;

    /**
     * \brief Ilość ograniczeń
     */
    int m;

    /**
     * \brief Funkcja celu
     */
    Equation ObjFunc;

    /**
     * \brief Zbiór ograniczeń
     */
    std::vector<Equation> ConstrSet;

    /**
     * \brief Typ optymalizacji
     */
    OptimizeType type;

public:
    LinProblem();
    LinProblem( int _n , OptimizeType _type );
    LinProblem( LinProblem& Copy );
    LinProblem( LinProblem* Copy );

    /**
     * \brief Tworzy funkcje celu
     *
     * Tworzy funkcję celu na postawie przekazanej tablicy współczynników
     * rzeczywistych.
     */
    void SetObjFunc(Equation& ObjFuncOrig);

    /**
     * \brief Tworzy i dodaje ograniczenie do zbioru ograniczeń
     *
     * Tworzy i dodaje ograniczenie do zbioru ograniczeń na podstawie danych z
     * tablicy oraz parametrów wyrazu wolnego i typu ogranczenia.
     */
    void setConstrains(const std::vector<Equation>& constrains );

    /**
     * \brief Usuwa ostatnie ograniczenie z tablicy
     */
    double RemoveLastConstr();

    void print() const;

    inline int getn() const { return n; }
    inline int getm() const { return m; }
    inline OptimizeType gettype() const { return type; }
    inline OptimizeType setType( OptimizeType newType ) { return type = newType; }
    int numLessEqualConstr() const;
    int numGreaterEqualConstr() const;
    inline Equation& getObjFunc() { return ObjFunc; }
    Equation getConstr( int _constrNum );

};

/*!	\brief Struktura przechowująca rozwiązanie problemu
 *
 * Zawiera wartości zmiennych decyzyjnych oraz wartość zmiennej celu
 * w punkcie wyznaczonym przez te zmienne.
 */
class LinProblemSolution {

public:
    LinProblemSolution( int _n );
    LinProblemSolution( LinProblemSolution* Solution );
    ~LinProblemSolution() { delete VariableValues; }
    int n;
    double* VariableValues;
    double ObjFuncValue;
    void print() const;
    LinProblemCase Case;
};

#endif /* __LINEAR_PROGRAMMING_HEADER__ */
