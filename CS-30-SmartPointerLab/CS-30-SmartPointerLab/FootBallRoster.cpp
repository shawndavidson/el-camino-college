//
//  FootBallRoster.cpp
//  CS-30-SmartPointerLab
//
//  Created by Shawn Davidson on 4/21/22.
//

#include "FootBallRoster.hpp"
#include "LinkedList.hpp"


// Default Constructor
FootBallRoster::FootBallRoster()
: m_pList(make_shared<LinkedList>()) {
}

// Adds a FootBallPlayer to the roster.
void FootBallRoster::addPlayer(FootBallPlayer player) {
    m_pList->insertToFront(player);
}

// deletes the first FootBallPlayer that matches name
bool FootBallRoster::deletePlayer(string name) {
    // TODO
    return false;
}

// Uses a weak_ptr to return true if the
bool FootBallRoster::setFavorite(string name) {
    // TODO
    return false;
}

// Returns an optional parameter if there is a favorite player
//std::optional<FootBallPlayer> FootBallRoster::getFavorite() const {
//
//}

// Prints the list of FootBallPlayers on the roster
void FootBallRoster::printPlayers() const {
    m_pList->printList(cout);
}

// Assignment Operator
bool FootBallRoster::operator==(const FootBallRoster& rhs) const {
    if (this == &rhs)
        return true;
    
    return (*m_pList) == (*rhs.m_pList);
}

void favoritePlayer(const FootBallRoster& roster) {
    // TODO
}
