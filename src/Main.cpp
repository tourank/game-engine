#include <iostream>
#include "Game.h"
#include "constants.h"

int main(int argc, char *argv[]) {
    //**** SKELETON ****
    Game *game = new Game();
    game->initialize(WINDOW_WIDTH,WINDOW_HEIGHT);

    while(game->checkIfRunning()) {
        game->processInput(); //use arrow cause its a pointer and we have to deref to access object parameters 
        game->update();
        game->Renderer();
    }
    game->destroy();
    return 0;
}
