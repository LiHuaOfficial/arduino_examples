#ifndef _LD3320_
#define _LD3320_
#include <arduino.h>
#include "OLED.h"
#define u8 unsigned char

#define SDCK 52      //SPI 时钟信号
#define SDO  50      //SPI 数据输出
#define SDI  51     //SPI 数据输入
#define SCS  53     //芯片片选信号
#define RSTB 9    //复位端口
#define IRQ  2     //中断引脚

#define SDCK_1 digitalWrite(SDCK, HIGH)
#define SDCK_0 digitalWrite(SDCK, LOW)

#define SDI_1 digitalWrite(SDI, HIGH)
#define SDI_0 digitalWrite(SDI, LOW)

#define SCS_1 digitalWrite(SCS, HIGH)
#define SCS_0 digitalWrite(SCS, LOW)

#define RSTB_1 digitalWrite(RSTB, HIGH)
#define RSTB_0 digitalWrite(RSTB, LOW)

//  以下三个状态定义用来记录程序是在运行ASR识别还是在运行MP3播放
#define LD_MODE_IDLE      0x00
#define LD_MODE_ASR_RUN   0x08
#define LD_MODE_MP3       0x40

//  以下五个状态定义用来记录程序是在运行ASR识别过程中的哪个状态
#define LD_ASR_NONE       0x00  //  表示没有在作ASR识别
#define LD_ASR_RUNING     0x01  //  表示LD3320正在作ASR识别中
#define LD_ASR_FOUNDOK    0x10  //  表示一次识别流程结束后，有一个识别结果
#define LD_ASR_FOUNDZERO  0x11  //  表示一次识别流程结束后，没有识别结果
#define LD_ASR_ERROR      0x31  //  表示一次识别流程中LD3320芯片内部出现不正确的状态


#define CLK_IN          16  /* 用户注意修改输入的晶振时钟大小 */
#define LD_PLL_11       (u8)((CLK_IN/2.0)-1)
#define LD_PLL_MP3_19   0x0f
#define LD_PLL_MP3_1B   0x18
#define LD_PLL_MP3_1D   (u8)(((90.0*((LD_PLL_11)+1))/(CLK_IN))-1)

#define LD_PLL_ASR_19   (u8)(CLK_IN*32.0/(LD_PLL_11+1) - 0.51)
#define LD_PLL_ASR_1B   0x48
#define LD_PLL_ASR_1D   0x1f

#define MIC_VOL 0x43   //咪头增益

//识别码客户修改处
#define CODE_CMD   0x00   //该命令码0x00用户不可进行修改。
#define CODE_DMCS  0x01   //代码测试
#define CODE_CSWB  0x02   //测试完毕

#define CODE_OPEN 0x04
#define CODE_CLOSE 0x05
#define CODE_1KL3 0x16
#define CODE_1KL4 0x17
                  
#define CODE_2KL1 0x18
#define CODE_2KL2 0x19
#define CODE_2KL3 0x1A
#define CODE_2KL4 0x1B
                  
#define CODE_3KL1 0x1C
#define CODE_3KL2 0x1D
#define CODE_3KL3 0x1E
#define CODE_3KL4 0x1F
                  
#define CODE_4KL1 0x20
#define CODE_4KL2 0x21
#define CODE_4KL3 0x22
#define CODE_4KL4 0x23

extern OLED displayer;

class LD3320{
public:
  
  void LD3320_IO_Init(void);
  void LD_Reset(void);
  void LD_Init_Common(void);
  void LD_Init_ASR(void);
  u8 LD_Check_ASRBusyFlag_b2(void);
  void LD_AsrStart(void);
  u8 LD_AsrRun(void);
  u8 LD_AsrAddFixed(void);
  u8 RunASR(void);
  u8 LD_GetResult(void);

  unsigned char LD_ReadReg(unsigned char address);
  void LD_WriteReg(unsigned char address,unsigned char dataout);
private:
  void SPI_WriteByte(unsigned char _data);
  unsigned char SPI_ReadByte();
  
  
};

#endif
