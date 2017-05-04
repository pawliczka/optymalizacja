#pragma once
/*
 * Status algorytmu
 *
 *	1. STATUS_BUSY - algorytm jest w toku
 *	2. STATUS_WRONG_TABLE - tabela przekazana nie spelnia warunku dopuszczalnosci
 *  3. STATUS_SOLVED - algorytm zakonczyl dzialanie i zwrocił wynik
 *	4. STATUS_INITIALIZED - algorytm zostal poprawnie zainicjalizowany
 */
enum class SimplexStatus
{
    STATUS_INITIALIZED,
    STATUS_BUSY,
    STATUS_WRONG_TABLE,
    STATUS_SOLVED
};
