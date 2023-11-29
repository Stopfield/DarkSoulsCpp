#ifndef BOSS_BATTLE_H
#define BOSS_BATTLE_H

#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Battle.h"

class BossBattle : Battle
{
    friend ostream& operator<<  ( ostream&, const BossBattle& );
    friend int      operator!   (const BossBattle& );
public:
    BossBattle  (  );
    BossBattle  ( Entity& );
    BossBattle  ( const BossBattle& );

    virtual ~BossBattle(  );

    bool begin_battle( ) override;
    void add_phase( Enemy& );

    const BossBattle& operator= ( const BossBattle& );
    int operator==              ( const BossBattle& );
    int operator!=              ( const BossBattle& );

protected:
    void copyBossPhases( const BossBattle& );
    vector<Enemy*> boss_phases;
    int phase_number;
};

#endif // BossBattle_H