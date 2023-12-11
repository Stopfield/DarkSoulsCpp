#ifndef BATTLE_H
#define BATTLE_H

#include "Entity.h"
#include "Player.h"
#include "Enemy.h"

class Battle
{
public:
    Battle(  );
    Battle( Entity&, Entity& );
    Battle( const Battle& );
    virtual ~Battle(  );

    virtual bool begin_battle (  ) = 0;

    void planTurn       ( const Attack*, size_t, const Attack*, size_t );
    void executeTurn    (  );

    void setPrimeiro    ( Entity& );
    void setSegundo     ( Entity& );
    void setTurno       ( int );

    int     getTurno()      const { return this->turno;         }
    Entity* getPrimeiro()   const { return this->primeiro_ptr;  }
    Entity* getSegundo()    const { return this->segundo_ptr;   }
protected:
    bool areEntitiesEqual (Entity&, Entity&);

    Entity* primeiro_ptr    = 0;
    Entity* segundo_ptr     = 0;

    const Attack* attack_primeiro_ptr = 0;
    const Attack* attack_segundo_ptr  = 0;

    size_t primeiro_aim_index = 0;
    size_t segundo_aim_index = 0;
    
    int turno;
};

#endif // BATTLE_H