#include <stdlib.h>
#include <stdio.h>
#include "game.h"

static void canvasPrintGameMap(Canvas *self, GameMap *gameMap) {
    UNUSED(self);
    for (int x = 0 ; x < MAP_ROW; x++) {
        for (int y = 0; y < MAP_COLUMN; y++) {
            int startX = y * GRID_SIDE_LENGTH;
            int startY = x * GRID_SIDE_LENGTH;
            if (gameMap->isWall(gameMap, x, y)) {
                char type = gameMap->grids[GRID_OFFSET(x, y)];
                switch (type) {
                case '0':
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_wall_0); break;
                case '1':
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_wall_1); break;
                case '2':
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_wall_2); break;
                case '3':
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_wall_3); break;
                case '4':
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_wall_4); break;
                case '5':
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_wall_5); break;
                case '6':
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_wall_6); break;
                case '7':
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_wall_7); break;
                case '8':
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_wall_8); break;
                case '9':
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_wall_9); break;
                case 'a':
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_wall_a); break;
                case 'b':
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_wall_b); break;
                case 'c':
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_wall_c); break;
                case 'd':
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_wall_d); break;
                case 'e':
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_wall_e); break;
                case 'f':
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_wall_f); break;
                case 'g':
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_wall_g); break;
                case 'h':
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_wall_h); break;
                case 'i':
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_wall_i); break;
                case 'j':
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_wall_j); break;
                case 'k':
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_wall_k); break;
                case 'l':
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_wall_l); break;
                case 'm':
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_wall_m); break;
                case 'n':
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_wall_n); break;
                case 'o':
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_wall_o); break;
                case 'p':
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_wall_p); break;
                case 'q':
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_wall_q); break;
                case 'r':
                    drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_wall_r); break;
                default:
                    break;
                }
            } else if (gameMap->isFood(gameMap, x, y)) {
                drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_food);
            } else {
                drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_empty);
            }
        }
    }
    drawRectDMA(MAP_COLUMN * GRID_SIDE_LENGTH, 0, WIDTH - MAP_COLUMN * GRID_SIDE_LENGTH, HEIGHT, BLACK);
    drawCenteredString(165, 10, 70, 20, "- PACMAN -", YELLOW);
    drawCenteredString(175, 30, 50, 20, "MODE", YELLOW);
    drawCenteredString(175, 50, 50, 20, "SINGLE", WHITE);
    drawCenteredString(175, 70, 50, 20, "LEVEL", YELLOW);
    drawCenteredString(175, 90, 50, 20, "1", WHITE);
    drawCenteredString(175, 110, 50, 20, "SCORE", YELLOW);
    drawCenteredString(175, 130, 50, 20, "0", WHITE);
}

static void rerenderGrid(GameMap *gameMap, int row, int col) {
    int startX = col * GRID_SIDE_LENGTH;
    int startY = row * GRID_SIDE_LENGTH;
    if (gameMap->isFood(gameMap, row, col)) {
        drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_food);
    } else {
        drawImageDMA(startX, startY, GRID_SIDE_LENGTH, GRID_SIDE_LENGTH, image_empty);
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
    int direction = pacman->getDirection(pacman);
    if (direction == DIRECTION_UP) {
        if (round < GRID_SIDE_LENGTH / 2) {
            drawImageDMA(x, y, CHARACTER_SIDE_LENGTH, CHARACTER_SIDE_LENGTH, image_pacman_up_1);
        } else {
            drawImageDMA(x, y, CHARACTER_SIDE_LENGTH, CHARACTER_SIDE_LENGTH, image_pacman_up_0);
        }
    } else if (direction == DIRECTION_RIGHT) {
        if (round < GRID_SIDE_LENGTH / 2) {
            drawImageDMA(x, y, CHARACTER_SIDE_LENGTH, CHARACTER_SIDE_LENGTH, image_pacman_right_1);
        } else {
            drawImageDMA(x, y, CHARACTER_SIDE_LENGTH, CHARACTER_SIDE_LENGTH, image_pacman_right_0);
        }
    } else if (direction == DIRECTION_DOWN) {
        if (round < GRID_SIDE_LENGTH / 2) {
            drawImageDMA(x, y, CHARACTER_SIDE_LENGTH, CHARACTER_SIDE_LENGTH, image_pacman_down_1);
        } else {
            drawImageDMA(x, y, CHARACTER_SIDE_LENGTH, CHARACTER_SIDE_LENGTH, image_pacman_down_0);
        }
    } else {
        if (round < GRID_SIDE_LENGTH / 2) {
            drawImageDMA(x, y, CHARACTER_SIDE_LENGTH, CHARACTER_SIDE_LENGTH, image_pacman_left_1);
        } else {
            drawImageDMA(x, y, CHARACTER_SIDE_LENGTH, CHARACTER_SIDE_LENGTH, image_pacman_left_0);
        }
    }
}

