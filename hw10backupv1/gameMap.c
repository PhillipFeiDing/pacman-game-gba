#include "game.h"
#include <stdlib.h>

static int gameMapIsWall(struct gameMap *self, int x, int y) {
    int offset = GRID_OFFSET(x, y);
    unsigned char symbol = self->grids[offset];
    return (symbol >= MIN_WALL_SYMBOL_LETTER && symbol <= MAX_WALL_SYBMOL_LETTER)
    || (symbol >= '0' && symbol <= '9') ? 1 : 0;
} 

static int gameMapIsFood(struct gameMap *self, int x, int y) {
    int offset = GRID_OFFSET(x, y);
    unsigned char symbol = self->grids[offset];
    return symbol == FOOD_SYMBOL ? 1 : 0;
}

static int gameMapNearGhost(struct gameMap *self, int x, int y) {
    for (int i = 0; i < self->numGhosts; i++) {
        Ghost *ghost = self->ghosts[i];
        int xDiff = x - ghost->x;
        int yDiff = y - ghost->y;
        if (xDiff < 0) {
            xDiff = ~(xDiff) + 1;
        }
        if (yDiff < 0) {
            yDiff = ~(yDiff) + 1;
        }
        if (xDiff + yDiff < 2) {
            return 1;
        }
    }
    return 0;
}

static void gameMapSetFood(struct gameMap *self, int x, int y, int food) {
    int offset = GRID_OFFSET(x, y);
    if (food != 0) {
        if (self->grids[offset] == 0) {
            self->numFoods++;
        }
        self->grids[offset] = FOOD_SYMBOL;
    } else {
        if (self->grids[offset] != 0) {
            self->numFoods--;
        }
        self->grids[offset] = EMPTY_SYMBOL;
    }
}

static int gameGetOutcome(struct gameMap *self) {
    Pacman *pacman = self->pacman;
    if (pacman->isLive(pacman) == 0) {
        return GAME_OVER;
    } else if (self->numFoods == 0) {
        return GAME_WIN;
    } else {
        return GAME_CONTINUE;
    }
}

GameMap *new_GameMap(char* map) {
    GameMap *gameMap = (GameMap *) malloc(sizeof(GameMap));
    if (gameMap == NULL) {
        return NULL;
    }
    for (int i = 0; i < MAX_NUM_GHOSTS; i++) {
        gameMap->ghosts[i] = NULL;
    }
    gameMap->pacman = NULL;

    gameMap->numFoods = 0;
    int ghostCount = 0;
    for (int i = 0; i < TOTAL_TILES; i++) {
        if (map[i] == PACMAN_SYMBOL && gameMap->pacman == NULL) {
            gameMap->pacman = new_Pacman();
            if (gameMap->pacman != NULL) {
                gameMap->pacman->x = GRID_X(i);
                gameMap->pacman->y = GRID_Y(i);
                gameMap->pacman->prevX = GRID_X(i);
                gameMap->pacman->prevY = GRID_Y(i);
            } else {
                delete_GameMap(gameMap);
                return NULL;
            }
            gameMap->grids[i] = EMPTY_SYMBOL;
        }
        if (map[i] == GHOST_SYMBOL && ghostCount < MAX_NUM_GHOSTS) {
            gameMap->ghosts[ghostCount] = new_Ghost();
            if (gameMap->ghosts[ghostCount] != NULL) {
                gameMap->ghosts[ghostCount]->x = GRID_X(i);
                gameMap->ghosts[ghostCount]->y = GRID_Y(i);
                gameMap->ghosts[ghostCount]->prevX = GRID_X(i);
                gameMap->ghosts[ghostCount]->prevY = GRID_Y(i);
                ghostCount++;
            } else {
                delete_GameMap(gameMap);
                return NULL;
            }
            gameMap->grids[i] = EMPTY_SYMBOL;
        } else {
            if (map[i] == FOOD_SYMBOL) {
                gameMap->numFoods++;
            }
            gameMap->grids[i] = map[i];
        }
    }
    gameMap->numGhosts = ghostCount;

    gameMap->isWall = gameMapIsWall;
    gameMap->isFood = gameMapIsFood;
    gameMap->setFood = gameMapSetFood;
    gameMap->nearGhost = gameMapNearGhost;
    gameMap->getOutcome = gameGetOutcome;

    return gameMap;
}

void delete_GameMap(GameMap *self) {
    if (self->pacman != NULL) {
        free(self->pacman);
    }
    for (int i = 0; i < MAX_NUM_GHOSTS; i++) {
        if (self->ghosts[i] != NULL) {
            free(self->ghosts[i]);
        }
    }
    free(self);
}