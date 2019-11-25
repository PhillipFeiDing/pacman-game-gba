#include "game.h"

int manhattanDistance(int x1, int y1, int x2, int y2) {
    int temp1 = x2 - x1;
    int temp2 = y2 - y1;
    if (temp1 < 0) {
        temp1 = (~temp1) + 1;
    }
    if (temp2 < 0) {
        temp2 = (~temp2) + 1;
    }
    return temp1 + temp2;
}

void nextPosition(int x, int y, int move, int result[], GameMap *gameMap) {
    result[0] = x;
    result[1] = y;
    switch (move) {
    case DIRECTION_UP:
        result[0]--;
        break;
    case DIRECTION_RIGHT:
        result[1]++;
        break;
    case DIRECTION_DOWN:
        result[0]++;
        break;
    case DIRECTION_LEFT:
        result[1]--;
        break;
    default:
        break;
    }
    if (gameMap->isWall(gameMap, result[0], result[1])) {
        result[0] = x;
        result[1] = y;
    }
}