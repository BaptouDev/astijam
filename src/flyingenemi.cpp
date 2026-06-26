#include <iostream>
#include "include/flyingenemy.h"
#include <cmath>
#include "include/utils.h"

using namespace std;


FlyingEnemy::FlyingEnemy(Vector2f init_pos):
AnimatedEntity(init_pos,"flyingenemy", {}, "res/img/dinoennemi2.png", 4.0, 0.0, 32, 0,
     {{"idle_left", {{0},{1.0},false}},
      {"idle_right", {{4},{1.0},false}}, 
      {"run_right", {{0,1},{0.3, 0.3}, false }},
      {"run_left",  { {4,5}, {0.3,0.3}, false }},
      {"dive_left", {{3}, {1.0}, false}},
      {"dive_right",  {{2}, {1.0}, false}}
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
    speed=10;
    
    player_pos = Vector2f(0,0);
    
    was_looking_right=false;

    dive_timer = 0;
    dive_time = 4;
    is_diving = false;
    dive_speed = 500;
    divedirection = Vector2f(0,0);
    divesright = false;

    dive_duration = 0.7;
    dive_duration_timer =0;

    maxhp = 150;
    hp = maxhp;

    is_dead = false;

    sprite.origin = Vector2f(16*sprite.scale,16*sprite.scale);
}

void FlyingEnemy::get_player_pos(Vector2f pos){
    player_pos = pos;
}

void FlyingEnemy::update(float dt, Vector2f mouse_pos){
    dive_timer += dt;
    dive_duration_timer+=dt;

    
    if(!is_diving){

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
    }


    if(dive_timer >= dive_time){
        dive_timer=-dive_duration;
        is_diving = true;
        dive_duration_timer = 0;
        divedirection = (mouse_pos - body.position ).normalized();
        if( (mouse_pos.x - body.position.x) <= 0 ){
            sprite.change_anim("dive_left");
            divesright = false;
        }else{
            sprite.change_anim("dive_right");
            divesright = true;
        }
    }
    if(dive_duration_timer >= dive_duration && is_diving){
        is_diving = false;


        if( (mouse_pos.x - body.position.x) <= 0 ){

                sprite.change_anim("run_left");
                was_looking_right = false;

        }else{

            sprite.change_anim("run_right");
            was_looking_right = true;

        }

    }

    if(is_diving){
        body.position =  divedirection*dive_speed*dt + body.position;
    }

    position = body.position;

}

void FlyingEnemy::damage(int amount){
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

void FlyingEnemy::draw(float dt,Vector2f camera_pos){
    sprite.pos = body.position;
    AnimatedEntity::draw(dt,camera_pos);
}

