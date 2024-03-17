#ifndef __AIP1944_H
#define __AIP1944_H
 
 
#include "main.h"
 
 
#define GrayScale_OFF 0x80 //关显示
#define GrayScale_ON 0x81 //开显示
 
 
 
#define GrayScale1   0x88 //灰度等级1
#define GrayScale2   0x89 //灰度等级2
#define GrayScale3   0x8A //灰度等级3
#define GrayScale4   0x8B //灰度等级4
#define GrayScale5   0x8C //灰度等级5
#define GrayScale6   0x8D //灰度等级6
#define GrayScale7   0x8E //灰度等级7
#define GrayScale8   0x8F //灰度等级8
 
 void _DelayUsec(unsigned int i)  ;
void AIP1944_Init(void);
void AIP1944_Fixed(uint8_t data, uint8_t add); //固定写地址 data 地址 add 数据
void AIP1944_Continuous(uint8_t addr,uint8_t data); 
void AIP1944_ClearDisplay(void); //清屏
void AIP1944_GrayScale(uint8_t data); //亮度调节
void AIP1944_Write_Command(uint8_t unm);
	    void Flow(void);
        void clearRam(void);
        void Write_Little_H(void);
        void AIP1944_Fixed_Add();
        void drawImage(unsigned char *buf);
        void AIP_DECIMAL_XXXX(int num);
#endif

