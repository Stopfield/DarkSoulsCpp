#include "Entity.h"

const size_t Entity::NAME_MAX_SIZE              = 20;
const size_t Entity::ITEM_MAX_STACK             = 99;
const size_t Entity::BODY_PART_DESC_MAX_SIZE    = 8;
const string Entity::DEFAULT_NAME               = "Empty Entity";

/* Cria uma Entidade vazia com valores padrão */
Entity::Entity()
{
    this->name      = Entity::DEFAULT_NAME;
    this->health    = 100.0f;
    this->stamina   = 100.0f;
    this->strength  = 50.0f;
    this->dexterity = 25.0f;

    this->guarding = false;
    this->equipedWeaponPtr = 0;
    this->position = Vector2D { 0 };
    this->bodyParts = DEFAULT_ENTITY_BODY_PARTS;
    this->inventory = vector< InventoryItem* > ();
}

Entity::Entity( string name,
                double health,
                double stamina,
                double strength,
                double dexterity,
                Vector2D position,
                vector< BodyPart > bodyParts )
{
    this->setName( name );
    this->setHealth( health );
    this->setMaxHealth( health );
    this->setStamina( stamina );
    this->setStrength( strength );
    this->setDexterity( dexterity );

    this->guarding = false;
    this->equipedWeaponPtr = 0;
    this->setPosition( position );

    this->setBodyParts( bodyParts );
}

Entity::Entity( const Entity& other )
{
    this->name = other.name;
    this->health = other.health;
    this->maxHealth = other.maxHealth;
    this->stamina = other.stamina;
    this->dexterity = other.dexterity;

    this->guarding = other.guarding;

    this->copyWeapon( other.equipedWeaponPtr );
    this->copyInventory( other.inventory );

    this->position = other.position;
    this->bodyParts = other.bodyParts;
}

