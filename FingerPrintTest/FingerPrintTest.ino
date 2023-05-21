#include "OLED.h"
#include "Adafruit_Fingerprint.h"

#define K1 22
#define K3 25
#define K5 24

OLED displayer=OLED(38,36);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial1);

unsigned char keyNum=0;

unsigned char GetKeyNum();

void KeyInit();
void DisplayMenu();
void ADD_FingerPrint();
void Verify_FingerPrint();

void setup() {
  // put your setup code here, to run once:
  displayer.OLED_Init();
  KeyInit();
  finger.begin(57600);
  DisplayMenu();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  DisplayMenu();
  keyNum=GetKeyNum();
  if(keyNum==1){
    keyNum=0;//函数内可能还要用到
    ADD_FingerPrint();
  }
  if(keyNum==5){
    keyNum=0;
    Verify_FingerPrint();
  }
}

void KeyInit(){
  pinMode(K1,INPUT_PULLUP);
  pinMode(K3,INPUT_PULLUP);
  pinMode(K5,INPUT_PULLUP);
}
unsigned char GetKeyNum(){
  if(digitalRead(K1)==0){delay(10);while(digitalRead(K1)==0);return 1;}
  if(digitalRead(K3)==0){delay(10);while(digitalRead(K3)==0);return 3;}
  if(digitalRead(K5)==0){delay(10);while(digitalRead(K5)==0);return 5;}
  return 0;
}

void DisplayMenu(){
  displayer.OLED_ShowString(1, 1,"Test program:   ");
  displayer.OLED_ShowString(2, 1,"ADD  DEL  VER   ");
  displayer.OLED_ShowString(3, 1,"K1   K3   K5    ");
}

void ADD_FingerPrint(){
  unsigned char statusNum=0;
  unsigned char returnValue;
  unsigned char cnt=0;//没有操作一定次数后返回至loop
  
  while(1){
    switch(statusNum){
      
      case 0:
        cnt++;
        
        displayer.OLED_ShowString(1, 1,"Press Finger    ");
        displayer.OLED_ShowString(2, 1,"                "); 
        displayer.OLED_ShowString(3, 1,"                "); 
        returnValue=finger.getImage();
        if(returnValue==FINGERPRINT_OK) 
        {
          returnValue=finger.image2Tz(1);//生成特征
          if(returnValue==FINGERPRINT_OK)
          {
            displayer.OLED_ShowString(2, 1,"FinishGenFinger1");
            cnt=0;
            statusNum=1;//跳到case1            
          }else {};       
        }else {};           
        break;
        
      case 1:
        cnt++;
        
        displayer.OLED_ShowString(1, 1,"Press Again     ");
        returnValue=finger.getImage();
        if(returnValue==FINGERPRINT_OK) 
        {
          returnValue=finger.image2Tz(2);//生成特征
          if(returnValue==FINGERPRINT_OK)
          {
            displayer.OLED_ShowString(2, 1,"FinishGenFinger2");
            cnt=0;
            statusNum=2;//跳到case2            
          }else {};       
        }else {};
        break;
        
        case 2:
        displayer.OLED_ShowString(2, 1,"                ");    
        displayer.OLED_ShowString(1, 1,"Creating Model  ");

        returnValue=finger.createModel();//将两个特征生成模板
        if(returnValue==FINGERPRINT_OK) {
          displayer.OLED_ShowString(2, 1,"Create Success  ");
          statusNum=3;//跳到第四步
        }
        else{
          displayer.OLED_ShowString(2, 1,"Create failed   ");
          cnt=0;
          statusNum=0;
          displayer.OLED_ShowString(3, 1,"Please retry    ");
        }
        delay(700);
        displayer.OLED_Clear();
        break;

        case 3:
          unsigned char ID_NUM=0;
          displayer.OLED_ShowString(1, 1,"ID ADD MIN  SAVE");
          displayer.OLED_ShowString(2, 1,"   K5  K1   K3  ");
          displayer.OLED_ShowString(3, 1,"ID=");displayer.OLED_ShowNum(3,4,ID_NUM,2);
          displayer.OLED_ShowString(4, 1,"0<=ID<=99       ");
          while(keyNum!=3){
            displayer.OLED_ShowNum(3,4,ID_NUM,2);
            keyNum=GetKeyNum();
            if(keyNum==5)
              if(ID_NUM+1<=99) ID_NUM++;
            if(keyNum==1) 
              if(ID_NUM-1>=0) ID_NUM--;
          }
          keyNum=0;
          returnValue=finger.storeModel(ID_NUM);//储存模板
          if(returnValue==0x00) 
          {   
            displayer.OLED_Clear();
            displayer.OLED_ShowString(1, 1,"Save Successful");
            delay(1500);
            return ;
          }else {statusNum=0;}
        break;
    }
    delay(400);
    if(cnt==10)//超过5次没有按手指则退出
    {
      break;  
    }
  }
}

void Verify_FingerPrint(){
  unsigned char cnt=0;
  unsigned char returnValue=0;

  displayer.OLED_Clear();
  while(1)
  {
    displayer.OLED_ShowString(1, 1,"Press finger    ");
    displayer.OLED_ShowString(2, 1,"to verify       ");
    displayer.OLED_ShowString(3, 1,"wait to quit    ");
    cnt++;
    if(cnt>15) break;
    returnValue=finger.getImage();//获取图像
    if(returnValue==FINGERPRINT_OK){
      displayer.OLED_Clear();
      displayer.OLED_ShowString(1, 1,"Get Successful  ");
      
      returnValue=finger.image2Tz();//生成特征
      if(returnValue==FINGERPRINT_OK){
        displayer.OLED_ShowString(1, 1,"Gen Successful  ");
        returnValue=finger.fingerFastSearch();//快速查询
        if(returnValue==FINGERPRINT_OK){
          displayer.OLED_ShowString(1, 1,"SearchSuccessful");
          char searchMsg[20];
          sprintf(searchMsg,"ID:%d Score:%d",finger.fingerID,finger.confidence);
          displayer.OLED_ShowString(2, 1,searchMsg);
        }
        else{
          displayer.OLED_ShowString(1, 1,"Search failed   ");
        }
        delay(2000);
        displayer.OLED_Clear();
      }
    }
  }
}
