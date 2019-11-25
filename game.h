#ifndef GAME_H
#define GAME_H

#include "gba.h"

                    /* TODO: */

            // Create any necessary structs //

#include "images/background/image_gamestart.h"
#include "images/background/image_gameover.h"
#include "images/background/image_gamewin.h"
#include "images/pacman/image_pacman_down_0.h"
#include "images/pacman/image_pacman_down_1.h"
#include "images/pacman/image_pacman_right_0.h"
#include "images/pacman/image_pacman_right_1.h"
#include "images/pacman/image_pacman_up_0.h"
#include "images/pacman/image_pacman_up_1.h"
#include "images/pacman/image_pacman_left_0.h"
#include "images/pacman/image_pacman_left_1.h"
#include "images/pacman/image_pacman_dying_0.h"
#include "images/pacman/image_pacman_dying_1.h"
#include "images/pacman/image_pacman_dying_2.h"
#include "images/pacman/image_pacman_dying_3.h"
#include "images/pacman/image_pacman_dying_4.h"
#include "images/pacman/image_pacman_dying_5.h"
#include "images/pacman/image_pacman_dying_6.h"
#include "images/pacman/image_pacman_dying_7.h"
#include "images/pacman/image_pacman_dying_8.h"
#include "images/pacman/image_pacman_dying_9.h"
#include "images/pacman/image_pacman_dying_a.h"
#include "images/ghost/image_red_ghost_down_0.h"
#include "images/ghost/image_red_ghost_down_1.h"
#include "images/ghost/image_red_ghost_right_0.h"
#include "images/ghost/image_red_ghost_right_1.h"
#include "images/ghost/image_red_ghost_up_0.h"
#include "images/ghost/image_red_ghost_up_1.h"
#include "images/ghost/image_red_ghost_left_0.h"
#include "images/ghost/image_red_ghost_left_1.h"
#include "images/ghost/image_blue_ghost_down_0.h"
#include "images/ghost/image_blue_ghost_down_1.h"
#include "images/ghost/image_blue_ghost_right_0.h"
#include "images/ghost/image_blue_ghost_right_1.h"
#include "images/ghost/image_blue_ghost_up_0.h"
#include "images/ghost/image_blue_ghost_up_1.h"
#include "images/ghost/image_blue_ghost_left_0.h"
#include "images/ghost/image_blue_ghost_left_1.h"
#include "images/ghost/image_pink_ghost_down_0.h"
#include "images/ghost/image_pink_ghost_down_1.h"
#include "images/ghost/image_pink_ghost_right_0.h"
#include "images/ghost/image_pink_ghost_right_1.h"
#include "images/ghost/image_pink_ghost_up_0.h"
#include "images/ghost/image_pink_ghost_up_1.h"
#include "images/ghost/image_pink_ghost_left_0.h"
#include "images/ghost/image_pink_ghost_left_1.h"
#include "images/ghost/image_orange_ghost_down_0.h"
#include "images/ghost/image_orange_ghost_down_1.h"
#include "images/ghost/image_orange_ghost_right_0.h"
#include "images/ghost/image_orange_ghost_right_1.h"
#include "images/ghost/image_orange_ghost_up_0.h"
#include "images/ghost/image_orange_ghost_up_1.h"
#include "images/ghost/image_orange_ghost_left_0.h"
#include "images/ghost/image_orange_ghost_left_1.h"
#include "images/ghost/image_ghost_scared_0.h"
#include "images/ghost/image_ghost_scared_1.h"
#include "images/ghost/image_ghost_scared_2.h"
#include "images/ghost/image_ghost_scared_3.h"
#include "images/ghost/image_dead_ghost_left.h"
#include "images/ghost/image_dead_ghost_right.h"
#include "images/ghost/image_dead_ghost_down.h"
#include "images/ghost/image_dead_ghost_up.h"
#include "images/map/image_food.h"
#include "images/map/image_big_food.h"
#include "images/map/image_empty.h"
#include "images/map/image_food_large.h"
#include "images/map/image_big_food_large.h"
#include "images/map/image_empty_large.h"
#include "images/map/image_food_tiny.h"
#include "images/map/image_horizontal_empty.h"
#include "images/map/image_vertical_empty.h"
#include "images/map/image_wall_0.h"
#include "images/map/image_wall_1.h"
#include "images/map/image_wall_2.h"
#include "images/map/image_wall_3.h"
#include "images/map/image_wall_4.h"
#include "images/map/image_wall_5.h"
#include "images/map/image_wall_6.h"
#include "images/map/image_wall_7.h"
#include "images/map/image_wall_8.h"
#include "images/map/image_wall_9.h"
#include "images/map/image_wall_a.h"
#include "images/map/image_wall_b.h"
#include "images/map/image_wall_c.h"
#include "images/map/image_wall_d.h"
#include "images/map/image_wall_e.h"
#include "images/map/image_wall_f.h"
#include "images/map/image_wall_g.h"
#include "images/map/image_wall_h.h"
#include "images/map/image_wall_i.h"
#include "images/map/image_wall_j.h"
#include "images/map/image_wall_k.h"
#include "images/map/image_wall_l.h"
#include "images/map/image_wall_m.h"
#include "images/map/image_wall_n.h"
#include "images/map/image_wall_o.h"
#include "images/map/image_wall_p.h"
#include "images/map/image_wall_q.h"
#include "images/map/image_wall_r.h"


