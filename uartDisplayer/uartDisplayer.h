#ifndef _UARTDISPLAYER_
#define _UARTDISPLAYER_

#include <HardwareSerial.h>

class UartDisplayer{
public:
  UartDisplayer(){
    
  };
  //Once in setup
  void init();

  /*
  x 1~480
  y 1~320
  */
  void drawCircle(int x,int y,int r);
  void displayString(int x,int y,String str);
  void clear();
  
private:
  HardwareSerial & DSerial=Serial3;
};

#endif
