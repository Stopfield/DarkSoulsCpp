/*
Expandir a hierarquia da atividade anterior: três hierarquias de três níveis.
    Sendo que em uma das hierarquias há dois níveis de classes 
    abstratas. Uma das classes abstratas precisa ter pelo menos dois métodos virtuais 
    puros. 

    Para cada lado da hierarquia criar ao menos duas classes concretas. 
        Pelo menos duas classes concretas herdando de uma dessas outras classes 
        concretas. 
        Cada classe, além dos métodos herdados, precisa ter pelo menos um método que tenha 
        alguma funcionalidade, que não seja set e get. 

Para cada classe do seu projeto criar pelo menos três constructores, sendo um o 
constructor de cópia. 
 
Em uma das hierarquias deve haver alocação de memória usando um vector< ptr * >, 
onde ptr é  um ponteiro de uma de suas classes criadas que tem relação de composição. 
 
Ter um atributo static e um atributo const static.  

Fazer a sobrecarga para cada classe dos operadores =, ==, ≠, ! e << (friend) para as 
classes concretas. Usar sempre que possível o static_cast para reaproveitamento de código - mas não é possível usar
para classes abstract.  
 
Criar um vector de ponteiros de uma das classes abstrata e  armazenar nele objetos 
de classes concretas. Usar dynamic_cast e typeid para fazer algo significativo com 
partes dessas classes concretas. 
 
Carregamento e salvamento de  arquivos: é necessário ter a funcionalidade de 
 1. leitura de arquivos para  configuração das suas classes e variáveis de status, 
 2. processamento das variáveis de status e 
 3. salvamento dessas variáveis. 
 
Todos os projetos devem ter um diagrama mostrando a hierarquia. 
Sem o diagrama e os dois videos, o trabalho não será avaliado.*/


//// Geral - parte para revisão
    //Diagrama UML    
    //Organização do código 

////Importante
//// Cada classe, além dos métodos herdados, precisa ter pelo menos um método que tenha 
//alguma funcionalidade, que não seja set e get.

//// Os .h

    /// O .h das classes bases

//Classe abstract base 1 - Item
#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>

using std::cout;
using std::string;
using std::ostream;

class Entity;

class Item
{
    friend ostream& operator<<  ( ostream&, const Item& );
    friend int      operator!   ( const Item& );
public:
    Item            ( );
    Item            ( string, string );
    Item            ( const Item& );
    virtual ~Item   ( );

    virtual void use( Entity& ) = 0;

    inline string getName()         const { return this->name;          }
    inline string getDescription()  const { return this->description;   }

    void setName            ( string );
    void setDescription     ( string );
    const Item&     operator=       ( const Item& );
    int             operator==      ( const Item& );
    int             operator!=      ( const Item& );

protected:
    const static u_int8_t   MAX_ITEM_STACK;
    const static size_t     MAX_NAME_SIZE;
    const static size_t     MAX_DESCRIPTION_SIZE;
    const static string     DEFAULT_ITEM_NAME;
    const static string     DEFAULT_DESCRIPTION;

    string name;
    string description;
};

#endif

//Classe abstract base 2 - GameObject
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <iostream>

using std::ostream;

#include "EssentialStructs.h"

/**
 * Essa classe administra qualquer objeto presente no jogo.
*/
class GameObject
{
    friend ostream& operator<<  ( ostream&, const GameObject& );
public:
    GameObject  (  );
    GameObject  ( Vector2D, char );
    GameObject  ( const GameObject& );
    virtual ~GameObject();

    virtual bool interact( GameObject& ) = 0;

    void setPosition            ( Vector2D );
    void setRepresentation      ( char );

    Vector2D getPosition()      const    { return this->position == 0 ? Vector2D { 0 } : *this->position;      };
    char getRepresentation()    const    { return this->representation; };

    const GameObject&   operator=   ( const GameObject& );
    int             operator==      ( const GameObject& );
    int             operator!=      ( const GameObject& );

protected:
    Vector2D* position = 0;
    char representation;
};

#endif

//Classe abstract base 3 - Battle
#ifndef BATTLE_H
#define BATTLE_H

#include <iostream>

#include "Entity.h"
#include "Attack.h"
#include "Player.h"
#include "Enemy.h"

using std::ostream;

class Battle
{
    friend ostream& operator<<  ( ostream&, const Battle& );
    friend bool areEntitiesEqual (Entity&, Entity&);

public:
    Battle(  );
    Battle( Entity&, Entity& );
    Battle( const Battle& );
    virtual ~Battle(  );

    virtual bool begin_battle (  ) = 0;

    void planTurn       ( const Attack*, size_t, const Attack*, size_t );
    void executeTurn    (  );

    void setPrimeiro    ( Entity& );
    void setSegundo     ( Entity& );
    void setTurno       ( int );

    int     getTurno()      const { return this->turno;         }
    Entity* getPrimeiro()   const { return this->primeiro_ptr;  }
    Entity* getSegundo()    const { return this->segundo_ptr;   }

    const Battle& operator=( const Battle& );
    int             operator==      ( const Battle& );
    int             operator!=      ( const Battle& );
protected:

    Entity* primeiro_ptr    = 0;
    Entity* segundo_ptr     = 0;

    const Attack* attack_primeiro_ptr = 0;
    const Attack* attack_segundo_ptr  = 0;

    size_t primeiro_aim_index = 0;
    size_t segundo_aim_index = 0;
    
    int turno;
};

#endif // BATTLE_H

/// O .h da hierarquia 1 (abstract base 1)
#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::ostream;

#include "Item.h"
class Entity;   /* Não precisa importar Entity, só precisa saber que tem */

class Weapon : public Item
{
public:
    Weapon();
    Weapon( string, double, int = 100 );
    Weapon( const Weapon& );
    virtual ~Weapon();

    virtual void use            ( Entity& ) = 0;
    virtual void inflict_damage ( Entity& ) = 0;

    void    increaseDurability  ( double );
    void    decreaseDurability  ( int );

    int     getDurability() const { return this->durability;    }
    double  getDamage()     const { return this->damage;        }

    void setDurability  ( int );
    void setDamage      ( double );

protected:
    const static string DEFAULT_WEAPON_NAME;

    double  damage;
    int     durability;
};  

#endif // WEAPON_H

//Classe Abstract 1 que herda da base abstract
//Deve ter seu próprio método virtual puro
#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::ostream;

#include "Item.h"
class Entity;   /* Não precisa importar Entity, só precisa saber que tem */

class Weapon : public Item
{
public:
    Weapon();
    Weapon( string, double, int = 100 );
    Weapon( const Weapon& );
    virtual ~Weapon();

    virtual void use            ( Entity& ) = 0;
    virtual void inflict_damage ( Entity& ) = 0;

    void    increaseDurability  ( double );
    void    decreaseDurability  ( int );

    int     getDurability() const { return this->durability;    }
    double  getDamage()     const { return this->damage;        }

    void setDurability  ( int );
    void setDamage      ( double );

protected:
    const static string DEFAULT_WEAPON_NAME;

    double  damage;
    int     durability;
};  

#endif // WEAPON_H

// Classe 2 - concrete
#ifndef LONG_RANGE_WEAPON_H
#define LONG_RANGE_WEAPON_H

#include "Weapon.h"
#include "Entity.h"

class LongRangeWeapon : public Weapon
{
    friend ostream& operator<<  ( ostream&, const LongRangeWeapon& );
    friend int      operator!   ( const LongRangeWeapon& );
public:
    LongRangeWeapon             (  );
    LongRangeWeapon             ( string, double, double );
    LongRangeWeapon             ( const LongRangeWeapon& );
    virtual ~LongRangeWeapon    (  );

    void use            ( Entity& ) override;
    void inflict_damage ( Entity& ) override;
    bool verifyHit      ( Entity& );
    void aim_at         ( Entity&, size_t );

    bool    isTargetHit         (  ) { return this->has_hit;            }
    size_t  get_body_part_index (  ) { return this->body_part_index;    }

    inline double getAccuracy() { return this->accuracy; }
    void setAccuracy( double );

    const LongRangeWeapon&  operator=   ( const LongRangeWeapon& );
    int                     operator==  ( const LongRangeWeapon& );
    int                     operator!=  ( const LongRangeWeapon& );

private:
    double accuracy;
    bool has_hit;   /* Checa na batalha pra ver se acertou! */
    size_t body_part_index = 0;
};

#endif

// Clase 3 - Concrete
#ifndef MELEE_WEAPON_H
#define MELEE_WEAPON_H

#include "Weapon.h"
#include "Entity.h"
#include "Attack.h"


class MeleeWeapon : public Weapon
{
    friend ostream& operator<<  ( ostream&, const MeleeWeapon& );
    friend int      operator!   ( const MeleeWeapon& );
public:
    MeleeWeapon             (  );
    MeleeWeapon             ( string, double, double );
    MeleeWeapon             ( const MeleeWeapon& );
    virtual ~MeleeWeapon    (  );

    void use            ( Entity& ) override;
    void inflict_damage ( Entity& ) override;
    void choose_attack  ( const Attack& );

    double  getBluntDamage() const { return this->blunt_damage; }
    void    setBluntDamage( double );

    const MeleeWeapon&  operator=   ( const MeleeWeapon& );
    int                 operator==  ( const MeleeWeapon& );
    int                 operator!=  ( const MeleeWeapon& );

private:
    double blunt_damage;
    double chosen_attack_damage_modifier = 1.0f;
};

#endif  // MELEE_WEAPON_H

// Classe 4 - Concrete
#ifndef ARMOR_H
#define ARMOR_H

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::ostream;

#include "Item.h"

class Armor : public Item
{
    friend ostream& operator<<  ( ostream&, const Armor& );
    friend int      operator!   (const Armor& );
public:
    Armor();
    Armor( double, double = 0.0, double = 1.0 );
    Armor( const Armor& );
    virtual ~Armor();

