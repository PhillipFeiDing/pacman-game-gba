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
    return symbol == FOOD_SYMBOL || symbol == BIG_FOOD_SYMBOL ? 1 : 0;
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
    if (food == BIG_FOOD_SYMBOL || food == FOOD_SYMBOL) {
        if (self->grids[offset] == EMPTY_SYMBOL) {
            self->numFoods++;
        }
        self->grids[offset] = food;
    } else if (food == EMPTY_SYMBOL) {
        if (self->grids[offset] != EMPTY_SYMBOL) {
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

    gameMap->isWall = gameMapIsWall;
    gameMap->isFood = gameMapIsFood;
    gameMap->setFood = gameMapSetFood;
    gameMap->nearGhost = gameMapNearGhost;
    gameMap->getOutcome = gameGetOutcome;

    gameMap->numFoods = 0;
    int ghostCount = 0;
    for (int i = 0; i < TOTAL_TILES; i++) {
        gameMap->grids[i] = EMPTY_SYMBOL;
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
        }
        if (IS_GHOST_SYMBOL(map[i]) && ghostCount < MAX_NUM_GHOSTS) {
            gameMap->ghosts[ghostCount] = new_Ghost();
            if (gameMap->ghosts[ghostCount] != NULL) {
                Ghost *currGhost = gameMap->ghosts[ghostCount];
                currGhost->x = GRID_X(i);
                currGhost->y = GRID_Y(i);
                currGhost->prevX = GRID_X(i);
                currGhost->prevY = GRID_Y(i);
                if (map[i] == RED_GHOST_SYMBOL) {
                    currGhost->setColor(currGhost, RED_GHOST);
                } else if (map[i] == BLUE_GHOST_SYMBOL) {
                    currGhost->setColor(currGhost, BLUE_GHOST);
                } else if (map[i] == PINK_GHOST_SYMBOL) {
                    currGhost->setColor(currGhost, PINK_GHOST);
                } else {
                    currGhost->setColor(currGhost, ORANGE_GHOST);
                }
                ghostCount++;
            } else {
                delete_GameMap(gameMap);
                return NULL;
            }
        } else {
            if (map[i] == FOOD_SYMBOL || map[i] == BIG_FOOD_SYMBOL) {
                gameMap->setFood(gameMap, GRID_X(i), GRID_Y(i), map[i]);
            } else if (map[i] != EMPTY_SYMBOL) {
                gameMap->grids[i] = map[i]; // this is just wall
            }
        }
    }
    gameMap->numGhosts = ghostCount;

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