Entity::~Entity()
{
    if (this->equipedWeaponPtr)
        delete this->equipedWeaponPtr;

    if ( !this->inventory.empty() )
        for (auto& item : inventory )
            if (item)
                delete item;
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
            Vector2D { this->position.x, this->position.y - 1 } 
        );
        break;
    
    case RIGHT:
        this->setPosition( 
            Vector2D { this->position.x + 1, this->position.y } 
        );
        break;
    
    case DOWN:
        this->setPosition( 
            Vector2D { this->position.x, this->position.y + 1 } 
        );
        break;

    case LEFT:
        this->setPosition( 
            Vector2D { this->position.x - 1, this->position.y } 
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
void Entity::equipWeapon( const Weapon& weapon )
{
    if (this->equipedWeaponPtr)
        delete this->equipedWeaponPtr;
    this->equipedWeaponPtr = new Weapon( weapon );
}

/**
 * Ataca outra entidade.
 * Calcula o modificador de dano baseado na forca do personagem e inflige o dano,
 * depois escolhe uma parte da entidade para atacar, aleatoriamente.
 * @param other Entidade que vai ser atacada.
 * @param attack Ataque a ser utilizado
*/
void Entity::attack( Entity& other, const Attack& attack)
{
    if (this->equipedWeaponPtr == 0)
    {
        cout << "You are unarmed! Be careful! \n";
        return;
    }

    // Get BodyPart damage modifier
    BodyPart randBodyPart = other.chooseRandBodyPart();

    double dmgModifier =
        this->calculateDamageModifier() * attack.getDamageModifier() * randBodyPart.damageModifier;
    double damage = this->equipedWeaponPtr->getDamage() * dmgModifier;

    other.receiveDamage( damage);
    this->equipedWeaponPtr->decreaseDurability( 1 );

    cout << this->name << " " << attack.getDisplayMessage() << "\n";
    cout << this->name << " acerta " << other.name
        << " em " << randBodyPart.partDescription << "!\n";
    cout << this->name << " dá " << damage << " de dano!\n";
}

/**
 * Faz com que a entidade receba alguma dano pré-definido.
 * @param amount Tanto de dano a ser feito. Não pode ser negativo
*/
void Entity::receiveDamage( double amount )
{
    if (amount < 0)
        return;
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
const BodyPart& Entity::chooseRandBodyPart() const
{
    srand(time(NULL));
    size_t randIndex = rand() % this->bodyParts.size();
    return this->bodyParts[ randIndex ]; 
}

/**
 * Pega um item do chão e guarda no inventário.
 * Checa-se o nome dos itens e se já chegou na quantidade máxima.
 * Se não houver o item no inventário, alocamos um novo.
 * @param pickedItem Item a ser guardado.
*/
void Entity::grabItem( const Item& pickedItem )
{
    for (auto& itemAndQuantities : this->inventory )
    {
        if ( itemAndQuantities->item.getName() == pickedItem.getName() 
            && itemAndQuantities->quantity < Entity::ITEM_MAX_STACK )
        {
            ++itemAndQuantities->quantity;
            return;
        }
    }

    this->inventory.push_back( new InventoryItem { pickedItem, 1 } );
}

/**
 * Mostra o inventário da Entidade. Onde não há espaco alocado,
 * apenas linhas são mostradas.
*/
void Entity::showInventory( ) const
{
    cout << " === " << this->getName() << " Inventory === \n";
    for (const auto& item : this->inventory)
    {
        if (item == 0)
        {
            cout << " ------ \n";
            continue;
        }
        cout << item->item << " | Qts: " << item->quantity << "\n";
    }
    cout << " ========================== \n";
}

/**
 * Usa um item do inventário.
 * @param item Item a ser usado
*/
void Entity::useItem( const Item& item )
{
    for (auto& itemAndQuantities : this->inventory)
    {
        if (itemAndQuantities->item.getName() == item.getName()
            && itemAndQuantities->quantity > 0)
        {
            --itemAndQuantities->quantity;
            this->heal(item.getHealQuantity());
            return;
        }
    }
}

/**
 * Usa um item do inventário.
 * @param inventoryIndex Índice do item no inventário
*/
void Entity::useItem( size_t inventoryIndex )
{
    if (inventoryIndex >= 0 && inventoryIndex < this->inventory.size())
    {
        this->inventory.at( inventoryIndex )->item.getHealQuantity();
        this->inventory.at( inventoryIndex )->quantity--;
        return;
    }
    std::cerr << "Insert a valid index. Between 0 and "
        << this->inventory.size() << "\n";
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

#pragma region PrivateMethods

/**
 * Aloca memória na Heap e copia a arma de uma Entidade para a outra.
 * @param otherWeapon Arma da outra entidade
*/
void Entity::copyWeapon( const Weapon* const otherWeapon )
{
    if (otherWeapon == 0)
    {
        this->equipedWeaponPtr = 0;
        return;
    }
    this->equipedWeaponPtr = new Weapon( *otherWeapon );
}

/**
 * Aloca espaço e copia o conteúdo de um inventário para outro.
 * @param otherInventory Inventário a ser copiado
*/
void Entity::copyInventory( const vector< InventoryItem* >& otherInventory )
{
    if (otherInventory.empty())
        return;
    
    for (auto item : otherInventory)
        this->inventory.push_back( new InventoryItem { item->item, item->quantity } );
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

void Entity::setPosition( Vector2D position )
{
    int new_x = position.x;
    int new_y = position.y;

    if (position.x < 0)
        new_x = 0;

    if (position.y < 0)
        new_y = 0;
    
    this->position = Vector2D { new_x, new_y }; 
}

void Entity::setBodyParts( vector< BodyPart >& bodyParts )
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

#pragma region OperatorOverloads

ostream &operator<<(ostream& output, const Entity& entity )
{
    output << " === Entity " << entity.name << " === \n";
    output << "Entity: " << entity.name << "\n";
    output << "Health: " << entity.health << "\n";
    output << "Stamina: " << entity.stamina << "\n";
    output << "Strength: " << entity.strength << "\n";
    output << "Dexterity: " << entity.dexterity;
    if (entity.equipedWeaponPtr == 0)
    {
        output << "\n === Weapon === \n";
        output << " Unarmed \n";
    }
    else
        output << *entity.equipedWeaponPtr;
    output << " === Body Parts === \n";
    for (const auto& part : entity.bodyParts)
        output << part.partDescription << "\n";
    output << " ======================== \n";
    return output;
}

int operator! (const Entity& right)
{
    return ( right.name.empty() || right.name == Entity::DEFAULT_NAME );
}

const Entity& Entity::operator= ( const Entity& right )
{
    if (this != &right)
    {
        this->name = right.name;
        this->maxHealth = right.maxHealth;
        this->health = right.health;
        this->stamina = right.stamina;
        this->strength = right.strength;
        this->dexterity = right.dexterity;
        this->bodyParts = right.bodyParts;

        this->copyWeapon( right.equipedWeaponPtr );
        this->copyInventory( right.inventory );
        this->position = right.position;
    }
    return *this;
}

int Entity::operator==(const Entity& right)
{
    if (this->name == right.name )
        return 1;
    return 0;
}

int Entity::operator!=(const Entity& right)
{
    return !( *this == right );
}

#pragma endregion

