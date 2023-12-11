#include "LongRangeWeapon.h"

LongRangeWeapon::LongRangeWeapon() : Weapon( )
{
    this->accuracy = 1.0f;
}

LongRangeWeapon::LongRangeWeapon(string name, double damage, double accuracy)
: Weapon( name, damage )
{
    this->setAccuracy( accuracy );
}

LongRangeWeapon::LongRangeWeapon(const LongRangeWeapon& right)
: Weapon( right )
{
    this->accuracy = right.accuracy;  
}

LongRangeWeapon::~LongRangeWeapon()
{
}

/* Usa arma e dá dano no inimigo. Decrementando durabilidade. */
void LongRangeWeapon::use( Entity& ent )
{
    this->inflict_damage( ent );
    this->durability--;
}

/* Tenta acertar em uma determinada parte do corpo */
void LongRangeWeapon::inflict_damage( Entity& ent )
{
    this->has_hit = verifyHit(ent);
    if (this->has_hit)
        ent.receiveDamage(
            this->damage * ent.getBodyParts().at(this->body_part_index).damageModifier
        );
}

/* Verifica se ocorre um acerto */
bool LongRangeWeapon::verifyHit(Entity& ent)
{
    vector<BodyPart>& ent_parts = ent.getBodyParts();
    int chance = rand() % 100;
    if (chance < this->accuracy * 1.5f / ent_parts.at(this->body_part_index).damageModifier )
        return true;
    return false;
}

/* Mira em algum lugar do inimigo */
void LongRangeWeapon::aim_at(Entity& ent, size_t index)
{
    if ( index > ent.getBodyParts().size() || index > 0 )
    {
        this->body_part_index = index;
        return;
    }
    this->body_part_index = 0;
    return;
}

void LongRangeWeapon::setAccuracy(double value)
{
    if (value < 0.0f)
    {
        this->accuracy = 0.0f;
        return;
    }
    this->accuracy = value;
}


#pragma region OperatorOverloads

const LongRangeWeapon &LongRangeWeapon::operator=(const LongRangeWeapon& right)
{
    if (&right != this)
    {
        this->name = right.name;
        this->description = right.description;
        this->damage = right.damage;
        this->durability = right.durability;
        this->accuracy = right.accuracy;
    }
    return *this;   
}

int LongRangeWeapon::operator==(const LongRangeWeapon& right)
{
    if (this->name == right.name)
        return 1;
    return 0;
}

int LongRangeWeapon::operator!=(const LongRangeWeapon& right)
{
    return !(*this == right);
}

ostream &operator<<(ostream& output, const LongRangeWeapon& weapon)
{
    output << "\n======   LONG RANGE WEAPON   =====\n";
    output << "* " << weapon.name << "\n";
    output << "* Damage: \t" << weapon.damage << "\n";
    output << "* Durability: \t" << weapon.durability << "\n";
    output << "* Accuracy: \t" << weapon.accuracy << "\n";
    return output;  
}

int operator!(const LongRangeWeapon& weapon)
{
    return ( weapon.name.empty() || weapon.name == weapon.DEFAULT_WEAPON_NAME );
}

#pragma endregion