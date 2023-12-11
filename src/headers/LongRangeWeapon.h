#ifndef LONG_RANGE_WEAPON_H
#define LONG_RANGE_WEAPON_H

#include "Weapon.h"
#include "Entity.h"

class LongRangeWeapon : public Weapon
{
    friend ostream& operator<<  ( ostream&, const LongRangeWeapon& );
    friend int      operator!   ( const LongRangeWeapon& );
public:
    LongRangeWeapon             (  );
    LongRangeWeapon             ( string, double, double );
    LongRangeWeapon             ( const LongRangeWeapon& );
    virtual ~LongRangeWeapon    (  );

    void use            ( Entity& ) override;
    void inflict_damage ( Entity& ) override;
    bool verifyHit      ( Entity& );
    void aim_at         ( Entity&, size_t );

    bool    isTargetHit         (  ) { return this->has_hit;            }
    size_t  get_body_part_index (  ) { return this->body_part_index;    }

    inline double getAccuracy() { return this->accuracy; }
    void setAccuracy( double );

    const LongRangeWeapon&  operator=   ( const LongRangeWeapon& );
    int                     operator==  ( const LongRangeWeapon& );
    int                     operator!=  ( const LongRangeWeapon& );

private:
    double accuracy;
    bool has_hit;   /* Checa na batalha pra ver se acertou! */
    size_t body_part_index = 0;
};

#endif