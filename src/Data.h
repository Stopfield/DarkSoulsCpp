/* 
 * File:   Data.h
 * Author: Cssj
 *
 * Created on 9 de Junho de 2012, 14:47
 */

#ifndef DATA_H
#define	DATA_H

#include <iostream>

using std::cout;
using std::ostream;

class Data 
{
    friend ostream& operator<< ( ostream&, const Data& ); 
public:
    
    Data( int = 1, int = 1, int = 1900 );
    
    void print() const;
    
    int operator== (const Data&);
    
private:
    
    int mes;
    int dia;
    int ano;
    
    int VerificaDia( int ) const;
};

#endif	/* DATA_H */
