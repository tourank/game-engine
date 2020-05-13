#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Entity.h"
#include "Component.h"
#include <vector>

class EntityManager {
    private:
        std::vector<Entity*> entities;
    public:
        void update(float deltaTime);
        void Renderer();
        void clearEntities();
        bool hasNoEntities();
        Entity &addEntity(std::string entityName);
        std::vector<Entity*> getEntities() const;
        unsigned int getNumEntities();
};

#endif
