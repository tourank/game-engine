#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
class AssetManager;

class Game {
    private:
        bool isRunning;
        SDL_Window *window;
   public:
        Game();
        ~Game();
        static SDL_Renderer *renderer;
        static AssetManager *assetManager;
        void loadLevel(int levelNumber);
        int ticksLastFrame;
        bool checkIfRunning() const; //getter
        void initialize(int width, int height);
        void processInput();
        void update();
        void Renderer();
        void destroy();

};

#endif
