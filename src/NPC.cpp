#include "NPC.h"

NPC::NPC() : GameObject()
{
    this->monologue_counter = 0;
}

NPC::NPC( vector<string>& monologues, Vector2D pos, char representation )
: GameObject( pos, representation )
{
    this->setMonologues( monologues );
    this->monologue_counter = 0;
}

NPC::NPC(const NPC& other) : GameObject( other )
{
    this->copyMonologue( other.getMonologues() );
    this->monologue_counter = other.monologue_counter;
}

NPC::~NPC()
{
}

void NPC::interact()
{
    this->talk();
    monologue_counter++;
}

/**
 * NPC fala alguma coisa
*/
void NPC::talk()
{
    if (monologue_counter >= this->monologues.size())
        this->monologue_counter = 0;
    std::cout << "\"" << this->monologues.at(monologue_counter) << "\"\n";
}

/**
 * Adiciona um novo monólogo ao vetor.
*/
void NPC::add_to_monologue(string new_monologue)
{
    if (new_monologue.size() < 1024)
        this->monologues.push_back( new_monologue );
}

/**
 * Copia outro monólogo
*/
void NPC::copyMonologue( const vector<string>& other_monologue )
{
    if (!this->monologues.empty())
    {
        this->monologues.clear();
        for (auto& speech : other_monologue )
            if (speech.size() < 1024)
                this->monologues.push_back(speech);
    }
}

bool NPC::areMonologuesEqual(
    const vector<string>& first_monologue,
    const vector<string>& second_monologue
)
{
    for (const auto& first_string : first_monologue)
        for (const auto& second_string : second_monologue)
            if (first_string != second_string)
                return false;
    return true;
}

void NPC::setMonologues( const vector<string>& new_monologue )
{
    if (!this->monologues.empty())
    {
        this->monologues.clear();
        this->copyMonologue( new_monologue );
        return;
    }
    this->copyMonologue( new_monologue );
}

#pragma region OperatorOverloads

const NPC &NPC::operator=(const NPC& other)
{
    if (this != &other)
    {
        this->representation = other.representation;
        if (other.position != nullptr)
            this->position = new Vector2D { other.position->x, other.position->y };
        else
            this->position = nullptr;
        this->copyMonologue( other.getMonologues() );
        this->monologue_counter = other.monologue_counter;
    }
    return *this;
}

int NPC::operator==(const NPC& right)
{
    return (this->areMonologuesEqual( this->monologues, right.monologues ));
}

int NPC::operator!=(const NPC& right)
{
    return !( *this == right );
}

ostream &operator<<(ostream& output, const NPC& npc)
{
    output << "NPC " << npc.getRepresentation() << "\n";
    output << "Falas:\n";
    for (auto falas : npc.getMonologues())
        std::cout << "* \"" << falas << "\"\n"; 
    return output;
}

int operator!(const NPC& npc)
{
    return (npc.monologues.empty());
}

#pragma endregion