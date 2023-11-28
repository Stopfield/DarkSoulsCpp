#ifndef GAME_H
#define GAME_H

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <map>

using std::vector;
using std::string;
using std::map;
using std::cout;
using std::stod;

#include "Player.h"
#include "Enemy.h"
#include "Attack.h"
#include "Weapon.h"
#include "Data.h"

enum LoadState 
{
    PLAYER,         END_PLAYER,
    INVENTORY,      END_INVENTORY,
    INVENTORY_ITEM, END_INVENTORY_ITEM
};

enum PlayerAttributes
{
    NAME,
    MAX_HEALTH, HEALTH,
    STAMINA,    STRENGTH,
    DEXTERITY,  EQUIPPED_WEAPON,
    DATE // Placeholder
};

class Game
{
    friend ostream& operator<<  ( ostream&, const Game& );
    friend int      operator!   (const Game& );
public:
    Game    (  );
    Game    ( const string );
    Game    ( const Game& );
    ~Game   (  );

    void initGame   (  );
    void mainLoop   (  );
    void input      (  );

    inline const Player *const getPlayerPtr()   { return this->playerPtr;   }
    inline const Data   *const getGameDate()    { return this->gameDatePtr; }

    const Game& operator= ( const Game& );
    int operator== ( const Game& );
    int operator!= ( const Game& );

private:
    void loadGame       ( const string );
    void loadEnemies    (  );
    void loadAttacks    (  );
    void loadWeapons    (  );

    void parsePlayerFile    ( std::ifstream& );
    void parseDate          ( string );

    static map< PlayerAttributes, string >  player_ParserMatches;
    static map< LoadState, string >         loadState_ParserMatches;

    static string saveDirectoryPath;
    static string defaultSaveFilePath;

    Data*               gameDatePtr;
    Player*             playerPtr;
    vector< Enemy* >    loadedEntitiesPtr;
    string*             loadedAreaPtr;

    vector< Enemy* >    enemyDatabase;
    vector< Attack* >   attackDatabase;
    vector< Weapon* >   weaponDatabase;

};

#endif // GAME_H