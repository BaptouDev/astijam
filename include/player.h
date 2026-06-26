#pragma once
#include <raylib.h>
#include "include/entity.h"
#include "include/physics.h"

class Player : public AnimatedEntity {
    public:
        //movement variables
        float speed;
        float accel;
        bool was_moving;

        //animation variables
        Vector2f last_dir;

        //sword variables
        Sprite sword_sprite;
        float sword_rot;
        float col_radius;
        float dist;
        float sword_dist_from_pivot;
        float sword_max_rot;
        float sword_rot_time;
        float sword_rot_timer;
        float sword_rot_halfway;
        float init_rot;

        PhysicsBody body;
        void update(float dt,Vector2f mouse_pos) override;
        void draw(float dt,Vector2f camera_pos) override;
        Player(Vector2f init_pos);
};
//if (IsKeyDown(KEY_RIGHT))