#pragma once
#include <raylib.h>
#include "include/vector2.h"
#include "include/sprite.h"
#include "include/physics.h"
#include "include/player.h"

class Entity{
    public:
        Vector2f position;
        virtual void update(float dt);
        virtual void draw(float dt);
        Entity(Vector2f position);
};

class SpriteEntity : Entity{
    public:
        Sprite sprite;
        void update(float dt) override;
        void draw(float dt) override;
        SpriteEntity(Vector2f position,const char* path_to_img, float scale, float rotation, int tile_size, int index);
};

class AnimatedEntity : Entity{
    public:
        AnimatedSprite sprite;
        void update(float dt) override;
        void draw(float dt) override;
        AnimatedEntity(Vector2f position,const char* path_to_img, float scale, float rotation, int tile_size, int index, std::map<std::string, animation> animations, std::string base_anim);
};