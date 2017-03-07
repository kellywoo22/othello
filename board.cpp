#include "board.hpp"

/*
 * Make a standard 8x8 othello board and initialize it to the standard setup.
 */
Board::Board() {
    taken.set(3 + 8 * 3);
    taken.set(3 + 8 * 4);
    taken.set(4 + 8 * 3);
    taken.set(4 + 8 * 4);
    black.set(4 + 8 * 3);
    black.set(3 + 8 * 4);
}

/*
 * Destructor for the board.
 */
Board::~Board() {
}

/*
 * Returns a copy of this board.
 */
Board *Board::copy() {
    Board *newBoard = new Board();
    newBoard->black = black;
    newBoard->taken = taken;
    return newBoard;
}

bool Board::occupied(int x, int y) {
    return taken[x + 8*y];
}

bool Board::get(Side side, int x, int y) {
    return occupied(x, y) && (black[x + 8*y] == (side == BLACK));
}

void Board::set(Side side, int x, int y) {
    taken.set(x + 8*y);
    black.set(x + 8*y, side == BLACK);
}

bool Board::onBoard(int x, int y) {
    return(0 <= x && x < 8 && 0 <= y && y < 8);
}


/*
 * Returns true if the game is finished; false otherwise. The game is finished
 * if neither side has a legal move.
 */
bool Board::isDone() {
    return !(hasMoves(BLACK) || hasMoves(WHITE));
}

/*
 * Returns true if there are legal moves for the given side.
 */
bool Board::hasMoves(Side side) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move move(i, j);
            if (checkMove(&move, side)) return true;
        }
    }
    return false;
}

/*
 * Returns true if a move is legal for the given side; false otherwise.
 */
bool Board::checkMove(Move *m, Side side) {
    // Passing is only legal if you have no moves.
    if (m == nullptr) return !hasMoves(side);

    int X = m->getX();
    int Y = m->getY();

    // Make sure the square hasn't already been taken.
    if (occupied(X, Y)) return false;

    Side other = (side == BLACK) ? WHITE : BLACK;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dy == 0 && dx == 0) continue;

            // Is there a capture in that direction?
            int x = X + dx;
            int y = Y + dy;
            if (onBoard(x, y) && get(other, x, y)) {
                do {
                    x += dx;
                    y += dy;
                } while (onBoard(x, y) && get(other, x, y));

                if (onBoard(x, y) && get(side, x, y)) return true;
            }
        }
    }
    return false;
}

/*
 * Modifies the board to reflect the specified move.
 */
void Board::doMove(Move *m, Side side) {
    // A nullptr move means pass.
    if (m == nullptr) return;

    // Ignore if move is invalid.
    if (!checkMove(m, side)) return;

    int X = m->getX();
    int Y = m->getY();
    Side other = (side == BLACK) ? WHITE : BLACK;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dy == 0 && dx == 0) continue;

            int x = X;
            int y = Y;
            do {
                x += dx;
                y += dy;
            } while (onBoard(x, y) && get(other, x, y));

            if (onBoard(x, y) && get(side, x, y)) {
                x = X;
                y = Y;
                x += dx;
                y += dy;
                while (onBoard(x, y) && get(other, x, y)) {
                    set(side, x, y);
                    x += dx;
                    y += dy;
                }
            }
        }
    }
    set(side, X, Y);
}

/*
 * Current count of given side's stones.
 */
int Board::count(Side side) {
    return (side == BLACK) ? countBlack() : countWhite();
}

/*
 * Current count of black stones.
 */
int Board::countBlack() {
    return black.count();
}

/*
 * Current count of white stones.
 */
int Board::countWhite() {
    return taken.count() - black.count();
}

