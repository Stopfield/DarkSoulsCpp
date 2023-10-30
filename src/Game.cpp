#include "Game.h"

/* String matches para Atributos do jogador */
map< PlayerAttributes, string > Game::player_ParserMatches = {
    { NAME,             "name"              },
    { HEALTH,           "health"            },
    { MAX_HEALTH,       "max_health"        },
    { STAMINA,          "stamina"           },
    { STRENGTH,         "strength"          },
    { DEXTERITY,        "dexterity"         },
    { EQUIPPED_WEAPON,  "equipped_weapon"   },
    { DATE,             "date"              }   // Placeholder
};

/* String Matches para LoadState */
map< LoadState, string > Game::loadState_ParserMatches = {
    { PLAYER,               "[PLAYER]"              },
    { END_PLAYER,           "[END_PLAYER]"          },
    { INVENTORY,            "[INVENTORY]"           },
    { END_INVENTORY,        "[END_INVENTORY]"       },
    { INVENTORY_ITEM,       "[INVENTORY_ITEM]"      },
    { END_INVENTORY_ITEM,   "[END_INVENTORY_ITEM]"  }
};

string Game::saveDirectoryPath = "../";

// TODO - Input save file
string Game::defaultSaveFilePath = "../save.sav";

Game::Game( )
{
    this->loadGame( Game::defaultSaveFilePath );
}

Game::Game( const string saveFilePath )
{
    this->loadGame( saveFilePath );
}

Game::Game( const Game& other )
{
    this->playerPtr = new Player( *other.playerPtr );
    this->gameDatePtr = new Data( *other.gameDatePtr );
    // TODO - Copy vectors
}

Game::~Game( )
{
    if (this->playerPtr)
        delete this->playerPtr;
    if (this->gameDatePtr)
        delete this->gameDatePtr;
    // if (this->loadedAreaPtr)
    //     delete this->loadedAreaPtr;
    
    // TODO - Delete vectors
}

void Game::initGame()
{
}

void Game::mainLoop()
{
}

void Game::input()
{
}

/**
 * Carrega um salvamento anterior. Faz o parse do arquivo e
 * cria um objeto Player novo.
 * @param saveFilePath Caminho do arquivo .sav para ser carregado.
*/
void Game::loadGame( const string saveFilePath )
{
    // TODO - Load Weapon files, Attack files and Enemy files.

    // Parse player file
    string first_line;
    std::ifstream loadedFile ( saveFilePath );
    
    if ( !loadedFile.is_open() )
    {
        std::cerr << "ERROR LOADING SAVE FILE! Couldn't open \""
            << saveFilePath << "\".\n";
        exit( EXIT_FAILURE );
    }

    loadedFile >> first_line;
    if ( first_line == Game::loadState_ParserMatches[ LoadState::PLAYER ])
        this->parsePlayerFile( loadedFile );
}

/**
 * Parse the player file and creates a new Player object.
 * Uses the static maps and associated enums to do so.
 * This is a line example "attribute=value", named "key=value"
 * for convenience.
 * @param input Input stream for the file.
*/
void Game::parsePlayerFile( std::ifstream& input_stream )
{
    string entire_line, line_value, line_key;
    size_t equal_sign_index;

    this->playerPtr = new Player();

    while (true)
    {
        input_stream >> entire_line;

        // If [END_PLAYER], stop parsing.
        if (entire_line == Game::loadState_ParserMatches[ END_PLAYER ])
            break;

        equal_sign_index = entire_line.find( '=' );

        line_key     = entire_line.substr( 0, equal_sign_index );
        line_value   = entire_line.substr( equal_sign_index + 1, entire_line.size() );
        
        if (line_key == player_ParserMatches[ NAME ])
        {
            this->playerPtr->setName( line_value );
            continue;
        }
        if (line_key == player_ParserMatches[ HEALTH ])
        {
            this->playerPtr->setHealth( stod( line_value ) );
            continue;
        }
        if (line_key == player_ParserMatches[ MAX_HEALTH ])
        {
            this->playerPtr->setMaxHealth( stod( line_value ) );
            continue;
        }
        if (line_key == player_ParserMatches[ STAMINA ])
        {
            this->playerPtr->setStamina( stod( line_value ) );
            continue;
        }
        if (line_key == player_ParserMatches[ STRENGTH ])
        {
            this->playerPtr->setStrength( stod( line_value ) );
            continue;
        }
        if (line_key == player_ParserMatches[ DEXTERITY ])
        {
            this->playerPtr->setDexterity( stod( line_value ) );
            continue;
        }
        if (line_key == player_ParserMatches[ DATE ])
        {
            this->parseDate( line_value );
            continue;
        }
        // WIP
        // if (line_key == player_ParserMatches[ EQUIPPED_WEAPON ])
        // {
        //     this->playerPtr->equipped_weapon = line_value;
        //     continue;
        // }
    }
}

/**
 * Parses date from save file.
 * @line Line with key value
*/
void Game::parseDate( string line )
{
    int* date = new int[ 3 ] { 0 };
    size_t slash_sign_index = 0;
    size_t current_index = 0;
    string key = line;

    for ( size_t i = 0; i < 2; i++ )
    {
        slash_sign_index = key.find( '/' );
        date[ i ] = std::stoi( key.substr( 0, slash_sign_index ) );
        key = key.substr( slash_sign_index + 1, key.size() );
    }
    date[ 2 ] =  std::stoi( key );
    this->gameDatePtr = new Data( date[0], date[1], date[2] );
}

void Game::loadEnemies()
{
}

void Game::loadAttacks()
{
}

void Game::loadWeapons()
{
}

#pragma region Operator Overloads

ostream& operator<< ( ostream& output, const Game& right )
{
    output << "Game running!\n";
    output << "Player: " << *right.playerPtr << "\n";
    output << "Data: " << *right.gameDatePtr << "\n";
    return output;
}

int operator! ( const Game& right)
{
    return ( ! *right.playerPtr );
}

const Game& Game::operator= ( const Game& right )
{
    if ( this != &right )
    {
        if (right.playerPtr)
            this->playerPtr = new Player( *right.playerPtr );
        if (right.gameDatePtr)
            this->gameDatePtr = new Data( *right.gameDatePtr );
    }
    return *this;
}

int Game::operator== ( const Game& right )
{
    if (*right.playerPtr == *this->playerPtr && *this->gameDatePtr == *right.gameDatePtr )
        return 1;
    return 0;
}

int Game::operator!= ( const Game& right )
{
    return !( *this == right );
}

#pragma endregion