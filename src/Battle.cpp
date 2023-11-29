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
    if (other.primeiro_ptr != nullptr)
        this->primeiro_ptr = new Entity( *other.primeiro_ptr );

    if (other.segundo_ptr != nullptr)
        this->segundo_ptr = new Entity( *other.segundo_ptr );
    
    this->turno = other.turno;
}

Battle::~Battle()
{
    // Não deleta nenhum dos ponteiros. Eles não são criados aqui.
    // A futura classe Game vai lidar com eles
    std::cout << "Destrutor do Battle\n" << std::endl;
}

/* Se um ataque é nulo, a entidade escolhe (WIP) */
void Battle::planTurn( const Attack& primeiro_attack, const Attack& segundo_attack )
{
    this->attack_primeiro_ptr = &primeiro_attack;
    this->attack_segundo_ptr = &segundo_attack;
}

void Battle::executeTurn()
{
    if (this->attack_primeiro_ptr == nullptr || this->attack_segundo_ptr == nullptr)
        return;
    if (this->primeiro_ptr == nullptr || this->segundo_ptr == nullptr)
        return;
    
    this->primeiro_ptr->attack  ( *this->segundo_ptr,   *this->attack_primeiro_ptr  );
    this->segundo_ptr->attack   ( *this->primeiro_ptr,  *this->attack_segundo_ptr   );

    this->attack_primeiro_ptr = nullptr;
    this->attack_segundo_ptr = nullptr;
}

void Battle::setPrimeiro(Entity& primeiro) 
{
    if ( this->primeiro_ptr == nullptr )
    {
        this->primeiro_ptr = &primeiro;
        return;
    }
    if (primeiro != *this->primeiro_ptr)
    {
        this->primeiro_ptr = &primeiro;
        return;
    }
}

void Battle::setSegundo(Entity& segundo)
{
    if ( this->segundo_ptr == nullptr )
    {
        this->segundo_ptr = &segundo;
        return;
    }
    if (segundo != *this->segundo_ptr)
    {
        this->segundo_ptr = &segundo;
        return;
    }
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