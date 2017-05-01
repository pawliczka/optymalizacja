#pragma once
#include <vector>
#include <string>
#include "Equation.hpp"
#include "LinearProblemCase.hpp"

enum class OptimizeType { MAX , MIN };

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
    int n = 0;

    /**
     * \brief Ilość ograniczeń
     */
    int m = 0;

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
    OptimizeType type = OptimizeType::MAX;

public:
    LinProblem();
    LinProblem( int _n , OptimizeType _type );

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

    int getn() const { return n; }
    int getm() const { return m; }
    OptimizeType gettype() const { return type; }
    OptimizeType setType( OptimizeType newType ) { return type = newType; }
    int numLessEqualConstr() const;
    int numGreaterEqualConstr() const;
    const Equation& getObjFunc() const { return ObjFunc; }
    Equation getConstr( int _constrNum ) const;

};

/*!	\brief Struktura przechowująca rozwiązanie problemu
 *
 * Zawiera wartości zmiennych decyzyjnych oraz wartość zmiennej celu
 * w punkcie wyznaczonym przez te zmienne.
 */
struct LinProblemSolution {
    LinProblemSolution( int _n );
    std::vector<double> VariableValues;
    double ObjFuncValue;
    void print() const;
    LinProblemCase Case;
};
