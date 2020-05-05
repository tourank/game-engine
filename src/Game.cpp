#include <iostream>
#include "constants.h"
#include "Game.h"


Game::Game() {
    this->isRunning = false;
}
Game::~Game() {
}

bool Game::checkIfRunning() const {
    return this->isRunning;
}

float projectilePosX = 0.0f;
float projectilePosY = 0.0f;
float projectiveVelX = 0.5f;
float projectiveVelY = 0.5f;

void Game::initialize(int width, int height) {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cerr<<"Error"<<std::endl;
        return;
    }
    window = SDL_CreateWindow( //SDL pointer declared in header
            NULL, 
            SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED, 
            width, 
            height,
            SDL_WINDOW_BORDERLESS
    );
    if(!window){
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(window,-1,0); //SDL pointer declared in header 
    if(!renderer){
        std::cerr << "Error creating SDL renderer." << std::endl;
        return; 
    }
    //at this point the game is running, since it must've failed both if conditions
    isRunning = true;
    return;
}
//processing input keys here 
void Game::processInput() {
    
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE){
                isRunning = false;
            }
        default:
            break;
    }
}
void Game::update() {
    
    projectilePosX += projectiveVelX;
    projectilePosY += projectiveVelY;
}
void Game::Renderer() {
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);//clear back buffer
    int convertedProjectilePosX = int (projectilePosX);
    int convertedProjectilePosY = int (projectilePosY);
    SDL_Rect projectile;
    projectile.x = convertedProjectilePosX; 
    projectile.y = convertedProjectilePosY;
    projectile.w = 10;
    projectile.h = 10;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &projectile);
    SDL_RenderPresent(renderer);
}
void Game::destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
