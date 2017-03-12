#include "player.hpp"

#include <iostream>
using namespace std;

// This is the file for player

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
//this is a test comment
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
     aiSide = side;
     if (side == WHITE)
     {
        opponentSide = BLACK;
     }
     else
     {
        opponentSide = WHITE;
     }




     board = new Board();

}

/*
 * Destructor for the player.
 */
Player::~Player() {
    delete board;
}



int Player::minimax(Board *node, int depth, Side side) {

    if (depth == 0)
    {
        return node->score(aiSide);
    }

    if (side == aiSide) //maximizing player
    {
        int bestVal = -9999; // initialize to low score
        int temp = 0; // holds score resulting from the potential move
        for (int i = 0; i < 8; i++) { // loop through rows and columns
            for (int j = 0; j < 8; j++) {
                Move prospectiveMove(i, j); // declare possible move to make
                if (node->checkMove(&prospectiveMove, aiSide)) // enter loop to see if this move is valid
                {
                    Board *tempBoard = node->copy(); // Create a temporary game board 
                    tempBoard->doMove(&prospectiveMove, aiSide); // and make the possible move

                    if ((temp = minimax(tempBoard, depth - 1, opponentSide)) > bestVal) // keep checking board scores after making another move until depth is 0
                    // get score and compare with previous best score
                    {
                        bestVal = temp; // set new bestVal if score from move is greater than previous bestVal
                    }

                    delete tempBoard;
                }
            }
        }

        if (bestVal != -9999) // if no prospective moves possible  
        {
            return bestVal;
        }
    }
    else //minimizing player (opponent)
    {//opponent tries to minimize player's score when it's their turn

        int bestVal = 9999;
        int temp = 0;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Move prospectiveMove(i, j);
                if (node->checkMove(&prospectiveMove, opponentSide)) 
                {
                    Board *tempBoard = node->copy();
                    tempBoard->doMove(&prospectiveMove, opponentSide);

                    if ((temp = minimax(tempBoard, depth - 1, aiSide)) < bestVal)
                    {
                        bestVal = temp; // player's minimized score due to opponent
                    }

                    delete tempBoard;
                }
            }
        }

        if (bestVal != 9999)
        {
            return bestVal;
        }
    }

    return node->score(aiSide);
}





/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */

    board->doMove(opponentsMove, opponentSide);

    int searchDepth = 4;

    int bestScore = -9999;
    int temp = 0;
    Move *bestMove = nullptr;

    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move *move = new Move(i, j); //might need to deallocate this

            if (board->checkMove(move, aiSide)) 
            {
                Board *boardCopy = board->copy();
                boardCopy->doMove(move, aiSide);

                if ((temp = minimax(boardCopy, searchDepth, opponentSide)) > bestScore)
                {
                    bestScore = temp;
                    bestMove = move;
                }
                delete boardCopy;
            }
        }
    }


    board->doMove(bestMove, aiSide);
    return bestMove;


}
