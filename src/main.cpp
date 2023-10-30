#include <iostream>
#include <iomanip>

#include "Weapon.h"
#include "Enemy.h"
#include "Player.h"
#include "Item.h"
#include "Entity.h"
#include "Attack.h"
#include "Game.h"

using std::cout;

int main()
{
    Weapon metal_glove("Metal Glove", 15.0f);
    Weapon sword("Sword", 25.0f);
    
    Attack slam("Slam", 1.5, 15.0f, " levanta os bracos e os derruba com forca!");
    Attack jump_and_cut("Jump n Cut", 1.25, 15.0f,
        "pula e cai desferindo um golpe com toda sua forca!");

    Player alphonse( "Alphonse" );
    Player edward( "Edward" );

    alphonse.equipWeapon( metal_glove );
    alphonse.addAttack( slam );

    edward.equipWeapon(sword);
    edward.addAttack(jump_and_cut);

    while ( alphonse.getHealth() > 0 && edward.getHealth() > 0 )
    {
        alphonse.attack( edward, slam );
        edward.attack( alphonse, jump_and_cut );
    }
    
    return 0;
}