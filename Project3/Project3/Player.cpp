//
//  Player.cpp
//  Project3
//
//  Created by Shawn Davidson on 10/4/21.
//

#include <iostream>
#include <algorithm>    // new
#include <math.h>       // new
#include <limits>       // new
#include "Player.hpp"
#include "Arena.hpp"
#include "globals.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

Player::Player(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** The player must be in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
             << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_dead = false;
}

int Player::row() const
{
    return m_row;
}

int Player::col() const
{
    return m_col;
}

int Player::age() const
{
    return m_age;
}

bool Player::computeRowCol(int &r, int &c, int dir) const {
    r = m_row;
    c = m_col;
    
    switch (dir)
    {
        case UP:
            if (r > 1)
                r--;
            else
                return false;
            break;
        case DOWN:
            if (r < m_arena->rows())
                r++;
            else
                return false;
            break;
        case LEFT:
            if (c > 1)
                c--;
            else
                return false;
            break;
        case RIGHT:
            if (c < m_arena->cols())
                c++;
            else
                return false;
            break;
    }
    
    return true;
}

string Player::takeComputerChosenTurn()
{
    // Your replacement implementation should do something intelligent
    // and return a string that describes what happened.  When you've
    // decided what action to take, take it by calling move, shoot, or stand.
    // This function must return one of the following four strings:
    //     "Moved."
    //     "Shot and hit!"
    //     "Shot and missed!"
    //     "Stood."

    // Here's one possible strategy:
    //   If moving in some direction would put me in less immediate danger
    //     than standing, then move in that direction.
    //   else shoot in the direction of the nearest robot I can hit.

    // A more aggressive strategy is possible, where you hunt down robots.
    
    // Tracks the danger for the position if we move UP, DOWN, LEFT, or RIGHT
    // The index represents the direction
    struct {
        int     row;
        int     col;
        double  danger;
    } danger[4];
    
    int leastDangerousDir = -1;
    
    // Compute the danger metric for each possible direction we can move
    // and figure out the least dangerous one.
    for (int dir = UP; dir <= RIGHT; dir++) {
        int r, c;
        
        bool valid = computeRowCol(r, c, dir);
        
        danger[dir].row     = r;
        danger[dir].col     = c;
        danger[dir].danger  = valid ? computeDanger(r, c) : std::numeric_limits<double>::max();
        
        if (leastDangerousDir == -1 ||
            danger[dir].danger < danger[leastDangerousDir].danger) {
            leastDangerousDir = dir;
        }
    }
    
    int robotDistance;
    int dirToShoot = getDirectionOfNearestRobot(m_row, m_col, robotDistance);
    
    // If we don't have shot or we're in imminent danger (robot next to us),
    // then consider moving
    if (dirToShoot == -1 || robotDistance < 2) {
        // Is there a move that puts us in a safer position?
        if (computeDanger(m_row, m_col) > danger[leastDangerousDir].danger) {
            move(leastDangerousDir);
            return "Moved.";
        }
        
        stand();
        return "Stood.";
    }
    
    // Take the shot
    if (shoot(dirToShoot))
        return "Shot and hit!";

    return "Shot and missed!";
}

// Compute a metric for the danger level from this position
// Where a lower value is safer, higher is more dangerous.
double Player::computeDanger(int row, int col) const {
    int distance;
    
    // We can ignore the return value
    getDirectionOfNearestRobot(row, col, distance);
    
    int dangerLevel = 100.0 / pow(distance, 2.0);

    return dangerLevel;
}

// Gets the direction of the nearest robot within shooting range
// Returns -1 if we don't have a shot. It also sets distance to
// the distance ofthe nearest robot is.
int Player::getDirectionOfNearestRobot(int row, int col, int& distance) const {
    int dir = -1;
    
    // Iterate outward in concentric circles with regards to distance
    // from our current position to check if there is a robot within shooting
    // range position.
    // Actually, we only check along the horizontal and vertical axis of our
    // current player because we can't shoot on a diagonal.
    int radius = 1;
    
    while (radius <= MAXSHOTLEN && dir == -1) {
        // Look up, if within bounds
        if (row - radius >= 1) {
            if ( m_arena->nRobotsAt(row - radius, col) > 0) {
                dir = UP;
                continue;
            }
        }
        
        if (row + radius <= m_arena->rows()) {
            if (m_arena->nRobotsAt(row + radius, col) > 0) {
                dir = DOWN;
                continue;
            }
        }
        
        if (col - radius >= 1) {
            if (m_arena->nRobotsAt(row, col - radius) > 0) {
                dir = LEFT;
                continue;
            }
        }
        
        if (col + radius <= m_arena->cols()) {
            if (m_arena->nRobotsAt(row, col + radius) > 0) {
                dir = RIGHT;
                continue;
            }
        }
        radius++;
    }
        
    // If we found a robot, return the distance via call by reference
    if (dir != -1)
        distance = radius;
        
    return dir;
}

void Player::stand()
{
    m_age++;
    m_arena->history().record(m_row, m_col);
}

void Player::move(int dir)
{
    m_age++;
    switch (dir)
    {
        case UP:
          if (m_row > 1)
              m_row--;
          break;
        case DOWN:
          if (m_row < m_arena->rows())
              m_row++;
          break;
        case LEFT:
          if (m_col > 1)
              m_col--;
          break;
        case RIGHT:
          if (m_col < m_arena->cols())
              m_col++;
          break;
    }
    
    m_arena->history().record(m_row, m_col);
}

bool Player::shoot(int dir)
{
    m_age++;

    if (rand() % 3 == 0)  // miss with 1/3 probability
        return false;

    switch(dir) {
        case UP: {
            int newRow = std::max(1, m_row - MAXSHOTLEN);
            
            for (int r = m_row-1; r >= newRow; r--) {
                if (m_arena->nRobotsAt(r, m_col) > 0) {
                    m_arena->damageRobotAt(r, m_col);
                    return true;
                }
            }
            break;
        }
        case DOWN: {
            int newRow = std::min(m_arena->rows(), m_row + MAXSHOTLEN);
            
            for (int r = m_row+1; r <= newRow; r++) {
                if (m_arena->nRobotsAt(r, m_col) > 0) {
                    m_arena->damageRobotAt(r, m_col);
                    return true;
                }
            }
            break;
        }
        case LEFT: {
            int newCol = std::max(1, m_col - MAXSHOTLEN);
            
            for (int c = m_col-1; c >= newCol; c--) {
                if (m_arena->nRobotsAt(m_row, c) > 0) {
                    m_arena->damageRobotAt(m_row, c);
                    return true;
                }
            }
            break;
        }
        case RIGHT: {
            int newCol = std::min(m_arena->cols(), m_col + MAXSHOTLEN);
            
            for (int c = m_col+1; c <= newCol; c++) {
                if (m_arena->nRobotsAt(m_row, c) > 0) {
                    m_arena->damageRobotAt(m_row, c);
                    return true;
                }
            }
            break;
        }
    }
    
    return false;  
}

bool Player::isDead() const
{
    return m_dead;
}

void Player::setDead()
{
    m_dead = true;
}

