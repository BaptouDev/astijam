#include <vector>
#include <raylib.h>
#include "vector2.h"

class Sprite{
    public:
        Vector2f pos;
        Vector2f scale;
        float rotation;
        Texture2D image;
        int tile_size;
        bool is_flipped;
        void change_pos(Vector2f new_pos);
        void draw(float dt);
};

struct animation;

class AnimatedSprite : public Sprite{
    public:
        std::vector<animation> animations;
        int current_frame;
        float current_time;
};