// forward declaration
typedef struct pacman Pacman;
typedef struct ghost Ghost;
typedef struct gameMap GameMap;
typedef struct canvas Canvas;

/**************************************** UTIL ****************************************/
#define MAP_COLUMN (20)
#define MAP_ROW (20)
#define TOTAL_TILES ((MAP_COLUMN) * (MAP_ROW))
#define MAX_NUM_GHOSTS (4)
#define DIRECTION_UP (0)
#define DIRECTION_RIGHT (1)
#define DIRECTION_DOWN (2)
#define DIRECTION_LEFT (3)
#define DIRECTION_STOP (-1)
#define FOOD_SYMBOL ('.')
#define BIG_FOOD_SYMBOL ('*')
#define MIN_WALL_SYMBOL_LETTER ('a')
#define MAX_WALL_SYBMOL_LETTER ('r')
#define EMPTY_SYMBOL (' ')
#define PACMAN_SYMBOL ('S')
#define RED_GHOST_SYMBOL ('R')
#define BLUE_GHOST_SYMBOL ('B')
#define PINK_GHOST_SYMBOL ('P')
#define ORANGE_GHOST_SYMBOL ('O')
#define IS_GHOST_SYMBOL(symbol) ((symbol) == (RED_GHOST_SYMBOL) || (symbol) == (BLUE_GHOST_SYMBOL) || (symbol) == (PINK_GHOST_SYMBOL) || (symbol) == (ORANGE_GHOST_SYMBOL))
#define GRID_OFFSET(x, y) ((x) * (MAP_COLUMN) + (y))
#define GRID_X(offset) ((offset) / (MAP_COLUMN))
#define GRID_Y(offset) ((offset) % (MAP_COLUMN))
#define GREEDINESS (20)
#define GAME_OVER (-1)
#define GAME_CONTINUE (0)
#define GAME_WIN (1)
#define FOOD_POINT (10)
#define BIG_FOOD_POINT (100)
#define EAT_GHOST_POINT (1000)
#define GRID_SIDE_LENGTH (8)
#define TINY_SIDE_LENGTH (2)
#define ANIMATION_DELAY (80000)
#define WIN_LOSE_DELAY (800000)
#define CHARACTER_SIDE_LENGTH (14)
#define RED_GHOST (0)
#define BLUE_GHOST (1)
#define PINK_GHOST (2)
#define ORANGE_GHOST (3)
#define NORMAL_GHOST (0)
#define SCARED_GHOST (1)
#define DEAD_GHOST (2)
#define WARNING_SCARE_COUNT (16)
#define INITIAL_SCARE_COUNT (64)