    void use( Entity& ) override;

    double getDamageReduction() const { return this->damage_reduction; }
    double getMinStrength()     const { return this->min_strength;     }
    double getWeight()          const { return this->weight;           }

    void setDamageReduction ( double );
    void setMinStrength     ( double );
    void setWeight          ( double );

    const Armor& operator=  ( const Armor& );
    int operator==          ( const Armor& );
    int operator!=          ( const Armor& );

protected:
    const static string DEFAULT_ARMOR_NAME;

    double  damage_reduction;
    double  min_strength;
    double  weight;
};  

#endif // ARMOR_H

// Classe 4 - Abstract
#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include "Item.h"

using std::ostream;

class Consumable : public Item
{
public:
    Consumable  (  );
    Consumable  ( string, string, double = 1.0f );
    Consumable  ( const Consumable& );
    virtual ~Consumable();

    virtual void use            ( Entity& ) = 0;
    virtual void inflict_effect ( Entity& ) = 0;

    double  getHealthFactor() const { return this->health_factor; }
    void    setHealthFactor( double );

protected:
    double health_factor;   // Ratio usado em operações - porcentagem!
};

#endif // CONSUMABLE_H

// Classe 5 - Concrete
#ifndef OFFENSIVE_CONSUMABLE_H
#define OFFENSIVE_CONSUMABLE_H

#include "Consumable.h"
#include "Entity.h"

using std::ostream;

class OffensiveConsumable : public Consumable
{
    friend ostream& operator<<  ( ostream&, const OffensiveConsumable& );
    friend int      operator!   ( const OffensiveConsumable& );
public:
    OffensiveConsumable  (  );
    OffensiveConsumable  ( string, string, double, double = 1.0f );
    OffensiveConsumable  ( const OffensiveConsumable& );
    virtual ~OffensiveConsumable();

    void use            ( Entity& ) override;
    void inflict_effect ( Entity& ) override;

    void    setDamageModifier   ( double );
    double  getDamageModifier   (  ) const { return this->damage; };

    const OffensiveConsumable&  operator=   ( const OffensiveConsumable& );
    int                         operator==  ( const OffensiveConsumable& );
    int                         operator!=  ( const OffensiveConsumable& );

protected:
    double damage;   // Ratio usado em operações 
};

#endif // OFFENSIVE_CONSUMABLE_H

// Classe 6 - concrete
#ifndef RESTORATIVE_CONSUMABLE_H
#define RESTORATIVE_CONSUMABLE_H

#include "Consumable.h"
#include "Entity.h"

using std::ostream;

class RestorativeConsumable : public Consumable
{
    friend ostream& operator<<  ( ostream&, const RestorativeConsumable& );
    friend int      operator!   ( const RestorativeConsumable& );
public:
    RestorativeConsumable  (  );
    RestorativeConsumable  ( string, string, double, double = 1.0f );
    RestorativeConsumable  ( const RestorativeConsumable& );
    virtual ~RestorativeConsumable();

    void use            ( Entity& ) override;
    void inflict_effect ( Entity& ) override;

    void    setRestorativeModifier   ( double );
    double  setRestorativeModifier   (  ) const { return this->restorative_modifier; };

    const RestorativeConsumable&    operator=   ( const RestorativeConsumable& );
    int                             operator==  ( const RestorativeConsumable& );
    int                             operator!=  ( const RestorativeConsumable& );

protected:
    double restorative_modifier;   // Ratio usado em operações 
};

#endif // RESTORATIVE_CONSUMABLE_H

/// O .h da hierarquia 2 (abstract base 2)
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <iostream>

using std::ostream;

#include "EssentialStructs.h"

/**
 * Essa classe administra qualquer objeto presente no jogo.
*/
class GameObject
{
public:

    GameObject  (  );
    GameObject  ( Vector2D, char );
    GameObject  ( const GameObject& );
    virtual ~GameObject();

    virtual void interact() = 0;

    void setPosition            ( Vector2D );
    void setRepresentation      ( char );

    Vector2D getPosition()      const    { return this->position == 0 ? Vector2D { 0 } : *this->position;      };
    char getRepresentation()    const    { return this->representation; };
protected:
    Vector2D* position = 0;
    char representation;
};

#endif

//Classe 1 (abstract or concrete)
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

#include "EntityDetails.h"
#include "Attack.h"
#include "GameObject.h"
#include "LongRangeWeapon.h"
#include "MeleeWeapon.h"
#include "Consumable.h"

/* Define as partes default de vector< BodyPart > */
#define DEFAULT_ENTITY_BODY_PARTS { \
    { "HEAD" , 2.0f }, \
    { "FRONT", 1.0f }, \
    { "BACK", 1.5f  } }

class Item;

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

    virtual void interact() = 0;

    void    move                        ( Direction );
    void    equipWeapon                 ( Weapon* );
    void    attack                      ( Entity&, const Attack *const, size_t = 0 );
    void    receiveDamage               ( double );
    double  calculateDamageModifier     (  );
    void    heal                        ( double );
    void    guard                       ( );
    void    grabItem                    ( Item& );
    void    useItemOn                   ( Entity&, Item& );
    void    useItemOn                   ( Entity&, size_t );

    void showInventory                  ( ) const;
    const BodyPart& chooseRandBodyPart  ( ) const;
    size_t chooseRandBodyPartIndex( ) const;


    // void battle     ( Entity& );

    inline bool isUnarmed()     const { return (equiped_weapon_ptr == 0) ? true : false; }
    inline bool isGuarding()    const { return this->guarding; }
    inline bool isLongRangeEquipped( )  { return this->isUsingRangedWeapon; }

    inline string   getName()               const   { return this->name;                }
    inline double   getMaxHealth()          const   { return this->maxHealth;           }
    inline double   getHealth()             const   { return this->health;              }
    inline double   getStrength()           const   { return this->strength;            }
    inline double   getStamina()            const   { return this->stamina;             }
    inline double   getDexterity()          const   { return this->dexterity;           }

    inline vector<BodyPart>&                getBodyParts() { return this->bodyParts; }
    inline const vector<InventoryItem*>&    getInventory() const { return *this->inventory_ptr; }
    
    inline const Weapon& getEquipedWeapon() const { return *this->equiped_weapon_ptr; }

    void setName        ( string );
    void setMaxHealth   ( double );
    void setHealth      ( double );
    void setStrength    ( double );
    void setStamina     ( double );
    void setDexterity   ( double );
    void setInventory   ( const vector< InventoryItem* >* const );
    void setBodyParts   ( vector< BodyPart > );

    const Entity&   operator=   ( const Entity& );
    int             operator==  ( const Entity& );
    int             operator!=  ( const Entity& );

protected:

    static bool isBodyPartValid( BodyPart& );

    void copyInventory      ( const vector< InventoryItem* >* const );
    void deleteInventory    (  );
    void copyWeapon         ( const Weapon* const );

    const static size_t NAME_MAX_SIZE;             // Máximo de um item que pode ser carregado
    const static size_t ITEM_MAX_STACK;             // Máximo de um item que pode ser carregado
    const static size_t BODY_PART_DESC_MAX_SIZE;    // Tamanho máximo da string do BodyPart
    const static string DEFAULT_NAME;               // Nome padrão de entidades não declaradas

    string  name;        // Nome que identifica identidade
    double  maxHealth;   // Vida máxima permitida pelo nível do personagem
    double  health;      // Vida atual da entidade
    double  stamina;     // Permite o ataque
    double  strength;    // Impacta no modificador de dano
    double  dexterity;   // O quão rápido a Stamina sobe
    bool    guarding;
    vector< BodyPart > bodyParts;
    bool isUsingRangedWeapon;

    Weapon* equiped_weapon_ptr = 0;                 // Arma equipada pela entidade
    vector< InventoryItem* >* inventory_ptr = 0;        // Inventário da entidade
};

#endif // ENTITY_H

//Classe 2 - Player
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

using std::string;
using std::cout;

#include "Entity.h"

class Player : public Entity
{
    friend ostream& operator<<  ( ostream&, const Player& );
    friend int      operator!   ( const Player& );
public:
    Player();
    Player( string,
            double = 100.0f,
            double = 100.0f,
            double = 50.0f,
            double = 25.0f,
            Vector2D = { 0 },
            vector< BodyPart > = DEFAULT_ENTITY_BODY_PARTS );
    Player( const Player& );
    virtual ~Player();

    void interact() override;

    // void receiveInput   ( );
    void addAttack      ( Attack& );
 
    inline static uint              getNumPlayers() { return Player::numPlayers;  };
    inline vector<Attack*>          getAttacks()    const { return this->attacks;       };

    const Player&   operator=   ( const Player& );
    int             operator==  ( const Player& );
    int             operator!=  ( const Player& );

private:
    void copyAttacks        ( const Player& );
    void deleteAttacks      (  );

    static unsigned int numPlayers;
    vector< Attack* >   attacks;        // É melhor um ponteiro de ataques ou só ataques?
};

#endif // PLAYER_H

// Classe 4 - Concrete
#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include <string>
#include <iostream>

using std::cout;
using std::string;
using std::ostream;

#include "GameObject.h" 
#include "Entity.h"

enum InteractionFlags {
    DAMAGE, HEAL, SHOW_MESSAGE
};

class Interactable : public GameObject
{
    friend ostream& operator<<  ( ostream&, const Interactable& );
    friend int      operator!   ( const Interactable& );
public:
    Interactable            (  );
    Interactable            ( char, char );
    Interactable            ( const Interactable& );
    virtual ~Interactable   (  );

    void interact   (  ) override;
    void do_something_to_entity( Entity&, InteractionFlags );
    void changeFlag( InteractionFlags );
    
    inline char getRepresentation()     const { return this->actual_representation;    }
    inline char getBefore()     const { return this->before_interaction;    }
    inline char getAfter()      const { return this->after_interaction;     }

