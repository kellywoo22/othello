#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <unordered_map>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
	Side aiSide;
	Side opponentSide;
    //unordered_map<Board*, Board*> transpositionTable;

    int turn;

    Player(Side side);
    ~Player();
    Board *board;

    int minimax(Board *node, int depth, Side side);
    int negamax_ab(Board *node, int depth, int alpha, int beta, Side side);
    

    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
