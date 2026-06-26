#include <iostream>
#include "include/enemy.h"
#include <cmath>
#include "include/utils.h"

using namespace std;


Enemy::Enemy(Vector2f init_pos):
AnimatedEntity(init_pos,"enemy", {}, "res/img/dinoennemi1.png", 4.0, 0.0, 32, 0,
     {{"idle_left", {{0},{1.0},false}},
        {"idle_right", {{1},{1.0},false}}}, "idle_left"
     ) {
    body = PhysicsBody(init_pos,Vector2f(16,16),Vector2f(8,8),{{"hit",false}});
    speed=67;
    
    player_pos = Vector2f(0,0);
    
    was_moving=false;


    hp = 2000;

    sprite.origin = Vector2f(16*sprite.scale,16*sprite.scale);
}

void Enemy::get_player_pos(Vector2f pos){
    player_pos = pos;
}

void Enemy::update(float dt, Vector2f mouse_pos){

    body.position =  (player_pos - body.position ).normalized()*speed*dt + body.position;


    if( (player_pos.x - body.position.x) <= 0 ){
        sprite.change_anim("idle_right");
    }else{
        sprite.change_anim("idle_left");
    }

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