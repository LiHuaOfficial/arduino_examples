#include "uartDisplayer.h"
#include "MyString.h"

void UartDisplayer::init(){
  DSerial.begin(9600);
  DSerial.println("@PRINTB BLack");
  DSerial.println("@PMODE 1,White");
  DSerial.println("@PRCLR");//清屏
  //DSerial.println("Hello world");
}

void UartDisplayer::drawCircle(int x,int y,int r){
  String input="@CIRF ";
  input+=MyString::toString(x);
  input+=',';
  input+=MyString::toString(y);
  input+=',';
  input+=MyString::toString(r);
  DSerial.println(input);
}

void UartDisplayer::displayString(int x,int y,String str){
  String input="@STR ";
  input+=MyString::toString(x);
  input+=',';
  input+=MyString::toString(y);
  input+=',';
  input+=str;
  DSerial.println(input);
}

void UartDisplayer::clear(){
  DSerial.println("@PRCLR");
}
