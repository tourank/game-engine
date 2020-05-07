#include <iostream>
#include "constants.h"
#include "Game.h"
#include "../lib/glm/glm.hpp" //header to glm library downloaded

Game::Game() {
    this->isRunning = false;
}
Game::~Game() {
}

bool Game::checkIfRunning() const {
    return this->isRunning;
}

glm::vec2 projectilePos = glm::vec2(0.0f, 0.0f);
glm::vec2 projectileVel = glm::vec2(20.0f, 20.0f);

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
    //Wait until 16 ms has ellapsed since last frame
    //if we render/update frames too quick we must put process to sleep to sync 
    int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);
    if(timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME){
        SDL_Delay(timeToWait);
    }

    //difference in ticks since last frame converted to seconds 
    float deltaTime = (SDL_GetTicks() - ticksLastFrame)/ 1000.0f;

    //Must cap delta time to maintain synchronous behaviour 
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    ticksLastFrame = SDL_GetTicks();

    projectilePos = glm::vec2(projectilePos.x + projectileVel.x * deltaTime, projectilePos.y + projectileVel.y * deltaTime);
}
void Game::Renderer() {
    
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    SDL_Rect projectile = {
        (int) projectilePos.x,
        (int) projectilePos.y,
        10,
        10
    };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &projectile);
    SDL_RenderPresent(renderer);
}
void Game::destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
