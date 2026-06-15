#include "entity.h"

Entity::Entity(Vector2f position){
    this->position = position;
}

void Entity::update(float dt){
}

void Entity::draw(float dt){
}

SpriteEntity::SpriteEntity(Vector2f position,const char* path_to_img, float scale, float rotation, int tile_size, int index)
: Entity(position){
    this->sprite = Sprite(path_to_img, position, scale, rotation, tile_size, index);
}

void SpriteEntity::draw(float dt){
    sprite.draw(dt);
}

AnimatedEntity::AnimatedEntity(Vector2f position,const char* path_to_img, float scale, float rotation, int tile_size, int index, std::map<std::string, animation> animations, std::string base_anim)
: Entity(position){
    this->sprite = AnimatedSprite(path_to_img, position, scale, rotation, tile_size, index, animations, base_anim);
}

void AnimatedEntity::draw(float dt){
    sprite.draw(dt);
}