    void setBefore          ( char );
    void setAfter           ( char );

    const Interactable& operator=       ( const Interactable& );
    int                 operator==      ( const Interactable& );
    int                 operator!=      ( const Interactable& );

protected:
    char actual_representation;
    char before_interaction;
    char after_interaction;

    double health_factor;
    string message;

    InteractionFlags current_flag;
    Entity* entity_to_afect = nullptr;
};

#endif // INTERACTABLE_H

// Classe 6 - Concrete
#ifndef NPC_H
#define NPC_H

#include <vector>
#include <string>

using std::vector;
using std::string;
using std::ostream;

#include "GameObject.h"

class NPC : public GameObject
{
    friend ostream& operator<<  ( ostream&, const NPC& );
    friend int      operator!   ( const NPC& );
public:
    NPC( );
    NPC( vector<string>&, Vector2D, char );
    NPC( const NPC& );
    virtual ~NPC();

    void interact() override;
    void talk();
    void add_to_monologue( string );

    void setMonologues( const vector<string>& );
    const vector<string>& getMonologues() const { return this->monologues; }
    
    const NPC&  operator=       ( const NPC& );
    int         operator==      ( const NPC& );
    int         operator!=      ( const NPC& );

private:
    void copyMonologue      ( const vector<string>& );
    bool areMonologuesEqual ( const vector<string>&, const vector<string>& );

    vector<string> monologues;
    int monologue_counter;
};

#endif

/// O .h da hierarquia 3 (abstract base 3)
#ifndef BATTLE_H
#define BATTLE_H

#include "Entity.h"
#include "Player.h"
#include "Enemy.h"

class Battle
{
public:
    Battle(  );
    Battle( Entity&, Entity& );
    Battle( const Battle& );
    virtual ~Battle(  );

    virtual bool begin_battle (  ) = 0;

    void planTurn       ( const Attack*, size_t, const Attack*, size_t );
    void executeTurn    (  );

    void setPrimeiro    ( Entity& );
    void setSegundo     ( Entity& );
    void setTurno       ( int );

    int     getTurno()      const { return this->turno;         }
    Entity* getPrimeiro()   const { return this->primeiro_ptr;  }
    Entity* getSegundo()    const { return this->segundo_ptr;   }
protected:
    bool areEntitiesEqual (Entity&, Entity&);

    Entity* primeiro_ptr    = 0;
    Entity* segundo_ptr     = 0;

    const Attack* attack_primeiro_ptr = 0;
    const Attack* attack_segundo_ptr  = 0;

    size_t primeiro_aim_index = 0;
    size_t segundo_aim_index = 0;
    
    int turno;
};

#endif // BATTLE_H

//Classe 1 - Concrete
#ifndef NORMAL_BATTLE_H
#define NORMAL_BATTLE_H

#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Battle.h"

class NormalBattle : public Battle
{
    friend ostream& operator<<  ( ostream&, const NormalBattle& );
    friend int      operator!   (const NormalBattle& );
public:
    NormalBattle(  );
    NormalBattle( Entity&, Entity& );
    NormalBattle( const NormalBattle& );

    virtual ~NormalBattle(  );

    bool begin_battle (  ) override;

    const NormalBattle& operator=   ( const NormalBattle& );
    int                 operator==  ( const NormalBattle& );
    int                 operator!=  ( const NormalBattle& );
private:
    bool primeiro_choose_attack;
    bool segundo_choose_attack;
};

#endif // NORMAL_BATTLE_H

//Classe 2
#ifndef BOSS_BATTLE_H
#define BOSS_BATTLE_H

#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Battle.h"

class BossBattle : Battle
{
    friend ostream& operator<<  ( ostream&, const BossBattle& );
    friend int      operator!   (const BossBattle& );
public:
    BossBattle  (  );
    BossBattle  ( Entity& );
    BossBattle  ( const BossBattle& );

    virtual ~BossBattle(  );

    bool begin_battle( ) override;
    void add_phase( Enemy& );

    void toNextPhase    ( );

    const BossBattle& operator= ( const BossBattle& );
    int operator==              ( const BossBattle& );
    int operator!=              ( const BossBattle& );

protected:
    vector<Enemy*> boss_phases;
    int phase_number;
};

#endif // BossBattle_H

////Implementação de constructores default de cópia

///Bases abstract

//Classe abstract base 1    
Item::Item( const Item& other )
{
    this->name = other.name;
    this->description = other.description;
}


//Classe abstract base 2
GameObject::GameObject(const GameObject& other)
{
    if (other.position != 0)
        this->position = new Vector2D { other.position->x, other.position->y };
    this->representation = other.representation;
}

//Classe abstract base 3
Battle::Battle(const Battle& other)
{
    Player* player_ptr  = nullptr;
    Enemy*  enemy_ptr   = nullptr;

    /* Verifica se a primeira entidade é Player ou Enemy */
    player_ptr = dynamic_cast<Player*> (other.primeiro_ptr);
    if (player_ptr != nullptr)
    {
        this->primeiro_ptr = new Player( *player_ptr );
        player_ptr = nullptr;
    }
    else
    {
        enemy_ptr = dynamic_cast<Enemy*> (other.primeiro_ptr);
        this->primeiro_ptr = new Enemy( *enemy_ptr );
        enemy_ptr = nullptr;
    }

    /* Verifica se a segunda entidade é Player ou Enemy */
    player_ptr = dynamic_cast<Player*> (other.segundo_ptr);
    if (player_ptr != nullptr)
    {
        this->segundo_ptr = new Player( *player_ptr );
        player_ptr = nullptr;
    }
    else
    {
        enemy_ptr = dynamic_cast<Enemy*> ( enemy_ptr );
        this->segundo_ptr = new Enemy( *enemy_ptr );
        enemy_ptr = nullptr;
    }
    
    this->turno = other.turno;
}

////Classes concretas - mostrar reaproveitamento de código

/// Hierarquia 1 (abstract base 1)

//Classe Abstract 1 que herda da base abstract
#include "Weapon.h"

const string Weapon::DEFAULT_WEAPON_NAME    = "Empty Weapon";

Weapon::Weapon() : Item( )
{
    this->setName( Weapon::DEFAULT_WEAPON_NAME );
    this->setDamage( 0.0f );
    this->setDurability( 100 );
}

/**
 * A ordem de inicialização no .h é importante!
*/
Weapon::Weapon(string name, double damage, int durability) : Item(  )
{
    // cout << "Creating weapon " << name << "...\n";
    this->setName(name);
    this->setDamage(damage);
    this->setDurability(durability);
}

Weapon::Weapon( const Weapon& other ) : Item( other )
{
    this->damage        = other.damage;
    this->durability    = other.durability;
}

Weapon::~Weapon()
{
    
}

/**
 * Aumenta a durabilidade da arma por uma porcentagem do total.
 * @param amount Incrementa a durabilidade por um valor numérico. Não pode ser negativo
*/
void Weapon::increaseDurability( double ratio)
{
    if (ratio < 0)
        return;
    this->setDurability( (int) (durability + (durability * ratio)) );
}

/**
 * Diminui a durabilidade da arma por um valor
 * @param amount Valor numérico que vai ser decrementado. Não pode ser negativo.
*/
void Weapon::decreaseDurability( int amount )
{
    if (amount < 0)
        return;
    this->setDurability( this->durability - amount );
}

#pragma region Setters

void Weapon::setDamage(double damage)
{
    if (damage < 0)
    {
        this->damage = 0;
        return;
    }
    this->damage = damage;
}

void Weapon::setDurability(int durability)
{
    if (durability < 0)
    {
        this->durability = 0;
        return;
    }
    this->durability = durability;
}

#pragma endregion

        
//Classe 2 - concrete
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

// Classe 3 - Concrete
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
        this->name = right.name;
        this->description = right.description;
        this->damage = right.damage;
        this->durability = right.durability;
        this->blunt_damage = right.blunt_damage;
    }
    return *this; 
}

