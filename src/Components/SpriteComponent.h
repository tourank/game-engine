#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL2/SDL.h>
#include "../TextureManager.h"
#include "../AssetManager.h"
#include "TransformComponent.h"
#include "../Animation.h"

class SpriteComponent : public Component {
    private:
        TransformComponent *transform; // keep track of player's transform
        SDL_Texture *texture;
        SDL_Rect sourceRectangle;
        SDL_Rect destinationRectangle; 
        bool isAnimated;
        int numFrames;
        int animationSpeed;
        bool isFixed; // fixed sprites always stay in the same position on the screen (like text, score, etc.)
        std::map<std::string, Animation> animations; // all animations for sprite component 
        std::string currentAnimationName;
        unsigned int animationIndex = 0;
    public:
        SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
        SpriteComponent(std::string assetTextureID) {
            this->isAnimated = false;
            this->isFixed = false;
            setTexture(assetTextureID);
        }
        SpriteComponent(std::string assetTextureID, bool isFixed) {
            this->isAnimated = false;
            this->isFixed = false;
            setTexture(assetTextureID);
        }
        SpriteComponent(std::string id, int numFrames, int animationSpeed, bool hasDirections, bool isFixed) {
            this->isAnimated = true;
            this->numFrames = numFrames;
            this->animationSpeed = animationSpeed;
            this->isFixed = isFixed;

            if (hasDirections) {
                Animation downAnimation = Animation(0, numFrames, animationSpeed);
                Animation rightAnimation = Animation(1, numFrames, animationSpeed);
                Animation leftAnimation = Animation(2, numFrames, animationSpeed);
                Animation upAnimation = Animation(3, numFrames, animationSpeed);

                animations.emplace("DownAnimation", downAnimation);
                animations.emplace("RightAnimation", rightAnimation);
                animations.emplace("LeftAnimation", leftAnimation);
                animations.emplace("UpAnimation", upAnimation);
                this->animationIndex = 0;
                this->currentAnimationName = "DownAnimation";
            }
            else {
                Animation singleAnimation = Animation(0, numFrames, animationSpeed);
                animations.emplace("SingleAnimation", singleAnimation);
                this->animationIndex = 0;
                this->currentAnimationName = "SingleAnimation";
            }

            play(this->currentAnimationName);
            setTexture(id);
        }
        void play(std::string animationName) {
            // picks something from the map of animations to play
            
            numFrames = animations[animationName].numFrames;
            animationIndex = animations[animationName].index;
            animationSpeed = animations[animationName].animationSpeed;
            currentAnimationName = animationName;
        }
        void setTexture(std::string assetTextureID) {
            texture = Game::assetManager->getTexture(assetTextureID);
        }
        void initialize() override {
            transform = owner->getComponent<TransformComponent>();
            sourceRectangle.x = 0;
            sourceRectangle.y = 0;
            sourceRectangle.w = transform->width;
            sourceRectangle.h = transform->height;
        }
        void update(float deltaTime) override {
            if (isAnimated) {
                sourceRectangle.x = sourceRectangle.w * static_cast<int>(((SDL_GetTicks() / animationSpeed) % numFrames));
            }
            sourceRectangle.y = animationIndex = transform->height;
            destinationRectangle.x = static_cast<int>(transform->position.x);
            destinationRectangle.y = static_cast<int>(transform->position.y);
            destinationRectangle.w = transform->width * transform->scale;
            destinationRectangle.h = transform->height * transform->scale;
        }

        void Renderer() override {
            TextureManager::Draw(texture, sourceRectangle, destinationRectangle, spriteFlip);
        }
};

#endif
