#include <iostream>
#include "constants.h"
#include "Game.h"
#include "./Components/TransformComponent.h"
#include "AssetManager.h"
#include "./Components/SpriteComponent.h"
#include "../lib/glm/glm.hpp" //header to glm library downloaded
#include "EntityManager.h"

EntityManager manager;
AssetManager *Game::assetManager = new AssetManager(&manager);
SDL_Renderer *Game::renderer;

Game::Game() {
    this->isRunning = false;
}
Game::~Game() {
}

bool Game::checkIfRunning() const {
    return this->isRunning;
}

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

    // At this point the game is running, since it must've failed both if conditions
    loadLevel(0);

    isRunning = true;
    return;
}
void Game::loadLevel(int levelNumber){

    // TODO file path might be wrong, so change it if error
    std::string textureFilePath = "./assets/images/tank-big-right.png";
    assetManager->addTexture("tank-image", textureFilePath.c_str());
    Entity &newEntity(manager.addEntity("projectile"));
    newEntity.addComponent<TransformComponent>(0,0,20,20,32,32,1);
    newEntity.addComponent<SpriteComponent>("tank-image");
}

// Processing input keys here 
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
    // Wait until 16 ms has ellapsed since last frame
    // If we render/update frames too quick we must put process to sleep to sync 
    int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);
    if(timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME){
        SDL_Delay(timeToWait);
    }

    //difference in ticks since last frame converted to seconds 
    float deltaTime = (SDL_GetTicks() - ticksLastFrame)/ 1000.0f;

    //Must cap delta time to maintain synchronous behaviour 
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    ticksLastFrame = SDL_GetTicks();

    manager.update(deltaTime); // loops over all entities and calls their update function

}
void Game::Renderer() {
    
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    if(manager.hasNoEntities()){
        return;
    }
    manager.Renderer();
    
    SDL_RenderPresent(renderer);
}
void Game::destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
