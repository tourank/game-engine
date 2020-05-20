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

    assetManager->addTexture("tank-image", std::string("./assets/images/tank-big-right.png").c_str());
    assetManager->addTexture("chopper-image", std::string("./assets/images/chopper-spritesheet.png").c_str());
    assetManager->addTexture("radar-image",std::string("./assets/images/radar.png").c_str());

    Entity &tankEntity(manager.addEntity("tank"));
    tankEntity.addComponent<TransformComponent>(0,0,20,20,32,32,1);
    tankEntity.addComponent<SpriteComponent>("tank-image");

    Entity& radarEntity(manager.addEntity("Radar"));
    radarEntity.addComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
    radarEntity.addComponent<SpriteComponent>("radar-image", 8, 150, false, true);

    Entity &chopperEntity(manager.addEntity("chopper"));
    chopperEntity.addComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
    chopperEntity.addComponent<SpriteComponent>("chopper-image", 2,90,true,false);
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
