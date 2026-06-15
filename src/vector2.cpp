#include "include/vector2.h"

Vector2f::Vector2f(){
    x=0.0;
    y=0.0;
}

Vector2f::Vector2f(float x, float y){
    this->x=x;
    this->y=y;
}

float Vector2f::length_sq(){
    return (x*x+y*y);
}

float Vector2f::length(){
    return sqrt(this->length_sq());
}

Vector2f Vector2f::operator+(const Vector2f& other) const{
    return Vector2f(x+other.x,y+other.y);
}

Vector2f Vector2f::operator-(const Vector2f& other) const{
    return Vector2f(x-other.x,y-other.y);
}

Vector2f Vector2f::operator*(float scalar) const{
    return Vector2f(x*scalar,y*scalar);
}

Vector2f operator * (float scalar, const Vector2f& self){
    return self*scalar;
}

Vector2f Vector2f::normalized(){
    float x = length();
    if(x!=0){
        return (*this)*(1/x);
    }else{
        return *this;
    }
}

Vector2 Vector2f::to_rayvect2(){
    return {x,y};
}