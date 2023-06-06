#ifndef _JOYSTICK_
#define _JOYSTICK_
#include <Arduino.h>

class Joystick{
public:
  Joystick(unsigned char x,unsigned char y,unsigned char z){
    pinX=x,pinY=y,pinZ=z;
  }

  /// @brief 初始化
  void init();

  /// @brief 返回X坐标的模拟量
  /// @return x在0-1023范围
  int readX();

  /// @brief 返回Y坐标的模拟量
  /// @return Y在0-1023范围
  int readY();
private:
  unsigned char pinX,pinY,pinZ;
};

#endif
