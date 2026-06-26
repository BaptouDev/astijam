#pragma once
#include <raylib.h>
#include "include/entity.h"
#include "include/physics.h"


class Enemy : public AnimatedEntity {
    public:
        //movement variables
        float speed;
        bool was_looking_right;
        int hp;
        int maxhp;

        //animation variables
        Vector2f last_dir;


        bool is_dead;

        Vector2f player_pos;

        PhysicsBody body;
        void update(float dt,Vector2f mouse_pos) override;
        void draw(float dt,Vector2f camera_pos) override;
        void damage(int damage) override;
        void is_dead() override;
        Enemy(Vector2f init_pos);
        void get_player_pos(Vector2f pos);
};
//if (IsKeyDown(KEY_RIGHT))