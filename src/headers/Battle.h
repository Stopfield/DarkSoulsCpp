#ifndef BATTLE_H
#define BATTLE_H

#include "Entity.h"
#include "Player.h"
#include "Enemy.h"

class Battle
{
    friend ostream& operator<<  ( ostream&, const Battle& );
    friend int      operator!   (const Battle& );
public:
    Battle(  );
    Battle( Entity&, Entity& );
    Battle( const Battle& );

    virtual ~Battle(  );

    virtual bool begin_battle   (  )    = 0;
    void planTurn( const Attack&, const Attack& );
    void executeTurn();

    void setPrimeiro    ( Entity& );
    void setSegundo     ( Entity& );
    void setTurno       ( int );

    int     getTurno()      const { return this->turno;     }
    Entity* getPrimeiro()   const { return this->primeiro_ptr;  }
    Entity* getSegundo()    const { return this->segundo_ptr;   }

    const Battle& operator= ( const Battle& );
    int operator==          ( const Battle& );
    int operator!=          ( const Battle& );

protected:
    Entity* primeiro_ptr    = 0;
    Entity* segundo_ptr     = 0;

    const Attack* attack_primeiro_ptr = 0;
    const Attack* attack_segundo_ptr  = 0;
    
    int turno;
};

#endif // BATTLE_H