#include <stdlib.h>
#include "game.h"

static int ghostGetDirection(Ghost *self) {
    return (int) (self->status & 3);
}

static void ghostSetDirection(Ghost *self, int dir) {
    if (dir < 0 || dir > 3) {
        return;
    }
    self->status = ((self->status>>2)<<2) | ((unsigned char) dir);
}

static int ghostMakeRandomMove(Ghost *self, GameMap *gameMap) {
    int nextMove = DIRECTION_STOP;
    int nextPos[2];
    int start = rand() % 4;
    for (int i = 0; i < 4; i++) {
        nextPosition(self->x, self->y, (i + start) % 4, nextPos, gameMap);
        if (nextPos[0] != self->x || nextPos[1] != self->y) {
            nextMove = (i + start) % 4;;
            break;
        }
    }
    self->moveDirection(self, nextMove, gameMap);
    return nextMove;
}

static int ghostMakeGreedyMove(Ghost *self, GameMap *gameMap) {
    Pacman *pacman = gameMap->pacman;
    int minManhattanDist = 999999;
    int nextMove = DIRECTION_STOP;
    int nextPos[2];
    for (int i = 0; i < 4; i++) {
        nextPosition(self->x, self->y, i, nextPos, gameMap);
        if (nextPos[0] != self->x || nextPos[1] != self->y) {
            int currManhattanDistance = manhattanDistance(pacman->x, pacman->y, nextPos[0], nextPos[1]);
            if (currManhattanDistance < minManhattanDist) {
                minManhattanDist = currManhattanDistance;
                nextMove = i;
            }
        }
    }
    self->moveDirection(self, nextMove, gameMap);
    return nextMove;
}

static int ghostMakeNextMove(Ghost *self, GameMap *gameMap) {
    int random = randint(0, 100);
    int move = DIRECTION_STOP;
    if (random < GREEDINESS) {
        move = ghostMakeGreedyMove(self, gameMap);
    } else {
        move = ghostMakeRandomMove(self, gameMap);
    }
    return move;
}

static void ghostMoveDirection(Ghost *self, int dir, GameMap *gameMap) {
    int nextPos[2];
    nextPosition(self->x, self->y, dir, nextPos, gameMap);
    self->prevX = self->x;
    self->prevY = self->y;
    self->x = nextPos[0];
    self->y = nextPos[1];
    self->setDirection(self, dir);
    Pacman *pacman = gameMap->pacman;
    if (self->x == pacman->x && self->y == pacman->y) {
        pacman->setLive(pacman, PACMAN_DEAD);
    }
}

Ghost *new_Ghost(void) {
    Ghost *ghost = (Ghost *) malloc(sizeof(Ghost));
    if (ghost == NULL) {
        return NULL;
    }
    ghost->x = 0;
    ghost->y = 0;
    ghost->prevX = 0;
    ghost->prevY = 0;
    ghost->status = 0;
    ghost->getDirection = ghostGetDirection;
    ghost->setDirection = ghostSetDirection;
    ghost->moveDirection = ghostMoveDirection;
    ghost->makeNextMove = ghostMakeNextMove;

    return ghost;
}

void delete_Ghost(Ghost *self) {
    free(self);
}