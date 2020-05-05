#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Game {
    private:
        bool isRunning;
        SDL_Window *window;
        SDL_Renderer *renderer;
    public:
        Game();
        ~Game();
        bool checkIfRunning() const; //getter
        void initialize(int width, int height);
        void processInput();
        void update();
        void Renderer();
        void destroy();

};

#endif
