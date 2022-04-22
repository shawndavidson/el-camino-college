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
//#include "LinkedList.hpp"

using namespace std;

struct FootBallPlayer {
    string name;
    int num;
    
    // Constructor
    FootBallPlayer() : name(), num(0) {}
    
    // Destructor
    ~FootBallPlayer() = default;
    
    // assignment operator
    FootBallPlayer& operator=(const FootBallPlayer& rhs) {
        if (this == &rhs)
            return *this;
        
        name    = rhs.name;
        num     = rhs.num;
        
        return *this;
    }
    
    // equality operator
    bool operator==(const FootBallPlayer& rhs) const noexcept {
        if (this == &rhs)
            return true;
        
        return name == rhs.name && num == rhs.num;
    }
    
    // in-equality operator
    bool operator!=(const FootBallPlayer& rhs) const noexcept {
        return !operator==(rhs);
    }
};

// Forward declaration
class LinkedList;

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
    
    bool operator==(const FootBallRoster& rhs) const;
    
private:
    shared_ptr<LinkedList> m_pList;
};

 // prints out the name of the favorite player or a message
 // stating there is no favorite player.
void favoritePlayer(const FootBallRoster& roster);

#endif /* FootBallRoster_hpp */
