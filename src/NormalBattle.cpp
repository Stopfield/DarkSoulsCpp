#include "NormalBattle.h"

NormalBattle::NormalBattle() : Battle()
{
}

NormalBattle::NormalBattle(Entity& primeiro, Entity& segundo) : Battle( primeiro, segundo )
{

}

NormalBattle::NormalBattle(const NormalBattle& battle) : Battle( battle )
{

}

NormalBattle::~NormalBattle()
{
    
}

/**
 * TODO: Verificar se é Enemy - Player ou Player - Enemy ou Enemy - Enemy
*/
bool NormalBattle::begin_battle()
{
    // Verifica se é Player ou Enemy
    Player* player_ptr  = dynamic_cast<Player*> (this->primeiro_ptr);
    Enemy*  enemy_ptr   = dynamic_cast<Enemy*>  (this->segundo_ptr);

    Attack* primeiro_atk_ptr = nullptr;
    Attack* segundo_atk_ptr = nullptr;

    size_t primeiro_aim_index = 0;
    size_t segundo_aim_index = 0;
    
    size_t chosen_attack;

    while ( player_ptr->getHealth() > 0
            && enemy_ptr->getHealth() > 0 )
    {
        system("clear");
        std::cout << "==========================\n";
        std::cout << " | " << player_ptr->getName() << "\t|\t" << enemy_ptr->getName() << "\t|\n";
        std::cout << " | " << player_ptr->getHealth() << "\t\t|\t" << enemy_ptr->getHealth() << "\t|\n";
        std::cout << "==========================\n";

        if (player_ptr->isLongRangeEquipped() == true)
        {
            std::cout << "Escolha onde atacar!\n";
            std::cout << "==========================\n";

            for (size_t i = 0; i < enemy_ptr->getBodyParts().size(); ++i)
                std::cout << "( " << i << ") - " << enemy_ptr->getBodyParts().at(i).partDescription << "\n";

            std::cout << "Escolha: ";
            std::cin >> chosen_attack;

            primeiro_atk_ptr = nullptr;
            primeiro_aim_index = chosen_attack;
        }
        else
        {
            std::cout << "Escolha seu ataque!\n";
            std::cout << "==========================\n";
            for ( size_t i = 0; i < player_ptr->getAttacks().size(); ++i)
                std::cout << "( " << i << " ) - " << *player_ptr->getAttacks().at(i) << "\n"; 
            std::cout << "Escolha: ";
            std::cin >> chosen_attack;
            primeiro_atk_ptr = player_ptr->getAttacks().at( chosen_attack );
        }

        

        this->planTurn(
            primeiro_atk_ptr, chosen_attack,
            enemy_ptr->chooseAttack(), player_ptr->chooseRandBodyPartIndex()
        );
        system("clear");
        this->executeTurn();
        std::cin >> chosen_attack;
    }

    if ( player_ptr->getHealth() > 0 )
    {
        system("clear");
        std::cout << "VOCÊ GANHOU!\n";
        std::cin >> chosen_attack;
        return true;
    }
    system("clear");
    std::cout << "GAME OVER\n";
    std::cin >> chosen_attack;
    return false;
}

const NormalBattle& NormalBattle::operator=(const NormalBattle& other)
{
    if (this != &other)
    {
        Enemy*  enemy_ptr   = nullptr;
        Player* player_ptr  = nullptr;

        /* Verifica se o primeiro_ptr é Player ou Enemy */
        player_ptr = dynamic_cast<Player*> (other.primeiro_ptr);
        if (player_ptr != nullptr)
        {
            this->primeiro_ptr = new Player( *player_ptr );
            player_ptr = nullptr;
        }
        else
        {
            enemy_ptr = dynamic_cast<Enemy*> ( other.primeiro_ptr );
            if (enemy_ptr != nullptr)
                this->primeiro_ptr = new Enemy( *enemy_ptr );
        }
        
        /* Verifica se o segundo_ptr é Player ou Enemy */
        player_ptr = dynamic_cast<Player*> (other.segundo_ptr);
        if (player_ptr != nullptr)
        {
            this->segundo_ptr = new Player( *player_ptr );
            player_ptr = nullptr;
        }
        else
        {
            enemy_ptr = dynamic_cast<Enemy*> (other.segundo_ptr);
            if (enemy_ptr != nullptr)
                this->segundo_ptr = new Enemy( *enemy_ptr );
        }
        
        this->turno = other.turno;
    }
    return *this;
}

ostream &operator<<(ostream& output, const NormalBattle& battle)
{
    output << battle.primeiro_ptr->getName() << " VS. " << battle.segundo_ptr->getName() << "\n";
    output << battle.primeiro_ptr->getHealth() << " | " << battle.segundo_ptr->getHealth() << "\n";
    output << "Turno: " << battle.turno << "\n";
    return output;
}

int operator!(const NormalBattle& battle)
{
    if ( battle.primeiro_ptr == nullptr )
        return false;
    if ( battle.segundo_ptr == nullptr )
        return false;
    return true;
}

int NormalBattle::operator==( const NormalBattle& other )
{
    return (
            this->areEntitiesEqual( *this->primeiro_ptr, *other.primeiro_ptr )
        &&  this->areEntitiesEqual( *this->segundo_ptr,  *other.segundo_ptr  )
    );
}

int NormalBattle::operator!=( const NormalBattle& other )
{
    return !( *this == other );
}