// mazeUtil
int manhattanDistance(int x1, int y1, int x2, int y2);
void nextPosition(int x, int y, int move, int result[], GameMap *gameMap);
// imageUtil
const unsigned short *getWallImage(char type);
const unsigned short *getGhostImage(Ghost *ghost, int round);
const unsigned short *getPacmanImage(Pacman *pacman, int round);
// renderUtil
void delay(int time);
// global definition
extern unsigned char isCheat;

/**************************************** GAME_MAP ****************************************/

struct gameMap {
    /**
     * stores where the foods and walls are
     */
    unsigned char grids[TOTAL_TILES];

    /**
     * an array of pointer to ghost object
     */
    Ghost *ghosts[MAX_NUM_GHOSTS];

    /**
     * number of ghost in game
     */
    int numGhosts;

    /**
     * number of foods remaining
     */
    int numFoods;

    /**
     * pacman object
     */
    Pacman *pacman;

    /**
     * method to tell if a pair of cooridinates correspond to wall
     * @param self referernce for creating method
     * @param x x coordinate
     * @param y y coordinate
     * @return 1 if it is wall, 0 otherwise
     */
    int (*isWall)(struct gameMap *self, int x, int y);

    /**
     * method to tell if a pair of coordinates correspond to food
     * @param self reference for creating method
     * @param x x coordiante
     * @param y y coordinate
     * @return 1 if has food, 0 otherwise
     */
    int (*isFood)(struct gameMap *self, int x, int y);

    /**
     * method to tell if a pair of coordinates is too close to ghost
     * @param self reference for creating method
     * @param x x coordiante
     * @param y y coordinate
     * @return 1 if is ghost, 0 otherwise
     */
    int (*nearGhost)(struct gameMap *self, int x, int y);

    /**
     * method to set food on a pair of coordinate
     * @param self reference for creating method
     * @param x x coordinate
     * @param y y coordinate
     * @param food 0 for no food and 1 for food
     */
    void (*setFood)(struct gameMap *self, int x, int y, int food);

    /**
     * get the outcome of the game
     * @param self reference for creating method
     * @return 1 if win, 0 if continue, and -1 if lost
     */
    int (*getOutcome)(struct gameMap *self);
};
/**
 * constructor of a gameMap
 */
GameMap *new_GameMap(char *map);
/**
 * destructor of a gameMap
 */
void delete_GameMap(GameMap *self);

/**************************************** PACMAN ****************************************/
#define PACMAN_LIVE (1)
#define  PACMAN_DEAD (0)
struct pacman {
    /**
     * pacman's x position
     */
    int x;

    /**
     * pacman's y position
     */
    int y;

    /**
     * pacman's previous x position
     */
    int prevX;

    /**
     * pacman's previous y position
     */
    int prevY;

    /**
     * pacman's score
     */
    int score;

    /**
     * "00000000"
     *         ^-------- live: 1, dead: 0
     *        ^--------- eating: 1, close: 0
     *      ^^---------- going up: 00, right: 01, down: 10, left: 11
     */
    unsigned char status;

    /**
     * method to decide if the pacman is still alive
     * @param self reference for creating method
     */
    int (*isLive)(struct pacman *self);

    /**
     * method to get the direction of the pacman
     * @param self reference for creating method
     * @return the direction in which pacman travels, 0 for up, 1 right, 2 down, 3 up
     */
    int (*getDirection)(struct pacman *self);

    /**
     * method to set the direction of the pacman
     * @param self reference for creaing method
     */
    void (*setDirection)(struct pacman *self, int dir);

    /**
     * method to move the pacman in the grid world
     * @param self reference for creating method
     * @param dir direction in which to move pacman
     * @param maxColumn max X of the grid
     * @param maxRow max y of the grid
     */
    void (*moveDirection)(struct pacman *self, int dir, GameMap *gameMap);

