#ifndef BRICKBREAKER_H
#define BRICKBREAKER_H

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <windows.h>

using namespace std;

class BrickBreaker {
private:
    static string wall;
    static string brick;
    static string ground;
    static string ball;

    static map<int, int> bricksWithLife;
    static int ballPos[2];
    static bool ballPosSet;
    static int ballLife;

    vector<vector<string>> gameBoard;
    int rows;
    int cols;

    int getExactBallPosition(int row, int col);
    void wallHit(int ballRow, int ballCol);
    void ballGoesDown(int ballRow, int ballCol);
    void movingIllusion(int ballRow, int ballCol);
    void reduceBrickAndBallLife(int ballRow, int ballCol);
    void prepareBoard();
    void sleepForOneSec();
    void moveDirection(int ballRow, int ballCol, int rowDirection, int colDirection);

public:
    BrickBreaker(int row, int col);
    void placeBricks(int row, int col, int life);
    void initiateBall(int ballRow, int ballCol, int rowDirection, int colDirection);
    void straightHit();
    void printGameBoard();
    int* getBallPosition();
    int getBallLife();
};

#endif
