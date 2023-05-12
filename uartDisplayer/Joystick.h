#ifndef _JOYSTICK_
#define _JOYSTICK_
#include <Arduino.h>

class Joystick{
public:
  Joystick(unsigned char x,unsigned char y,unsigned char z){
    pinX=x,pinY=y,pinZ=z;
  }
  void init();
  int readX();
  int readY();
private:
  unsigned char pinX,pinY,pinZ;
};

#endif
