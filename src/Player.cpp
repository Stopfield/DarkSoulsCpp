#include "Player.h"

uint Player::numPlayers = 0;
const size_t Player::NAME_MAX_SIZE = 20;
const size_t Player::ITEM_MAX_STACK = 99;
const size_t Player::INVENTORY_MIN_SIZE = 5;
const float Player::INVENTORY_REALLOC_RATE = 1.5f;

Player::Player()
    : name("Empty Player"),
    health(100.0f), stamina(100.0), strength(15.0f),
    equipedWeapon(0)
{
    // Cria um inventário com o tamanho mínimo!
    this->inventory = new pair<Item, short> [Player::INVENTORY_MIN_SIZE];
    Player::numPlayers++;
}

Player::Player( string name, double health, double stamina, double strength )
{
    this->setName(name);
    this->setHealth(health);
    this->setStamina(stamina);
    this->setStrenght(strength);
    this->inventory = new pair<Item, short> [Player::INVENTORY_MIN_SIZE];
    Player::numPlayers++;
}

Player::Player( const Player& other )
{
    this->name = other.name;
    this->health = other.health;
    this->stamina = other.stamina;
    this->strength = other.strength;
    this->position = other.position;
    this->equipedWeapon = copyWeapon(other.equipedWeapon);

    this->inventory = copyInventory(other.inventory, other.inventorySize);
    this->inventorySize = other.inventorySize;
    this->inventoryIndex = other.inventoryIndex;
    
    Player::numPlayers++;
}

Player::~Player()
{
    Player::numPlayers--;
    // Destrói o inventário
    delete [] this->inventory;
    delete this->equipedWeapon;
}

/* Ataca um inimigo */
void Player::attack( Enemy& enemy ) const
{
    if (this->equipedWeapon == 0)
    {
        cout << "You have no weapon!\n";
        return;
    }

    string bodyPart = Enemy::chooseBodyPart();

    double damage = 0.0f;
    // O certo seria usar enums - string mágica
    if (bodyPart == "Back" || bodyPart == "Head")
        // Dobro de dano
        damage = this->equipedWeapon->inflictDamage(enemy.getHealth() / 2);

    else
        damage = this->equipedWeapon->inflictDamage(enemy.getHealth());
    
    enemy.setHealth(damage);
}

/* Entra ou sai da postura de defesa */
void Player::guard()
{
    if (!isGuarding())
        cout << "Personagem entra em postura de defesa! Perde velocidade!\n";
    else
        cout << "Personagem sai da postura de defesa! Velocidade normal\n";
    this->guarding = !this->guarding;
}

/**
 * @brief Pega um item do chão
 * @param item Item para ser adicionado ao inventário
*/
void Player::grabItem(Item& item)
{   
    // Se o tamanho for menor
    if (inventoryIndex == inventorySize - 1)
    {
        allocateInventorySpace();
    }

    // Vamos só até o índice já utilizado! Sabemos que não tem mais nada depois!
    for (size_t i = 0; i < this->inventoryIndex; ++i)
    {
        if (this->inventory[i].first.getName() == item.getName())
        {
            if (this->inventory[i].second >= Player::ITEM_MAX_STACK)
                return;
            this->inventory[i].second++;
            return;
        }
    }

    inventory[inventoryIndex++] = std::make_pair( item, (short) 1);
}

/**
 * @brief Consome um item do inventário.
 * @param item Item a ser consumido
*/
void Player::useItem(Item& item)
{
    // Vamos só até o índice já utilizado! Sabemos que não tem mais nada depois!
    for (size_t i = 0; i < this->inventoryIndex; ++i)
    {
        if (this->inventory[i].first.getName() == item.getName())
        {
            if (this->inventory[i].second <= 0)
                return;
            
            this->inventory[i].second--;
            this->setHealth(
                this->getHealth() + this->inventory[i].first.getHealQuantity()
            );
            return;
        }
    }  
}

/**
 * Equipa uma arma
 * @param weapon Arma a ser equipada - pegue da base de dados
*/
void Player::equipWeapon(Weapon &weapon)
{
    cout << "Personagem equipa " << weapon.getName() << "\n";
    this->equipedWeapon = new Weapon(weapon);
}

/**
 * @brief Ataca um inimigo até um dos dois cair.
 * @returns Bool - True == Vitória e false == Derrota
*/
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

