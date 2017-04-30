/**
 * \file linprog.cpp
 *
 * To jest plik zawierający źródła biblioteki implemetującej obiekty
 * wykorzystywane w problematyce programowania liniowego.
 *
 * Version 1.2
 * Last mod: 08.04.13
 * Authors: StilL {yarpen_zigrin11@wp.pl}
 *			Vova {vovagorodok2@gmail.com}
 */

#include "linprog.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <QDebug>

using namespace std;

/**
 * Zamienia ciąg znaków na typ ograniczenia.
 */
ConstrType StrToConstrType( string& _type )
{
    if( _type == "EQU" ) return EQU;
    if( _type == "LE" ) return LE;
    if( _type == "GE" ) return GE;

    return LE;
}

/**
 * Zamienia typ ograniczenia na ciag znakow.
 */
const char* ConstrTypeToSign( ConstrType _type )
{
    if( _type == EQU ) return "= ";
    if( _type == LE ) return "<=";
    if( _type == GE ) return ">=";

    return "";
}

/* ========================================================================= */
/* Constraints ------------------------------------------------------------- */


Constraint::Constraint()
{

}

Constraint::Constraint( int _n , double _a[] , double _b , ConstrType _type )
{
    n = _n ;
    b = _b ;
    type = _type ;
    for( int i = 0 ; i < n ; i++ )
        a.push_back( _a[i] ) ;
}

void Constraint::print() const
{
    if( this->n ) {
        qDebug() << this->a[0] << " x_1 ";
        for( int i = 1 ; i < this->n ; i++ ) {
            if( this->a[i]<0 )
                qDebug() << "  " << this->a[i];
            else
                qDebug() << "  +" << this->a[i];
            qDebug() << " x_" << i+1 << " ";
        }
        qDebug() << ConstrTypeToSign( this->type ) << "  " << b << endl;
    } else {
        qDebug() << "Constraint::Print> Ograniczenie nie istnieje." << endl;
    }
}

double Constraint::geta( int coeffNum ) const
{
    if( coeffNum >= n ) coeffNum= n-1 ;
    return a[ coeffNum ] ;
}


/* Constraints ------------------------------------------------------------- */
/* ========================================================================= */



/* ========================================================================= */
/* ObjectiveFunc ----------------------------------------------------------- */


ObjectiveFunc::ObjectiveFunc()
{

}

ObjectiveFunc::ObjectiveFunc( int _n , double _c[] )
{
    n = _n ;
    for( int i = 0 ; i < n ; i++ )
        c.push_back( _c[i] ) ;
}

void ObjectiveFunc::print() const
{
    if( this->n ) {
        qDebug() << "Z = ";
        qDebug() << this->c[0] << " x_1 ";
        for( int i = 1 ; i < this->n ; i++ ) {
            if( this->c[i]<0 )
                qDebug() << "  " << this->c[i];
            else
                qDebug() << "  +" << this->c[i];
            qDebug() << " x_" << i+1 << " ";
        }
        qDebug() << endl;
    } else {
        qDebug() << "ObjectiveFunc::Print> Funkcja celu nie istnieje." << endl;
    }
}

double ObjectiveFunc::getc( int coeffNum ) const
{
    if( coeffNum >= n )
        coeffNum= n-1 ;
    return c[ coeffNum ] ;
}


/* ObjectiveFunc ----------------------------------------------------------- */
/* ========================================================================= */


/* ========================================================================= */
/* LinProblem -------------------------------------------------------------- */


LinProblem::LinProblem()
{
    n = m = 0;
    type = MAX;
}
LinProblem::LinProblem( int _n , OptimizeType _type )
{
    n = _n;
    type = _type;
    m = 0;
}
LinProblem::LinProblem( LinProblem& Copy )
{
    n = Copy.getn();
    m = Copy.getm();
    ObjFunc = Copy.getObjFunc();
    ConstrSet = Copy.ConstrSet;

    type = Copy.gettype();
}
LinProblem::LinProblem( LinProblem* Copy )
{
    n = Copy->getn();
    m = 0;

    ObjFunc = Copy->getObjFunc();
    ConstrSet = Copy->ConstrSet;

    type = Copy->gettype();
}

void LinProblem::SetObjFunc(Equation& ObjFuncOrig)
{
    ObjFunc = ObjFuncOrig;
    n = ObjFunc.getIndexOfLastCofficient();
}

void LinProblem::setConstrains( const std::vector<Equation>& constrains )
{
    ConstrSet = constrains;
    m = constrains.size();
}

double LinProblem::RemoveLastConstr()
{
    double LastConstrb = ConstrSet[m].getCoefficient(0);
    ConstrSet.pop_back();
    m--;
    return LastConstrb;
}

void LinProblem::print() const
{
    int i;

    qDebug() << "Zadanie ";
    switch( type ) {
        case MAX: qDebug() << "maksymalizacji"; break;
        case MIN: qDebug() << "minimalizacji"; break;
    }
    qDebug() << " funkcji celu postaci:" << endl;
    //qDebug() << ObjFunc << endl;
    qDebug() << endl << "Przy ograniczeniach:" << endl;
    for( i = 0 ; i < this->m ; i++ ) {
        //ConstrSet[i]->print();
    }
    qDebug() << endl;
}

int LinProblem::numLessEqualConstr() const
{
    int lessEqualCnt = 0;
    for( int i = 0 ; i < this->m ; i++ )
        if( ConstrSet[i].getComparisonOperator() == ComparisonOperator::LessEqual) lessEqualCnt++;

    return lessEqualCnt;
}

int LinProblem::numGreaterEqualConstr() const
{
    int greaterEqualCnt = 0;
    for( int i = 0 ; i < this->m ; i++ )
        if( ConstrSet[i].getComparisonOperator() == ComparisonOperator::GreaterEqual ) greaterEqualCnt++;

    return greaterEqualCnt;
}

Equation LinProblem::getConstr( int constrNum )
{
    if( constrNum >= m ) constrNum= m-1 ;
    return ConstrSet[constrNum];
}

/* LinProblem -------------------------------------------------------------- */
/* ========================================================================= */


/* ========================================================================= */
/* LinProblemSolution ------------------------------------------------------ */

LinProblemSolution::LinProblemSolution( int _n )
{
    n = _n;
    Case = UNKNOWN;
    VariableValues = new double[ n ];
}

LinProblemSolution::LinProblemSolution( LinProblemSolution* Solution )
{
    n = Solution->n;
    ObjFuncValue = Solution->ObjFuncValue;
    VariableValues = new double[n];
    Case = Solution->Case;
    for( int i = 0 ; i < n ; i++ )
        VariableValues[i] = Solution->VariableValues[i];
}

void LinProblemSolution::print() const
{
    QString str;
    str += QString("\nRozwiazanie:\n");
    for( int i = 0 ; i < n ; i++ )
        str += QString("\tx") + QString::number(i+1) + QString(" = ") +
               QString::number(VariableValues[i]) + QString("\n");

    qDebug() << str;
    qDebug() << "Wartosc funkcji celu:";
    qDebug() << "\t" << ObjFuncValue << endl;
}


/* LinProblemSolution ------------------------------------------------------ */
/* ========================================================================= */
