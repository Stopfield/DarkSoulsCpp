#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <random>
#include <ctime>

using std::string;
using std::vector;
using std::map;

#include "Weapon.h"
#include "Item.h"
#include "Consumable.h"
#include "Attack.h"
#include "GameObject.h"
#include "EssentialStructs.h"

/* Define as partes default de vector< BodyPart > */
#define DEFAULT_ENTITY_BODY_PARTS { \
    { "HEAD" , 2.0f }, \
    { "FRONT", 1.0f }, \
    { "BACK", 1.5f  } }

#include "EntityDetails.h"

/**
 * Classe que abstrai tudo que se move e pode batalhar!
*/
class Entity : public GameObject
{
    friend ostream& operator<<  ( ostream&, const Entity& );
    friend int      operator!   ( const Entity& );
public:
    Entity                  ( );
    Entity                  (   string,
                                double = 100.0f, 
                                double = 100.0f,
                                double = 50.0f,
                                double = 25.0f,
                                Vector2D = { 0 },
                                vector< BodyPart > = DEFAULT_ENTITY_BODY_PARTS );
    Entity                  ( const Entity& );
    virtual ~Entity         ( );


    void    move                        ( Direction );
    void    equipWeapon                 ( const Weapon& );
    void    attack                      ( Entity&, const Attack& );
    void    receiveDamage               ( double );
    double  calculateDamageModifier     (  );
    void    heal                        ( double );
    void    guard                       ( );
    void    grabItem                    ( Item& );
    void    useItem                     ( Item& );
    void    useItem                     ( size_t );

    void showInventory                  ( ) const;
    const BodyPart& chooseRandBodyPart  ( ) const;

    // void battle     ( Entity& );

    inline bool isUnarmed()     const { return (equiped_weapon_ptr == 0) ? true : false; }
    inline bool isGuarding()    const { return this->guarding; }

    inline string   getName()           const   { return this->name;        }
    inline double   getHealth()         const   { return this->health;      }
    inline double   getStrength()       const   { return this->strength;    }
    inline double   getStamina()        const   { return this->stamina;     }
    inline double   getDexterity()      const   { return this->dexterity;   }

    inline const vector<BodyPart>&          getBodyParts() const { return this->bodyParts; }
    inline const vector<InventoryItem*>&    getInventory() const { return this->inventory; }
    
    inline const Weapon& getEquipedWeapon() const { return *this->equiped_weapon_ptr; }

    void setName        ( string );
    void setHealth      ( double );
    void setMaxHealth   ( double );
    void setStrength    ( double );
    void setStamina     ( double );
    void setDexterity   ( double );
    void setBodyParts   ( vector< BodyPart >& );

    const Entity&   operator=   ( const Entity& );
    int             operator==  ( const Entity& );
    int             operator!=  ( const Entity& );

private:

    static bool isBodyPartValid( BodyPart& );

    void copyInventory  ( const vector< InventoryItem* >& );
    void copyWeapon     ( const Weapon* const );

    const static size_t NAME_MAX_SIZE;             // Máximo de um item que pode ser carregado
    const static size_t ITEM_MAX_STACK;             // Máximo de um item que pode ser carregado
    const static size_t BODY_PART_DESC_MAX_SIZE;    // Tamanho máximo da string do BodyPart
    const static string DEFAULT_NAME;               // Nome padrão de entidades não declaradas

    string name;        // Nome que identifica identidade
    double maxHealth;   // Vida máxima permitida pelo nível do personagem
    double health;      // Vida atual da entidade
    double stamina;     // Permite o ataque
    double strength;    // Impacta no modificador de dano
    double dexterity;   // O quão rápido a Stamina sobe
    bool guarding;
    vector< BodyPart > bodyParts;

    Weapon* equiped_weapon_ptr = 0;               // Arma equipada pela entidade
    vector< InventoryItem* > inventory;     // Inventário da entidade
};

#endif // ENTITY_H