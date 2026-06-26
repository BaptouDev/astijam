#include <iostream>
#include "include/enemy.h"
#include <cmath>
#include "include/utils.h"

using namespace std;


Enemy::Enemy(Vector2f init_pos):
AnimatedEntity(init_pos,"enemy", {}, "res/img/dinoennemi1.png", 4.0, 0.0, 32, 0,
     {{"idle_left", {{0},{1.0},false}},
      {"idle_right", {{3},{1.0},false}}, 
      {"run_right", {{0,1,0,2},{0.3, 0.3,0.3,0.3}, false }},
      {"run_left",  { {3,4,3,5}, {0.3,0.3,0.3,0.3}, false }}
    },
      "idle_left"
     ) {

       /*    {{"idle_front", {{6},{1.0},false}},
    {"idle_back", {{9},{1.0},false}},
    {"idle_right", {{0},{1.0},false}},
    {"idle_left", {{3},{1.0},false}},
    {"run_front", {{6,7,6,8},{.3,.3,.3,.3},false}},
    {"run_back", {{9,10,9,11},{.3,.3,.3,.3},false}},
    {"run_right", {{0,1,0,2},{.3,.3,.3,.3},false}},
    {"run_left", {{3,4,3,5},{.3,.3,.3,.3},false}},}, */
    body = PhysicsBody(init_pos,Vector2f(16,16),Vector2f(8,8),{{"hit",false}});
    speed=127;
    
    player_pos = Vector2f(0,0);
    
    was_looking_right=false;


    maxhp = 200;
    hp = maxhp;

    is_dead = false;

    sprite.origin = Vector2f(16*sprite.scale,16*sprite.scale);
}

void Enemy::get_player_pos(Vector2f pos){
    player_pos = pos;
}

void Enemy::update(float dt, Vector2f mouse_pos){

    body.position =  (mouse_pos - body.position ).normalized()*speed*dt + body.position;


    if( (mouse_pos.x - body.position.x) <= 0 ){
        if(was_looking_right){
            sprite.change_anim("run_left");
            was_looking_right = false;
        }
    }else{
        if(!was_looking_right){
        sprite.change_anim("run_right");
            was_looking_right = true;
        }
    }
    position = body.position;
}

void Enemy::damage(int amount){
    hp-=amount;
}

/*
    Vector2f relative_mouse_pos = body.position + sprite.origin - mouse_pos;
    float mouse_angle = atan2(relative_mouse_pos.y,relative_mouse_pos.x);

   
    //body.velocity = lerpv(body.velocity,input.normalized()*speed);

    
    body.update_physics_col_list({},dt);
    body.last_pos = body.position;
    was_moving = is_moving;
 */

void Enemy::draw(float dt,Vector2f camera_pos){
    sprite.pos = body.position;
    AnimatedEntity::draw(dt,camera_pos);
}