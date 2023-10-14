#include "enemy.h"

/* Atributos static */
const uint Enemy::MAX_NUM_ENEMIES = 64;
const size_t Enemy::NAME_MAX_SIZE = 20;
const ushort Enemy::MIN_ENEMIES_TO_RAGE = 3;
uint Enemy::numEnemies = 0;

const array<string, 3> Enemy::BODY_PARTS {
    "Front", "Back", "Head"
};

/** 
 * @brief Pick a body part of an Enemy.
 * @return String representing body part
*/
string Enemy::chooseBodyPart()
{
    // Choose a seed
    srand(time(0));
    size_t random_indice = rand() % Enemy::BODY_PARTS.size();

    return Enemy::BODY_PARTS.at(random_indice);
}

/**
 * @brief Quando há menos de três inimigos, os inimigos ficam mais fortes.
 * Nem todos os inimigos fazem isso. Pode ser encadeado com elementos da
 * história.
*/
void Enemy::enrageEnemy(Enemy& enemy)
{
    // Se houver mais de três, desbalanceamento da dificuldade
    if (Enemy::numEnemies < Enemy::MIN_ENEMIES_TO_RAGE)
    {
        cout << enemy.getName() << " is enraged! 20% buff in strength!\n";
        enemy.strength *= 1.20f;
        return;
    }
    cout << "There is more than " << Enemy::MIN_ENEMIES_TO_RAGE << " enemies!\n"
        << enemy.getName() << " is confident in victory! No Buffs!\n";
}

Enemy::Enemy()
    : name("Empty Enemy"),
      health(100.0f), stamina(100.0), strength(15.0f),
      equipedWeapon(0)
{
    /*
     * Para que o usuário seja impossibilitado de criar um novo objeto,
     * é necessário criar uma função no main que impossibilite isso. 
    */
    if (Enemy::numEnemies >= Enemy::MAX_NUM_ENEMIES)
        cout << "Number of enemies reached maximum value! Be careful!\n";

    numEnemies++;
}

Enemy::Enemy( string name, double health, double stamina, double strength )
{
    if (Enemy::numEnemies >= Enemy::MAX_NUM_ENEMIES)
        cout << "Number of enemies reached maximum value! Be careful!\n";

    this->setName(name);
    this->setHealth(health);
    this->setStamina(stamina);
    this->setStrenght(strength);
    numEnemies++;
}

Enemy::Enemy( const Enemy& other )
{
    if (Enemy::numEnemies >= Enemy::MAX_NUM_ENEMIES)
        cout << "Number of enemies reached maximum value! Be careful!\n";

    this->name = other.name;
    this->health = other.health;
    this->stamina = other.stamina;
    this->strength = other.strength;
    this->equipedWeapon = other.equipedWeapon;
    numEnemies++;
}

Enemy::~Enemy()
{
    numEnemies--;
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

/* Entra ou sai da postura de defesa */
void Enemy::guard()
{
    if (!guarding)
        cout << "Inimigo entra em postura de defesa! Perde velocidade!\n";
    else
        cout << "Inimigo sai da postura de defesa! Velocidade normal\n";
    this->guarding = !this->guarding;
}

void Enemy::equipWeapon( Weapon& weapon )
{
    cout << this->getName() << " equipa " << weapon.getName() << "\n";
    this->equipedWeapon = &weapon;
}

void Enemy::attack( Player& player ) const
{
    if (this->equipedWeapon == 0)
    {
        cout << "You have no weapon!\n";
        return;
    }
    double damage = this->equipedWeapon->inflictDamage(player.getHealth());
    player.setHealth(damage);
}

void Enemy::setName(string name)
{
    /* Names can't be empty */
    if (name.empty())
    {
        cout << "Enemy name can't be empty! Defaulting to \"Empty Enemy\"\n";
        this->name = "Empty Enemy";
        return;
    }

    /* Names can't be too long */
    if (name.size() > Enemy::NAME_MAX_SIZE)
    {
        string substr_name = name.substr(0, NAME_MAX_SIZE);
        cout << "Enemy name can't be more than "
             << NAME_MAX_SIZE << " chars long! "
             << "Getting " << substr_name << " substring!\n";

        this->name = substr_name;
        return;
    }

    this->name = name;
}

void Enemy::setHealth( double health )
{
    /* Health can't be negative */
    if (health < 0)
    {
        cout << "Health can't be negative! Defaulting to 0!\n";
        this->health = 0;
        return;
    }
    this->health = health;
}

void Enemy::setStrenght( double strength )
{
    /* Strength can't be negative */
    if (strength < 0)
    {
        cout << "Strength can't be negative! Defaulting to 0!\n";
        this->strength = 0;
        return;
    }
    this->strength = strength;
}

void Enemy::setStamina( double stamina )
{
    /* Stamina can't be negative */
    if (stamina < 0)
    {
        cout << "Stamina can't be negative! Defaulting to 0!\n";
        this->stamina = 0;
        return;
    }
    this->stamina = stamina;
}