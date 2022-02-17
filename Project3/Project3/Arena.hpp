//
//  Arena.hpp
//  Project3
//
//  Created by Shawn Davidson on 10/4/21.
//

#ifndef Arena_hpp
#define Arena_hpp

#include <iostream>
#include "globals.h"
#include "History.hpp"

class Player;
class Robot;
class History;

class Arena
{
  public:
        // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();

    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     robotCount() const;
    int     nRobotsAt(int r, int c) const;
    void    display(std::string msg) const;

    History& history();

    // Mutators
    bool   addRobot(int r, int c);
    bool   addPlayer(int r, int c);
    void   damageRobotAt(int r, int c);
    bool   moveRobots();

  private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Robot*  m_robots[MAXROBOTS];
    int     m_nRobots;
    
    History m_history;
};



#endif /* Arena_hpp */