int MeleeWeapon::operator==(const MeleeWeapon& right)
{
    if (this->name == right.name)
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

// Classe 4
#include "Armor.h"

const string Armor::DEFAULT_ARMOR_NAME    = "Empty Armor";

Armor::Armor() : Item( )
{
    this->damage_reduction = 0.0f;
    this->min_strength = 0.0f;
    this->weight = 0.0f;
}

/**
 * A ordem de inicialização no .h é importante!
*/
Armor::Armor(double damage_reduction, double min_strength, double weight) : Item()
{
    this->setDamageReduction( damage_reduction );
    this->setMinStrength( min_strength );
    this->setWeight( weight );
}

Armor::Armor( const Armor& other ) : Item( other )
{
    this->damage_reduction = other.damage_reduction;
    this->min_strength = other.min_strength;
    this->weight = other.weight;
}

Armor::~Armor()
{
}

void Armor::use( Entity& )
{
}

#pragma region Setters

void Armor::setDamageReduction( double ratio )
{
    if (ratio < 0.0f)
    {
        this->damage_reduction = 0.0f;
        return;
    }
    this->damage_reduction = ratio;
}

void Armor::setMinStrength( double minimum )
{
    if (minimum < 0)
    {
        this->min_strength = 0;
        return;
    }
    this->min_strength = minimum;
}

void Armor::setWeight( double weight )
{
    if (weight < 0)
    {
        this->weight = 0;
        return;
    }
    this->weight = weight;
}

#pragma endregion

#pragma region Operator Overloads

ostream& operator<< (ostream& output, const Armor& Armor)
{
    output << "\n======   Armor   =====\n";
    output << "* " << Armor.name << "\n";
    output << "* Damage Reduction: \t" << Armor.damage_reduction << "\n";
    output << "* Strength required: \t" << Armor.min_strength << "\n";
    output << "* Weight: \t" << Armor.weight << "\n";
    return output;  
}

int operator! (const Armor& Armor)
{
    return ( Armor.name.empty() || Armor.name == Armor::DEFAULT_ARMOR_NAME );
}

const Armor &Armor::operator=(const Armor &right)
{
    if (&right != this)
    {
        this->name              = right.name;
        this->description       = right.description;
        this->damage_reduction  = right.damage_reduction;
        this->min_strength      = right.min_strength;
        this->weight            = right.weight;
    }
    return *this;
}

int Armor::operator== (const Armor& right )
{
    if (this->name == right.name)
        return 1;
    return 0;
}

int Armor::operator!= (const Armor& right)
{
    return !( *this == right );
}

#pragma endregion

// Classe 5
#include "Consumable.h"
#include "Item.h"

Consumable::Consumable() : Item()
{
    this->health_factor = 1.0;
}

Consumable::Consumable(string name, string description, double health_factor)
: Item( name, description )
{
    this->setHealthFactor( health_factor );
}

Consumable::Consumable(const Consumable& other) : Item( other )
{
    this->health_factor = other.health_factor;
}

Consumable::~Consumable()
{
}

void Consumable::setHealthFactor(double ratio)
{
    if (ratio < 1.0)
    {
        this->health_factor = 1.0;
        return;
    }
    this->health_factor = ratio;
}

// Classe 6
#include "OffensiveConsumable.h"

OffensiveConsumable::OffensiveConsumable()
: Consumable()
{
    this->damage = 1.0f;
}

OffensiveConsumable::OffensiveConsumable(
    string name, string description,
    double dmg_modifier, double health_factor )
: Consumable( name, description, health_factor )
{
    this->setDamageModifier( dmg_modifier );
}

OffensiveConsumable::OffensiveConsumable(const OffensiveConsumable& other)
: Consumable( other )
{
    this->damage = other.damage;
}

OffensiveConsumable::~OffensiveConsumable()
{
}

void OffensiveConsumable::use(Entity& ent)
{
    this->inflict_effect( ent );
}

void OffensiveConsumable::inflict_effect(Entity& ent)
{
    ent.receiveDamage(
        (this->health_factor * this->damage) * ent.getHealth()
    );
}

void OffensiveConsumable::setDamageModifier(double dmg)
{
    if (dmg < 0)
    {
        this->damage = 1.0f;
        return;
    }
    this->damage = dmg;
}

#pragma region OperatorOverloads

const OffensiveConsumable &OffensiveConsumable::operator=(const OffensiveConsumable& right)
{
    if (&right != this)
    {
        this->name = right.name;
        this->description = right.description;
        this->health_factor = right.health_factor;
    }
    return *this;
}

int OffensiveConsumable::operator==(const OffensiveConsumable& right)
{
    if (this->name == right.name)
        return 1;
    return 0;
}

int OffensiveConsumable::operator!=(const OffensiveConsumable& right)
{
    return !( *this == right );
}

ostream &operator<<(ostream& output, const OffensiveConsumable& item)
{
    output << "Offensive Consumable: " << item.name << " | " << item.description;
    output << "Damage: " << item.damage;
    return output;
}

int operator!(const OffensiveConsumable& right)
{
    return !( right.name.empty() || right.name == right.DEFAULT_ITEM_NAME );
}

#pragma endregion

// Classe 7
#include "RestorativeConsumable.h"

RestorativeConsumable::RestorativeConsumable()
: Consumable()
{
    this->restorative_modifier = 1.0f;
}

RestorativeConsumable::RestorativeConsumable(
    string name, string description,
    double health_factor, double restorative_modifier)
: Consumable(name, description, health_factor)
{
    this->setRestorativeModifier( restorative_modifier );
}

RestorativeConsumable::RestorativeConsumable(const RestorativeConsumable& other)
: Consumable( other )
{
    this->restorative_modifier = other.restorative_modifier;
}

RestorativeConsumable::~RestorativeConsumable()
{
}

void RestorativeConsumable::use(Entity& ent)
{
    this->inflict_effect( ent );
}

void RestorativeConsumable::inflict_effect(Entity& ent)
{
    ent.heal( this->health_factor * this->restorative_modifier );
}

void RestorativeConsumable::setRestorativeModifier(double modifier)
{
    if (modifier < 0)
    {
        this->restorative_modifier = 1.0f;
        return;
    }
    this->restorative_modifier = modifier;
}

#pragma region OperatorOverloads

ostream &operator<<(ostream& output, const RestorativeConsumable& item)
{
    output << "Restorative Consumable: " << item.name << " | " << item.description;
    output << "Restore points: " << item.restorative_modifier;
    return output;
}

int operator!(const RestorativeConsumable& right)
{
    return !( right.name.empty() || right.name == right.DEFAULT_ITEM_NAME );
}

const RestorativeConsumable &RestorativeConsumable::operator=(const RestorativeConsumable& right)
{
    if (&right != this)
    {
        this->name = right.name;
        this->description = right.description;
        this->health_factor = right.health_factor;
        this->restorative_modifier = right.restorative_modifier;
    }
    return *this;
}

int RestorativeConsumable::operator==(const RestorativeConsumable& right)
{
    if (this->name == right.name)
        return 1;
    return 0;
}

int RestorativeConsumable::operator!=(const RestorativeConsumable& right)
{
    return !( *this == right );
}

#pragma endregion

/// Hierarquia 2 (abstract base 1)

#include "GameObject.h"

GameObject::GameObject()
{
    this->position = 0;
    this->representation = 'O';
}

GameObject::GameObject(Vector2D pos, char representation)
{
    this->setPosition( pos );
    this->setRepresentation( representation );
}

GameObject::GameObject(const GameObject& other)
{
    if (other.position != 0)
        this->position = new Vector2D { other.position->x, other.position->y };
    this->representation = other.representation;
}

GameObject::~GameObject()
{
    if (this->position != 0)
        delete this->position;
}

void GameObject::setPosition(Vector2D new_pos)
{
    int new_x = new_pos.x;
    int new_y = new_pos.y;

    if (new_pos.x < 0)
        new_x = 0;

    if (new_pos.y < 0)
        new_y = 0;
    
    if (this->position == nullptr)
    {
        Vector2D* new_vector_2d = new Vector2D { new_x, new_y };
        this->position = new_vector_2d;
        return;
    }

    this->position->x = new_x; 
    this->position->y = new_y; 
}

void GameObject::setRepresentation(char new_repr)
{
    // Representation tem que ser ASCII legível
    if (new_repr > 32 && new_repr < 127)
    {
        this->representation = new_repr;
        return;
    }
    this->representation = 'O';
}

//Classe 1 - concrete
#include "Entity.h"

const size_t Entity::NAME_MAX_SIZE              = 35;
const size_t Entity::ITEM_MAX_STACK             = 99;
const size_t Entity::BODY_PART_DESC_MAX_SIZE    = 8;
const string Entity::DEFAULT_NAME               = "Empty Entity";

/* Cria uma Entidade vazia com valores padrão */
Entity::Entity() : GameObject(  )
{
    this->name      = Entity::DEFAULT_NAME;
    this->health    = 100.0f;
    this->maxHealth = 100.0f;
    this->stamina   = 100.0f;
    this->strength  = 50.0f;
    this->dexterity = 25.0f;

    this->guarding = false;
    this->equiped_weapon_ptr = 0;
    this->bodyParts = DEFAULT_ENTITY_BODY_PARTS;
    this->inventory_ptr = new vector< InventoryItem* >;
}

Entity::Entity( string name,
                double health,
                double stamina,
                double strength,
                double dexterity,
                Vector2D position,
                vector< BodyPart > bodyParts )
: GameObject( position, 'E' )
{
    this->setName( name );
    this->setMaxHealth( health );
    this->setHealth( health );
    this->setStamina( stamina );
    this->setStrength( strength );
    this->setDexterity( dexterity );


    this->guarding = false;
    this->equiped_weapon_ptr = 0;

    this->setBodyParts( bodyParts );
    this->inventory_ptr = new vector< InventoryItem* >;
}

Entity::Entity( const Entity& other )
: GameObject( other )
{
    this->name = other.name;
    this->health = other.health;
    this->maxHealth = other.maxHealth;
    this->stamina = other.stamina;
    this->dexterity = other.dexterity;

    this->guarding = other.guarding;

    this->copyWeapon( other.equiped_weapon_ptr );

    this->isUsingRangedWeapon = other.isUsingRangedWeapon;

    this->copyInventory( other.inventory_ptr );

    this->bodyParts = other.bodyParts;
}

Entity::~Entity()
{
    if (this->inventory_ptr == 0)
        return;

    if ( !this->inventory_ptr->empty() )
        for (auto& item : *inventory_ptr )
            if (item)
                delete item;
    // delete this->inventory_ptr;
}

/**
 * Move a entidade através da matriz
 * @param where Direcão baseada no Enum Direction
*/
void Entity::move( Direction where )
{
    switch (where)
    {
    case UP:
        this->setPosition( 
            Vector2D { this->position->x, this->position->y - 1 } 
        );
        break;
    
    case RIGHT:
        this->setPosition( 
            Vector2D { this->position->x + 1, this->position->y } 
        );
        break;
    
    case DOWN:
        this->setPosition( 
            Vector2D { this->position->x, this->position->y + 1 } 
        );
        break;

    case LEFT:
        this->setPosition( 
            Vector2D { this->position->x - 1, this->position->y } 
        );
        break;
    
    default:
        break;
    }
}

/**
 * Equipa uma arma.
 * @param weapon Arma a ser equipada - pegue da base de dados!
*/
void Entity::equipWeapon( Weapon* weapon_ptr )
{
    // Tã usando long ranged?
    LongRangeWeapon* long_range_wpn = dynamic_cast<LongRangeWeapon*> (weapon_ptr);

    if (long_range_wpn != nullptr)
        this->isUsingRangedWeapon = true;
    else
        this->isUsingRangedWeapon = false;

    this->equiped_weapon_ptr = weapon_ptr;
}

/**
 * Ataca outra entidade.
 * Calcula o modificador de dano baseado na forca do personagem e inflige o dano,
 * depois escolhe uma parte da entidade para atacar, aleatoriamente.
 * @param other Entidade que vai ser atacada.
 * @param attack Ataque a ser utilizado
*/
void Entity::attack(
    Entity& other,
    const Attack *const attack,
    size_t aim_index 
)
{
    if (this->equiped_weapon_ptr == 0)
    {
        cout << "You are unarmed! Be careful! \n";
        return;
    }

    /* Verificamos se a arma equipada é LongRanged */
    if (this->isUsingRangedWeapon)
    {
        LongRangeWeapon* long_range_wpn_ptr
            = dynamic_cast<LongRangeWeapon*> (this->equiped_weapon_ptr);
        long_range_wpn_ptr->aim_at( other, aim_index );
        long_range_wpn_ptr->use( other );

        cout << this->name << " mira em "
            << other.getBodyParts().at(aim_index).partDescription << "\n";

        if (long_range_wpn_ptr->isTargetHit())
        {
            double damage = long_range_wpn_ptr->getDamage()
                        * other.getBodyParts().at(aim_index).damageModifier;
            cout << this->name << " acerta " << other.name 
                << " em " << other.getBodyParts().at(aim_index).partDescription  << "!\n";
            cout << this->name << " dá " << damage << " de dano!\n";
            return;
        }

        cout << "Mas erra! O projétil passa voando por " << other.name << "!\n";
        return;
    }

    /* Se não está usando LongRanged está usando Melee! */
    MeleeWeapon* melee_wpn_ptr
        = dynamic_cast<MeleeWeapon*> (this->equiped_weapon_ptr);

    BodyPart randBodyPart = other.chooseRandBodyPart();

    double dmgModifier = this->calculateDamageModifier()
                            * attack->getDamageModifier()
                            * randBodyPart.damageModifier;
    double damage = this->equiped_weapon_ptr->getDamage() * dmgModifier;

    cout << this->name << " " << attack->getDisplayMessage() << "\n";
    cout << this->name << " acerta " << other.name
        << " em " << randBodyPart.partDescription << "!\n";
    cout << this->name << " dá " << damage << " de dano!\n";
    melee_wpn_ptr->choose_attack(*attack);
    melee_wpn_ptr->use( other );
    return;
}

/**
 * Faz com que a entidade receba alguma dano pré-definido.
 * @param amount Tanto de dano a ser feito. Não pode ser negativo
*/
void Entity::receiveDamage( double amount )
{
    if (amount < 0)
        return;
    std::cout << amount << std::endl;
    this->setHealth( this->health - amount );
}

/**
 * Calcula o modificador de dano. Game designers, facam alteracoes aqui!
*/
double Entity::calculateDamageModifier( )
{
    return ( (this->strength * 1.10) + (this->dexterity * 1.05) ) / 100;
}

/**
 * Escolhe uma parte aleatória da Entidade e a retorna.
 * @returns BodyPart escolhida aleatoriamente
*/
const BodyPart &Entity::chooseRandBodyPart() const
{
    srand(time(NULL));
    size_t randIndex = rand() % this->bodyParts.size();
    return this->bodyParts[ randIndex ]; 
}

/**
 * Escolhe uma parte aleatória da Entidade e a retorna.
 * @returns BodyPart escolhida aleatoriamente
*/
size_t Entity::chooseRandBodyPartIndex() const
{
    srand(time(NULL));
    size_t randIndex = rand() % this->bodyParts.size();
    return randIndex;
}

/**
 * Cura um tanto de vida do jogador.
 * @param amount Quantidade a ser curada.
*/
void Entity::heal( double amount )
{
    if (this->getHealth() == this->maxHealth)
        return;
    this->setHealth( this->getHealth() + amount );
}

void Entity::guard( )
{
    this->guarding = !this->guarding;
}

/**
 * Pega um item do chão e guarda no inventário.
 * Checa-se o nome dos itens e se já chegou na quantidade máxima.
 * Se não houver o item no inventário, alocamos um novo.
 * @param pickedItem Item a ser guardado.
*/
void Entity::grabItem( Item& picked_item )
{   
    for (auto& itemAndQuantities : *this->inventory_ptr )
    {
        if ( itemAndQuantities->item->getName() == picked_item.getName()
            && itemAndQuantities->quantity < Entity::ITEM_MAX_STACK )
        {
            ++itemAndQuantities->quantity;
            return;
        }
    }
    this->inventory_ptr->push_back( new InventoryItem { &picked_item, 1 } );
}

/**
 * Usa um item do inventário em alguma entidade.
 * Não pode usar um item que não seja consumível!
 * @param item Item a ser usado
*/
void Entity::useItemOn( Entity& ent, Item& item_to_use )
{
    Consumable* consumable_ptr = dynamic_cast<Consumable*> (
        &item_to_use
    );

    if (consumable_ptr == 0)
    {
        std::cerr << "You can't use " << item_to_use.getName()
            << "! It's unconsumable!\n";
        return;
    }

    /* Use and discard */
    consumable_ptr->use( ent );
    for (auto& itemAndQuantities : *this->inventory_ptr)
    {
        if (itemAndQuantities->item->getName() == item_to_use.getName()
            && itemAndQuantities->quantity > 0)
        {
            --itemAndQuantities->quantity;
            return;
        }
    }
}

/**
 * Usa um item do inventário em alguma entidade.
 * @param inventory_index Índice do item no inventário
*/
void Entity::useItemOn( Entity& ent, size_t inventory_index )
{
    Item* item_at_index = this->inventory_ptr->at( inventory_index )->item;
    int item_qts        = this->inventory_ptr->at( inventory_index )->quantity;
    
    Consumable* consumable_ptr 
        = dynamic_cast<Consumable*> ( item_at_index );
    
    if (consumable_ptr == 0)
    {
        std::cerr << "You can't use " << item_at_index->getName()
            << "! It's unconsumable!\n";
        return;
    }
    
    /* Use and discard */
    consumable_ptr->use( ent );
    if (inventory_index >= 0 && inventory_index < this->inventory_ptr->size()
        && item_qts > 0 )
    {
        this->inventory_ptr->at( inventory_index )->quantity--;
        return;
    }
    std::cout << "No more " << item_at_index->getName() << " left!\n";
}

/**
 * Mostra o inventário da Entidade. Onde não há espaco alocado,
 * apenas linhas são mostradas.
*/
void Entity::showInventory( ) const
{
    cout << " === " << this->getName() << " Inventory === \n";
    for (const auto& inventory_item : *this->inventory_ptr)
    {
        if (inventory_item == 0)
        {
            cout << " ------ \n";
            continue;
        }
        cout << inventory_item->item->getName() << " - " << inventory_item->item->getDescription()
            << " | Qts: " << inventory_item->quantity << "\n";
    }
    cout << " ========================== \n";
}

#pragma region PrivateMethods

/**
 * Aloca memória na Heap e copia a arma de uma Entidade para a outra.
 * @param otherWeapon Arma da outra entidade
*/
void Entity::copyWeapon( const Weapon* const otherWeapon )
{
    if (otherWeapon == 0)
    {
        this->equiped_weapon_ptr = 0;
        return;
    }

    /**
     * Verifica se é LongRanged ou Melee pra fzr a cópia direito.
     * Usa MAGIA NEGRA, cuidado!
    */
    const LongRangeWeapon *const long_range_wpn_ptr
        = dynamic_cast<const LongRangeWeapon *const> (otherWeapon);
    if (long_range_wpn_ptr != nullptr)
    {
        this->equiped_weapon_ptr = new LongRangeWeapon( *long_range_wpn_ptr );
        return;
    }

    const MeleeWeapon *const melee_wpn_ptr
        = dynamic_cast<const MeleeWeapon *const> (otherWeapon);
    if (melee_wpn_ptr != nullptr)
    {
        this->equiped_weapon_ptr = new MeleeWeapon( *melee_wpn_ptr );
        return;
    }
    this->equiped_weapon_ptr = 0;
    return;
}

/**
 * Aloca espaço e copia o conteúdo de um inventário para outro.
 * Se houver algum inventário alocado na instância atual, ele
 * é deletado, depois copiado.
 * @param otherInventoryPtr Inventário a ser copiado
*/
void Entity::copyInventory( const vector< InventoryItem* >* otherInventoryPtr )
{
    if (otherInventoryPtr == 0)
    {
        this->inventory_ptr = 0;
        return;
    }

    if (otherInventoryPtr->empty())
        return;
    

    this->deleteInventory();

    this->inventory_ptr = new vector<InventoryItem*>;
    
    for (auto item : *otherInventoryPtr)
        this->inventory_ptr->push_back( new InventoryItem { item->item, item->quantity } );
}

/**
 * Checa se o inventário está vazio. Se estiver,
 * deleta todo o vetor do inventário e dá clear nele.
*/
void Entity::deleteInventory()
{
    if (this->inventory_ptr == 0)
        return;
    if (this->inventory_ptr->empty())
        return;
    
    for ( auto& item : *this->inventory_ptr )
    {
        if (item != 0)
            delete item;
    }

    this->inventory_ptr->clear();
}

/**
 * Verifica se uma parte do corpo é válida ou não.
 * Se a string for maior que o tamanho especificado, pega-se uma substring.
 * @param part Referência da BodyPart, importante que não seja constante para aplicar a substring.
*/
bool Entity::isBodyPartValid( BodyPart& part )
{
    if (part.damageModifier < 0.0f)
    {
        std::cerr << "ValidationError: In \"" << part.partDescription << "\" BodyPart damage modifier can't be negative!\n";
        return false;
    }

    if (part.partDescription.empty())
    {
        std::cerr << "ValidationError: BodyPart part description can't be empty!\n";
        return false;
    }

    if ( part.partDescription.size() > Entity::BODY_PART_DESC_MAX_SIZE )
    {
        std::cerr << "BodyPart part description can't have more than"
                    << Entity::BODY_PART_DESC_MAX_SIZE << " chars!"
                    << " Getting substring!\n";

        part.partDescription = part.partDescription.substr(
            0, Entity::BODY_PART_DESC_MAX_SIZE
        );
        return true;
    }
    return true;
}

#pragma endregion

#pragma region Setters

void Entity::setName( string name )
{
    if (name.empty())
    {
        std::cerr << "Name can't be empty! Defaulting to \"Empty!\"";
        this->name = "Empty Entity";
        return;
    }

    if (name.size() > Entity::NAME_MAX_SIZE)
    {
        std::cerr << "Name can't be more than " << Entity::NAME_MAX_SIZE << "chars.\n"
            << "getting substring!";
        this->name = name.substr(0, Entity::NAME_MAX_SIZE);
        return;
    }

    this->name = name;
}

void Entity::setHealth( double health )
{
    if (health < 0)
    {
        this->health = 0;
        return;
    }

    if (health > this->maxHealth)
    {
        this->health = this->maxHealth;
        return;
    }

    this->health = health;
}

void Entity::setMaxHealth( double health )
{
    if (health < 0.0f)
    {
        this->maxHealth = 1.0f;
        return;
    }

    this->maxHealth = health;
}

void Entity::setStrength( double strength )
{
    if (strength < 0)
    {
        this->strength = 0;
        return;
    }
    this->strength = strength;
}

void Entity::setStamina( double stamina )
{
    if (stamina < 0)
    {
        this->stamina = 0;
        return;
    }
    this->stamina = stamina;
}

void Entity::setDexterity( double dexterity )
{
    if (dexterity < 0)
    {
        this->dexterity = 0;
        return;
    }
    this->dexterity = dexterity;
}

void Entity::setInventory(const vector<InventoryItem *>* const other_inventory)
{

    if (this->inventory_ptr->empty())
    {
        this->copyInventory( other_inventory );
        return;
    }

    this->copyInventory( other_inventory );
    
}

void Entity::setBodyParts( vector< BodyPart > bodyParts )
{
    if (bodyParts.empty())
    {
        std::cerr << "ValidationError: The enemy must have at least one Body Part!\n";
        return;
    }

    if ( !std::all_of ( bodyParts.begin(), bodyParts.end(), Entity::isBodyPartValid ) )
    {
        std::cerr << "ValidationError: BodyPart validation failed!\n";
        return;
    }
    this->bodyParts = bodyParts;
}

#pragma endregion


// Classe 2 - concrete
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


// Classe 3
#include "Interactable.h"

Interactable::Interactable()
{
    this->before_interaction = 'B';   
    this->after_interaction = 'A';   
}

Interactable::Interactable(char before, char after)
{
    this->setBefore(before);
    this->setAfter(after);
}

Interactable::Interactable(const Interactable& other)
{
    this->before_interaction = other.before_interaction;
    this->after_interaction = other.after_interaction;
}

Interactable::~Interactable()
{
}

void Interactable::interact()
{
    if (this->actual_representation == this->before_interaction)
    {
        this->actual_representation = this->after_interaction;
        this->do_something_to_entity( *this->entity_to_afect, this->current_flag );
        return;
    }
    this->actual_representation = this->before_interaction;
    this->do_something_to_entity( *this->entity_to_afect, this->current_flag );
}

/**
 * Dependendo da flag passada, o interactable faz alguma coisa
*/
void Interactable::do_something_to_entity(Entity& ent, InteractionFlags flag)
{
    switch (flag)
    {
    case DAMAGE:
        ent.receiveDamage( health_factor );
        std::cout << message << "\n";
        break;
    
    case HEAL:
        ent.heal( health_factor );
        std::cout << message << "\n";
        break;

    case SHOW_MESSAGE:
        std::cout << "O objeto diz: \"" << message << "\"\n";
        break;
    }
}

/* Não precisa de checagem, o tipo InteractionFlags só garante um conjunto de valores */
void Interactable::changeFlag(InteractionFlags new_flag)
{
    this->current_flag = new_flag;
}

ostream &operator<<(ostream& output, const Interactable& inter)
{
    output << "Abstract Interactable object: " << inter.before_interaction
        << " -> " << inter.after_interaction << "\n";
    return output; 
}

int operator!(const Interactable& inter)
{
    return ( inter.before_interaction == inter.after_interaction );
}

void Interactable::setBefore(char new_repr)
{
    // Representation tem que ser ASCII legível
    if (new_repr > 32 && new_repr < 127)
    {
        this->before_interaction = new_repr;
        return;
    }
    this->before_interaction = 'B';
}

void Interactable::setAfter(char new_repr)
{
    // Representation tem que ser ASCII legível
    if (new_repr > 32 && new_repr < 127)
    {
        this->after_interaction = new_repr;
        return;
    }
    this->after_interaction = 'A';
}

const Interactable &Interactable::operator=(const Interactable& other)
{
    if (this != &other)
    {
        this->representation = other.representation;
        if (other.position != nullptr)
            this->position = new Vector2D { other.position->x, other.position->y };
        else
            this->position = nullptr;
        this->after_interaction = other.after_interaction;
        this->before_interaction = other.before_interaction;
    }
    return *this;
}

int Interactable::operator==(const Interactable& other)
{
    return ( this->before_interaction == other.before_interaction
            && this->after_interaction == other.after_interaction );
}

int Interactable::operator!=(const Interactable& other)
{
    return !( *this == other );
}

// Classe 5
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

/// Hierarquia 3 (abstract base 1)
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
    Player* player_ptr  = nullptr;
    Enemy*  enemy_ptr   = nullptr;

    /* Verifica se a primeira entidade é Player ou Enemy */
    player_ptr = dynamic_cast<Player*> (other.primeiro_ptr);
    if (player_ptr != nullptr)
    {
        this->primeiro_ptr = new Player( *player_ptr );
        player_ptr = nullptr;
    }
    else
    {
        enemy_ptr = dynamic_cast<Enemy*> (other.primeiro_ptr);
        this->primeiro_ptr = new Enemy( *enemy_ptr );
        enemy_ptr = nullptr;
    }

    /* Verifica se a segunda entidade é Player ou Enemy */
    player_ptr = dynamic_cast<Player*> (other.segundo_ptr);
    if (player_ptr != nullptr)
    {
        this->segundo_ptr = new Player( *player_ptr );
        player_ptr = nullptr;
    }
    else
    {
        enemy_ptr = dynamic_cast<Enemy*> ( enemy_ptr );
        this->segundo_ptr = new Enemy( *enemy_ptr );
        enemy_ptr = nullptr;
    }
    
    this->turno = other.turno;
}

