#include "player.h"

Player::Player()
    : name("Empty Player"), health(100.0f), stamina(100.0), strength(15.0f), equipedWeapon(0)
{
    cout << "Creating empty player with default stats...\n";
}

Player::Player( string name, double health, double stamina, double strength )
{
    this->setName(name);
    this->setHealth(health);
    this->setStamina(stamina);
    this->setStrenght(strength);
}

Player::Player( const Player& other )
{
    this->name = other.name;
    this->health = other.health;
    this->stamina = other.stamina;
    this->strength = other.strength;
    this->equipedWeapon = other.equipedWeapon;
}

/* Ataca um inimigo */
void Player::attack( Enemy& enemy ) const
{
    if (this->equipedWeapon == 0)
    {
        cout << "You have no weapon!\n";
        return;
    }
    double damage = this->equipedWeapon->inflictDamage(enemy.getHealth());
    enemy.setHealth(damage);
}

/* Entra ou sai da postura de defesa */
void Player::guard()
{
    if (!isGuarding())
        cout << "Personagem entra em postura de defesa! Perde velocidade!\n";
    else
        cout << "Personagem sai da postura de defesa! Velocidade normal\n";
    this->guarding = !this->guarding;
}

void Player::equipWeapon( Weapon& weapon )
{
    cout << "Personagem equipa " << weapon.getName() << "\n";
    this->equipedWeapon = &weapon;
}

void Player::grabItem()
{
    if (this->item > ITEM_MAX_STACK)
    {
        cout << "Quantidade máxima de itens batida!\n";
        cout << "O item continua no chão!\n";
        return;
    }
    this->item++;
}

/* Placeholder */
void Player::move()
{
    if (isGuarding())
    {
        // Velocidade reduzida
        this->position += this->velocity / 2;
        return;
    }
    this->position += this->velocity;
}

void Player::setName(string name)
{
    /* Names can't be empty */
    if (name.empty())
    {
        cout << "Player name can't be empty! Defaulting to \"Empty Player\"\n";
        this->name = "Empty Player";
        return;
    }

    /* Names can't be too long */
    if (name.size() > this->NAME_MAX_SIZE)
    {
        string substr_name = name.substr(0, NAME_MAX_SIZE);
        cout << "Player name can't be more than "
             << NAME_MAX_SIZE << " chars long! "
             << "Getting " << substr_name << " substring!";

        this->name = substr_name;
        return;
    }

    this->name = name;
}

void Player::setHealth( double health )
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

void Player::setStrenght( double strength )
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

void Player::setVelocity(double velocity)
{
    if (velocity < 0.0f)
    {
        cout << "Velocidade não pode ser menor que zero\n";
        this->velocity = 0.0f;
        return;
    }

    if (velocity > 100.0f)
    {
        cout << "Velocidade não pode ser maior que cem\n";
        this->velocity = 100.0f;
        return;
    }

    this->velocity = velocity;
}

void Player::setStamina( double stamina )
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