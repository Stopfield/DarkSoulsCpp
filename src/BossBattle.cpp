#include "BossBattle.h"

BossBattle::BossBattle() : Battle()
{
    this->phase_number = 0;
}

BossBattle::BossBattle(Entity& primeiro ) : Battle()
{
    this->setPrimeiro( primeiro );
    this->phase_number = 0;
}

BossBattle::BossBattle(const BossBattle& other)
{
    this->primeiro_ptr = other.primeiro_ptr;
    this->phase_number = other.phase_number;
    // Receber vetores de fases
    
}

BossBattle::~BossBattle()
{
    std::cout << "Destrutor do BossBattle\n" << std::endl;
}

/**
 * TODO: Verificar se é Enemy - Player ou Player - Enemy ou Enemy - Enemy
*/
bool BossBattle::begin_battle()
{
    size_t chosen_attack;

    // Verifica se é Player ou Enemy
    Player* player_ptr  = dynamic_cast<Player*> (this->primeiro_ptr);

    for (auto& phase : this->boss_phases)
    {
        this->segundo_ptr = phase;
        Enemy*  enemy_ptr   = dynamic_cast<Enemy*>  (this->segundo_ptr);
        
        while ( player_ptr->getHealth() > 0
                && enemy_ptr->getHealth() > 0 )
        {
            system("clear");
            std::cout << "==========================\n";
            std::cout << " | " << player_ptr->getName() << "\t|\t * " << enemy_ptr->getName() << " * \t|\n";
            std::cout << " | " << player_ptr->getHealth() << "\t\t|\t" << enemy_ptr->getHealth() << "\t|\n";
            std::cout << "==========================\n";
            std::cout << "Escolha seu ataque!\n";
            std::cout << "==========================\n";
            for ( size_t i = 0; i < player_ptr->getAttacks().size(); ++i)
            {
                std::cout << "( " << i << " ) - " << *player_ptr->getAttacks().at(i) << "\n"; 
            }
            std::cout << "Escolha: ";
            std::cin >> chosen_attack;

            this->planTurn(
                *player_ptr->getAttacks().at( chosen_attack ),  *enemy_ptr->chooseAttack()
            );
            system("clear");
            this->executeTurn();
            std::cin >> chosen_attack;
        }

        system("clear");
        if (this->phase_number != this->boss_phases.size() - 1)
        {
            std::cout << "O cavaleiro negro se debate, mas seu coração é mais forte!\nEle não está morto, ainda.\nAsas começam a sair da sua armadura!\n";
            std::cout << "Ele está mais forte!\n";
            std::cin >> chosen_attack;
            this->phase_number++;
        }

        if ( player_ptr->getHealth() <= 0 )
            return false;
    }

    if ( player_ptr->getHealth() > 0 )
        return true;
    return false;
}

void BossBattle::add_phase( Enemy& phase )
{
    // std::cout << phase << std::endl;
    Enemy* new_phase = new Enemy( phase );
    this->boss_phases.push_back( new_phase );
}

void BossBattle::toNextPhase()
{

}


ostream &operator<<(ostream& output, const BossBattle& battle)
{
    output << battle.primeiro_ptr->getName() << " VS. * " << battle.segundo_ptr->getName() << " * \n";
    output << battle.primeiro_ptr->getHealth() << " | " << battle.segundo_ptr->getHealth() << "\n";
    output << "Turno: " << battle.turno << "\n";
    return output;
}

int operator!(const BossBattle& battle)
{
    if ( battle.primeiro_ptr == nullptr )
        return false;
    if ( battle.segundo_ptr == nullptr )
        return false;
    return true;
}

const BossBattle& BossBattle::operator=(const BossBattle& other)
{
    if (this != &other)
    {
        Enemy* enemy_ptr;
        Player* player_ptr;
        // Is primeiro_ptr a player or an enemy?
        player_ptr = dynamic_cast<Player*> (other.primeiro_ptr);
        if (player_ptr == nullptr)
        {
            enemy_ptr = dynamic_cast<Enemy*> ( other.primeiro_ptr );
            if (enemy_ptr != nullptr)
                this->primeiro_ptr = new Enemy( *enemy_ptr );
        }
        else
        {
            this->primeiro_ptr = new Player( *player_ptr );
        }
        
        // Is segundo_ptr a player?
        player_ptr = dynamic_cast<Player*> (other.segundo_ptr);
        if (player_ptr == nullptr)
        {
            enemy_ptr = dynamic_cast<Enemy*> (other.segundo_ptr);
            if (enemy_ptr != nullptr)
                this->segundo_ptr = new Enemy( *enemy_ptr );
        }
        else
        {
            this->segundo_ptr = new Player( *player_ptr );
        }
        this->turno = other.turno;
    }
    return *this;
}

int BossBattle::operator==( const BossBattle& other )
{
    return ( *this->primeiro_ptr == *other.primeiro_ptr 
            && *this->segundo_ptr == *other.segundo_ptr );
}

int BossBattle::operator!=( const BossBattle& other )
{
    return !( *this == other );
}