#pragma once
#include <string>
#include <vector>
#include <raylib.h>
#include "include/vector2.h"
#include "include/sprite.h"
#include "include/physics.h"
#include "include/player.h"

using namespace std;

class Entity{
    public:
        Vector2f position;
        string tag;
        vector<string> layers;
        virtual void update(float dt)=0;
        virtual void draw(float dt)=0;
        Entity(Vector2f position, string tag, vector<string> layers);
};

class SpriteEntity : Entity{
    public:
        Sprite sprite;
        void update(float dt) override;
        void draw(float dt) override;
        SpriteEntity(Vector2f position, string tag, vector<string> layers,const char* path_to_img, float scale, float rotation, int tile_size, int index);
};

class AnimatedEntity : Entity{
    public:
        AnimatedSprite sprite;
        void update(float dt) override;
        void draw(float dt) override;
        AnimatedEntity(Vector2f position, string tag, vector<string> layers, const char* path_to_img, float scale, float rotation, int tile_size, int index, std::map<std::string, animation> animations, std::string base_anim);
};