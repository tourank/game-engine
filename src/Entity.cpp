#include "Entity.h"

Entity::Entity(EntityManager &manager): manager(manager){
    this->isActive = true;
}  

Entity::Entity(EntityManager &manager, std::string name): manager(manager), name(name) {
    this->isActive = true;
}

void Entity::update(float deltaTime) {
    // loop all components of entity and call update 
    for(auto &component : components) {
        component->update(deltaTime);
    }
}
void Entity::Renderer() {

    for(auto &component : components) {
        component->Renderer();
    }
}

void Entity::destroy() {
    this->isActive = false;
}

bool Entity::IsActive() const {
    return this->isActive;
}
