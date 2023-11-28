#include "Enemy.h"

/* Atributos static */
const unsigned int      Enemy::MAX_NUM_ENEMIES      = 64;
const unsigned short    Enemy::MIN_ENEMIES_TO_RAGE  = 3;
unsigned short          Enemy::numEnemies           = 0;

// /**
//  * @brief Quando há menos de três inimigos, os inimigos ficam mais fortes.
//  * Nem todos os inimigos fazem isso. Pode ser encadeado com elementos da
//  * história.
// */
// void Enemy::enrageEnemy(Enemy& enemy)
// {
//     // Se houver mais de três, desbalanceamento da dificuldade
//     if (Enemy::numEnemies < Enemy::MIN_ENEMIES_TO_RAGE)
//     {
//         cout << enemy.getName() << " is enraged! 20% buff in strength!\n";
//         enemy.strength *= 1.20f;
//         return;
//     }
//     cout << "There is more than " << Enemy::MIN_ENEMIES_TO_RAGE << " enemies!\n"
//         << enemy.getName() << " is confident in victory! No Buffs!\n";
// }

Enemy::Enemy() : Entity()
{
    /*
     * Para que o usuário seja impossibilitado de criar um novo objeto,
     * é necessário criar uma função no main que impossibilite isso. 
    */
    if (Enemy::numEnemies >= Enemy::MAX_NUM_ENEMIES)
        cout << "Number of enemies reached maximum value! Be careful!\n";

    numEnemies++;
}

Enemy::Enemy(   string name,
                double health,
                double stamina,
                double strength,
                double dexterity,
                Vector2D position,
                vector< BodyPart > bodyParts,
                map< short, Attack* > attacks )
: Entity( name, health, stamina, strength, dexterity, position, bodyParts )
{
    /*
     * Para que o usuário seja impossibilitado de criar um novo objeto,
     * é necessário criar uma função no main que impossibilite isso. 
    */
    if (Enemy::numEnemies >= Enemy::MAX_NUM_ENEMIES)
        cout << "Number of enemies reached maximum value! Be careful!\n";

    probabilitiesAndAttacks = map< short, Attack* > ();

    numEnemies++;
}

Enemy::Enemy( const Enemy& other ) : Entity( static_cast<Entity> (other) )
{
    if (Enemy::numEnemies >= Enemy::MAX_NUM_ENEMIES)
        cout << "Number of enemies reached maximum value! Be careful!\n";
    numEnemies++;
}

Enemy::~Enemy()
{
    for ( auto& probAndAtk : this->probabilitiesAndAttacks )
        if (probAndAtk.second)
            delete probAndAtk.second;
    numEnemies--;
}

/**
 * Escolhe aleatoriamente um ataque do map.
*/
Attack& Enemy::chooseAttack( )
{
    short chance = rand() % 100;
    Attack *const atk = this->probabilitiesAndAttacks[ chance ];
    return *atk;
}

void Enemy::enrageEnemy(Enemy &) const
{
}

/* Ataca um inimigo */
// void Enemy::attack( Player& player ) const
// {
//     if (this->equipedWeapon == 0)
//     {
//         cout << "Enemy has no weapon!\n";
//         return;
//     }
//     double damage = this->equipedWeapon->inflictDamage(player.getHealth());
//     player.setHealth(damage);
// }

ostream &operator<<(ostream& output, const Enemy& enemy)
{
    output << " * Enemy Entity" << enemy.getName() << " *\n";
    output << static_cast<Entity> (enemy);
    return output;
}

int operator!(const Enemy& enemy)
{
    return !( static_cast<Entity> ( enemy ) );
}

const Enemy &Enemy::operator=(const Enemy& other)
{
    if (this != &other)
    {
        static_cast<Entity> (*this) = static_cast<Entity> (other);
    }
    return *this;
}

int Enemy::operator==(const Enemy& other)
{
    return ( static_cast<Entity> ( *this ) == static_cast<Entity> (other) ) ;
}

int Enemy::operator!=(const Enemy& other)
{
    return !( *this == other );
}
