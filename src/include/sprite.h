#pragma once

#include <map>
#include <string>
#include <vector>
#include <raylib.h>
#include "include/vector2.h"

class Sprite{
    public:
        Vector2f pos;
        float scale;
        float rotation;
        Texture2D image;
        int tile_size;
        bool is_flipped;
        int current_frame;
        Sprite(const char* path_to_img, Vector2f pos, float scale, float rotation, int tile_size, int index);
        Sprite();
        void change_pos(Vector2f new_pos);
        virtual void draw(float dt);
};

struct animation;

class AnimatedSprite : public Sprite{
    public:
        std::map<std::string, animation> animations;
        std::string base_anim;
        float current_time;
        std::string current_anim;
        void draw(float dt) override;
        void change_anim(std::string new_anim);
        AnimatedSprite(const char* path_to_img, Vector2f pos, float scale, float rotation, int tile_size, int index, std::map<std::string, animation> animations, std::string base_anim);
        AnimatedSprite();
};