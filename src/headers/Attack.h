#ifndef ATTACK_H
#define ATTACK_H

#include <iostream>
#include <string>

using std::string;
using std::ostream;

class Attack
{
    friend ostream& operator<<  ( ostream&, const Attack& );
    friend int      operator!   ( const Attack& );
public:
    Attack  ();
    Attack  ( string, double, double, string );
    Attack  ( Attack& );
    ~Attack ();

    inline double getDamageModifier()       const { return this->damageModifier;        }
    inline double getStaminaCostModifier()  const { return this->staminaCostModifier;   }
    inline string getDisplayMessage()       const { return this->displayMessage;        }

    void setName                ( string );
    void setDamageModifier      ( double );
    void setStaminaCostModifier ( double );
    void setDisplayMessage      ( string );

    const Attack& operator= ( const Attack& );
    int operator==          ( const Attack& );
    int operator!=          ( const Attack& );

private:
    const static size_t DISPLAY_MSG_MAX_SIZE;
    const static size_t NAME_MAX_SIZE;
    const static string DEFAULT_ATTACK_NAME;

    string name;
    double damageModifier;
    double staminaCostModifier;
    string displayMessage;
};

#endif // ATTACK_H