Battle::~Battle()
{
    // Não deleta nenhum dos ponteiros. Eles não são criados aqui.
    // A futura classe Game vai lidar com eles
    // std::cout << "Destrutor do Battle\n" << std::endl;
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
    if ( !this->areEntitiesEqual( *this->primeiro_ptr, primeiro ) )
        this->primeiro_ptr = &primeiro;
}

void Battle::setSegundo(Entity& segundo)
{
    if ( this->segundo_ptr == nullptr )
    {
        this->segundo_ptr = &segundo;
        return;
    }
    if ( !this->areEntitiesEqual( *this->segundo_ptr, segundo ) )
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

/**
 * Verifica se duas entidades são iguais.
 * Função de utilidade.
*/
bool Battle::areEntitiesEqual(Entity& primeiro, Entity& segundo)
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

// Classe 1 - concrete
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

//Classe 2 - concrete
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
    Attack* primeiro_atk_ptr = nullptr;
    Attack* segundo_atk_ptr = nullptr;

    size_t primeiro_aim_index = 0;
    size_t segundo_aim_index = 0;
    
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
    return (
            this->areEntitiesEqual( *this->primeiro_ptr, *other.primeiro_ptr ) 
        &&  this->areEntitiesEqual( *this->segundo_ptr,  *other.segundo_ptr  )
    );
}

