#include <include/player.h>
#include <iostream>
#include "include/utils.h"

Player::Player(Vector2f init_pos):
AnimatedEntity(init_pos,"player", {}, "res/img/player.png", 4.0, 0.0, 32, 0,
     {{"idle_front", {{2},{1.0},false}},
    {"idle_back", {{3},{1.0},false}},
    {"idle_right", {{0},{1.0},false}},
    {"idle_left", {{1},{1.0},false}}}, 
     "idle_front") {
    body = PhysicsBody();
    speed=200;
    accel=67;
}

void Player::update(float dt){
    Vector2f input= Vector2f(0,0);
    if(IsKeyDown(KEY_RIGHT)){
        input=input+Vector2f(1,0);
        sprite.change_anim("idle_right");
    }
    if(IsKeyDown(KEY_LEFT)){
        input=input+Vector2f(-1,0);
        sprite.change_anim("idle_left");

    }
    if(IsKeyDown(KEY_UP)){
        input=input+Vector2f(0,-1);
        sprite.change_anim("idle_back");
    }
    if(IsKeyDown(KEY_DOWN)){
        input=input+Vector2f(0,1);
        sprite.change_anim("idle_front");
    }
    input = input.normalized();
    /*input_vect = input_vect.normalize()
        self.vel = utils.lerp(self.vel,input_vect*self.max_speed,self.accel*dt)*/
    body.velocity = lerpv(body.velocity,input*speed,accel*dt);
    body.update_physics_col_list({},dt);
    std::cout << body.position.x;
    std::cout << body.position.y;
    std::cout << "\n";
    body.last_pos = body.position;
}

void Player::draw(float dt){
    sprite.pos = body.position;
    AnimatedEntity::draw(dt);
}