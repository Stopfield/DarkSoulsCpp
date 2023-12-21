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

Enemy::Enemy( const Enemy& other ) : Entity( other )
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
    std::cout << "Destrutor do Enemy\n";
}

bool Enemy::interact( GameObject& other )
{
    char choice;
    std::cout << "Você quer interagir com " << this->name << "?";
    std::cin >> choice;

    if (choice == 'Y')
        return true;
    else
        return false;

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

ostream &operator<<(ostream& output, const Enemy& entity)
{
    output << " === Enemy Entity " << entity.name << " === \n";
    output << "Entity: " << entity.name << "\n";
    output << "Health: " << entity.health << "\n";
    output << "Stamina: " << entity.stamina << "\n";
    output << "Strength: " << entity.strength << "\n";
    output << "Dexterity: " << entity.dexterity;

    if (entity.equiped_weapon_ptr == 0)
    {
        output << "\n === Weapon === \n";
        output << " Unarmed \n";
    }
    /* Verifica o tipo de arma */
    else
    {
        LongRangeWeapon* long_range_wpn_ptr
            = dynamic_cast<LongRangeWeapon*> (entity.equiped_weapon_ptr);

        if (long_range_wpn_ptr != nullptr)
        {
            output << *long_range_wpn_ptr;
            long_range_wpn_ptr = nullptr;
        }
        else
        {
            MeleeWeapon* melee_wpn_ptr
                = dynamic_cast<MeleeWeapon*> (entity.equiped_weapon_ptr);
            output << *melee_wpn_ptr;
            melee_wpn_ptr = nullptr;
        }
    }
    output << " === Body Parts === \n";
    for (const auto& part : entity.bodyParts)
        output << part.partDescription << "\n";
    output << " ======================== \n";
    return output;
}

int operator!(const Enemy& right)
{
    return ( right.name.empty() || right.name == right.DEFAULT_NAME );
}

const Enemy& Enemy::operator=(const Enemy& right)
{
    if (this != &right)
    {
        Entity::operator=(right);

        // Copia map
        if (!right.probabilitiesAndAttacks.empty())
        {
            for ( auto& prob_and_attacks : right.probabilitiesAndAttacks )
            {
                std::cout << *prob_and_attacks.second << std::endl;
                this->addAttackAndProbability(
                    new Attack (*prob_and_attacks.second), prob_and_attacks.first
                );
            }
        }

    }
    return *this;
}

int Enemy::operator==(const Enemy& right)
{
    return (Entity::operator==(right));
}

int Enemy::operator!=(const Enemy& other)
{
    return !( *this == other );
}