    /**
     * setter method to toggle the living state of pacman
     * @param self reference for creating method
     * @param live to tell if the pacman is alive, 1 for live and 0 for dead
     */
    void (*setLive)(struct pacman *self, int live);
};
/**
 * constructor of a pacman
 */
Pacman *new_Pacman(void);
/**
 * destructor of a pacman
 */
void delete_Pacman(Pacman *self);


/**************************************** GHOST ****************************************/
struct ghost {
    /**
     * ghost's x position
     */
    int x;

    /**
     * ghost's y position
     */
    int y;

    /**
     * ghost's previous x position
     */
    int prevX;

    /**
     * ghost's previous y position
     */
    int prevY;

    /**
     * "00000000"
     *        ^^--------- going up: 00, right: 01, down: 10, left: 11
     *      ^^----------- red: 00, blue: 01, pink: 10, blue: 11
     *    ^^------------- normal: 00, scared: 01, dead: 10
     */
    unsigned char status;

    /**
     * ghost's scareness count down
     */
    int scareCountdown;

    /** 
     * method to get the direction of the ghost
     * @param self reference for creating method
     * @return the direction in which ghost travels, 0 for up, 1 right, 2 down, 3 up
     */
    int (*getDirection)(struct ghost *self);

    /**
     * method to set the direction of the ghost
     * @param self reference for creaing method
     */
    void (*setDirection)(struct ghost *self, int dir);

    /**
     * method to get the color of the ghost
     * @param self reference for creating method
     * @return the color of the ghost
     */
    int (*getColor)(struct ghost *self);

    /**
     * method to set the color of the ghost
     * @param self reference for creating method
     */
    void (*setColor)(struct ghost *self, int color);

    /**
     * method to get the state of the ghost
     * @param self reference for creating method
     * @return the state of the ghost
     */
    int (*getState)(struct ghost *self);

    /**
     * method to set the state of the ghost
     * @param self reference for creating method
     */
    void (*setState)(struct ghost *self, int state);

    /**
     * method to make the next move based on current game map
     * @param self reference for creating method
     * @param pacman reference to the pacman in game
     * @param isWall function pointer to probe walls
     * @return integer to represent next move, 
     */
    int (*makeNextMove)(struct ghost *self, GameMap *gameMap);

    /**
     * method to let the ghost decide its next move based on current game map
     * @param self reference for creating method
     * @param dir direction in which to move the ghost
     * @param isWallPtr function pointer to probe walls
     */
    void (*moveDirection)(struct ghost *self, int dir, GameMap *gameMap);
};
/**
 * constructor of a ghost
 */
Ghost *new_Ghost(void);
/**
 * destructor of a ghost
 */
void delete_Ghost(Ghost *self);

/**************************************** CANVAS ****************************************/
/**
 * GUI class
 */
struct canvas {

    /**
     * print the entire game map to the gba screen
     */
    void (*printGameMap)(struct canvas *self, GameMap *gameMap, int level);

    /**
     * print the start page of pacman game with instructions
     */
    void (*printStartPage)(struct canvas *self);

    /**
     * print the game over page of the pacman game with instructions
     */
    void (*printGameOverPage)(struct canvas *self);

    /**
     * print the game win page of the pacman game with instructions and next leve
     */
    void (*printGameWinPage)(struct canvas *self);

    /**
     * print the current mode to the canvas: normal or cheat
     */
    void (*drawToggleMode)(struct canvas *self);
    
    /**
     * animate characters on the gamemap by partial animation
     */
    void (*animateCharacters)(struct canvas *self, GameMap *gameMap);
};
/**
 * constructor of a canvas
 */
Canvas *new_Canvas(void);
/**
 * destructor of a cancas
 */
void delete_Canvas(Canvas *self);


/*
* For example, for a Snake game, one could be:
*
* typedef struct snake {
*   int heading;
*   int length;
*   int x;
*   int y;
* } Snake;
*
*
* 
*
*
* Example of a struct to hold state machine data:
* 
* typedef struct state {
*   int currentState;
*   int nextState;
* } State
*
*/

#endif
