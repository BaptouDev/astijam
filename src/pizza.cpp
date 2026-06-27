#include <iostream>
#include "include/pizza.h"
#include <cmath>
#include "include/utils.h"

using namespace std;


Pizza::Pizza(Vector2f init_pos):
SpriteEntity(init_pos,"enemy", {}, "res/img/pizza.png", 4.0, 0.0, 32, 0) {


    
}



void Pizza::update(float dt, Vector2f mouse_pos){

   
}

void Pizza::damage(int amount){

}

/*
    Vector2f relative_mouse_pos = body.position + sprite.origin - mouse_pos;
    float mouse_angle = atan2(relative_mouse_pos.y,relative_mouse_pos.x);

   
    //body.velocity = lerpv(body.velocity,input.normalized()*speed);

    
    body.update_physics_col_list({},dt);
    body.last_pos = body.position;
    was_moving = is_moving;
 */

void Pizza::draw(float dt,Vector2f camera_pos){
    sprite.pos = body.position;
    SpriteEntity::draw(dt,camera_pos);
}
