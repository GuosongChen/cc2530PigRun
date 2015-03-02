//---------------温度采集并显示在液晶上----------------//
/*                  Creat By ES                       */
/*           http://es-tech.taobao.com          */
/******************************************************
实验内容：
1.设定 P00为AD输入口，单次转换,参考电压为内部基准电压，
  基准电压为1.15V，14位分辨率
2.采样到数据后，通过计算换算成电压值并显示在液晶上
3.每完成一次转化，液晶上数值增加1.

注意：液晶显示需要在本店铺购买液晶模块 JLX12864
P00引脚可以接一个可调的电压已测试本程序的功能，注意
测量的输入电压范围为0-1.15V。如果要改输入电压范围，
可以选择不同的基准电压，入选择VDD作为基准电压时，
测量的电压输入范围为0-VDD。
******************************************************/

#include <ioCC2530.h>
#include "JLX12864.h" 
#include  "hal_adc.h"

#define uint unsigned int
#define uchar unsigned char

#define Red_LED     P1_4    

uint AD_data=0;
float num=0;

/****************************
//IO初始化程序
*****************************/
void Initial_IO(void)
{
      P0DIR |= 0xfe;     //P0定义为输出      
      P1DIR |= 0xff;     //P1_7定义为输出
} 

/****************************************************************
*函数功能 ：延时						*
*入口参数 ：定性延时						*
****************************************************************/
void Delay(uint n)
{
	uint i;
	for(i=0;i<n;i++);
	for(i=0;i<n;i++);
	for(i=0;i<n;i++);
	for(i=0;i<n;i++);
	for(i=0;i<n;i++);
}

/**************************************************************** 
主函数   
****************************************************************/ 
void main(void) 
{   
        uchar temp;
        Initial_IO();
        initial_lcd();
        HalAdcSetReference(HAL_ADC_REF_125V); /* Internal Reference (1.25V-CC2430)(1.15V-CC2530) */
        
        clear_screen();      //clear all dots
        LCD_write_english_string(1,1,"    Welcome to ES ");  //显示英文字符串
        LCD_write_english_string(2,1," es-tech.taobao.com");
        LCD_write_english_string(5,1,"Sample Voltage at P00");
        
        LCD_write_english_string(4,1,"AD Value:      V");  //显示字符串
        

        while(1) 
        {          
	       AD_data = HalAdcRead(HAL_ADC_CHANNEL_0,HAL_ADC_RESOLUTION_14); //P00
               num = (float)(AD_data)*1.15/8096.0;  //定参考电压为1.15V。14位精确度  
               LCD_disp_Float(4,62, num,2);     //显示数据
	       Delay(30000);
               temp++;                      //完成数据处理
               LCD_disp_char(7,62, temp);     //显示数据
               Red_LED=!Red_LED;
                      
        } 
}