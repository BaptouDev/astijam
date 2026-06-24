#pragma once
#include <raylib.h>
#include "include/entity.h"
#include "include/physics.h"

class Player : AnimatedEntity {
    public:
        float speed;
        float accel;
        PhysicsBody body;
        void update(float dt) override;
        void draw(float dt) override;
        Player(Vector2f init_pos);
};
//if (IsKeyDown(KEY_RIGHT))