//
//  main.cpp
//  CS2-Homework4.3
//
//  Created by Shawn Davidson on 11/7/21.
//

#include <iostream>
#include <math.h>

using namespace std;

#define GUESS_TOO_LOW   -1
#define GUESS_TOO_HIGH   1
#define GUESS_CORRECT    0

const int MAXGUESS = 1000;  // range is [0,MAXGUESS]


// Polymorphic classes

class Player {
public:
    Player() {}
    virtual ~Player() {}
    
    virtual int getGuess() const = 0;
    
    static void setLowGuess(int low) {
        Player::lowGuess = max(low, Player::lowGuess);
    }
    
    static void setHighGuess(int high) {
        Player::highGuess = min(high, Player::highGuess);
    }
    
protected:
    static int lowGuess;
    static int highGuess;
};

int Player::lowGuess    = 0;
int Player::highGuess   = MAXGUESS;

class HumanPlayer : public Player {
public:
    HumanPlayer() {};
    
    virtual int getGuess() const {
        int guess;
        
        cout << endl;
        cout << "Please enter a number for your guess: ";
        cin >> guess;
        
        return guess;
    }
};

class ComputerPlayer : public Player {
public:
    ComputerPlayer() {}
    
    virtual int getGuess() const {
        int guess = rand() % (MAXGUESS + 1);

        cout << endl;
        cout << "The computer's guess was " << guess << endl;
        
        return guess;
    }
};

class SmartComputerPlayer : public ComputerPlayer {
public:
    SmartComputerPlayer() {}
    
    virtual int getGuess() const {
        // Kludgy! If the answer is 0 and we only take the ceiling of the middle value (lowGuess+highGuess)/2.0 we
        // won't find it so alternate between taking the ceiling and the floor
        int guess = rand() % 2 == 0 ? ceil((lowGuess + highGuess) / 2.0) : floor((lowGuess + highGuess) / 2.0);
        
        cout << endl;
        cout << "The Smart Computer's guess was " << guess << endl;
        
        return guess;
    }

};


// Check for a win. You win if the guess matches the answer.
// Returns 0 if it's a win, -1 if you're too low, and 1 if you're too high
int checkForWin (int guess, int answer) {
    if (answer == guess) {
        cout << "You're right! You win!" << endl;
        return GUESS_CORRECT;
    }
    else if (answer < guess) {
        cout << "Your guess is too high." << endl;
        return GUESS_TOO_HIGH;
    }
    else
        cout << "Your guess is too low." << endl;
    return  GUESS_TOO_LOW;
}

int play(Player &player1, Player &player2) {  // do not change this line
    // change anything you like below this line
    int answer = 0, guess = 0;
    int numGuesses = 0;
    // TODO: Is this a bug in the homework? It looks like answer will lie within [1, MAXGUESS] instead of [0, MAXGUESS].
    answer = rand() % MAXGUESS + 1;
    
    // missing from sample code at:
    // https://elcamino.instructure.com/courses/23253/pages/homework-4-guess-dot-cpp
    int win = GUESS_TOO_LOW;
    
    while (win != GUESS_CORRECT) {
        cout << "Player 1's turn to guess." << endl;
        guess = player1.getGuess();
        numGuesses++;
        win = checkForWin(guess, answer);
        if (win == GUESS_CORRECT)
            break;
        else if (win == GUESS_TOO_HIGH)
            player1.setHighGuess(guess);
        else
            player1.setLowGuess(guess);
        
        cout << "\nPlayer 2's turn to guess." << endl;
        guess = player2.getGuess();
        numGuesses++;
        win = checkForWin(guess, answer);
        if (win == GUESS_TOO_HIGH)
            player2.setHighGuess(guess);
        else if (win == GUESS_TOO_LOW)
            player2.setLowGuess(guess);
    }
    return numGuesses;
}

// Create a new player based on the given type
// h or H => Human Player (user)
// c or C => Computer Player (random guesses)
// s or S => smart Computer Player (binary search)
Player* createPlayer(int playerNumber) {
    char type;
    
    cout << "Would you like player #" << playerNumber << " to be a human or computer (H=Human/C=Computer/S=SmartComputer)? ";
    cin >> type;
        
    switch(toupper(type)) {
        case 'H':
            return new HumanPlayer();
        case 'C':
            return new ComputerPlayer();
        case 'S':
            return new SmartComputerPlayer();
        default:
            return nullptr;
    }
}

int main () {
    Player* player1;
    Player* player2;
    
    player1 = createPlayer(1);
    player2 = createPlayer(2);
    
    play(*player1, *player2);
    
    delete player1;
    delete player2;
}
 