static void rerenderGhost(Ghost *ghost, int x, int y, int round) {
    int direction = ghost->getDirection(ghost);
    if (direction == DIRECTION_UP) {
        if (round < GRID_SIDE_LENGTH / 2) {
            drawImageDMA(x, y, CHARACTER_SIDE_LENGTH, CHARACTER_SIDE_LENGTH, image_ghost_up_1);
        } else {
            drawImageDMA(x, y, CHARACTER_SIDE_LENGTH, CHARACTER_SIDE_LENGTH, image_ghost_up_0);
        }
    } else if (direction == DIRECTION_RIGHT) {
        if (round < GRID_SIDE_LENGTH / 2) {
            drawImageDMA(x, y, CHARACTER_SIDE_LENGTH, CHARACTER_SIDE_LENGTH, image_ghost_right_1);
        } else {
            drawImageDMA(x, y, CHARACTER_SIDE_LENGTH, CHARACTER_SIDE_LENGTH, image_ghost_right_0);
        }
    } else if (direction == DIRECTION_DOWN) {
        if (round < GRID_SIDE_LENGTH / 2) {
            drawImageDMA(x, y, CHARACTER_SIDE_LENGTH, CHARACTER_SIDE_LENGTH, image_ghost_down_1);
        } else {
            drawImageDMA(x, y, CHARACTER_SIDE_LENGTH, CHARACTER_SIDE_LENGTH, image_ghost_down_0);
        }
    } else {
        if (round < GRID_SIDE_LENGTH / 2) {
            drawImageDMA(x, y, CHARACTER_SIDE_LENGTH, CHARACTER_SIDE_LENGTH, image_ghost_left_1);
        } else {
            drawImageDMA(x, y, CHARACTER_SIDE_LENGTH, CHARACTER_SIDE_LENGTH, image_ghost_left_0);
        }
    }
}

// static void delay(void) {
// 	volatile int x = 0;
// 	for (int i = 0; i < ANIMATION_DELAY; i++) {
//         x++;
//     }
// }

static void gameAnimateCharacters(Canvas *canvas, GameMap *gameMap) {
    UNUSED(canvas);
    for (int round = 0; round < GRID_SIDE_LENGTH; round++) {

        waitForVBlank();
        Pacman *pacman = gameMap->pacman;
        int startX = pacman->prevY * GRID_SIDE_LENGTH - (CHARACTER_SIDE_LENGTH - GRID_SIDE_LENGTH) / 2;
        int startY = pacman->prevX * GRID_SIDE_LENGTH - (CHARACTER_SIDE_LENGTH - GRID_SIDE_LENGTH) / 2;
        int direction = pacman->getDirection(pacman);
        if ((pacman->prevX != pacman->x || pacman->prevY != pacman->y)) {
            int result[2];
            nextPixelLocation(startX, startY, direction, round, result);
            drawRectDMA(result[0], result[1], CHARACTER_SIDE_LENGTH, CHARACTER_SIDE_LENGTH, BLACK);
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
                nextPixelLocation(startX, startY, direction, round, result);
                drawRectDMA(result[0], result[1], CHARACTER_SIDE_LENGTH, CHARACTER_SIDE_LENGTH, BLACK);
                if (gameMap->isFood(gameMap, ghost->prevX, ghost->prevY)) {
                    rerenderGrid(gameMap, ghost->prevX, ghost->prevY);
                }
                nextPixelLocation(startX, startY, direction, round + 1, result);
                rerenderGhost(ghost, result[0], result[1], round);
            } else {
                rerenderGhost(ghost, startX, startY, 0);
            }
        }

        drawRectDMA(175, 130, 50, 20, BLACK);
        int score = gameMap->pacman->score;
        char buffer[10];
        sprintf(buffer, "%d", score);
        drawCenteredString(175, 130, 50, 20, buffer, WHITE);

        // delay();
    }
}

Canvas *new_Canvas(void) {
    Canvas *canvas = (Canvas *) malloc(sizeof(Canvas));
    canvas->printGameMap = canvasPrintGameMap;
    canvas->animateCharacters = gameAnimateCharacters;
    return canvas;
}

void delete_Canvas(Canvas *self) {
    free(self);
}