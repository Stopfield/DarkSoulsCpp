#include "Battle.h"

Battle::Battle()
{
    this->primeiro_ptr = 0;
    this->segundo_ptr = 0;
    this->turno = 0;
}

Battle::Battle(Entity& primeiro, Entity& segundo)
{
    this->primeiro_ptr = &primeiro;
    this->segundo_ptr = &segundo;
    this->turno = 0;
}

Battle::Battle(const Battle& other)
{
    this->primeiro_ptr = other.primeiro_ptr;
    this->segundo_ptr = other.segundo_ptr;
    
    this->turno = other.turno;
}

Battle::~Battle()
{
    // Não deleta nenhum dos ponteiros. Eles não são criados aqui.
    // A futura classe Game vai lidar com eles
    // std::cout << "Destrutor do Battle\n" << std::endl;
}

bool areEntitiesEqual(Entity& primeiro, Entity& segundo)
{
    Player* first_player_ptr = nullptr;
    Player* second_player_ptr = nullptr;

    Enemy* first_enemy_ptr = nullptr;
    Enemy* second_enemy_ptr = nullptr;

    first_player_ptr    = dynamic_cast<Player*> (&primeiro);
    second_player_ptr   = dynamic_cast<Player*> (&segundo);

    if (first_player_ptr != nullptr && second_player_ptr != nullptr)
        return ( *first_player_ptr == *second_player_ptr );

    first_enemy_ptr = dynamic_cast<Enemy*> (&primeiro);
    second_enemy_ptr = dynamic_cast<Enemy*> (&segundo);

    if (first_enemy_ptr != nullptr && second_enemy_ptr != nullptr)
        return ( *first_enemy_ptr == *second_enemy_ptr );

    return false;
}


/* Se um ataque é nulo, a entidade escolhe (WIP) */
void Battle::planTurn(
    const Attack* primeiro_melee,   size_t primeiro_aim_index,
    const Attack* segundo_melee,    size_t segundo_aim_index
)
{
    if (primeiro_melee == nullptr)
        this->attack_primeiro_ptr = nullptr;
    else
        this->attack_primeiro_ptr = primeiro_melee;

    if (segundo_melee == nullptr)
        this->attack_segundo_ptr = nullptr;
    else
        this->attack_segundo_ptr = segundo_melee;

    this->primeiro_aim_index = primeiro_aim_index;
    this->segundo_aim_index = segundo_aim_index;
}

/**
 * Executa um turno, executando o ataque de cada entidade.
*/
void Battle::executeTurn(  )
{
    this->primeiro_ptr->attack( *this->segundo_ptr, this->attack_primeiro_ptr, primeiro_aim_index);
    this->segundo_ptr->attack(  *this->primeiro_ptr, this->attack_segundo_ptr, segundo_aim_index);

    this->attack_primeiro_ptr = nullptr;
    this->attack_segundo_ptr = nullptr;

    primeiro_aim_index = 0;
    segundo_aim_index = 0;

}

void Battle::setPrimeiro(Entity& primeiro) 
{
    if ( this->primeiro_ptr == nullptr )
    {
        this->primeiro_ptr = &primeiro;
        return;
    }
    if ( areEntitiesEqual( *this->primeiro_ptr, primeiro ) )
        this->primeiro_ptr = &primeiro;
}

void Battle::setSegundo(Entity& segundo)
{
    if ( this->segundo_ptr == nullptr )
    {
        this->segundo_ptr = &segundo;
        return;
    }
    if ( areEntitiesEqual( *this->segundo_ptr, segundo ) )
        this->segundo_ptr = &segundo;
}

void Battle::setTurno(int new_turno)
{
    if (new_turno < 0 && new_turno > this->turno)
    {
        this->turno = new_turno;
        return;
    }
    this->turno = new_turno;
}

const Battle &Battle::operator=(const Battle& other)
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

int Battle::operator== (const Battle& right )
{
    return ( areEntitiesEqual(*this->primeiro_ptr, *right.primeiro_ptr)
            && areEntitiesEqual(*this->segundo_ptr, *right.segundo_ptr) );
}

int Battle::operator!= (const Battle& right )
{
    return !( *this == right );
}

ostream &operator<<(ostream& output, const Battle& battle)
{
    output << battle.primeiro_ptr->getName() << " VS. " << battle.segundo_ptr->getName() << "\n";
    output << battle.primeiro_ptr->getHealth() << " | " << battle.segundo_ptr->getHealth() << "\n";
    output << "Turno: " << battle.turno << "\n";
    return output;
}