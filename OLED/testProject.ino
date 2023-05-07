#include "OLED.h"

OLED OLED1=OLED((unsigned char)38,(unsigned char)36);

void setup() {
  // put your setup code here, to run once:
  OLED1.OLED_Init();  
}

void loop() {
  // put your main code here, to run repeatedly:
  OLED1.OLED_ShowString(1,1,"hello world");
  
}
