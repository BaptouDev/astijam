#pragma once

#include <vector>
#include <raylib.h>
#include <string>
#include <map>
#include "include/vector2.h"
using namespace std;

class PhysicsBody{
    public:
        Rectangle collision_rect;
        Vector2f position;
        Vector2f velocity;
        PhysicsBody(Vector2f position, Vector2f dimensions, Vector2f offset, map<string,bool> events);
        PhysicsBody();
        void update_physics_col_list(std::vector<PhysicsBody> col_list,float dt);
        Vector2f last_pos;
    private:
        Vector2f offset;
        Rectangle base_rect;
        map<string,bool> events;
};

class AreaRect{
    public:
        Rectangle collision_rect;
        Vector2f position;
        Vector2f velocity;
        vector<string> layers;
        AreaRect(Vector2f position, Vector2f dimensions, Vector2f offset);
};

/*for(auto i : shit){

}*/