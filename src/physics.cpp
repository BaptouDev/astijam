#include "include/physics.h"

PhysicsBody::PhysicsBody(Vector2f position, Vector2f dimensions, Vector2f offset, map<string,bool> events){
    this->position = position;
    this->collision_rect = {position.x+offset.x,position.y+offset.y,dimensions.x,dimensions.y};
    this->base_rect=collision_rect;
    this->offset=offset;
    this->last_pos=position;
    this->events = events;
}

PhysicsBody::PhysicsBody(){
    
}

void PhysicsBody::update_physics_col_list(std::vector<PhysicsBody> col_list,float dt){
    //check "side" collision first (this method is not the most efficient but it's fine in reality)
    position = position + Vector2f(velocity.x*dt,0.0);
    collision_rect = {position.x+offset.x,position.y+offset.y,collision_rect.width,collision_rect.height};
    bool has_collided = false;
    for (auto i : col_list)
    {
        has_collided = has_collided || CheckCollisionRecs(i.collision_rect,collision_rect);
    }
    if(has_collided){
        position.x = last_pos.x;
        collision_rect.x = position.x+offset.x;
    }
    //now check "vertical" collision
    position = position + Vector2f(0.0,velocity.y*dt);
    collision_rect = {position.x+offset.x,position.y+offset.y,collision_rect.width,collision_rect.height};
    has_collided = false;
    for (auto &i : col_list)
    {
        has_collided = has_collided || CheckCollisionRecs(i.collision_rect,collision_rect);
    }
    if(has_collided){
        position.y = last_pos.y;
        collision_rect.y = position.y+offset.y;
    }
}