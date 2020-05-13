#include "AssetManager.h"

AssetManager::AssetManager(EntityManager *manager): manager(manager) {
}

void AssetManager::clearData() {
    textures.clear();
}

void AssetManager::addTexture(std::string textureID, const char *filePath) {
    textures.emplace(textureID, TextureManager::LoadTexture(filePath));
}

SDL_Texture *AssetManager::getTexture(std::string textureID) {
    return textures[textureID];
}
