#include "OLED.h"
#include "OLED_Font.h"


OLED::OLED(SlowSoftI2CMaster _si){
    si=_si;
}

OLED::OLED(unsigned char _sda, unsigned char _scl){
    si = SlowSoftI2CMaster(38,36,true);
}

void OLED::OLED_WriteCommand(unsigned char Command){
  si.i2c_start(0x78);
  //si.i2c_write(0x78);//单字节形式
  si.i2c_write(0x00);
  si.i2c_write(Command);
  si.i2c_stop(); 
}

void OLED::OLED_WriteData(unsigned char Data){
  si.i2c_start(0x78);
  //si.i2c_write(0x78);//单字节形式
  si.i2c_write(0x40);
  si.i2c_write(Data);
  si.i2c_stop(); 
}

void OLED::OLED_SetCursor(unsigned char Y, unsigned char X)
{
  OLED_WriteCommand(0xB0 | Y);          //设置Y位置
  /*下面两个都是低四位有效*/
  OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));  //设置X位置高4位
  OLED_WriteCommand((0x00 | (X & 0x0F))+2);     //设置X位置低4位，以及2的偏移量（1.3‘ 128x64 oled）
}

void OLED::OLED_Clear(void)
{  
  unsigned char i, j;
  for (j = 0; j < 8; j++)
  {
    OLED_SetCursor(j, 0);
    for(i = 0; i < 128; i++)
    {
      OLED_WriteData(0x00);
    }
  }
}

void OLED::OLED_ShowChar(unsigned char Line, unsigned char Column, char Char)
{        
  unsigned char i;
  OLED_SetCursor((Line - 1) * 2, (Column - 1) * 8);   //设置光标位置在上半部分
  for (i = 0; i < 8; i++)
  {
    OLED_WriteData(OLED_F8x16[Char - ' '][i]);      //显示上半部分内容
  }
  OLED_SetCursor((Line - 1) * 2 + 1, (Column - 1) * 8); //设置光标位置在下半部分
  for (i = 0; i < 8; i++)
  {
    OLED_WriteData(OLED_F8x16[Char - ' '][i + 8]);    //显示下半部分内容
  }
}

void OLED::OLED_ShowString(unsigned char Line, unsigned char Column, char *String)
{
  unsigned char i;
  for (i = 0; String[i] != '\0'; i++)
  {
    OLED_ShowChar(Line, Column + i, String[i]);
  }
}

unsigned long OLED::OLED_Pow(unsigned long X, unsigned long Y)
{
  unsigned long Result = 1;
  while (Y--)
  {
    Result *= X;
  }
  return Result;
}

void OLED::OLED_ShowNum(unsigned char Line, unsigned char Column, unsigned long Number, unsigned char Length)
{
  uint8_t i;
  for (i = 0; i < Length; i++)              
  {
    OLED_ShowChar(Line, Column + i, Number / OLED_Pow(10, Length - i - 1) % 10 + '0');
  }
}

void OLED::OLED_ShowSignedNum(unsigned char Line, unsigned char Column, long Number, unsigned char Length)
{
  unsigned char i;
  unsigned long Number1;
  if (Number >= 0)
  {
    OLED_ShowChar(Line, Column, '+');
    Number1 = Number;
  }
  else
  {
    OLED_ShowChar(Line, Column, '-');
    Number1 = -Number;
  }
  for (i = 0; i < Length; i++)              
  {
    OLED_ShowChar(Line, Column + i + 1, Number1 / OLED_Pow(10, Length - i - 1) % 10 + '0');
  }
}

void OLED::OLED_Init(void)
{
  
  unsigned long i, j;
  
  for (i = 0; i < 1000; i++)      //上电延时
  {
    for (j = 0; j < 1000; j++);
  }
  si.i2c_init();
  OLED_WriteCommand(0xAE);  //关闭显示
  
  OLED_WriteCommand(0xD5);  //设置显示时钟分频比/振荡器频率
  OLED_WriteCommand(0x80);
  
  OLED_WriteCommand(0xA8);  //设置多路复用率
  OLED_WriteCommand(0x3F);
  
  OLED_WriteCommand(0xD3);  //设置显示偏移
  OLED_WriteCommand(0x00);
  
  OLED_WriteCommand(0x40);  //设置显示开始行
  
  OLED_WriteCommand(0xA1);  //设置左右方向，0xA1正常 0xA0左右反置
  
  OLED_WriteCommand(0xC8);  //设置上下方向，0xC8正常 0xC0上下反置

  OLED_WriteCommand(0xDA);  //设置COM引脚硬件配置
  OLED_WriteCommand(0x12);
  
  OLED_WriteCommand(0x81);  //设置对比度控制
  OLED_WriteCommand(0xCF);

  OLED_WriteCommand(0xD9);  //设置预充电周期
  OLED_WriteCommand(0xF1);

  OLED_WriteCommand(0xDB);  //设置VCOMH取消选择级别
  OLED_WriteCommand(0x30);

  OLED_WriteCommand(0xA4);  //设置整个显示打开/关闭

  OLED_WriteCommand(0xA6);  //设置正常/倒转显示

  OLED_WriteCommand(0x8D);  //设置充电泵
  OLED_WriteCommand(0x14);

  OLED_WriteCommand(0xAF);  //开启显示
    
  OLED_Clear();       //OLED清屏
}
