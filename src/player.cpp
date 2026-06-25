#include <include/player.h>
#include <iostream>
#include <cmath>
#include "include/utils.h"

Player::Player(Vector2f init_pos):
AnimatedEntity(init_pos,"player", {}, "res/img/player.png", 4.0, 0.0, 32, 0,
     {{"idle_front", {{6},{1.0},false}},
    {"idle_back", {{9},{1.0},false}},
    {"idle_right", {{0},{1.0},false}},
    {"idle_left", {{3},{1.0},false}},
    {"run_front", {{6,7,6,8},{.3,.3,.3,.3},false}},
    {"run_back", {{9,10,9,11},{.3,.3,.3,.3},false}},
    {"run_right", {{0,1,0,2},{.3,.3,.3,.3},false}},
    {"run_left", {{3,4,3,5},{.3,.3,.3,.3},false}},}, 
     "idle_front") {
    body = PhysicsBody(init_pos,Vector2f(16,16),Vector2f(8,8),{{"hit",false}});
    speed=200;
    accel=67;

    sword_sprite = Sprite("res/img/boneweapon.png",init_pos,4.0,0.0,Vector2f(16*4.0,16*4.0),16,0);//const char* path_to_img, Vector2f pos, float scale, float rotation, Vector2f origin, int tile_size, int index
    dist = 32*4.0;
    
    was_moving=false;
    sprite.origin = Vector2f(16*sprite.scale,16*sprite.scale);
}

void Player::update(float dt,Vector2f mouse_pos){
    sword_rot_timer+=dt;

    Vector2f input= Vector2f(0,0);
    bool is_moving = false;

    if(IsKeyDown(KEY_RIGHT)){
        input=input+Vector2f(1,0);
        
        if (!(input.x == last_dir.x)){
            sprite.change_anim("run_right");
        }
        is_moving =true;
        was_moving =true;
    }
    if(IsKeyDown(KEY_LEFT)){
        input=input+Vector2f(-1,0);
        if (!(input.x == last_dir.x)){
            sprite.change_anim("run_left");
        }
        is_moving =true;
        was_moving =true;
    }
    if(IsKeyDown(KEY_UP)){
        input=input+Vector2f(0,-1);
        if (!(input.y == last_dir.y)){
            sprite.change_anim("run_back");
        }
        is_moving =true;
        was_moving =true;
    }
    if(IsKeyDown(KEY_DOWN)){
        input=input+Vector2f(0,1);
        if (!(input.y == last_dir.y)){
            sprite.change_anim("run_front");
        }
        is_moving =true;
        was_moving =true;
    }
    if(is_moving){
        last_dir = input;
    }else{
        if(last_dir.x==1){
            sprite.change_anim("idle_right");
        }
        if(last_dir.x==-1){
            sprite.change_anim("idle_left");
        }
        if(last_dir.y==1){
            sprite.change_anim("idle_front");
        }
        if(last_dir.y==-1){
            sprite.change_anim("idle_back");
        }
    }

    Vector2f relative_mouse_pos = body.position + sprite.origin - mouse_pos;
    float mouse_angle = atan2(relative_mouse_pos.y,relative_mouse_pos.x);
    sword_sprite.rotation = RAD2DEG*mouse_angle;
    sword_sprite.pos = Vector2f(cos(mouse_angle),sin(mouse_angle))*dist + body.position + sprite.origin;

    body.velocity = lerpv(body.velocity,input.normalized()*speed,accel*dt);
    body.update_physics_col_list({},dt);
    body.last_pos = body.position;
    was_moving = is_moving;
}

void Player::draw(float dt){
    sprite.pos = body.position;
    sword_sprite.draw(dt);
    AnimatedEntity::draw(dt);
}