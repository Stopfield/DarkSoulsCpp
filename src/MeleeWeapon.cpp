#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon()
: Weapon()
{
    this->blunt_damage = 2.5f;
    this->chosen_attack_damage_modifier = 1.0f;
}

MeleeWeapon::MeleeWeapon(string name, double damage, double blunt_damage)
: Weapon(name, damage)
{
    this->setBluntDamage( blunt_damage );
}

MeleeWeapon::MeleeWeapon(const MeleeWeapon& other)
: Weapon( other )
{
    this->blunt_damage = other.blunt_damage;
}

MeleeWeapon::~MeleeWeapon()
{
}

void MeleeWeapon::use(Entity& ent)
{
    this->inflict_damage( ent );
    this->durability--;
}

void MeleeWeapon::inflict_damage(Entity& ent)
{
    ent.receiveDamage(
        (this->damage + this->blunt_damage) * this->chosen_attack_damage_modifier
    );
}

/* Escolhe um ataque e o guarda */
void MeleeWeapon::choose_attack(const Attack& choice)
{
    this->chosen_attack_damage_modifier = choice.getDamageModifier();
}

#pragma region OperatorOverloads

void MeleeWeapon::setBluntDamage( double dmg )
{
    if (dmg < 0.0f)
    {
        this->blunt_damage = 0.0f;
        return;
    }
    this->blunt_damage = dmg;
}

const MeleeWeapon &MeleeWeapon::operator=(const MeleeWeapon &right)
{
    if (&right != this)
    {
        Weapon::operator=(right);
        this->blunt_damage = right.blunt_damage;
    }
    return *this; 
}

int MeleeWeapon::operator==(const MeleeWeapon& right)
{
    if ( Weapon::operator==(right) && this->blunt_damage == right.blunt_damage)
        return 1;
    return 0;
}

int MeleeWeapon::operator!=(const MeleeWeapon& right)
{
    return !(*this == right);
}

ostream &operator<<(ostream& output, const MeleeWeapon& weapon)
{
    output << "\n======   MELEE WEAPON   =====\n";
    output << "* "                  << weapon.name          << "\n";
    output << "* Damage: \t"        << weapon.damage        << "\n";
    output << "* Durability: \t"    << weapon.durability    << "\n";
    output << "* Blunt Damage: \t"  << weapon.blunt_damage  << "\n";
    return output; 
}

int operator!(const MeleeWeapon& weapon)
{
    return ( weapon.name.empty() || weapon.name == weapon.DEFAULT_WEAPON_NAME );
}

#pragma endregion