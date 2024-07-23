//
// Created by 28487 on 2024/5/28.
//
#include "zf_common_headfile.h"

double my_abs(double x)
{
    return x>=0?x:(-x);
}

float my_alpha;
float my_beta;

void turn_f()
{
    my_beta = car_target_angle - car_direction;  //¦Ì?-3¦Ì
    
   // my_alpha = ComplementaryFilter(my_beta,mic_angle,0.85);
    
   my_alpha = my_beta;

    if((my_alpha >= 0 && my_alpha <= 180) || (my_alpha <= -180 && my_alpha >= -360))  //¨®¨°1?
    {
        if (my_alpha >= 0) {
            turn_angle(-my_alpha);
        } else if (my_alpha < 0) {
            my_alpha = 360 - my_abs(my_alpha);
            turn_angle(my_alpha);
        }
    } else if ((my_alpha >= 180 && my_alpha <= 360) || (my_alpha <= 0 && my_alpha >= -180))  //¡Á¨®¡Áa
    {
        if(my_alpha >= 0) {
            my_alpha = 360 - my_abs(my_alpha);
            turn_angle(my_alpha);
        }else if (my_alpha < 0) {
            turn_angle(-my_alpha);
        }
    }
}

// void turn_b()
// {

//     my_beta = car_target_angle - car_direction;  //µã-³µ
    
//    // my_alpha = ComplementaryFilter(my_beta,mic_angle,0.85);
    
//    my_alpha = my_beta;

//     if((my_alpha >= 0 && my_alpha <= 180) || (my_alpha <= -180 && my_alpha >= -360))  //ÓÒ¹Õ
//     {
//         if (my_alpha >= 0) {
//             turn_angle(-my_alpha);
//         } else if (my_alpha < 0) {
//             my_alpha = 360 - my_abs(my_alpha);
//             turn_angle(my_alpha);
//         }
//     } else if ((my_alpha >= 180 && my_alpha <= 360) || (my_alpha <= 0 && my_alpha >= -180))  //×ó×ª
//     {
//         if(my_alpha >= 0) {
//             my_alpha = 360 - my_abs(my_alpha);
//             turn_angle(my_alpha);
//         }else if (my_alpha < 0) {
//             turn_angle(-my_alpha);
//         }
//     }
// }
