#ifndef NORMAL_BATTLE_H
#define NORMAL_BATTLE_H

#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Battle.h"

class NormalBattle : public Battle
{
    friend ostream& operator<<  ( ostream&, const NormalBattle& );
    friend int      operator!   (const NormalBattle& );
public:
    NormalBattle(  );
    NormalBattle( Entity&, Entity& );
    NormalBattle( const NormalBattle& );

    virtual ~NormalBattle(  );

    bool begin_battle (  ) override;

    const NormalBattle& operator=   ( const NormalBattle& );
    int                 operator==  ( const NormalBattle& );
    int                 operator!=  ( const NormalBattle& );
private:
    bool primeiro_choose_attack;
    bool segundo_choose_attack;
};

#endif // NORMAL_BATTLE_H