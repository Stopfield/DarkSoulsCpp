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
: Entity ( static_cast<Entity> (other) )
{
    this->copyAttacks( other );
    Player::numPlayers++;
}

Player::~Player()
{
    this->deleteAttacks();
    Player::numPlayers--;
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

ostream &operator<<(ostream& output, const Player& player)
{
    output << " * Player Entity" << player.getName() << " *\n";
    output << static_cast<Entity> (player);
    return output;
}

int operator!(const Player& player)
{
    return !( static_cast<Entity> ( player ) );
}

const Player &Player::operator=(const Player& other)
{
    if (this != &other)
    {
        static_cast<Entity> (*this) = static_cast<Entity> (other);

        if (this->attacks.empty())
            this->deleteAttacks();
    
        this->copyAttacks(other);
    }
    return *this;
}

int Player::operator==(const Player& other)
{
    return ( static_cast<Entity> ( *this ) == static_cast<Entity> (other) ) ;
}

int Player::operator!=(const Player& other)
{
    return !( *this == other );
}
