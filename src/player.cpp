#include "player.h"

uint Player::numPlayers = 0;

Player::Player()
    : name("Empty Player"),
    health(100.0f), stamina(100.0), strength(15.0f),
    equipedWeapon(0)
{
    Player::numPlayers++;
}

Player::Player( string name, double health, double stamina, double strength )
{
    this->setName(name);
    this->setHealth(health);
    this->setStamina(stamina);
    this->setStrenght(strength);
    Player::numPlayers++;
}

Player::Player( const Player& other )
{
    this->name = other.name;
    this->health = other.health;
    this->stamina = other.stamina;
    this->strength = other.strength;
    this->equipedWeapon = other.equipedWeapon;
    Player::numPlayers++;
}

Player::~Player()
{
    Player::numPlayers--;
}

/* Ataca um inimigo */
void Player::attack( Enemy& enemy ) const
{
    if (this->equipedWeapon == 0)
    {
        cout << "You have no weapon!\n";
        return;
    }

    string bodyPart = Enemy::chooseBodyPart();

    double damage = 0.0f;
    // O certo seria usar enums - string mágica
    if (bodyPart == "Back" || bodyPart == "Head")
        // Dobro de dano
        damage = this->equipedWeapon->inflictDamage(enemy.getHealth() / 2);

    else
        damage = this->equipedWeapon->inflictDamage(enemy.getHealth());
    
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

/**
 * @brief Pega um item do chão
 * @param item Item para ser adicionado ao inventário
*/
void Player::grabItem(Item& item)
{
    for (pair<Item, short>& inventoryItem : this->inventory)
    {
        if (inventoryItem.first.getName() == item.getName())
        {
            if (inventoryItem.second >= Player::ITEM_MAX_STACK)
                return;
            inventoryItem.second++;
            return;
        }
    }

    this->inventory.push_back( std::make_pair( item, (short) 1 ) );
}

/**
 * @brief Consome um item do inventário.
 * @param item Item a ser consumido
*/
void Player::useItem(Item& item)
{
    for (pair<Item, short>& inventoryItem : this->inventory)
    {
        if (inventoryItem.first.getName() == item.getName())
        {
            if (inventoryItem.second <= 0)
                return;
                
            inventoryItem.second--;
            this->setHealth(
                this->getHealth() + inventoryItem.first.getHealQuantity()
            );
            
            return;
        }
    }    
}

void Player::equipWeapon(Weapon &weapon)
{
    cout << "Personagem equipa " << weapon.getName() << "\n";
    this->equipedWeapon = &weapon;
}

/**
 * @brief Ataca um inimigo até um dos dois cair.
 * @returns Bool - True == Vitória e false == Derrota
*/
bool Player::battle(Enemy & enemy)
{
    cout << this->getName() << " inicia uma batalha com "<< enemy.getName()
        << "\n";

    while (enemy.getHealth() > 0 && this->getHealth() > 0)
    {
        cout << "===========\n";
        cout << enemy.getName() << " : " << enemy.getHealth() << "\n";
        cout << this->getName() << " : " << this->getHealth() << "\n";
        cout << "===========\n";

        enemy.attack(*this);
        this->attack(enemy);
    }

    cout << "===========\n";
    cout << enemy.getName() << " : " << enemy.getHealth() << "\n";
    cout << this->getName() << " : " << this->getHealth() << "\n";
    cout << "===========\n";

    return ( enemy.getHealth() > 0 ) ? false : true;
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

/**
 * @brief Printa o inventário do player
*/
void Player::showInventory()
{
    cout << "===" << this->getName() << " 's Inventory ===\n";
    for (std::pair< Item, short > item : this->inventory)
    {
        cout << item.first.getName() << "\t" << item.second << "\n";
    }
    cout << "================================\n";
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
    if (name.size() > Player::NAME_MAX_SIZE)
    {
        string substr_name = name.substr(0, Player::NAME_MAX_SIZE);
        cout << "Player name can't be more than "
             << NAME_MAX_SIZE << " chars long! "
             << "Getting " << substr_name << " substring!\n";

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