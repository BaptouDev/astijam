#pragma once
#include <raylib.h>
#include "include/entity.h"
#include "include/physics.h"


class Fireball : public SpriteEntity {
    public:
        Fireball(Vector2f position,float angle, float speed,Vector2f dir);
        Vector2f direction;
        float speed;
        float radius;
        float life_timer;
        float life_time;
        void update(float dt,Vector2f mouse_pos) override;
        void draw(float dt,Vector2f camera_pos) override;
        void damage(int amount) override;
        bool is_dead() override;
};

class Player : public AnimatedEntity {
    public:
        //movement variables
        float speed;
        float accel;
        bool was_moving;

        //animation variables
        Vector2f last_dir;

        vector<PhysicsBody> col_list;

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

        //fireball variables
        float fireball_intervall;
        float fireball_cd;

        float invis_time;
        float invis_timer;

        int curhp;
        int maxhp;

        int h_barw;
        int h_barh;

        PhysicsBody body;

        void get_col_list(vector<PhysicsBody>);
        void update(float dt,Vector2f mouse_pos) override;
        void draw(float dt,Vector2f camera_pos) override;
        void damage(int amount) override;
        bool is_dead() override;
        Player(Vector2f init_pos);
};
//if (IsKeyDown(KEY_RIGHT))
