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

#pragma region OperatorOverloads

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

        this->setBodyParts( other.bodyParts );
        if (this->equiped_weapon_ptr != 0)
            delete equiped_weapon_ptr;
        this->copyWeapon( other.equiped_weapon_ptr );
        this->copyInventory( other.inventory_ptr );
    }

    return *this;
}

int Entity::operator== (const Entity& right )
{
    return ( GameObject::operator==(right) && this->name == right.name );
}

int Entity::operator!= (const Entity& right )
{
    return !( *this == right );
}

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

#pragma endregion