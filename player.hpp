#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
	Side aiSide;
	Side opponentSide;
	//int searchDepth;
	//Side startSide;

    Player(Side side);
    ~Player();
    Board *board;

    int minimax(Board *node, int depth, Side side);
    Move *minimax(Board *node, int depth, bool maximizingPlayer);
    

    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
