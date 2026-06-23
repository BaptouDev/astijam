#include "include/entity.h"

Entity::Entity(Vector2f position, string tag, vector<string> layers){
    this->position = position;
    this->tag = tag;
    this->layers = layers;
}


SpriteEntity::SpriteEntity(Vector2f position, string tag, vector<string> layers, const char* path_to_img, float scale, float rotation, int tile_size, int index)
: Entity(position,tag,layers){
    this->sprite = Sprite(path_to_img, position, scale, rotation, Vector2f(0,0),tile_size, index);
}

void SpriteEntity::draw(float dt){
    sprite.draw(dt);
}

void SpriteEntity::update(float dt){
}

AnimatedEntity::AnimatedEntity(Vector2f position, string tag, vector<string> layers, const char* path_to_img, float scale, float rotation, int tile_size, int index, std::map<std::string, animation> animations, std::string base_anim)
: Entity(position,tag,layers){
    this->sprite = AnimatedSprite(path_to_img, position, scale, rotation, Vector2f(0,0), tile_size, index, animations, base_anim);
}

void AnimatedEntity::update(float dt){
}

void AnimatedEntity::draw(float dt){
    sprite.draw(dt);
}