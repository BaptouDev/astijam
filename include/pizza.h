#pragma once
#include <raylib.h>

#include <include/entity.h>


class Pizza : public SpriteEntity {
    public:
   

        PhysicsBody body;
        void update(float dt,Vector2f mouse_pos) override;
        void draw(float dt,Vector2f camera_pos) override;
        void damage(int damage) override;

        Pizza(Vector2f init_pos);

};

