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