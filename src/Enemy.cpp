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
                map< int, Attack* > attacks_and_probabilities )
: Entity( name, health, stamina, strength, dexterity, position, bodyParts )
{
    /*
     * Para que o usuário seja impossibilitado de criar um novo objeto,
     * é necessário criar uma função no main que impossibilite isso. 
    */
    if (Enemy::numEnemies >= Enemy::MAX_NUM_ENEMIES)
        cout << "Number of enemies reached maximum value! Be careful!\n";

    probabilitiesAndAttacks = map< int, Attack* > ();

    numEnemies++;
}

Enemy::Enemy( const Enemy& other ) : Entity( static_cast<Entity> (other) )
{
    std::cout << "Teste" << std::endl;
    if (Enemy::numEnemies >= Enemy::MAX_NUM_ENEMIES)
        cout << "Number of enemies reached maximum value! Be careful!\n";
    numEnemies++;

    // Copia map
    if (!other.probabilitiesAndAttacks.empty())
    {
        for ( auto& prob_and_attacks : other.probabilitiesAndAttacks )
        {
            std::cout << *prob_and_attacks.second << std::endl;
            this->addAttackAndProbability(
                new Attack (*prob_and_attacks.second), prob_and_attacks.first
            );
        }
    }
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
const Attack *const Enemy::chooseAttack( )
{
    std::random_device rd;
    std::mt19937 gerador(rd());
    std::uniform_int_distribution<int> distribuicao(1, 100);
    int chance = distribuicao(gerador);

    Attack* chosen_attack = 0;

    for (const auto& par : this->probabilitiesAndAttacks)
    {
        if (chance < par.first)
        {
            return par.second;
        }
        chosen_attack = par.second;
    }

    return chosen_attack;
}

void Enemy::enrageEnemy(Enemy &) const
{
}

void Enemy::addAttackAndProbability( Attack* attack, int probability )
{
    probabilitiesAndAttacks[probability] = new Attack( *attack );
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
    output << *(dynamic_cast<const Entity*> (&enemy));  // Static_cast não funciona????
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
    return ( static_cast<Entity> ( *this ) == static_cast<Entity> (other)
            && this->compareAttacks( other )) ;
}

int Enemy::operator!=(const Enemy& other)
{
    return !( *this == other );
}

bool Enemy::compareAttacks(const Enemy& other)
{
    bool is_equal = false;
    for ( auto& pair : this->probabilitiesAndAttacks )
    {
        for (auto& other_pair : other.probabilitiesAndAttacks )
        {
            if (pair.first == other_pair.first && *pair.second == *other_pair.second)
            {
                is_equal = true;
                break;
            }
            is_equal = false;
        }
    }
    return is_equal;
}
