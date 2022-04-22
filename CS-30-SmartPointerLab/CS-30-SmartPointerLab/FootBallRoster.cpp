//
//  FootBallRoster.cpp
//  CS-30-SmartPointerLab
//
//  Created by Shawn Davidson on 4/21/22.
//

#include "FootBallRoster.hpp"
#include "LinkedList.hpp"

// Default Constructor
FootBallPlayer::FootBallPlayer()
: name(), num(0)
{
}

// Constructor
FootBallPlayer::FootBallPlayer(string name, int num)
: name(name), num(num)
{
}

// assignment operator
FootBallPlayer& FootBallPlayer::operator=(const FootBallPlayer& rhs) {
    if (this == &rhs)
        return *this;
    
    name    = rhs.name;
    num     = rhs.num;
    
    return *this;
}

// equality operator
bool FootBallPlayer::operator==(const FootBallPlayer& rhs) const {
    if (this == &rhs)
        return true;
    
    return name == rhs.name && num == rhs.num;
}

// in-equality operator
bool FootBallPlayer::operator!=(const FootBallPlayer& rhs) const {
    return !operator==(rhs);
}

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
    FootBallPlayer player;
    
    if (m_pList->findItem(player, [name](const FootBallPlayer& player) {
        return player.name == name;
    })) {
        m_pList->deleteItem(player);
    }
    
    // Reset the favorite if it was the deleted player
    if (m_pFavoritePlayer && m_pFavoritePlayer->name == player.name)
        m_pFavoritePlayer.reset();
    
    return false;
}

// Uses a weak_ptr to return true if the
bool FootBallRoster::setFavorite(string name) {
    // TODO
    FootBallPlayer player;
    
    if (m_pList->findItem(player, [name](const FootBallPlayer& player) {
        return player.name == name;
    })) {
        m_pFavoritePlayer = make_shared<FootBallPlayer>();
        *m_pFavoritePlayer = player;
    }
    
    return false;
}

// Returns an optional parameter if there is a favorite player
std::optional<FootBallPlayer> FootBallRoster::getFavorite() const {
    if (m_pFavoritePlayer)
        return *m_pFavoritePlayer;
    
    return {};
}

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
    std::optional<FootBallPlayer> favoritePlayer =
        roster.getFavorite();
    
    if (favoritePlayer.has_value())
        cout << "Your favorite player is: " << favoritePlayer.value();
    else
        cout << "You don't have a favorite player";
    
    cout << endl;
}
