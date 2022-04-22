//
//  FootBallRoster.hpp
//  CS-30-SmartPointerLab
//
//  Created by Shawn Davidson on 4/21/22.
//

#ifndef FootBallRoster_hpp
#define FootBallRoster_hpp

#include <memory>
#include <iostream>
#include <string>
#include <optional>

using namespace std;

// Forward declaration -
// avoids circular dependency since LinkedList needs to include FootBallRoster.hpp (needs FootBallPlayer definition)
class LinkedList;

struct FootBallPlayer {
    string name;
    int num;
    
    // Default Constructor
    FootBallPlayer();
    // Constructor
    FootBallPlayer(string name, int num);
    
    // Destructor
    ~FootBallPlayer() = default;
    
    // assignment operator
    FootBallPlayer& operator=(const FootBallPlayer& rhs);
    
    // equality operator
    bool operator==(const FootBallPlayer& rhs) const;
    
    // in-equality operator
    bool operator!=(const FootBallPlayer& rhs) const;
};



class FootBallRoster {
public:
    // Default Constructor
    FootBallRoster();
    
     // Adds a FootBallPlayer to the roster.
    void addPlayer(FootBallPlayer player);
    
     // deletes the first FootBallPlayer that matches name
    bool deletePlayer(string name);
    
     // Uses a weak_ptr to return true if the
    bool setFavorite(string name);
    
     // Returns an optional parameter if there is a favorite player
    std::optional<FootBallPlayer> getFavorite() const;

     // Prints the list of FootBallPlayers on the roster
    void printPlayers() const;
    
    // Equality Operator 
    bool operator==(const FootBallRoster& rhs) const;
    
private:
    shared_ptr<LinkedList>      m_pList;
    shared_ptr<FootBallPlayer>  m_pFavoritePlayer;
};

 // prints out the name of the favorite player or a message
 // stating there is no favorite player.
void favoritePlayer(const FootBallRoster& roster);

#endif /* FootBallRoster_hpp */
