#include <stdio.h>
#include <unistd.h>
#include "game.h"

void printGameMap(GameMap *gameMap) {
    Pacman *pacman = gameMap->pacman;
    Ghost **ghosts = gameMap->ghosts;
    for (int x = 0; x < MAP_ROW; x++) {
        for (int y = 0; y < MAP_COLUMN; y++) {
            if (gameMap->isWall(gameMap, x, y)) {
                printf("##");
            } else {
                int dir = -1;
                for (int i = 0; i < gameMap->numGhosts; i++) {
                    if (ghosts[i]->x == x && ghosts[i]->y == y) {
                        printf("G");
                        dir = ghosts[i]->getDirection(ghosts[i]);
                        break;
                    }
                }
                if (dir == -1) {
                    if (pacman->x == x && pacman->y == y) {
                        printf("P");
                        dir = pacman->getDirection(pacman);
                    }
                }
                if (dir != -1) {
                    switch (dir) {
                    case DIRECTION_UP:
                        printf("^");
                        break;
                    case DIRECTION_DOWN:
                        printf("v");
                        break;
                    case DIRECTION_LEFT:
                        printf("<");
                        break;
                    case DIRECTION_RIGHT:
                        printf(">");
                        break;
                    case DIRECTION_STOP:
                        printf("x");
                        break;
                    default:
                        break;
                    }
                } else {
                    if (gameMap->isFood(gameMap, x, y)) {
                        printf(". ");
                    } else {
                        printf("  ");
                    }
                }
            }
        }
        printf("\n");
    }
    printf("Pacman: ");
    if (gameMap->pacman->isLive(pacman) != 0) {
        printf("alive ");
    } else {
        printf("dead  ");
    }
    printf("%d", pacman->score);
    printf("\n");
}

int translateInput(char c) {
    switch (c) {
    case 'w':
        return DIRECTION_UP;
        break;
    case 'a':
        return DIRECTION_LEFT;
        break;
    case 'd':
        return DIRECTION_RIGHT;
        break;
    case 's':
        return DIRECTION_DOWN;
    default:
        break;
    }
    return DIRECTION_STOP;
}

int main() {

    char *level1 = "noghoooghoooooooghokq.23...23.......23.rq.89...23.ab.ab.89.rq......23.23.23....rq.a111153.2415411b.rq.8000073.80000009.rq......23G.........re1111b.23.a111111b.rf00009.89.80076009.rq............23....rq.a11b.a111b.23.a11cq.8073.80009.89.800dq...23............Gre1b.23.ab.a111111b.rf09.89.23.80076009.rq.....P23....23....rq.a11115411b.23.ab.rq.8000000009.89.89.rq..................rmppppppppppppppppppl";

    GameMap *gameMap = new_GameMap(level1);
    Pacman *pacman = gameMap->pacman;

    char buffer[10];

    // int directions[] = {DIRECTION_UP, DIRECTION_UP, DIRECTION_UP, DIRECTION_RIGHT, DIRECTION_RIGHT, DIRECTION_RIGHT, DIRECTION_DOWN, DIRECTION_DOWN, DIRECTION_DOWN, DIRECTION_RIGHT, DIRECTION_LEFT};

    // int directions[] = {DIRECTION_STOP, DIRECTION_STOP, DIRECTION_STOP, DIRECTION_STOP, DIRECTION_STOP, DIRECTION_STOP, DIRECTION_STOP, DIRECTION_STOP};

    int outcome = GAME_CONTINUE;

    while(1) {
        printGameMap(gameMap);
        printf("Next move: ");
        scanf("%10s", buffer);
        int direction = translateInput(buffer[0]);
        pacman->moveDirection(pacman, direction, gameMap);
        for(int ghostIdx = 0; ghostIdx < gameMap->numGhosts; ghostIdx++) {
            Ghost *ghost = gameMap->ghosts[ghostIdx];
            ghost->makeNextMove(ghost, gameMap);
        }
        outcome = gameMap->getOutcome(gameMap);
        if (outcome != GAME_CONTINUE) {
            break;
        }
    }

    printGameMap(gameMap);
    if (outcome == GAME_OVER) {
        printf("PACMAN DIED. GAME OVER.\n");
    } else {
        printf("YOU WON!\n");
    }

    delete_GameMap(gameMap);

    return 0;
}