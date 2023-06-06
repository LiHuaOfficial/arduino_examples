#ifndef _OLED_H_
#define _OLED_H_
#include "SlowSoftI2CMaster.h"

class OLED{
public:
  OLED(SlowSoftI2CMaster _si);

  ///@brief 构造函数，指定OLED的sda和scl连接的位置
  OLED(unsigned char _sda, unsigned char _scl);
  
  /// @brief 初始化函数，需要在setup中调用
  void OLED_Init(void);
  
  /// @brief 调用这个函数来清屏
  void OLED_Clear(void);

  /*
  line 1-4
  column 1-16
  */
  /// @brief 显示单个字符
  void OLED_ShowChar(unsigned char Line, unsigned char Column, char Char);

  /// @brief 显示字符串
  void OLED_ShowString(unsigned char Line, unsigned char Column, char *String);

  /// @brief 显示一个无符号整数
  /// @param Length 指定整数总共显示的位数
  void OLED_ShowNum(unsigned char Line, unsigned char Column, unsigned long Number, unsigned char Length);

  /// @brief 显示一个有符号整数，会在第一位显示+/、或-
  /// @param Length 指定整数除去符号位显示的位数
  void OLED_ShowSignedNum(unsigned char Line, unsigned char Column, long Number, unsigned char Length);
private:
  SlowSoftI2CMaster si;
  void OLED::OLED_WriteCommand(unsigned char Command);
  void OLED::OLED_WriteData(unsigned char Data);
  void OLED::OLED_SetCursor(unsigned char Y, unsigned char X);
  unsigned long OLED::OLED_Pow(unsigned long X, unsigned long Y);
};

#endif
