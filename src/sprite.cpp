#include "include/sprite.h"

Sprite::Sprite(const char* path_to_img, Vector2f pos, float scale, float rotation, Vector2f origin, int tile_size, int index){
    this->image = LoadTexture(path_to_img);
    this->pos = pos;
    this->scale = scale;
    this->rotation = rotation;
    this->origin = origin;
    this->tile_size = tile_size;
    this->is_flipped = false;
    this->draw_frame = index;
}

Sprite::Sprite(){

}

void Sprite::change_pos(Vector2f new_pos){
    this->pos = new_pos;
}
void Sprite::draw(float dt,Vector2f camera_pos){
    Rectangle src_rect = {draw_frame%image.width*tile_size,
        draw_frame/image.width*tile_size,
        tile_size,
        tile_size};
    Rectangle draw_rect = {pos.x+origin.x-camera_pos.x, pos.y+origin.y-camera_pos.y, tile_size*scale,tile_size*scale};
    //DrawTextureRec(image,draw_rect,pos.to_rayvect2(),WHITE);
    DrawTexturePro(image,src_rect,draw_rect,origin.to_rayvect2(),rotation,WHITE);
}




AnimatedSprite::AnimatedSprite(const char* path_to_img, Vector2f pos, float scale, float rotation, Vector2f origin,int tile_size, int index,std::map<std::string, animation> animations, std::string base_anim)
: Sprite(path_to_img, pos, scale, rotation, origin, tile_size, index){
    this->animations = animations;
    this->current_time = 0.0;
    this->current_frame=0;
    this->animations["null"] = {{0},{0.0},false};
    this->draw_frame =0;
    this->current_anim = base_anim;
    this->base_anim = base_anim;
}

AnimatedSprite::AnimatedSprite(){
    
}

void AnimatedSprite::change_anim(std::string new_anim){
    current_anim = new_anim;
    current_frame = 0;
}

void AnimatedSprite::draw(float dt,Vector2f camera_pos){
    current_time+=dt;
    if (current_time>animations[current_anim].durations[current_frame]){
        current_time = 0;
        if (current_frame < animations[current_anim].frames.size()-1){
            current_frame += 1;
        }else{
            current_frame = 0;
            if (animations[current_anim].one_shot){
                change_anim(base_anim);
            }
        }
    }
    draw_frame = animations[current_anim].frames[current_frame];
    Sprite::draw(dt,camera_pos);
}

