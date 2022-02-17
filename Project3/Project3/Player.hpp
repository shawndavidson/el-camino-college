//
//  Player.hpp
//  Project3
//
//  Created by Shawn Davidson on 10/4/21.
//

#ifndef Player_hpp
#define Player_hpp

#include <string>

class Arena;

class Player
{
  public:
    // Constructor
    Player(Arena *ap, int r, int c);

    // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    bool isDead() const;
    
    // Mutators
    std::string takeComputerChosenTurn();
    void   stand();
    void   move(int dir);
    bool   shoot(int dir);
    void   setDead();

    ////////////////////////////////////////
    // New Methods -
  private:
    double computeDanger(int row, int col) const;
    int    getDirectionOfNearestRobot(int row, int col, int& distance) const;
    bool   computeRowCol(int &r, int &c, int dir) const;

    // New Methods -
    ////////////////////////////////////////

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_age;
    bool   m_dead;
};

#endif /* Player_hpp */
