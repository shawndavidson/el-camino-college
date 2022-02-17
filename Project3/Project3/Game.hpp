//
//  Game.hpp
//  Project3
//
//  Created by Shawn Davidson on 10/4/21.
//

#ifndef Game_hpp
#define Game_hpp

class Arena;

class Game
{
  public:
        // Constructor/destructor
    Game(int rows, int cols, int nRobots);
    ~Game();

        // Mutators
    void play();

  private:
    Arena* m_arena;
};

#endif /* Game_hpp */
