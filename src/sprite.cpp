#include "sprite.h"

Sprite::Sprite(const char* path_to_img, Vector2f pos, float scale, float rotation, int tile_size, int index){
    this->image = LoadTexture(path_to_img);
    this->pos = pos;
    this->scale = scale;
    this->rotation = rotation;
    this->tile_size = tile_size;
    this->is_flipped = false;
    this->current_frame = index;
}
void Sprite::change_pos(Vector2f new_pos){
    this->pos = new_pos;
}
void Sprite::draw(float dt){
    Rectangle draw_rect = {(current_frame*tile_size)%(image.width/tile_size),((current_frame*tile_size)/(image.width/tile_size)),tile_size,tile_size};
    DrawTextureRec(image,draw_rect,pos.to_rayvect2(),WHITE);
}