int BossBattle::operator!=( const BossBattle& other )
{
    return !( *this == other );
}


//// Mostrar implementação dos métodos virtuais puros nas classes concretas
 /// Mostrar reaproveitamente de código da base

    /// Hierarquia 1
         //Base - métodos virtuais puros
            virtual void use( Entity& ) = 0;
            virtual void inflict_damage ( Entity& ) = 0;
         //Classe concrete 1
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

//Classe concrete 2
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

// Classe Abstrata Consumable
    virtual void use            ( Entity& ) = 0;
    virtual void inflict_effect ( Entity& ) = 0;

// Classe Offensive Consumable
void OffensiveConsumable::use(Entity& ent)
{
    this->inflict_effect( ent );
}

void OffensiveConsumable::inflict_effect(Entity& ent)
{
    ent.receiveDamage(
        (this->health_factor * this->damage) * ent.getHealth()
    );
}

// Classe Restorative Consumable
void RestorativeConsumable::use(Entity& ent)
{
    this->inflict_effect( ent );
}

void RestorativeConsumable::inflict_effect(Entity& ent)
{
    ent.heal( this->health_factor * this->restorative_modifier );
}

/// Hierarquia 2

//Base - métodos virtuais puros
    virtual void interact() = 0;

//Classe concrete 1
void Player::interact( GameObject& other )
{
    if (Entity* other_entity = dynamic_cast<Entity*> (&other))
    {
        NormalBattle new_battle(*this, *other_entity);
        new_battle.begin_battle();
        return;
    }
    if (Interactable* interactable = dynamic_cast<Interactable*> (&other))
    {
        interactable->interact();
        return;
    }
}

// Classe concrete 2
void Enemy::interact( GameObject& other )
{
    if (Player* other_entity = dynamic_cast<Player*> (&other))
    {
        NormalBattle new_battle(*other_entity, *this);
        new_battle.begin_battle();
        return;
    }
}

