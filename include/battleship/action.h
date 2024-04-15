#ifndef ACTION_H
#define ACTION_H

#include "battleship/constants.h"
#include "battleship/board.h"

enum ActionType
{
    SHOOT,
    INIT,
    CHECK_WIN,
    START,
    GET_GAME_STATUS,
};

struct ShootData
{
    int x;
    int y;
};

struct CheckWinData
{
};

struct StartData
{
};

struct GetGameStatusData
{
};

struct InitData
{
    char board[BOARD_SIZE][BOARD_SIZE];
};

struct Action
{
    ActionType type;
    union
    {
        ShootData shootData;
        InitData initData;
        CheckWinData checkWinData;
        StartData startData;
        GetGameStatusData getGameStatusData;
    };
};

#endif // ACTION_H