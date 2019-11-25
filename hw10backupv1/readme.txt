1. Introduction
    This is a simplified implementation of the classical game PACMAN!
    In the case if you are not familiar with Pacman, the game basically
    makes the player control the pacman to navigate through a maze filled
    with food dots. The goal is to eat through all food dots without
    being caught by a ghost. The ghosts moves as fast as your pacman and
    are really smart to figure out where you are, so keep far far away
    from them, and most importantly, don't get stuck in the corner. : )
    If you are caught by a ghost, you lose the game and must restart a
    new game to play. If you eat all dots, you win and can play again!
    In possible future implementations, I am considering to add more
    levels to the game to make it more fun and challenging!

2. How to Play
    1) Start Screen
        Press Start button (ENTER on your keyboard for emulators), and 
        you will enter the main game.

    2) Main Game
        Here on the left you should see a maze layout filled with food
        dots, your pacman, and some ghosts. You can control your pacman
        using the arrow keys on your keyboard to navigate through the
        maze. If you hit the wall, the pacman will try to go in that
        direction but gets stuck there eventually.

        You can exit the game at any time, just hit the Select button
        (DELETE on your keyboard for emulators), and this should
        reset the game state and redirect you to the Start Screen.

        If you get caught by a ghost, you lose and will be redirected
        to the Lose Screen.

        If you win the game by eating all dots. Congratulations, you
        are redirected to the Win Screen.
    
    3. Lose Screen
        Hit Select (DELETE) to restart
    
    4. Win Screen
        Hit Select (DELETE) to restart

3. How I Structured It
    Emm, kind of interesting. I know C is mostly a procedural programming
    language, but somehow I figured out to use function pointers to create
    methods associated with structs, and thus simulating early form of 
    objects, which gives the code an object-oriend taste. However, I just
    used the most simple features of OO like encapsulation, and never
    managed to do fancy things like inheritance or polymorphism, which also
    aren't particularly useful for this small program. However, in this
    style I could separate my control, model, and view logic into different
    modules, and hopefully make the project easier to maintain and debug.

    Particularly about the rendering logic, the maze is dynamically painted
    to the screen by padding tiny pictures (8 x 8 pixels). As the game
    procedes, and ghosts and pacman changes position, the canvas ojbect takes
    advantange of partial rendering instead of drawing out the full screen,
    and thus letting the game flow smoothly.

4. Files I Editted and Created
    gba.c
    game.h
    game.c
    canvas.c
    ghost.c
    pacman.c
    mazeUtil.c
    gameMap.c