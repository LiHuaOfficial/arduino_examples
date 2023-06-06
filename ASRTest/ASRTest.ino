#include "OLED.h"
#include "LD3320.h"

extern u8 ucRegVal;

/*
  需要配合串口屏使用
  有结果会显示到串口屏中
*/
OLED displayer=OLED(38,36);
LD3320 asr=LD3320();

int cnt=0;
unsigned char nAsrStatus=LD_ASR_NONE;
u8 nAsrRes=0;

void User_Modification();

void setup() {
  // put your setup code here, to run once:
  //pinMode(2, INPUT_PULLUP);

  attachInterrupt(0,GetResult,CHANGE);
  displayer.OLED_Init();
  asr.LD3320_IO_Init();
  Serial3.begin(9600);
  Serial3.println("test");
}

void loop() {
  // put your main code here, to run repeatedly:
   switch(nAsrStatus)
    {
      case LD_ASR_RUNING:

        break;
      case LD_ASR_ERROR:
      {
        displayer.OLED_ShowString(1,1,"SomethingWrong");
        delay(500);
        break;
      }
      case LD_ASR_NONE:
      {
        nAsrStatus=LD_ASR_RUNING;
        if (asr.RunASR()==0)  /*  启动一次ASR识别流程：ASR初始化，ASR添加关键词语，启动ASR运算*/
        {
          nAsrStatus = LD_ASR_ERROR;
        }
        break;
      }
      case LD_ASR_FOUNDOK:
      {
        Serial3.println("Has result");                       
        //User_Modification();
        nAsrStatus = LD_ASR_NONE;
        break;
      }
      case LD_ASR_FOUNDZERO:
      {
        Serial3.println("No result");
        nAsrStatus = LD_ASR_NONE;
        break;
      }
      default:
      {
        nAsrStatus = LD_ASR_NONE;
        break;
      }
    } 
}

void GetResult(void){
  u8 nAsrResCount=0;
  ucRegVal = asr.LD_ReadReg(0x2B);
  asr.LD_WriteReg(0x29,0) ;
  asr.LD_WriteReg(0x02,0) ;
  if((ucRegVal & 0x10)&&asr.LD_ReadReg(0xb2)==0x21&&asr.LD_ReadReg(0xbf)==0x35)     /*识别成功*/
  {
    Serial3.println("");
    nAsrResCount = asr.LD_ReadReg(0xba);
    if(nAsrResCount>0 && nAsrResCount<=4) 
    {
      Serial3.println("Find sth");
      User_Modification();
      nAsrStatus=LD_ASR_NONE;
    }
    else
    {
      Serial3.println("No clear result");
      nAsrStatus=LD_ASR_FOUNDZERO;
    } 
  }                              /*没有识别结果*/
  else
  {  
    nAsrStatus=LD_ASR_FOUNDZERO;
  }
    
  asr.LD_WriteReg(0x2b, 0);
  asr.LD_WriteReg(0x1C,0);/*写0:ADC不可用*/
  asr.LD_WriteReg(0x29,0);
  asr.LD_WriteReg(0x02,0);
  asr.LD_WriteReg(0x2B,0);
  asr.LD_WriteReg(0xBA,0);  
  asr.LD_WriteReg(0xBC,0);  
  asr.LD_WriteReg(0x08,1);   /*清除FIFO_DATA*/
  asr.LD_WriteReg(0x08,0);  /*清除FIFO_DATA后 再次写0*/
}

void User_Modification()
{
    delay(20);
    nAsrRes=asr.LD_ReadReg(0xc5);
    switch(nAsrRes)      /*对结果执行相关操作,客户修改*/
    {
      case CODE_OPEN:     /*命令“代码测试”*/
          Serial3.print("kai\r\n"); /*text.....*/
                        break;
      
      case CODE_CLOSE:     /*命令“代码测试”*/
          Serial3.print("guan\r\n"); /*text.....*/
                        break;                  
  //    case CODE_3KL3:  /*命令“....”*/
  //        Serial.print("\"代码测试\"识别成功"); /*text.....*/
  //                      break;
  //    case CODE_3KL4:  /*命令“....”*/
  //        Serial.print("\"代码测试\"识别成功"); /*text.....*/
  //                      break;
  //          
  //          case CODE_4KL1:  /*命令“....”*/
  //              Serial.print("O"); /*text.....*/
  //                            break;
  //          case CODE_4KL2:  /*命令“....”*/
  //              Serial.print("P"); /*text.....*/
  //                            break;
  //          case CODE_4KL3:  /*命令“....”*/
  //              Serial.print("Q"); /*text.....*/
  //                            break;
  //          case CODE_4KL4:  /*命令“....”*/
  //              Serial.print("R"); /*text.....*/
  //                            break;
      
      default:
      Serial3.print("No correspond\r\n");
      break;
    } 
}
