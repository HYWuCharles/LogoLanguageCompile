#include <stdio.h>
#include <math.h>

#define PI 3.1415926
int main(void){
    int cur_x, cur_y, tar_x, tar_y, angle;
    float rad;
    cur_x = 10;
    cur_y = 20;
    angle = 150;
    /* Calculate rad */
    rad = angle*PI/180;
    tar_x = cur_x+100*sin(rad);
    tar_y = cur_y+100*cos(rad);

    printf("%d\n%d", tar_x, tar_y);
}