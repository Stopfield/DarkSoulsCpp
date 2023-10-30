/* 
 * File:   Data.cpp
 * Author: Cssj
 * 
 * Created on 9 de Junho de 2012, 14:47
 */

#include "Data.h"

#include <iostream>
using std::cout;
using std::ostream;

Data::Data(int d, int m, int a) 
{
    if ( m > 0 && m <= 12 ) // validate the month
        mes = m;
    
    if ( a < 0 )
        ano = 1900;
    else
        ano = a;
   
    dia = VerificaDia(d);
}

void Data::print() const
{
   cout << dia << '/' << mes << '/' << ano;
}

ostream& operator<< ( ostream& output, const Data& right )
{
    output << right.dia << '/' << right.mes << '/' << right.ano;
    return output;
}

int Data::operator== ( const Data& right )
{
    if (this->ano == right.ano && this->mes == right.mes && this->dia == right.dia)
        return 1;
    return 0;
}

int Data::VerificaDia(int diaTeste) const
{
    static const int diasPorMes[ 13 ] = 
       { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    
    if ( diaTeste > 0 && diaTeste <= diasPorMes[ mes ] )
        return diaTeste;
    
    if ( mes == 2 && diaTeste == 29 && ( ano % 400 == 0 ||
            ( ano % 4 == 0 && ano % 100 != 0 ) ) )
        return diaTeste;
    
    cout << "Dia invalido (" << diaTeste << ") configurado para 1.\n";
    return 1; 
   
}