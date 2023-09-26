#include "enemy.h"

Enemy::Enemy()
    : name("Empty Enemy"), health(100.0f), stamina(100.0), strength(15.0f), equipedWeapon(0)
{
    cout << "Creating empty enemy with default stats...\n";
}

Enemy::Enemy( string name, double health, double stamina, double strength )
{
    this->setName(name);
    this->setHealth(health);
    this->setStamina(stamina);
    this->setStrenght(strength);
}

Enemy::Enemy( const Enemy& other )
{
    this->name = other.name;
    this->health = other.health;
    this->stamina = other.stamina;
    this->strength = other.strength;
    this->equipedWeapon = other.equipedWeapon;
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
    if (!isGuarding)
        cout << "Inimigo entra em postura de defesa! Perde velocidade!\n";
    else
        cout << "Inimigo sai da postura de defesa! Velocidade normal\n";
    this->isGuarding = !this->isGuarding;
}

void Enemy::equipWeapon( Weapon& weapon )
{
    cout << "Inimigo equipa " << weapon.getName() << "\n";
    this->equipedWeapon = &weapon;
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
    if (name.size() > this->NAME_MAX_SIZE)
    {
        string substr_name = name.substr(0, NAME_MAX_SIZE);
        cout << "Enemy name can't be more than "
             << NAME_MAX_SIZE << " chars long! "
             << "Getting " << substr_name << " substring!";

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