#pragma once
#include <raylib.h>
#include "include/entity.h"
#include "include/physics.h"


class FlyingEnemy : public AnimatedEntity {
    public:
        //movement variables
        float speed;
        bool was_looking_right;
        int hp;
        int maxhp;

        //animation variables
        Vector2f last_dir;

        //dive
        float dive_timer;
        float dive_time; //periode
        bool is_diving;
        float dive_speed;
        Vector2f divedirection;
        bool divesright;
        float dive_duration;
        float dive_duration_timer;

        Vector2f player_pos;

        PhysicsBody body;
        void update(float dt,Vector2f mouse_pos) override;
        void draw(float dt,Vector2f camera_pos) override;
        FlyingEnemy(Vector2f init_pos);
        void get_player_pos(Vector2f pos);
};