int Board::scoreWhite() {
    int whiteScore = 0;
    int counter = 0;
    int cornerVal = 12;
    int goodSideVal = 7;
    int badSideVal = -7;
    int badAdjCornerVal = -12;
    if (get(WHITE, 0, 0))
    {
        whiteScore += cornerVal;
        counter++;
    }
    if (get(WHITE, 0, 7))
    {
        whiteScore += cornerVal;
        counter++;
    }
    if (get(WHITE, 7, 0))
    {
        whiteScore += cornerVal;
        counter++;
    }
    if (get(WHITE, 7, 7))
    {
        whiteScore += cornerVal;
        counter++;
    }
    if (get(WHITE, 2, 0))
    {
        whiteScore += goodSideVal;
        counter++;
    }
    if (get(WHITE, 3, 0))
    {
        whiteScore += goodSideVal;
        counter++;
    }
    if (get(WHITE, 4, 0))
    {
        whiteScore += goodSideVal;
        counter++;
    }
    if (get(WHITE, 5, 0))
    {
        whiteScore += goodSideVal;
        counter++;
    }
    if (get(WHITE, 0, 2))
    {
        whiteScore += goodSideVal;
        counter++;
    }
    if (get(WHITE, 0, 3))
    {
        whiteScore += goodSideVal;
        counter++;
    }
    if (get(WHITE, 0, 4))
    {
        whiteScore += goodSideVal;
        counter++;
    }
    if (get(WHITE, 0, 5))
    {
        whiteScore += goodSideVal;
        counter++;
    }
    if (get(WHITE, 7, 2))
    {
        whiteScore += goodSideVal;
        counter++;
    }
    if (get(WHITE, 7, 3))
    {
        whiteScore += goodSideVal;
        counter++;
    }
    if (get(WHITE, 7, 4))
    {
        whiteScore += goodSideVal;
        counter++;
    }
    if (get(WHITE, 7, 5))
    {
        whiteScore += goodSideVal;
        counter++;
    }
    if (get(WHITE, 2, 7))
    {
        whiteScore += goodSideVal;
        counter++;
    }
    if (get(WHITE, 3, 7))
    {
        whiteScore += goodSideVal;
        counter++;
    }
    if (get(WHITE, 4, 7))
    {
        whiteScore += goodSideVal;
        counter++;
    }
    if (get(WHITE, 5, 7))
    {
        whiteScore += goodSideVal;
        counter++;
    }
    if (get(WHITE, 0, 1))
    {
        whiteScore += badSideVal;
        counter++;
    }
    if (get(WHITE, 1, 0))
    {
        whiteScore += badSideVal;
        counter++;
    }
    if (get(WHITE, 7, 1))
    {
        whiteScore += badSideVal;
        counter++;
    }
    if (get(WHITE, 6, 0))
    {
        whiteScore += badSideVal;
        counter++;
    }
    if (get(WHITE, 0, 6))
    {
        whiteScore += badSideVal;
        counter++;
    }
    if (get(WHITE, 1, 7))
    {
        whiteScore += badSideVal;
        counter++;
    }
    if (get(WHITE, 7, 6))
    {
        whiteScore += badSideVal;
        counter++;
    }
    if (get(WHITE, 6, 7))
    {
        whiteScore += badSideVal;
        counter++;
    }
    if (get(WHITE, 1, 1))
    {
        whiteScore += badAdjCornerVal;
        counter++;
    }
    if (get(WHITE, 6, 1))
    {
        whiteScore += badAdjCornerVal;
        counter++;
    }
    if (get(WHITE, 1, 6))
    {
        whiteScore += badAdjCornerVal;
        counter++;
    }
    if (get(WHITE, 6, 6))
    {
        whiteScore += badAdjCornerVal;
        counter++;
    }
    whiteScore += (countWhite() - counter);

    return whiteScore;
}


