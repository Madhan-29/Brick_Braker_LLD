#include "BrickBreaker.h"

// Static member initialization
string BrickBreaker::wall = "w";
string BrickBreaker::brick = "1";
string BrickBreaker::ground = "g";
string BrickBreaker::ball = "o";

map<int, int> BrickBreaker::bricksWithLife;
int BrickBreaker::ballPos[2] = {0, 0};
bool BrickBreaker::ballPosSet = false;
int BrickBreaker::ballLife = 5;

BrickBreaker::BrickBreaker(int row, int col) {
    rows = row;
    cols = col;
    gameBoard.resize(row, vector<string>(col));
    prepareBoard();
    // ball placement
    gameBoard[row - 1][(col / 2)] = ball; // bottom center
    ballPos[0] = row - 1;
    ballPos[1] = col / 2;
    ballPosSet = true;
}

void BrickBreaker::placeBricks(int row, int col, int life) {
    gameBoard[row][col] = brick;
    int exactPosition = getExactBallPosition(row, col); // returns exact position
    bricksWithLife[exactPosition] = life;
}

void BrickBreaker::initiateBall(int ballRow, int ballCol, int rowDirection, int colDirection) {
    moveDirection(ballRow, ballCol, rowDirection, colDirection);
    // show ground if ball pos changed
    if (gameBoard[ballRow][ballCol] != ball) gameBoard[ballRow][ballCol] = ground;
}

void BrickBreaker::moveDirection(int ballRow, int ballCol, int rowDirection, int colDirection) {
    while (gameBoard[ballRow][ballCol] != wall) {
        if (gameBoard[ballRow][ballCol] == brick) {
            ballGoesDown(ballRow, ballCol);
            return;
        }
        movingIllusion(ballRow, ballCol); // move the ball
        ballCol += colDirection;
        ballRow += rowDirection;
    }

    wallHit(ballRow, ballCol); // show ball in the place of wall

    // If already moving horizontally and hit another wall → no brick found, go down
    if (rowDirection == 0) {
        // Go down from 1 cell inside the wall (row+1 since we're at a wall row, col adjusted inside)
        int downCol = ballCol + (colDirection * -1); // step back 1 col from the wall
        ballGoesDown(ballRow + 1, downCol);
        return;
    }

    // First wall hit during diagonal: switch to horizontal movement
    rowDirection = 0;
    colDirection = colDirection * -1;

    if (colDirection == 0)     // means ball was going straight. No bricks possible in straight line
        ballGoesDown(ballRow + 1, ballCol);
    else
        moveDirection(ballRow, ballCol + colDirection, rowDirection, colDirection);
}

int BrickBreaker::getExactBallPosition(int row, int col) {
    return (row * cols) + col + 1;

    /*  Exact position calculation. Ex: 10th position, 26th position etc.
        1 2 3 4 5 6 7
        8 9 10......
        ..............
     */
}

void BrickBreaker::wallHit(int ballRow, int ballCol) {
    // No animation - wall hit is handled by moveDirection logic
}

void BrickBreaker::ballGoesDown(int ballRow, int ballCol) {
    while (ballRow != rows) {
        movingIllusion(ballRow, ballCol); // move the ball
        ballRow++;
    }
    ballPos[0] = ballRow - 1;
    ballPos[1] = ballCol;
    gameBoard[ballPos[0]][ballPos[1]] = ball; // new ball position
}

void BrickBreaker::movingIllusion(int ballRow, int ballCol) {
    if (gameBoard[ballRow][ballCol] == brick) {
        reduceBrickAndBallLife(ballRow, ballCol);
        if (bricksWithLife[getExactBallPosition(ballRow, ballCol)] == 0) {
            gameBoard[ballRow][ballCol] = " ";
        }
    }
    // No animation for non-brick cells - just pass through
}

void BrickBreaker::reduceBrickAndBallLife(int ballRow, int ballCol) {
    int exactPosition = getExactBallPosition(ballRow, ballCol);
    ballLife--;  // if ball hits brick, ball's life reduces

    if (ballLife >= 0) // if ball life is not negative
        bricksWithLife[exactPosition] = bricksWithLife[exactPosition] - 1;
}

void BrickBreaker::prepareBoard() {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (row == 0 || col == 0 || col == cols - 1) {
                gameBoard[row][col] = wall;
            }
            else if (row == rows - 1) {
                gameBoard[row][col] = ground;
            }
            else {
                gameBoard[row][col] = " ";
            }
        }
    }
}

void BrickBreaker::printGameBoard() {
    for (const auto& str : gameBoard) {
        for (const auto& s : str) {
            cout << s << " ";
        }
        cout << endl;
    }
}

void BrickBreaker::sleepForOneSec() {
    Sleep(100); // reduced from 1000ms for faster gameplay
}

int* BrickBreaker::getBallPosition() {
    return ballPos;
}

int BrickBreaker::getBallLife() {
    return ballLife;
}

void BrickBreaker::straightHit() {
    int col = ballPos[1];

    // Move straight up from ball position, find first brick
    for (int row = ballPos[0] - 1; row >= 0; row--) {
        if (gameBoard[row][col] == wall) {
            break; // hit wall, no brick found
        }
        if (gameBoard[row][col] == brick) {
            // Remove the brick (module 1: instant removal)
            int exactPos = getExactBallPosition(row, col);
            bricksWithLife.erase(exactPos);
            gameBoard[row][col] = " ";
            break; // only hit the first brick
        }
    }
    // Ball stays at original position, NO ball life reduction
    printGameBoard();
}
