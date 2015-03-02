//--------------------液晶显示程序 -------------------//
/*                  Creat By ES                       */
/*           http://shop101811732.taobao.com          */
/******************************************************
实验内容：
1.在液晶上显示一串字符 Welcome to ES
2.在液晶上显示一个 unsigned char 类型的数据（数据自动自增）
3.在液晶上显示一个 unsigned int 类型的数据（数据自动自增）

注意：需要在本店铺购买JLX12864液晶模块
******************************************************/

#include "JLX12864.h"
#include "DS18b20.h"
#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char

#define Bell       P2_0	   //Bell为P2.0口控制



//函数声明
void Delayms(uint xms);		//延时函数
void Initial_IO(void);		//初始化P1口

uchar temp1=58;
uint  temp2=23567;

unsigned char DS18B20_1[8]={40,240,137,130,4,0,0,20};
unsigned char DS18B20_2[8]={40,59,160,130,4,0,0,120};
unsigned char DS18B20_3[8]={40,189,29,130,4,0,0,131};
unsigned char DS18B20_4[8]={40,112,57,130,4,0,0,177};
unsigned char DS18B20_5[8]={40,32,141,130,4,0,0,207};
unsigned char DS18B20_6[8]={40,37,48,130,4,0,0,135};

/****************************
//延时函数
*****************************/
void Delayms(uint xms)   //i=xms 即延时i毫秒
{
 uint i,j;
 for(i=xms;i>0;i--)
   for(j=587;j>0;j--);
}



/****************************
//初始化程序
*****************************/
void Initial_IO(void)
{
	P0DIR |= 0xff;     //P0为输入，其他引脚定义为输出
        P1DIR |= 0x01;     //P0为输入，其他引脚定义为输出
        P1SEL &= 0xfd;
        P2DIR |= 0x01;     //P2_0 为输出
}



/***************************
//主函数
***************************/
void main(void)
{	
  float M_wendu[10]={0};  
//     LCD_write_english_string(2,1," es-tech.taobao.com");
     
   DISABLE_ALL_INTERRUPTS();
   SET_MAIN_CLOCK_SOURCE(0);
   Initial_IO();   
   initial_lcd();
   clear_screen(); //clear all dots
   LCD_write_english_string(1,1,"    Welcome to ES ");  //显示英文字符串
/*   
   get_id();
   
   LCD_disp_char(7,1,id[0]);
   LCD_disp_char(7,21,id[1]);
   LCD_disp_char(7,41,id[2]);
   LCD_disp_char(7,61,id[3]);
   
   LCD_disp_char(8,1,id[4]);
   LCD_disp_char(8,21,id[5]);
   LCD_disp_char(8,41,id[6]);
   LCD_disp_char(8,61,id[7]);
*/  
   

   while(1)
   { 
     M_wendu[0]= read_data(DS18B20_1);
     M_wendu[1]= read_data(DS18B20_2);
     M_wendu[2]= read_data(DS18B20_3);
     M_wendu[3]= read_data(DS18B20_4);
     M_wendu[4]= read_data(DS18B20_5);
     M_wendu[5]= read_data(DS18B20_6);
     
         
     
     LCD_disp_Float(4,1, M_wendu[0],1);     //显示数据
     LCD_disp_Float(4,40, M_wendu[1],1);     //显示数据
     LCD_disp_Float(4,80, M_wendu[2],1);     //显示数据
     
     LCD_disp_Float(5,1, M_wendu[3],1);     //显示数据
     LCD_disp_Float(5,40, M_wendu[4],1);     //显示数据
     LCD_disp_Float(5,80, M_wendu[5],1);     //显示数据
     
     temp1++;          //数据自增
     Delayms(300);	
     
     }
}


