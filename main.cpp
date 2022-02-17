#include <iostream>
#include "BMP.h"
#include <cmath>
/*NIMET OZKAN*/

void DrawPoints(BMP& obj, long x_rad, long y_rad, long x_central, long y_central){
  obj.set_pixel(x_rad+x_central, y_rad+y_central, 255, 255, 255, 0);
  obj.set_pixel(-x_rad+x_central, y_rad+y_central, 255, 255, 255, 0);
  obj.set_pixel(x_rad+x_central, -y_rad+y_central, 255, 255, 255, 0);
  obj.set_pixel(-x_rad+x_central, -y_rad+y_central, 255, 255, 255, 0);
}

void DrawEllipse(BMP& newObj, long x_central, long y_central, long rad_x, long rad_y){
  long stop_x, stop_y, quad1, quad2, x, y;
  x = 0, y = rad_y;

    quad1 = pow(rad_y,2) - (pow(rad_x,2)*rad_y) + (0.25 * pow(rad_x,2));
    stop_x = 2 * pow(rad_y,2) * x;
    stop_y = 2 * pow(rad_x,2) * y;

     while(stop_x < stop_y){
        DrawPoints(newObj, x, y, x_central, y_central);
        if (quad1 < 0){
            ++x;
            stop_x = stop_x + (2 * rad_y * rad_y);
            quad1 = quad1 + stop_x + (rad_y * rad_y);
        }else{
            ++x;
            --y;
            stop_x = stop_x + (2 * rad_y * rad_y);
            stop_y = stop_y - (2 * rad_x * rad_x);
            quad1 = quad1 + stop_x - stop_y + (rad_y * rad_y);
        }
    }
    quad2 = (pow(rad_y,2) * ((x + 0.5) * (x + 0.5))) +
          (pow(rad_x,2) * ((y - 1) * (y - 1))) -(rad_x * rad_x * rad_y * rad_y);
  
    while(y){
        DrawPoints(newObj, x, y, x_central, y_central);
        
        if (quad2 > 0){
            y--;
            stop_y = stop_y - (2 * rad_x * rad_x);
            quad2 = quad2 + (rad_x * rad_x) - stop_y;
        }
        else{
            --y;
            ++x;
            stop_x = stop_x + (2 * rad_y * rad_y);
            stop_y = stop_y - (2 * rad_x * rad_x);
            quad2 = quad2 + stop_x - stop_y + (rad_x * rad_x);
        }
    }
}

int main(){
  BMP newObj(1792, 1792, false);

  long x_central = 896, y_central = 1400; //centers y >= 1
  long rad_x = 768, rad_y = 384; //radius vals
  
  // to see the ellipse in the middle of the screen:
  // x_cetral = 800, y_central = 800 and window size (1600, 1600)
  // but since y >= 1, put the ellipse about above the 0
  
  DrawEllipse(newObj, x_central, y_central, rad_x, rad_y);

  newObj.write("output.bmp");
  return 0;
}

