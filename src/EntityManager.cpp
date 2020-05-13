#include "Entity.h"
#include <string>
#include <vector>
#include "EntityManager.h"

void EntityManager::clearEntities() {

    for(auto& entity : entities) {
        entity->destroy();
    }
}

bool EntityManager::hasNoEntities() {
    return entities.size()==0;
}

void EntityManager::update(float deltaTime) {

    for(auto &entity : entities) {
        entity->update(deltaTime);
    }
}

void EntityManager::Renderer() {
    for(auto &entity : entities) {
        entity->Renderer();
    }
}

// Add and return the added entity
Entity& EntityManager::addEntity(std::string entityName) {

    Entity *entity = new Entity(*this, entityName);
    entities.emplace_back(entity); // entities holds a list of entity pointers 
    return *entity;
}

std::vector<Entity*> EntityManager::getEntities() const {
    return entities;
}

unsigned int EntityManager::getNumEntities() {
    return entities.size();
}