// Classe Concreta
void Interactable::interact( GameObject& other )
{
    if (this->actual_representation == this->before_interaction)
    {
        this->actual_representation = this->after_interaction;
        this->do_something_to_entity( *this->entity_to_afect, this->current_flag );
        return;
    }
    this->actual_representation = this->before_interaction;
    this->do_something_to_entity( *this->entity_to_afect, this->current_flag );
}

// Classe Concreta
void NPC::interact( GameObject& other)
{
    if (Player* player_ptr = dynamic_cast<Player*> (other))
    {
        this->talk();
        monologue_counter++;
    }
}

/// Hierarquia 3

//Base - métodos virtuais puros
virtual bool begin_battle (  ) = 0;

//Classe concrete 1
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

// Classe concrete 2
bool BossBattle::begin_battle()
{
    Attack* primeiro_atk_ptr = nullptr;
    Attack* segundo_atk_ptr = nullptr;

    size_t primeiro_aim_index = 0;
    size_t segundo_aim_index = 0;
    
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

//// Em uma das hierarquias deve haver alocação de memória usando um vector< ptr * >, 
// onde ptr é um ponteiro de uma de
//suas classes criadas que tem relação de composição.

    /// Mostrar .h com este vector (com apenas ele presente) usando "..." para omitir
    //o resto

    (...)
class Entity : public GameObject
    (...)
private:
    (...)
    vector< InventoryItem* >* inventory_ptr = 0;        // Inventário da entidade
    (...)
};

/// Mostrar inicialização do vector 
Entity::Entity() : GameObject(  )
{
    (...)
    this->inventory_ptr = new vector< InventoryItem* >;
    (...)
}

/// Mostrar o método que aplica new nele
/**
 * Pega um item do chão e guarda no inventário.
 * Checa-se o nome dos itens e se já chegou na quantidade máxima.
 * Se não houver o item no inventário, alocamos um novo.
 * @param pickedItem Item a ser guardado.
*/
void Entity::grabItem( Item& picked_item )
{   
    for (auto& itemAndQuantities : *this->inventory_ptr )
    {
        if ( itemAndQuantities->item->getName() == picked_item.getName()
            && itemAndQuantities->quantity < Entity::ITEM_MAX_STACK )
        {
            ++itemAndQuantities->quantity;
            return;
        }
    }
    this->inventory_ptr->push_back( new InventoryItem { &picked_item, 1 } );
}

    /// Mostrar método em que ele é usado efetivamente
    //preenchimento, set e get serão ignorados
    /**
 * Usa um item do inventário em alguma entidade.
 * Não pode usar um item que não seja consumível!
 * @param item Item a ser usado
*/
void Entity::useItemOn( Entity& ent, Item& item_to_use )
{
    Consumable* consumable_ptr = dynamic_cast<Consumable*> (
        &item_to_use
    );

    if (consumable_ptr == 0)
    {
        std::cerr << "You can't use " << item_to_use.getName()
            << "! It's unconsumable!\n";
        return;
    }

    /* Use and discard */
    consumable_ptr->use( ent );
    for (auto& itemAndQuantities : *this->inventory_ptr)
    {
        if (itemAndQuantities->item->getName() == item_to_use.getName()
            && itemAndQuantities->quantity > 0)
        {
            --itemAndQuantities->quantity;
            return;
        }
    }
}

///Mostrar destructor e desalocação
Entity::~Entity()
{
    if (this->inventory_ptr == 0)
        return;

    if ( !this->inventory_ptr->empty() )
        for (auto& item : *inventory_ptr )
            if (item)
                delete item;
    // delete this->inventory_ptr;
}

/// Mostrar o uso (indireto) deste vector -- Não entendi muito bem
/**
 * Mostra o inventário da Entidade. Onde não há espaco alocado,
 * apenas linhas são mostradas.
*/
void Entity::showInventory( ) const
{
    cout << " === " << this->getName() << " Inventory === \n";
    for (const auto& inventory_item : *this->inventory_ptr)
    {
        if (inventory_item == 0)
        {
            cout << " ------ \n";
            continue;
        }
        cout << inventory_item->item->getName() << " - " << inventory_item->item->getDescription()
            << " | Qts: " << inventory_item->quantity << "\n";
    }
    cout << " ========================== \n";
}

//// Ter um atributo static e um atributo const static.

/// .h mostrando apenas eles e o método que os manipula

#ifndef ENTITY_H
#define ENTITY_H
class Entity : GameObject {    
public:
        void setName        ( string );
        void grabItem                    ( Item& );
        void setBodyParts   ( vector< BodyPart >& );
private:
        const static size_t NAME_MAX_SIZE;             // Máximo de um item que pode ser carregado
        const static size_t ITEM_MAX_STACK;             // Máximo de um item que pode ser carregado
        const static size_t BODY_PART_DESC_MAX_SIZE;    // Tamanho máximo da string do BodyPart
        const static string DEFAULT_NAME;               // Nome padrão de entidades não declaradas
};
#endif

/// Inicialização no .cpp
#include "Entity.h"

const size_t Entity::NAME_MAX_SIZE              = 35;
const size_t Entity::ITEM_MAX_STACK             = 99;
const size_t Entity::BODY_PART_DESC_MAX_SIZE    = 8;
const string Entity::DEFAULT_NAME               = "Empty Entity";

(...)

/// Mostra método(s) em que são usados efetivamente
void Entity::setName( string name )
{
    if (name.empty())
    {
        std::cerr << "Name can't be empty! Defaulting to \"Empty!\"";
        this->name = "Empty Entity";
        return;
    }

    if (name.size() > Entity::NAME_MAX_SIZE)
    {
        std::cerr << "Name can't be more than " << Entity::NAME_MAX_SIZE << "chars.\n"
            << "getting substring!";
        this->name = name.substr(0, Entity::NAME_MAX_SIZE);
        return;
    }

    this->name = name;
}

/**
 * Pega um item do chão e guarda no inventário.
 * Checa-se o nome dos itens e se já chegou na quantidade máxima.
 * Se não houver o item no inventário, alocamos um novo.
 * @param pickedItem Item a ser guardado.
*/
void Entity::grabItem( Item& picked_item )
{   
    for (auto& itemAndQuantities : *this->inventory_ptr )
    {
        if ( itemAndQuantities->item->getName() == picked_item.getName()
            && itemAndQuantities->quantity < Entity::ITEM_MAX_STACK )
        {
            ++itemAndQuantities->quantity;
            return;
        }
    }
    this->inventory_ptr->push_back( new InventoryItem { &picked_item, 1 } );
}


//// Fazer a sobrecarga para todas as classes dos operadores =, ==, ≠ e << (friend)
/// Operator=

/// Hierarquia 1
//Base Abstract - GameObject
const GameObject &GameObject::operator=(const GameObject& other)
{
    if (this != &other)
    {
        if (other.position != 0)
        {
            if (this->position != 0)
                delete this->position;
            this->position = new Vector2D {other.position->x, other.position->y };
        }
        this->representation = other.representation;
    }
    return *this;
}

// Derivada - Classe Abstrata Entity
const Entity& Entity::operator=(const Entity& other)
{
    if (this != &other)
    {
        this->name = other.name;
        this->maxHealth = other.maxHealth;
        this->health = other.health;
        this->stamina = other.stamina;
        this->strength = other.strength;
        this->dexterity = other.dexterity;

        this->setBodyParts( other.getBodyParts() );
        if (this->equiped_weapon_ptr != 0)
            delete equiped_weapon_ptr;
        this->copyWeapon( other.equiped_weapon_ptr );
        this->copyInventory( other.inventory_ptr );
    }

    return *this;
}

// Derivada - Classe Concreta Player
const Player &Player::operator=(const Player& right)
{
    if (this != &right)
    {
        Entity::operator=(right);

        if (this->attacks.empty())
            this->deleteAttacks();
    
        this->copyAttacks(right);
    }
    return *this;
}

// Derivada - Classe Concreta Enemy
const Enemy& Enemy::operator=(const Enemy& right)
{
    if (this != &right)
    {
        Entity::operator=(right);

        // Copia map
        if (!right.probabilitiesAndAttacks.empty())
        {
            for ( auto& prob_and_attacks : right.probabilitiesAndAttacks )
            {
                std::cout << *prob_and_attacks.second << std::endl;
                this->addAttackAndProbability(
                    new Attack (*prob_and_attacks.second), prob_and_attacks.first
                );
            }
        }
    }
    return *this;
}

// Derivada - Classe Concreta Interactable
const Interactable &Interactable::operator=(const Interactable& other)
{
    if (this != &other)
    {
        GameObject::operator=(other);
        this->after_interaction = other.after_interaction;
        this->before_interaction = other.before_interaction;
    }
    return *this;
}

// Derivada - Classe Concreta NPC
const NPC &NPC::operator=(const NPC& other)
{
    if (this != &other)
    {
        GameObject::operator=(other);
        this->copyMonologue( other.getMonologues() );
        this->monologue_counter = other.monologue_counter;
    }
    return *this;
}

/// Hierarquia 2
             //Base
const Item& Item::operator= ( const Item& other )
{
    if (this != &other)
    {
        this->name = other.name;
        this->description = other.description;
    }
    return *this;
}

//Derivadas da Base 2 - mostrar uso static_cast

const Weapon& Weapon::operator= ( const Weapon& other )
{
    if (this != &other)
    {
        Item::operator=(other);
        this->damage = other.damage;
        this->durability = other.durability;
    }
    return *this;
}

