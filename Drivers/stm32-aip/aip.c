#include "aip.h"  
 
#define CLK_PORT GPIOG
#define DIO_PORT GPIOG
#define STB_PORT GPIOG
#define CLK_PIN GPIO_PIN_0
#define DIO_PIN GPIO_PIN_1
#define STB_PIN GPIO_PIN_3
#define CLK_PORT_CLK_ENABLE __HAL_RCC_GPIOG_CLK_ENABLE
#define DIO_PORT_CLK_ENABLE __HAL_RCC_GPIOG_CLK_ENABLE
#define STB_PORT_CLK_ENABLE __HAL_RCC_GPIOG_CLK_ENABLE


#define AIP1944_CKL_H    HAL_GPIO_WritePin(CLK_PORT, CLK_PIN, GPIO_PIN_SET);_DelayUsec(1)
#define AIP1944_CKL_L    HAL_GPIO_WritePin(CLK_PORT, CLK_PIN, GPIO_PIN_RESET) ;_DelayUsec(1)
 
#define AIP1944_DIO_H HAL_GPIO_WritePin(DIO_PORT, DIO_PIN, GPIO_PIN_SET);_DelayUsec(1)
#define AIP1944_DIO_L HAL_GPIO_WritePin(DIO_PORT, DIO_PIN, GPIO_PIN_RESET);_DelayUsec(1)
 
 
#define AIP1944_STB_H HAL_GPIO_WritePin(STB_PORT, STB_PIN, GPIO_PIN_SET);_DelayUsec(1)
#define AIP1944_STB_L HAL_GPIO_WritePin(STB_PORT, STB_PIN, GPIO_PIN_RESET);_DelayUsec(1)


void _DelayUsec(unsigned int i)  
{
   for (; i>0; i--) {
       for (int j = 0; j < 168; ++j) {
           __nop(); 
       }
   }
}



void AIP1944_Init(void)
{
    AIP1944_ClearDisplay();
}
 
/*************************************
函数名称:AIP1944_Write_Bit
函数说明:写单个字节
函数参数:命令返回
函数返回:NULL
*************************************/
void AIP1944_Write_Bit(uint8_t data)
{
	uint8_t i;
	
	for(i = 0; i < 8; i++)
	{
        AIP1944_CKL_L;
		if((data & 0x01) == 1)
		{
			AIP1944_DIO_H;
		}
		else
		{
			AIP1944_DIO_L;
		}
		AIP1944_CKL_H;
		data = data >> 1;
	}
}
 
/*************************************
函数名称:AIP1944_Write_Command
函数说明:写命令
函数参数:命令参数
函数返回:NULL
*************************************/
void AIP1944_Write_Command(uint8_t unm)
{
	AIP1944_STB_L;
	AIP1944_Write_Bit(unm);
    AIP1944_STB_H;
    
}
 
 
/*************************************
函数名称:AIP1944_Continuous
函数说明:固定写显示
函数参数:(1)add 地址    (2)data 数据  
函数返回:NULL
*************************************/
#if 0
char buf_H[7] =
{
    0xC6,0xC6,0xFE,0xFE,0xC6,0xC6,0xC6
};
#else
char buf_H[7] =
{
    0x00,0xE7,0x42,0x7E,0x42,0xE7,0x00, 
};

#endif
char buf_I[7] =
{
    0x00,0x3E,0x08,0x08,0x08,0x3E,0x00,
};



char buf_1[7] =
{ 0x08, 0x0C, 0x08, 0x08, 0x08, 0x1c, 0x00};
char buf_2[7] =
{ 0x1C, 0x12, 0x08, 0x04, 0x02, 0x1E, 0x00};
char buf_3[7] =
{ 0x00, 0x1E, 0x10, 0x1E, 0x10, 0x1E, 0x00};


unsigned char idxArray[] = "1234567890";
unsigned char fontArray[][7] = 
{
    0x00,0x3C,0x42,0x42,0x42,0x3C,0x00,    //  [9], "0",Size:7, W8×H7, addr:0x003F
    0x00,0x30,0x38,0x30,0x30,0x78,0x00,    //  [0], "1",Size:7, W8×H7, addr:0x0000
    0x00,0x3C,0x42,0x30,0x08,0x7E,0x00,    //  [1], "2",Size:7, W8×H7, addr:0x0007
    0x00,0x3C,0x40,0x38,0x40,0x3C,0x00,    //  [2], "3",Size:7, W8×H7, addr:0x000E
    0x00,0x20,0x38,0x26,0xFF,0x20,0x00,    //  [3], "4",Size:7, W8×H7, addr:0x0015
    0x00,0x7C,0x02,0x7E,0x40,0x3E,0x00,    //  [4], "5",Size:7, W8×H7, addr:0x001C
    0x00,0x10,0x0C,0x76,0xC2,0x7C,0x00,    //  [5], "6",Size:7, W8×H7, addr:0x0023
    0x00,0x7E,0x20,0x10,0x08,0x0C,0x00,    //  [6], "7",Size:7, W8×H7, addr:0x002A
    0x00,0x3C,0x42,0x3E,0x43,0x3E,0x00,    //  [7], "8",Size:7, W8×H7, addr:0x0031
    0x00,0x3E,0x43,0x26,0x18,0x08,0x00,    //  [8], "9",Size:7, W8×H7, addr:0x0038
};


