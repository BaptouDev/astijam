#pragma once
#include <raylib.h>
#include <cmath>

//Linear interpolation from a to b with parameter t
double lerp(double a, double b, double t);

//cubic interpolation from a to b with parameter t
double cerp(double a, double b, double t);

//returns a value from 1 to 0 but like nice
double ease_in_sine(double t);

//same but goes from 0 to 1
double ease_out_sine(double t);

//same but from 0 to 1 back down to 0 (not very useful)
double ease_in_out_sine(double t);

//where the real magic happens. Interpolates really smoothly from a to b but using a midpoint m associated with when the rises stops
// midpoint should be between 0 and 1, and max_height is just a bad name since it's the midway point between a and b
double smooth_interp(double a, double b, double midpoint, double max_height, double t);

//just applying the previous function with classic parameters. useful for animations as the name suggests
double simple_anim_smooth(double a, double b, double t);