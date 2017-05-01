#pragma once
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
enum class LinProblemCase
{
    ONE_SOLUTION,
    NO_SOLUTIONS,
    INCONSISTENT,
    INF_SOLUTIONS_BOUND,
    INF_SOLUTIONS_UNBOUND,
    UNKNOWN
};
