
#include <iostream>

#include "Armor.h"
#include "Entity.h"
#include "Consumable.h"
#include "Attack.h"
#include "Player.h"
#include "Enemy.h"

#include "ConsumableParser.h"
#include "WeaponParser.h"
#include "ArmorParser.h"
#include "InventoryParser.h"
#include "EntityParser.h"
#include "BodyPartsParser.h"
#include "AttackParser.h"
#include "PlayerParser.h"
#include "EnemyParser.h"
#include "OffensiveConsumable.h"
#include "RestorativeConsumable.h"

#include "NormalBattle.h"
#include "BossBattle.h"
#include "NPC.h"

int main()
{
    LongRangeWeapon arco("Arco", 15.0f, 10.0f);
    MeleeWeapon martelo("Martelo", 20.0f, 1.5f);
    OffensiveConsumable bomba("Bomba", "Explode", 0.25f);
    RestorativeConsumable estus_flask("Estus Flask", "Recupera vida", 2.0f);

    Attack *const estocada = new Attack("Estocada", 10.0f, 2.0f, "estoca o inimigo!");

    Player thiago("Thiago");
    Enemy jonas("Jonas");
    Enemy ultron("Ultron");

    thiago.grabItem( arco );
    thiago.grabItem( estus_flask );
    thiago.grabItem( bomba );

    // thiago.showInventory();
    thiago.useItemOn( thiago, 2 );

    thiago.equipWeapon( &martelo );
    thiago.addAttack(*estocada);
    jonas.equipWeapon( &arco );

    NPC jorge;

    jorge.add_to_monologue( "Testando" );
    jorge.add_to_monologue( "Arqueiros para ali" );

    NormalBattle nova_batalha( thiago, jonas );
    BossBattle batalha_do_seculo(thiago);

    std::cout << jonas.isLongRangeEquipped() << "\n";

    batalha_do_seculo.add_phase( jonas );
    batalha_do_seculo.add_phase( ultron );

    batalha_do_seculo.begin_battle();

    delete estocada;
    return 0;
}