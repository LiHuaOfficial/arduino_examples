#include "MyString.h"
#include "uartDisplayer.h"
#include "Joystick.h"
#include "FlexiTimer2.h"

UartDisplayer displayer=UartDisplayer();
Joystick js=Joystick(56,55,29);

const float jsToSpeed=100;

int pointPosX=240,pointPosY=160;

int jsX=512,jsY=512;
int oldJsX=512,oldJsY=512;

String pointInfo;
String joystickInfo;

void OneFrameDisplay(void *);


void setup() {
  // put your setup code here, to run once:
  displayer.init();
  //Serial3.println(MyString::toString(110));
   FlexiTimer2::set(100, OneFrameDisplay);
   FlexiTimer2::start();
}

void loop() {
  // put your main code here, to run repeatedly:
//  oldJsX=jsX;
//  oldJsY=jsY;
  jsX=1023-js.readX();
  jsY=js.readY();
  //根据摇杆位置得出点位置的改变速度
  //增大jsToSpeed忽略较小的扰动
  int aX=jsX-512;int speedX=aX/jsToSpeed;
  int aY=jsY-512;int speedY=aY/jsToSpeed;
  if( (pointPosX+speedX)<=480 && (pointPosX+speedX)>=0 ) pointPosX+=(int)speedX;
  if( (pointPosY+speedY)<=320 && (pointPosY+speedY)>=0 ) pointPosY+=(int)speedY;
  delay(20);
}

void OneFrameDisplay(){
  displayer.clear();
  pointInfo="Point:"+MyString::toString(pointPosX,3)+" "+MyString::toString(pointPosY,3);
  joystickInfo="Joystick X:"+MyString::toString(jsX,4)+" Y:"+MyString::toString(jsY,4);
  displayer.displayString(1,15,joystickInfo);
  displayer.displayString(1,1,pointInfo);
  displayer.drawCircle(pointPosX,pointPosY,10);

}
