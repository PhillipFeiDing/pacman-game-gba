#include <stdlib.h>
#include "game.h"

static int pacmanIsLive(Pacman *self) {
    return (int) ((self->status) & 1);
}

static int pacmanGetDirection(Pacman *self) {
    return (int) ((self->status>>2) & 3);
}

static void setGhostScared(GameMap *gameMap) {
    for (int i = 0; i < gameMap->numGhosts; i++) {
        Ghost *ghost = gameMap->ghosts[i];
        if (ghost->getState(ghost) != DEAD_GHOST) {
            ghost->setState(ghost, SCARED_GHOST);
            ghost->scareCountdown = INITIAL_SCARE_COUNT;
        }
    }
}

static void pacmanMoveDirection(Pacman *self, int dir, GameMap *gameMap) {
    int nextPos[2];
    nextPosition(self->x, self->y, dir, nextPos, gameMap);
    self->prevX = self->x;
    self->prevY = self->y;
    self->x = nextPos[0];
    self->y = nextPos[1];
    self->setDirection(self, dir);
    for (int i = 0; i < gameMap->numGhosts; i++) {
        Ghost *ghost = gameMap->ghosts[i];
        if (ghost->x == self->x && ghost->y == self->y) {
            if (ghost->getState(ghost) == NORMAL_GHOST) {
                if (isCheat == 0) {
                    self->setLive(self, PACMAN_DEAD);
                    return;
                }
            } else if (ghost->getState(ghost) == SCARED_GHOST) {
                self->score += EAT_GHOST_POINT;
                ghost->setState(ghost, DEAD_GHOST);
                delay(ANIMATION_DELAY * 6);
            }
        }
    }
    if (gameMap->isFood(gameMap, self->x, self->y)) {
        if (gameMap->grids[GRID_OFFSET(self->x, self->y)] == BIG_FOOD_SYMBOL) {
            self->score = self->score + BIG_FOOD_POINT;
            setGhostScared(gameMap);
            delay(ANIMATION_DELAY * 6);
        } else {
            self->score = self->score + FOOD_POINT;
        }
        gameMap->setFood(gameMap, self->x, self->y, EMPTY_SYMBOL);
    }
}

static void pacmanSetDirection(Pacman *self, int dir) {
    if (dir < 0 || dir > 3) {
        return;
    }
    self->status = (~(((unsigned char) 3)<<2) & self->status) | ((unsigned char) dir)<<2;
}

static void pacmanSetLive(Pacman *self, int live) {
    self->status = ((self->status>>1)<<1) | ((unsigned char) live);
}

Pacman *new_Pacman(void) {
    Pacman *pacman = (Pacman *) malloc(sizeof(Pacman));
    if (pacman == NULL) {
        return NULL;
    }
    pacman->x = 0;
    pacman->y = 0;
    pacman->prevX = 0;
    pacman->prevY = 0;
    pacman->score = 0;
    pacman->status = 0;
    pacman->isLive = &pacmanIsLive;
    pacman->getDirection = pacmanGetDirection;
    pacman->setDirection = pacmanSetDirection;
    pacman->moveDirection = pacmanMoveDirection;
    pacman->setLive = pacmanSetLive;
    pacman->setLive(pacman, PACMAN_LIVE);
    return pacman;
}

void delete_Pacman(Pacman *self) {
    free(self);
}
