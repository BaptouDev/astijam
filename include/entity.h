#pragma once
#include <string>
#include <vector>
#include <raylib.h>
#include "include/vector2.h"
#include "include/sprite.h"
#include "include/physics.h"
//#include "include/player.h"

using namespace std;

class Entity{
    public:
        Vector2f position;
        string tag;
        vector<string> layers;
        virtual void update(float dt,Vector2f mouse_pos)=0;
        virtual void draw(float dt,Vector2f camera_pos)=0;
        Entity(Vector2f position, string tag, vector<string> layers);
};

class SpriteEntity : public Entity{
    public:
        Sprite sprite;
        void update(float dt,Vector2f mouse_pos) override;
        void draw(float dt,Vector2f camera_pos) override;
        SpriteEntity(Vector2f position, string tag, vector<string> layers,const char* path_to_img, float scale, float rotation, int tile_size, int index);
};

class AnimatedEntity : public Entity{
    public:
        AnimatedSprite sprite;
        void update(float dt,Vector2f mouse_pos) override;
        void draw(float dt,Vector2f camera_pos) override;
        AnimatedEntity(Vector2f position, string tag, vector<string> layers, const char* path_to_img, float scale, float rotation, int tile_size, int index, std::map<std::string, animation> animations, std::string base_anim);
};

class PhysicsEntity : AnimatedEntity {
    public:
        PhysicsBody body;
        PhysicsEntity(Vector2f position, string tag, vector<string> layers, 
            const char* path_to_img, float scale, float rotation, int tile_size, int index, 
            std::map<std::string, animation> animations, std::string base_anim, 
            Vector2 body_dimensions, Vector2 offset);
};