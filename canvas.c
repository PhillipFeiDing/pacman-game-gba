#include <stdlib.h>
#include <stdio.h>
#include "game.h"

static void canvasPrintGameMap(Canvas *self, GameMap *gameMap, int level) {
    UNUSED(self);
    for (int x = 0 ; x < MAP_ROW; x++) {
        for (int y = 0; y < MAP_COLUMN; y++) {
            int startX = y * GRID_SIDE_LENGTH;
            int startY = x * GRID_SIDE_LENGTH;
            if (gameMap->isWall(gameMap, x, y)) {
                char type = gameMap->grids[GRID_OFFSET(x, y)];
                const unsigned short *targetImage = getWallImage(type);
                if (targetImage != NULL) {
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, targetImage);
                }
            } else if (gameMap->isFood(gameMap, x, y)) {
                if (gameMap->grids[GRID_OFFSET(x, y)] == BIG_FOOD_SYMBOL) {
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_big_food);
                } else {
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_food);
                }
            } else {
                drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_empty);
            }
        }
    }
    drawRectDMA(MAP_COLUMN * GRID_SIDE_LENGTH, 0, WIDTH - MAP_COLUMN * GRID_SIDE_LENGTH, HEIGHT, BLACK);
    drawCenteredString(165, 10, 70, 20, "+ PACMAN +", YELLOW);
    drawCenteredString(175, 30, 50, 20, "MODE", YELLOW);
    self->drawToggleMode(self);
    drawCenteredString(175, 70, 50, 20, "LEVEL", YELLOW);
    char buffer[10];
    sprintf(buffer, "%d", level + 1);
    drawCenteredString(175, 90, 50, 20, buffer, WHITE);
    drawCenteredString(175, 110, 50, 20, "SCORE", YELLOW);
    drawCenteredString(175, 130, 50, 20, "0", WHITE);
}

static void canvasPrintStartPage(Canvas *self) {
    UNUSED(self);
    drawFullScreenImageDMA(image_gamestart);
    waitForVBlank();
    drawCenteredString(20, 10, 200, 10, "PRESS <START>", YELLOW);
}

static void canvasPrintGameOverPage(Canvas *self) {
    UNUSED(self);
    drawFullScreenImageDMA(image_gameover);
    waitForVBlank();
    drawCenteredString(20, 120, 200, 10, "RETRY PRESS <START>", YELLOW);
    drawCenteredString(20, 140, 200, 10, "QUIT PRESS <SELECT>", YELLOW);
}

static void canvasPrintGameWinPage(Canvas *self) {
    UNUSED(self);
    drawFullScreenImageDMA(image_gamewin);
    waitForVBlank();
    drawCenteredString(20, 100, 200, 10, "NEXT  PRESS <START>", YELLOW);
    drawCenteredString(20, 120, 200, 10, "QUIT PRESS <SELECT>", YELLOW);
}

static void canvasDrawToggleMode(Canvas *self) {
    UNUSED(self);
    drawRectDMA(175, 50, 50, 20, BLACK);
    if (isCheat != 0) {
        drawCenteredString(175, 50, 50, 20, "CHEAT", RED);
    } else {
        drawCenteredString(175, 50, 50, 20, "NORMAL", WHITE);
    }
}

static void stackingDraw(int x, int y, int width, int height, const unsigned short *image) {
    int count = 0;
    for (int row = 0; row < width; row++) {
        for (int col = 0; col < height; col++) {
            if (image[count] != BLACK) {
                setPixel(col + x, row + y, image[count]);
            }
            count++;
        }
    }
}

