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

    sword_sprite = Sprite("res/img/boneweapon.png",init_pos,4.0,0.0,Vector2f(16*4.0,16*4.0),32,0);//const char* path_to_img, Vector2f pos, float scale, float rotation, Vector2f origin, int tile_size, int index
    dist = 26*4.0;
    sword_dist_from_pivot = 16*4.0;
    sword_max_rot = 0;
    sword_rot_timer=.5;
    sword_rot_time=.67;

    maxhp = 1000;
    curhp = 750;
    

    h_barw = 200;
    h_barh = 15;
    
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

    if(sword_rot_time<=sword_rot_timer){
        sword_rot = cerp(-sword_max_rot,sword_max_rot,sword_rot_time/sword_rot_timer);
    }else{
        sword_rot = sword_max_rot;
    }

    Vector2f relative_mouse_pos = body.position + sprite.origin - mouse_pos;
    float mouse_angle = atan2(relative_mouse_pos.y,relative_mouse_pos.x);
    sword_sprite.rotation = RAD2DEG*(mouse_angle+sword_rot);
    Vector2f pivot = Vector2f(-cos(mouse_angle),-sin(mouse_angle))*dist + body.position;//+Vector2f(-cos(sword_rot),-sin(sword_rot))*16*4.0; //+ sprite.origin;
    //Vector2f sword_pos = pivot + Vector2f(cos(sword_rot+mouse_angle), sin(sword_rot+mouse_angle))*sword_dist_from_pivot;
    sword_sprite.pos = pivot;
    body.velocity = lerpv(body.velocity,input.normalized()*speed,accel*dt);

    
    body.update_physics_col_list({},dt);
    body.last_pos = body.position;
    was_moving = is_moving;
}

void Player::draw(float dt,Vector2f camera_pos){
    sprite.pos = body.position;
    sword_sprite.draw(dt,camera_pos);
    DrawRectangle(400-h_barw/2,400,h_barw,h_barh,BLACK);
    DrawRectangle(400-h_barw/2,400,h_barw*(static_cast<float>(curhp)/(float)maxhp),h_barh,GREEN);
    AnimatedEntity::draw(dt,camera_pos);
}