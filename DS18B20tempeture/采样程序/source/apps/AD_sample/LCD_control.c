//--------------------Һ����ʾ���� -------------------//
/*                  Creat By ES                       */
/*           http://shop101811732.taobao.com          */
/******************************************************
ʵ�����ݣ�
1.��Һ������ʾһ���ַ� Welcome to ES
2.��Һ������ʾһ�� unsigned char ���͵����ݣ������Զ�������
3.��Һ������ʾһ�� unsigned int ���͵����ݣ������Զ�������

ע�⣺��Ҫ�ڱ����̹���JLX12864Һ��ģ��
******************************************************/

#include "JLX12864.h"
#include "DS18b20.h"
#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char

#define Bell       P2_0	   //BellΪP2.0�ڿ���



//��������
void Delayms(uint xms);		//��ʱ����
void Initial_IO(void);		//��ʼ��P1��

uchar temp1=58;
uint  temp2=23567;

unsigned char DS18B20_1[8]={40,240,137,130,4,0,0,20};
unsigned char DS18B20_2[8]={40,59,160,130,4,0,0,120};
unsigned char DS18B20_3[8]={40,189,29,130,4,0,0,131};
unsigned char DS18B20_4[8]={40,112,57,130,4,0,0,177};
unsigned char DS18B20_5[8]={40,32,141,130,4,0,0,207};
unsigned char DS18B20_6[8]={40,37,48,130,4,0,0,135};

/****************************
//��ʱ����
*****************************/
void Delayms(uint xms)   //i=xms ����ʱi����
{
 uint i,j;
 for(i=xms;i>0;i--)
   for(j=587;j>0;j--);
}



/****************************
//��ʼ������
*****************************/
void Initial_IO(void)
{
	P0DIR |= 0xff;     //P0Ϊ���룬�������Ŷ���Ϊ���
        P1DIR |= 0x01;     //P0Ϊ���룬�������Ŷ���Ϊ���
        P1SEL &= 0xfd;
        P2DIR |= 0x01;     //P2_0 Ϊ���
}



/***************************
//������
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
   LCD_write_english_string(1,1,"    Welcome to ES ");  //��ʾӢ���ַ���
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
     
         
     
     LCD_disp_Float(4,1, M_wendu[0],1);     //��ʾ����
     LCD_disp_Float(4,40, M_wendu[1],1);     //��ʾ����
     LCD_disp_Float(4,80, M_wendu[2],1);     //��ʾ����
     
     LCD_disp_Float(5,1, M_wendu[3],1);     //��ʾ����
     LCD_disp_Float(5,40, M_wendu[4],1);     //��ʾ����
     LCD_disp_Float(5,80, M_wendu[5],1);     //��ʾ����
     
     temp1++;          //��������
     Delayms(300);	
     
     }
}