static void rerenderGrids(GameMap *gameMap, int row, int col, int row2, int col2) {
    int startX = col * GRID_SIDE_LENGTH - (CHARACTER_SIDE_LENGTH - GRID_SIDE_LENGTH) / 2;
    int startY = row * GRID_SIDE_LENGTH - (CHARACTER_SIDE_LENGTH - GRID_SIDE_LENGTH) / 2;
    int startX2 = col2 * GRID_SIDE_LENGTH - (CHARACTER_SIDE_LENGTH - GRID_SIDE_LENGTH) / 2;
    int startY2 = row2 * GRID_SIDE_LENGTH - (CHARACTER_SIDE_LENGTH - GRID_SIDE_LENGTH) / 2;
    drawImageDMA(startX, startY, CHARACTER_SIDE_LENGTH, CHARACTER_SIDE_LENGTH, image_empty_large);
    drawImageDMA(startX2, startY2, CHARACTER_SIDE_LENGTH, CHARACTER_SIDE_LENGTH, image_empty_large);
    int shiftRow[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
    int shiftCol[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
    for (int i = 0; i < 9; i++) {
        if (gameMap->isFood(gameMap, row + shiftRow[i], col + shiftCol[i])) {
            if (gameMap->grids[GRID_OFFSET(row + shiftRow[i], col + shiftCol[i])] == FOOD_SYMBOL) {
                if (i == 4) {
                    startX = (col + shiftCol[i]) * GRID_SIDE_LENGTH - (TINY_SIDE_LENGTH - GRID_SIDE_LENGTH) / 2;
                    startY = (row + shiftRow[i]) * GRID_SIDE_LENGTH - (TINY_SIDE_LENGTH - GRID_SIDE_LENGTH) / 2;
                    drawImageDMA(startX, startY, TINY_SIDE_LENGTH, TINY_SIDE_LENGTH, image_food_tiny);
                }
            } else {
                startX = (col + shiftCol[i]) * GRID_SIDE_LENGTH;
                startY = (row + shiftRow[i]) * GRID_SIDE_LENGTH;
                drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_big_food);
            }
        }
    }
    for (int i = 0; i < 9; i++) {
        if (gameMap->isFood(gameMap, row2 + shiftRow[i], col2 + shiftCol[i])) {
            if (gameMap->grids[GRID_OFFSET(row2 + shiftRow[i], col2 + shiftCol[i])] == FOOD_SYMBOL) {
                if (i == 4) {
                    startX2 = (col2 + shiftCol[i]) * GRID_SIDE_LENGTH - (TINY_SIDE_LENGTH - GRID_SIDE_LENGTH) / 2;
                    startY2 = (row2 + shiftRow[i]) * GRID_SIDE_LENGTH - (TINY_SIDE_LENGTH - GRID_SIDE_LENGTH) / 2;
                    drawImageDMA(startX2, startY2, TINY_SIDE_LENGTH, TINY_SIDE_LENGTH, image_food_tiny);
                }
            } else {
                startX2 = (col2 + shiftCol[i]) * GRID_SIDE_LENGTH;
                startY2 = (row2 + shiftRow[i]) * GRID_SIDE_LENGTH;
                drawImageDMA(startX2, startY2, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_big_food);
            }
        }
    }
}

static void nextPixelLocation(int x, int y, int move, int cycle, int *result) {
    result[0] = 0;
    result[1] = 0;
    switch (move) {
    case DIRECTION_UP:
        result[1] = -1;
        break;
    case DIRECTION_RIGHT:
        result[0] = 1;
        break;
    case DIRECTION_DOWN:
        result[1] = 1;
        break;
    case DIRECTION_LEFT:
        result[0] = -1;
        break;
    default:
        break;
    }
    result[0] = result[0] * cycle + x;
    result[1] = result[1] * cycle + y;
}

static void rerenderPacman(Pacman *pacman, int x, int y, int round) {
    const unsigned short *targetImage = getPacmanImage(pacman, round);
    if (pacman->isLive(pacman) != 0) {
        stackingDraw(x, y, CHARACTER_SIDE_LENGTH, CHARACTER_SIDE_LENGTH, targetImage);
    } else {
        drawImageDMA(x, y, CHARACTER_SIDE_LENGTH + 1, CHARACTER_SIDE_LENGTH + 1, getPacmanImage(pacman, round));
    }
}

static void rerenderGhost(Ghost *ghost, int x, int y, int round) {
    const unsigned short *targetImage = getGhostImage(ghost, round);
    stackingDraw(x, y, CHARACTER_SIDE_LENGTH, CHARACTER_SIDE_LENGTH, targetImage);
    // drawImageDMA(x, y, CHARACTER_SIDE_LENGTH, CHARACTER_SIDE_LENGTH, getGhostImage(ghost, round));
}

void delay(int time) {
	volatile int x = 0;
	for (int i = 0; i < time; i++) {
        x++;
    }
}

static void canvasAnimateCharacters(Canvas *canvas, GameMap *gameMap) {
    UNUSED(canvas);
    Pacman *pacman = gameMap->pacman;
    if (pacman->isLive(pacman) != 0) {
        for (int round = 0; round < GRID_SIDE_LENGTH; round++) {
            waitForVBlank();
            rerenderGrids(gameMap, pacman->prevX, pacman->prevY, pacman->x, pacman->y);
            for (int i = 0; i < gameMap->numGhosts; i++) {
                Ghost *ghost = gameMap->ghosts[i];
                rerenderGrids(gameMap, ghost->prevX, ghost->prevY, ghost->x, ghost->y);
            }

            int startX = pacman->prevY * GRID_SIDE_LENGTH - (CHARACTER_SIDE_LENGTH - GRID_SIDE_LENGTH) / 2;
            int startY = pacman->prevX * GRID_SIDE_LENGTH - (CHARACTER_SIDE_LENGTH - GRID_SIDE_LENGTH) / 2;
            int direction = pacman->getDirection(pacman);
            if ((pacman->prevX != pacman->x || pacman->prevY != pacman->y)) {
                int result[2];
                // nextPixelLocation(startX, startY, direction, round, result);
                // drawRectDMA(result[0], result[1], CHARACTER_SIDE_LENGTH, CHARACTER_SIDE_LENGTH, BLACK);
                nextPixelLocation(startX, startY, direction, round + 1, result);
                rerenderPacman(pacman, result[0], result[1], round);
            } else {
                rerenderPacman(pacman, startX, startY, 0);
            }

            for (int ghostIdx = 0; ghostIdx < gameMap->numGhosts; ghostIdx++) {
                Ghost *ghost = gameMap->ghosts[ghostIdx];
                int startX = ghost->prevY * GRID_SIDE_LENGTH - (CHARACTER_SIDE_LENGTH - GRID_SIDE_LENGTH) / 2;
                int startY = ghost->prevX * GRID_SIDE_LENGTH - (CHARACTER_SIDE_LENGTH - GRID_SIDE_LENGTH) / 2;
                int direction = ghost->getDirection(ghost);
                if ((ghost->prevX != ghost->x || ghost->prevY != ghost->y)) {
                    int result[2];
                    // nextPixelLocation(startX, startY, direction, round, result);
                    // drawRectDMA(result[0], result[1], CHARACTER_SIDE_LENGTH, CHARACTER_SIDE_LENGTH, BLACK);
                    nextPixelLocation(startX, startY, direction, round + 1, result);
                    rerenderGhost(ghost, result[0], result[1], round);
                } else {
                    rerenderGhost(ghost, startX, startY, 0);
                }
            }
        }
    } else {
        int pacmanX = pacman->prevY * GRID_SIDE_LENGTH - (CHARACTER_SIDE_LENGTH - GRID_SIDE_LENGTH) / 2;
        int pacmanY = pacman->prevX * GRID_SIDE_LENGTH - (CHARACTER_SIDE_LENGTH - GRID_SIDE_LENGTH) / 2;
        delay(WIN_LOSE_DELAY);
        for (int round = 0; round < 11; round++) {
            waitForVBlank();
            rerenderPacman(pacman, pacmanX, pacmanY, round);
            for (int ghostIdx = 0; ghostIdx < gameMap->numGhosts; ghostIdx++) {
                Ghost *ghost = gameMap->ghosts[ghostIdx];
                int ghostX = ghost->prevY * GRID_SIDE_LENGTH - (CHARACTER_SIDE_LENGTH - GRID_SIDE_LENGTH) / 2;
                int ghostY = ghost->prevX * GRID_SIDE_LENGTH - (CHARACTER_SIDE_LENGTH - GRID_SIDE_LENGTH) / 2;
                rerenderGhost(ghost, ghostX, ghostY, 1);
            }
            delay(ANIMATION_DELAY);
        }
        delay(WIN_LOSE_DELAY);
    }

    waitForVBlank();
    drawRectDMA(175, 130, 50, 20, BLACK);
    char buffer[10];
    sprintf(buffer, "%d", gameMap->pacman->score);
    drawCenteredString(175, 130, 50, 20, buffer, WHITE);
}

Canvas *new_Canvas(void) {
    Canvas *canvas = (Canvas *) malloc(sizeof(Canvas));
    canvas->printGameMap = canvasPrintGameMap;
    canvas->printStartPage = canvasPrintStartPage;
    canvas->printGameOverPage = canvasPrintGameOverPage;
    canvas->printGameWinPage = canvasPrintGameWinPage;
    canvas->animateCharacters = canvasAnimateCharacters;
    canvas->drawToggleMode = canvasDrawToggleMode;
    return canvas;
}

void delete_Canvas(Canvas *self) {
    free(self);
}