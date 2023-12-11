#include "Player.h"

uint Player::numPlayers = 0;

Player::Player() : Entity()
{
    Player::numPlayers++;
}

Player::Player( string name,
                double health,
                double stamina,
                double strength,
                double dexterity,
                Vector2D position,
                vector< BodyPart > bodyParts )
: Entity( name, health, stamina, strength, dexterity, position, bodyParts )
{
    Player::numPlayers++;
}

Player::Player( const Player& other )
: Entity ( other )
{
    this->copyAttacks( other );
    Player::numPlayers++;
}

Player::~Player()
{
    std::cout << "Destrutor do Player\n" << std::endl;
    this->deleteAttacks();
    Player::numPlayers--;
}

void Player::interact()
{
    std::cout << "É outro jogador. Ele não parece agressivo. Atacar?\n";
}

/**
 * Adiciona um ataque no vetor de ataques.
 * @param atk Ataque a ser adicionado.
*/
void Player::addAttack( Attack& atk )
{
    this->attacks.push_back( new Attack( atk ) );
}

#pragma region Private Methods

/**
 * Copia o vetor de ataques de outro Player.
 * @param other O player do qual o inventário será copiado.
*/
void Player::copyAttacks(const Player& other )
{
    if ( !this->attacks.empty() )
        this->deleteAttacks();

    for ( const auto& otherAtk : other.attacks )
        this->attacks.push_back( new Attack( *otherAtk ) );
}

/**
 * Deleta os ponteiros de ataques dentro do Vetor attacks.
*/
void Player::deleteAttacks( )
{
    for ( auto& atk : this->attacks )
        if ( atk )
            delete atk;
    this->attacks.clear();
}

#pragma endregion

/* Exemplo de batalha
 * @brief Ataca um inimigo até um dos dois cair.
 * @returns Bool - True == Vitória e false == Derrota
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

*/

#pragma region OperatorOverloads

ostream &operator<<(ostream& output, const Player& entity )
{
    output << " === Player Entity " << entity.name << " === \n";
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

int operator!(const Player& right)
{
    return ( right.name.empty() || right.name == right.DEFAULT_NAME );
}

const Player &Player::operator=(const Player& right)
{
    if (this != &right)
    {
        if (right.position == 0)
            this->position = 0;
        else
            this->position = new Vector2D { right.position->x, right.position->y };
        this->representation = right.representation;
        this->name = right.name;
        this->maxHealth = right.maxHealth;
        this->health = right.health;
        this->stamina = right.stamina;
        this->strength = right.strength;
        this->dexterity = right.dexterity;
        this->bodyParts = right.bodyParts;

        this->copyWeapon( right.equiped_weapon_ptr );
        this->copyInventory( right.inventory_ptr );

        if (this->attacks.empty())
            this->deleteAttacks();
    
        this->copyAttacks(right);
    }
    return *this;
}

int Player::operator==(const Player& right)
{
    if (this->name == right.name )
        return 1;
    return 0;
}

int Player::operator!=(const Player& other)
{
    return !( *this == other );
}

#pragma endregion