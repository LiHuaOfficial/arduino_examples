#ifndef _MY_STRING_
#define _MY_STRING_

#include <WString.h>

class MyString{
  public:
    /// @brief 将传入的数字转换为字符串
    /// @param a 需要转换的数字
    /// @param digit 如果数字位数小于该值则在前面补零
    /// @return 返回String类的字符串
    static String toString(int a,int digit=-1);
};


#endif