/* Placeholder */
void Player::move()
{
    if (isGuarding())
    {
        // Velocidade reduzida
        this->position += this->velocity / 2;
        return;
    }
    this->position += this->velocity;
}

/**
 * @brief Printa o inventário do player
*/
void Player::showInventory()
{
    cout << "===" << this->getName() << " 's Inventory ===\n";
    cout << "(Size: " << inventorySize << ")\n";
    for (size_t i = 0; i < this->inventorySize; ++i)
    {
        cout << this->inventory[i].first.getName() << "\t" << this->inventory[i].second << "\n";
    }
    cout << "================================\n";
}


/**
 * @brief Aloca mais espaço para o inventário.
 * 
 * Veja INVENTORY_REALLOC_RATE para a taxa de crescimento do vetor.
 * 
 * Cria um novo vetor na Heap para o inventário, repassa os valores
 * do inventário para o novo espaço e, por fim, retorna o endereço
 * desse novo espaço para o atributo da classe.
 * */
void Player::allocateInventorySpace()
{
    size_t newSize = size_t(inventorySize * INVENTORY_REALLOC_RATE);
    cout << "Realloc to new size: " << newSize << "\n";
    pair<Item, short>* newInventory = new pair<Item, short> [newSize];

    // Passa os itens de um para o outro
    for (size_t i = 0; i < inventorySize; ++i)
        newInventory[i] = inventory[i];

    delete [] inventory;
    
    inventory = newInventory;
    inventorySize = newSize;
    // Realocado!
    cout << "Realocado!\n";
}

/**
 * Aloca espaço e copia o conteúdo de um inventário para outro.
 * @param otherInventory Inventário a ser copiado
 * @param size Tamanho do inventário a ser copiado
 * @return O ponteiro para o espaço alocado
*/
std::pair<Item, short>* Player::copyInventory(std::pair<Item, short>* otherInventory, size_t size)
{
    std::pair<Item, short>* newInventory = new std::pair<Item, short> [size] ;
    cout << "size: " << size << "\n";
    for (size_t i = 0; i < size; ++i)
        newInventory[i] = otherInventory[i];
    return newInventory;
}

/**
 * Aloca memório na Heap e copia a arma de um Player para o outro.
 * @param otherWeapon Arma do outro player
 * @returns Ponteiro da memória alocada no Heap
*/
Weapon* Player::copyWeapon(const Weapon* otherWeapon )
{
    if (otherWeapon == 0)
        return 0;
    Weapon* newWeapon = new Weapon(*otherWeapon);
    return newWeapon;
}

#pragma region Sets/Gets

void Player::setName(string name)
{
    /* Names can't be empty */
    if (name.empty())
    {
        cout << "Player name can't be empty! Defaulting to \"Empty Player\"\n";
        this->name = "Empty Player";
        return;
    }

    /* Names can't be too long */
    if (name.size() > Player::NAME_MAX_SIZE)
    {
        string substr_name = name.substr(0, Player::NAME_MAX_SIZE);
        cout << "Player name can't be more than "
             << NAME_MAX_SIZE << " chars long! "
             << "Getting " << substr_name << " substring!\n";

        this->name = substr_name;
        return;
    }

    this->name = name;
}

void Player::setHealth( double health )
{
    /* Health can't be negative */
    if (health < 0)
    {
        cout << "Health can't be negative! Defaulting to 0!\n";
        this->health = 0;
        return;
    }
    this->health = health;
}

void Player::setStrenght( double strength )
{
    /* Strength can't be negative */
    if (strength < 0)
    {
        cout << "Strength can't be negative! Defaulting to 0!\n";
        this->strength = 0;
        return;
    }
    this->strength = strength;
}

void Player::setVelocity(double velocity)
{
    if (velocity < 0.0f)
    {
        cout << "Velocidade não pode ser menor que zero\n";
        this->velocity = 0.0f;
        return;
    }

    if (velocity > 100.0f)
    {
        cout << "Velocidade não pode ser maior que cem\n";
        this->velocity = 100.0f;
        return;
    }

    this->velocity = velocity;
}

void Player::setStamina( double stamina )
{
    /* Stamina can't be negative */
    if (stamina < 0)
    {
        cout << "Stamina can't be negative! Defaulting to 0!\n";
        this->stamina = 0;
        return;
    }
    this->stamina = stamina;
}

#pragma endregion