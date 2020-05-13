#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <string>
#include "TextureManager.h"
#include "EntityManager.h"

class AssetManager {
    private:
        EntityManager *manager;
        std::map<std::string, SDL_Texture*> textures;
    public:
        AssetManager(EntityManager *manager);
        ~AssetManager();
        void clearData();
        void addTexture(std::string textureID, const char *filePath);
        SDL_Texture *getTexture(std::string textureID);
};

#endif