int Board::scoreBlack() {
    int blackScore = 0;
    int counter = 0;
    int cornerVal = 12;
    int goodSideVal = 5;
    int badSideVal = -5;
    int badAdjCornerVal = -12;
    if (get(BLACK, 0, 0))
    {
        blackScore += cornerVal;
        counter++;
    }
    if (get(BLACK, 0, 7))
    {
        blackScore += cornerVal;
        counter++;
    }
    if (get(BLACK, 7, 0))
    {
        blackScore += cornerVal;
        counter++;
    }
    if (get(BLACK, 7, 7))
    {
        blackScore += cornerVal;
        counter++;
    }
    if (get(BLACK, 2, 0))
    {
        blackScore += goodSideVal;
        counter++;
    }
    if (get(BLACK, 3, 0))
    {
        blackScore += goodSideVal;
        counter++;
    }
    if (get(BLACK, 4, 0))
    {
        blackScore += goodSideVal;
        counter++;
    }
    if (get(BLACK, 5, 0))
    {
        blackScore += goodSideVal;
        counter++;
    }
    if (get(BLACK, 0, 2))
    {
        blackScore += goodSideVal;
        counter++;
    }
    if (get(BLACK, 0, 3))
    {
        blackScore += goodSideVal;
        counter++;
    }
    if (get(BLACK, 0, 4))
    {
        blackScore += goodSideVal;
        counter++;
    }
    if (get(BLACK, 0, 5))
    {
        blackScore += goodSideVal;
        counter++;
    }
    if (get(BLACK, 7, 2))
    {
        blackScore += goodSideVal;
        counter++;
    }
    if (get(BLACK, 7, 3))
    {
        blackScore += goodSideVal;
        counter++;
    }
    if (get(BLACK, 7, 4))
    {
        blackScore += goodSideVal;
        counter++;
    }
    if (get(BLACK, 7, 5))
    {
        blackScore += goodSideVal;
        counter++;
    }
    if (get(BLACK, 2, 7))
    {
        blackScore += goodSideVal;
        counter++;
    }
    if (get(BLACK, 3, 7))
    {
        blackScore += goodSideVal;
        counter++;
    }
    if (get(BLACK, 4, 7))
    {
        blackScore += goodSideVal;
        counter++;
    }
    if (get(BLACK, 5, 7))
    {
        blackScore += goodSideVal;
        counter++;
    }
    if (get(BLACK, 0, 1))
    {
        blackScore += badSideVal;
        counter++;
    }
    if (get(BLACK, 1, 0))
    {
        blackScore += badSideVal;
        counter++;
    }
    if (get(BLACK, 7, 1))
    {
        blackScore += badSideVal;
        counter++;
    }
    if (get(BLACK, 6, 0))
    {
        blackScore += badSideVal;
        counter++;
    }
    if (get(BLACK, 0, 6))
    {
        blackScore += badSideVal;
        counter++;
    }
    if (get(BLACK, 1, 7))
    {
        blackScore += badSideVal;
        counter++;
    }
    if (get(BLACK, 7, 6))
    {
        blackScore += badSideVal;
        counter++;
    }
    if (get(BLACK, 6, 7))
    {
        blackScore += badSideVal;
        counter++;
    }
    if (get(BLACK, 1, 1))
    {
        blackScore += badAdjCornerVal;
        counter++;
    }
    if (get(BLACK, 6, 1))
    {
        blackScore += badAdjCornerVal;
        counter++;
    }
    if (get(BLACK, 1, 6))
    {
        blackScore += badAdjCornerVal;
        counter++;
    }
    if (get(BLACK, 6, 6))
    {
        blackScore += badAdjCornerVal;
        counter++;
    }
    blackScore += (countBlack() - counter);

    return blackScore;
}


int Board::score(Side side) {
    int returnScore = scoreWhite() - scoreBlack();
    if (side == WHITE)
    {
        //return (countWhite() - countBlack());
        return returnScore;
    }
    else
    {
        //return (countBlack() - countWhite());
        return (-1*returnScore);
    }
}

/*
 * Sets the board state given an 8x8 char array where 'w' indicates a white
 * piece and 'b' indicates a black piece. Mainly for testing purposes.
 */
void Board::setBoard(char data[]) {
    taken.reset();
    black.reset();
    for (int i = 0; i < 64; i++) {
        if (data[i] == 'b') {
            taken.set(i);
            black.set(i);
        } if (data[i] == 'w') {
            taken.set(i);
        }
    }
}