const LongRangeWeapon &LongRangeWeapon::operator=(const LongRangeWeapon& right)
{
    if (&right != this)
    {
        Weapon::operator=(right);
        this->accuracy = right.accuracy;
    }
    return *this;   
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

const Consumable& Consumable::operator= ( const Consumable& other )
{
    if (this != &other)
    {
        Item::operator=(other);
        this->health_factor = other.health_factor;
    }
    return *this;
}

const OffensiveConsumable &OffensiveConsumable::operator=(const OffensiveConsumable& right)
{
    if (&right != this)
    {
        Consumable::operator=(right);
        this->damage = right.damage;
    }
    return *this;
}

const RestorativeConsumable &RestorativeConsumable::operator=(const RestorativeConsumable& right)
{
    if (&right != this)
    {
        Consumable::operator=(right);
        this->restorative_modifier = right.restorative_modifier;
    }
    return *this;
}

/// Hierarquia 3
    //Base
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

//Derivadas da Base 3 - mostrar uso static_cast
const NormalBattle& NormalBattle::operator=(const NormalBattle& other)
{
    if (this != &other)
    {
        Battle::operator=(other);
    }
    return *this;
}

const BossBattle& BossBattle::operator=(const BossBattle& other)
{
    if (this != &other)
    {
        Battle::operator=(other);
    }
    return *this;
}

//// Operators== e !=
// Hierarquia 1

// Base - Classe Abstrata Item
int Item::operator== ( const Item& right )
{
    return (this->name == right.name);
}

int Item::operator!= (const Item& right)
{
    return !( *this == right );
}

// Derivada - Classe Abstrata Weapon
int Weapon::operator== (const Weapon& right )
{
    return ( Item::operator==(right) && this->damage == right.damage );
}

int Weapon::operator!= (const Weapon& right )
{
    return !( *this == right );
}

// Derivada - Classe Concreta Long Range Weapon
int LongRangeWeapon::operator==(const LongRangeWeapon& right)
{
    if ( Weapon::operator==(right) && this->accuracy == right.accuracy)
        return 1;
    return 0;
}

int LongRangeWeapon::operator!=(const LongRangeWeapon& right)
{
    return !(*this == right);
}

// Derivada - Classe Concreta Melee Weapon
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

//// Hierarquia 2
//Base - Classe Abstrata GameObject
int GameObject::operator== (const GameObject& right )
{
    return ( this->representation == right.representation );
}

int GameObject::operator!= (const GameObject& right )
{
    return !( *this == right );
}

// Derivada - Classe Abstrata Entity
int Entity::operator== (const Entity& right )
{
    return ( GameObject::operator==(right) && this->name == right.name );
}

int Entity::operator!= (const Entity& right )
{
    return !( *this == right );
}

// Derivada - Classe Concreta Player
int Player::operator==(const Player& right)
{
    return ( Entity::operator==(right) );
}

int Player::operator!=(const Player& other)
{
    return !( *this == other );
}

// Derivada - Classe Concreta Enemy
int Enemy::operator==(const Enemy& right)
{
    return (Entity::operator==(right));
}

int Enemy::operator!=(const Enemy& other)
{
    return !( *this == other );
}

// Derivada - Classe Concreta Interactable
int Interactable::operator==(const Interactable& other)
{
    return ( GameObject::operator==(other)
            && this->before_interaction == other.before_interaction
            && this->after_interaction == other.after_interaction );
}

int Interactable::operator!=(const Interactable& other)
{
    return !( *this == other );
}

// Derivada - Classe Concreta NPC
int NPC::operator==(const NPC& right)
{
    return ( GameObject::operator==(right) && this->areMonologuesEqual( this->monologues, right.monologues ));
}

int NPC::operator!=(const NPC& right)
{
    return !( *this == right );
}

// Hierarquia 3
// Base - Classe Abstrata Battle
int Battle::operator== (const Battle& right )
{
    return ( this->areEntitiesEqual(*this->primeiro_ptr, *right.primeiro_ptr)
            && this->areEntitiesEqual(*this->segundo_ptr, *right.segundo_ptr) );
}

int Battle::operator!= (const Battle& right )
{
    return !( *this == right );
}

// Derivada - Classe Concreta NormalBattle
int NormalBattle::operator==( const NormalBattle& other )
{
    return ( Battle::operator==(other) );
}

int NormalBattle::operator!=( const NormalBattle& other )
{
    return !( *this == other );
}

// Derivada - Classe Concreta BossBattle
int BossBattle::operator==( const BossBattle& other )
{
    return ( Battle::operator==(other));
}

int BossBattle::operator!=( const BossBattle& other )
{
    return !( *this == other );
}

//// Operator<<
//// Hierarquia 1
//Base - Classe Abstrata Item
ostream& operator<< ( ostream& output, const Item& item )
{
    output << item.name << " | " << item.description;
    return output;
}

//Derivada - Classe Concreta Weapon
ostream& operator<< (ostream& output, const Weapon& weapon)
{
    output << "\n======   WEAPON   =====\n";
    output << "* " << weapon.name << "\n";
    output << "* Damage: \t" << weapon.damage << "\n";
    output << "* Durability: \t" << weapon.durability << "\n";
    return output;  
}

// Derivada - Classe Concreta LongRangeWeapon
ostream &operator<<(ostream& output, const LongRangeWeapon& weapon)
{
    output << "\n======   LONG RANGE WEAPON   =====\n";
    output << "* " << weapon.name << "\n";
    output << "* Damage: \t" << weapon.damage << "\n";
    output << "* Durability: \t" << weapon.durability << "\n";
    output << "* Accuracy: \t" << weapon.accuracy << "\n";
    return output;  
}

// Derivada - Classe Concreta MelleeWeapon
ostream &operator<<(ostream& output, const MeleeWeapon& weapon)
{
    output << "\n======   MELEE WEAPON   =====\n";
    output << "* "                  << weapon.name          << "\n";
    output << "* Damage: \t"        << weapon.damage        << "\n";
    output << "* Durability: \t"    << weapon.durability    << "\n";
    output << "* Blunt Damage: \t"  << weapon.blunt_damage  << "\n";
    return output; 
}

// Derivada - Classe Abstrata Consumable
ostream& operator<< ( ostream& output, const Consumable& item )
{
    output << "Consumable: " << item.name << " | " << item.description;
    return output;
}

// Derivada - Classe Concreta OffensiveConsumable - static_cast não é possível
ostream &operator<<(ostream& output, const OffensiveConsumable& item)
{
    output << "Offensive Consumable: " << item.name << " | " << item.description;
    output << "Damage: " << item.damage;
    return output;
}

// Derivada - Classe Concreta RestorativeConsumable - static_cast não é possível
ostream &operator<<(ostream& output, const RestorativeConsumable& item)
{
    output << "Restorative Consumable: " << item.name << " | " << item.description;
    output << "Restore points: " << item.restorative_modifier;
    return output;
}

//// Hierarquia 2
//Base - Classe Abstrata GameObject
ostream &operator<<(ostream& output, const GameObject& object)
{
    output << "Object " << object.getRepresentation() <<
        " at (" << object.getPosition().x << ", " << object.getPosition().y
        << ")\n";
    return output;
}

// Derivada - Classe Abstrata Entity
ostream &operator<<(ostream& output, const Entity& entity )
{
    output << " === Entity " << entity.name << " === \n";
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
    else
        output << *entity.equiped_weapon_ptr;
    output << " === Body Parts === \n";
    for (const auto& part : entity.bodyParts)
        output << part.partDescription << "\n";
    output << " ======================== \n";
    return output;
}

// Derivada - Classe Concreta Player
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

// Derivada - Classe Concreta Enemy
ostream &operator<<(ostream& output, const Enemy& entity)
{
    output << " === Enemy Entity " << entity.name << " === \n";
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

// Derivada - Classe Concreta Interactable
ostream &operator<<(ostream& output, const Interactable& inter)
{
    output << "Abstract Interactable object: " << inter.before_interaction
        << " -> " << inter.after_interaction << "\n";
    return output; 
}

// Derivada - Classe Concreta NPC
ostream &operator<<(ostream& output, const NPC& npc)
{
    output << "NPC " << npc.getRepresentation() << "\n";
    output << "Falas:\n";
    for (auto falas : npc.getMonologues())
        std::cout << "* \"" << falas << "\"\n"; 
    return output;
}

// Hierarquia 3
// Base - Classe Abstrata Battle
ostream &operator<<(ostream& output, const Battle& battle)
{
    output << battle.primeiro_ptr->getName() << " VS. " << battle.segundo_ptr->getName() << "\n";
    output << battle.primeiro_ptr->getHealth() << " | " << battle.segundo_ptr->getHealth() << "\n";
    output << "Turno: " << battle.turno << "\n";
    return output;
}

// Derivada - Classe Concreta NormalBattle - static_cast<Battle> impossĩvel
ostream &operator<<(ostream& output, const NormalBattle& battle)
{
    output << battle.primeiro_ptr->getName() << " VS. " << battle.segundo_ptr->getName() << "\n";
    output << battle.primeiro_ptr->getHealth() << " | " << battle.segundo_ptr->getHealth() << "\n";
    output << "Turno: " << battle.turno << "\n";
    return output;
}

// Derivada - Classe Concreta BossBattle - static_cast<Battle> impossĩvel
ostream &operator<<(ostream& output, const BossBattle& battle)
{
    output << battle.primeiro_ptr->getName() << " VS. * " << battle.segundo_ptr->getName() << " * \n";
    output << battle.primeiro_ptr->getHealth() << " | " << battle.segundo_ptr->getHealth() << "\n";
    output << "Turno: " << battle.turno << "\n";
    return output;
}
            
//// Carregamento e salvamento de arquivos
    /*É necessário ter a funcionalidade: 1. 
      leitura de arquivos para configuração das suas classes e variáveis de status, 
      2. processamento das variáveis de status e 
      3. salvamento dessas variáveis. 
    
    // Os salvamentos são realizados pelos parsers demonstrados no trabalho passado.
    // Eles não mudaram nada desde a ũltima vez, mas ainda estão corretos.
      
///Sem o diagrama UML, a saída do programa e o vídeo, o trabalho não será avaliado.*/

    //Link arquivo de configuração no repositório

    //Link vídeo mostrando a execução do código usando o arquivo de configuração