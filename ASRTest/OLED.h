#ifndef _OLED_H_
#define _OLED_H_
#include "SlowSoftI2CMaster.h"

class OLED{
public:
  OLED(SlowSoftI2CMaster _si);
  OLED(unsigned char _sda, unsigned char _scl);
  
  //Init function. Needs to be called once in the beginning.
  void OLED_Init(void);
  
  void OLED_Clear(void);

  /*
  line 1-4
  column 1-16
  */
  void OLED_ShowChar(unsigned char Line, unsigned char Column, char Char);
  void OLED_ShowString(unsigned char Line, unsigned char Column, char *String);
  void OLED_ShowNum(unsigned char Line, unsigned char Column, unsigned long Number, unsigned char Length);
  void OLED_ShowSignedNum(unsigned char Line, unsigned char Column, long Number, unsigned char Length);
private:
  SlowSoftI2CMaster si;
  void OLED::OLED_WriteCommand(unsigned char Command);
  void OLED::OLED_WriteData(unsigned char Data);
  void OLED::OLED_SetCursor(unsigned char Y, unsigned char X);
  unsigned long OLED::OLED_Pow(unsigned long X, unsigned long Y);
};

#endif
