#pragma once
#include <raylib.h>
#include "include/entity.h"
#include "include/physics.h"

class Player : AnimatedEntity {
    public:
        //movement variables
        float speed;
        float accel;

        //animation variables
        Vector2f last_dir;

        PhysicsBody body;
        void update(float dt) override;
        void draw(float dt) override;
        Player(Vector2f init_pos);
};
//if (IsKeyDown(KEY_RIGHT))