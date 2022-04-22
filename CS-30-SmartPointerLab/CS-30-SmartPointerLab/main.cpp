//
//  main.cpp
//  CS-30-SmartPointerLab
//
//  Created by Shawn Davidson on 4/21/22.
//

#include <iostream>
#include "FootBallRoster.hpp"
#include "LinkedList.hpp"

int main() {

    FootBallPlayer fb1{ "Matthew Stafford", 9 };
    FootBallPlayer fb2{ "Aaron Donald", 99 };
    FootBallPlayer fb3{ "Jalen Ramsey", 5 };

    FootBallRoster roster;

    roster.addPlayer(fb1);
    roster.addPlayer(fb2);
    roster.addPlayer(fb3);

    roster.printPlayers();
    roster.setFavorite("Aaron Donald");

    favoritePlayer(roster);

    roster.deletePlayer("Aaron Donald");
    favoritePlayer(roster);
}
