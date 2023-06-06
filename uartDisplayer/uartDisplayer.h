#ifndef _UARTDISPLAYER_
#define _UARTDISPLAYER_

#include <HardwareSerial.h>

class UartDisplayer{
public:
  UartDisplayer(){
    
  };

  /// @brief 初始化串口屏
  void init();

  /*
  左上为(0,0)
  x 1~480
  y 1~320
  */

  /// @brief 画一个实心圆
  /// @param x,y 圆心坐标
  /// @param r 圆的半径
  void drawCircle(int x,int y,int r);

  /// @brief 按照默认大小显示字符串
  /// @param x,y 第一个字符的左上角
  /// @param str 显示的字符
  void displayString(int x,int y,String str);

  /// @brief 清屏
  void clear();
  
private:
  HardwareSerial & DSerial=Serial3;
};

#endif
