#pragma once

#include <map>
#include <string>
#include <raylib.h>
#include "vector2.h"

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
        void change_pos(Vector2f new_pos);
        void draw(float dt);
};

struct animation;

class AnimatedSprite : public Sprite{
    public:
        std::map<std::string, animation> animations;
        float current_time;
};