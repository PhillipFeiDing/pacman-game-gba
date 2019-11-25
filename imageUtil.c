#include "game.h"
#include <stdlib.h>

static const unsigned short *wallImages[] = {
    image_wall_0, image_wall_1, image_wall_2, image_wall_3, image_wall_4, image_wall_5, image_wall_6, 
    image_wall_7, image_wall_8, image_wall_9, image_wall_a, image_wall_b, image_wall_c, image_wall_d, 
    image_wall_e, image_wall_f, image_wall_g, image_wall_h, image_wall_i, image_wall_j, image_wall_k, 
    image_wall_l, image_wall_m, image_wall_n, image_wall_o, image_wall_p, image_wall_q, image_wall_r
};

static const unsigned short *ghostImages[] = {
    image_red_ghost_up_0, image_red_ghost_up_1, image_red_ghost_right_0, image_red_ghost_right_1,
    image_red_ghost_down_0, image_red_ghost_down_1, image_red_ghost_left_0, image_red_ghost_left_1,
    image_blue_ghost_up_0, image_blue_ghost_up_1, image_blue_ghost_right_0, image_blue_ghost_right_1,
    image_blue_ghost_down_0, image_blue_ghost_down_1, image_blue_ghost_left_0, image_blue_ghost_left_1,
    image_pink_ghost_up_0, image_pink_ghost_up_1, image_pink_ghost_right_0, image_pink_ghost_right_1,
    image_pink_ghost_down_0, image_pink_ghost_down_1, image_pink_ghost_left_0, image_pink_ghost_left_1,
    image_orange_ghost_up_0, image_orange_ghost_up_1, image_orange_ghost_right_0, image_orange_ghost_right_1,
    image_orange_ghost_down_0, image_orange_ghost_down_1, image_orange_ghost_left_0, image_orange_ghost_left_1,
    image_ghost_scared_0, image_ghost_scared_1, image_ghost_scared_2, image_ghost_scared_3,
    image_dead_ghost_up, image_dead_ghost_right, image_dead_ghost_down, image_dead_ghost_left
};

static const unsigned short *pacmanImages[] = {
    image_pacman_up_1, image_pacman_up_0, image_pacman_right_1, image_pacman_right_0,
    image_pacman_down_1, image_pacman_down_0, image_pacman_left_1, image_pacman_left_0,
    image_pacman_dying_0, image_pacman_dying_1, image_pacman_dying_2, image_pacman_dying_3,
    image_pacman_dying_4, image_pacman_dying_5, image_pacman_dying_6, image_pacman_dying_7,
    image_pacman_dying_8, image_pacman_dying_9, image_pacman_dying_a
};

const unsigned short *getWallImage(char type) {
    if (type >= '0' && type <= '9') {
        return wallImages[type - '0'];
    } else if (type >= MIN_WALL_SYMBOL_LETTER && type <= MAX_WALL_SYBMOL_LETTER) {
        return wallImages[type - 'a' + 10];
    } else {
        return NULL;
    }
}

const unsigned short *getGhostImage(Ghost *ghost, int round) {
    int color = ghost->getColor(ghost);
    int direction = ghost->getDirection(ghost);
    if (ghost->getState(ghost) == NORMAL_GHOST) {
        return ghostImages[color * 8 + 2 * direction + round % 2];
    } else if (ghost->getState(ghost) == SCARED_GHOST) {
        if (ghost->scareCountdown < WARNING_SCARE_COUNT) {
            return ghostImages[32 + round / 2 % 4];
        } else {
            return ghostImages[32 + round % 2];
        }
    } else {
        return ghostImages[36 + direction]; // dead ghost
    }
}

const unsigned short *getPacmanImage(Pacman *pacman, int round) {
    if (pacman->isLive(pacman) != 0) {
        int direction = pacman->getDirection(pacman);
        return pacmanImages[direction * 2 + round / (GRID_SIDE_LENGTH / 2)];
    } else {
        return pacmanImages[8 + round];
    }
}