void AIP1944_Find()
{
	AIP1944_Write_Command(0x00);
    AIP1944_Write_Command(0x06);
	AIP1944_Write_Command(0x44);
    
    for(int j = 0xC0; j <0XFF; j++)
    {
        AIP1944_Write_Command(0x00);
        AIP1944_Write_Command(0x06);
        AIP1944_Write_Command(0x44);

        for(int i = 0; i < 7; i++)
        {
            AIP1944_STB_L;
            AIP1944_Write_Bit(j+i*4);
            AIP1944_Write_Bit(buf_H[i]);
            AIP1944_STB_H;
        }
        AIP1944_Write_Command(0x8F);
        HAL_Delay(1000);
        clearRam();
        HAL_Delay(1000);
    }
}
        
void AIP_DECIMAL_XXXX(int num)
{
    if(num > 9999)
    {
        return;
    }
    
   static unsigned int dig_1,dig_2,dig_3,dig_4;
   static unsigned int _dig_1,_dig_2,_dig_3,_dig_4;
    
    // Cal
    dig_1 = num % 10;
    num /= 10;
    dig_2 = num % 10;
    num /= 10;
    dig_3 = num % 10;
    num /= 10;
    dig_4 = num % 10;
    num /= 10;

    //Config
    AIP1944_Write_Command(0x00);
    AIP1944_Write_Command(0x06);
	AIP1944_Write_Command(0x44);
    
    
    //Draw on RAM
    if(_dig_4 != dig_4)
    {   
        _dig_4 = dig_4; 
        for(int i = 0; i < 7; i++)
        {
            AIP1944_STB_L;
            AIP1944_Write_Bit(0XC0+ i*4);
            AIP1944_Write_Bit(fontArray[dig_4][i]);
            AIP1944_STB_H;
        }
    }

    if(_dig_3 != dig_3)
    {
        _dig_3 = dig_3;
        for(int i = 0; i < 7; i++)
        {
            AIP1944_STB_L;
            AIP1944_Write_Bit(0XC1+ i*4);
            AIP1944_Write_Bit(fontArray[dig_3][i]);
            AIP1944_STB_H;
        }
    }
        
    if(_dig_2 != dig_2)
    {
        _dig_2 = dig_2;
        for(int i = 0; i < 7; i++)
        {
            AIP1944_STB_L;
            AIP1944_Write_Bit(0xdc+ i*4);
            AIP1944_Write_Bit(fontArray[dig_2][i]);
            AIP1944_STB_H;
        }
    }
        
    if(_dig_1 != dig_1)
    {
        _dig_1 = dig_1;
        for(int i = 0; i < 7; i++)
        {
            AIP1944_STB_L;
            AIP1944_Write_Bit(0xdd+ i*4);
            AIP1944_Write_Bit(fontArray[dig_1][i]);
            AIP1944_STB_H;
        }
    }
        

	AIP1944_Write_Command(0x8F);
}



void clearRam(void)
{
    AIP1944_Write_Command(0x00);
    AIP1944_Write_Command(0x06);
    AIP1944_Write_Command(0x40);
    AIP1944_STB_L;
	AIP1944_Write_Bit(0xC0);
    for(int i = 0; i < 56; i++)
        AIP1944_Write_Bit(0x00);
    AIP1944_STB_H;
}



//void Write_Little_H(void)
//{
//    AIP1944_Write_Command(0x00);
//    AIP1944_Write_Command(0x06);
//	AIP1944_Write_Command(0xC0);
//    AIP1944_STB_L;
//	AIP1944_Write_Bit(0xC0); //Start Address
//    
//    AIP1944_Write_Bit(0xC6);
//    AIP1944_Write_Bit(0x0C);
//    gap();

//    AIP1944_Write_Bit(0xC6);
//    AIP1944_Write_Bit(0x0c);
//    gap();

//    AIP1944_Write_Bit(0xFE);
//    AIP1944_Write_Bit(0x00);
//    gap();
//    AIP1944_Write_Bit(0xFE);
//    AIP1944_Write_Bit(0x0c);
//    gap();
//    AIP1944_Write_Bit(0xC6);
//    AIP1944_Write_Bit(0x0c);
//    gap();
//    AIP1944_Write_Bit(0xC6);
//    AIP1944_Write_Bit(0x0c);
//    gap();
//    AIP1944_Write_Bit(0xC6);
//    AIP1944_Write_Bit(0x0c);
//    gap();
//    
//    AIP1944_STB_H;
//    AIP1944_Write_Command(0x8F);
//}
 

 
/*************************************
函数名称:AIP1944_ClearDisplay
函数说明:清屏
函数参数:NULL
函数返回:NULL
*************************************/
 
void AIP1944_ClearDisplay(void)
{
    clearRam();
}


