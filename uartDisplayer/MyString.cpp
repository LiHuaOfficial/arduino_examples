#include "MyString.h"

static String MyString::toString(int a,int digit=-1){
  String tmp="";
  while(a){
    tmp+=(char)(a%10+'0');
    a/=10;
  }
  
  String res="";
  //补零
  if((int)tmp.length()<digit) {int t=digit-tmp.length();while(t--){res+='0';}}
  //翻转
  for(int i=tmp.length()-1;i>=0;i--){
    res+=tmp[i];
  }
  return res;
}
