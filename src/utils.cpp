#include "utils.h"

double lerp(double a, double b, double t){
    return (a + (b-a) * t);
}

double cerp(double a, double b, double t){
    //honnêtement j'avais trouvé cette formule sous crack c'est juste des maths mais sah j'ai oublié quels maths
    return (2*(a-b)*t*t*t+3*(b-a)*t*t+a);
}

double ease_in_sine(double t){
    //on décale juste une sinusoïdale pour qu'elle nous arrange y'a rien de magique
    return (1-cos(t*PI/2));
}

double ease_out_sine(double t){
    //de même
    return (sin(t*PI/2));
}

double ease_in_out_sine(double t){
    //cette fonction est juste un peu neuille et juste inférieure à simple_anim_smooth
    return -(cos(PI*t)-1)/2;
}

double smooth_interp(double a, double b, double midpoint, double max_height, double t){
    //du pur crack c'est tellement utile comme fonction
    if (t<=midpoint){
        return a + (max_height-a)*ease_in_sine(1/midpoint*t);
    }
    else{
        return max_height + (b-max_height)*ease_out_sine(1/(1-midpoint)*t+midpoint/(midpoint-1));
    }
}

double simple_anim_smooth(double a, double b, double t){
    //on utilise juste tellement la fonction sous cette forme que c'est plus simple en réalité
    return smooth_interp(a,b,(a+b)*.5,.5,t);
}