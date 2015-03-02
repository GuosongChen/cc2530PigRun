//---------------�¶Ȳɼ�����ʾ��Һ����----------------//
/*                  Creat By ES                       */
/*           http://es-tech.taobao.com          */
/******************************************************
ʵ�����ݣ�
1.�趨 P00ΪAD����ڣ�����ת��,�ο���ѹΪ�ڲ���׼��ѹ��
  ��׼��ѹΪ1.15V��14λ�ֱ���
2.���������ݺ�ͨ�����㻻��ɵ�ѹֵ����ʾ��Һ����
3.ÿ���һ��ת����Һ������ֵ����1.

ע�⣺Һ����ʾ��Ҫ�ڱ����̹���Һ��ģ�� JLX12864
P00���ſ��Խ�һ���ɵ��ĵ�ѹ�Ѳ��Ա�����Ĺ��ܣ�ע��
�����������ѹ��ΧΪ0-1.15V�����Ҫ�������ѹ��Χ��
����ѡ��ͬ�Ļ�׼��ѹ����ѡ��VDD��Ϊ��׼��ѹʱ��
�����ĵ�ѹ���뷶ΧΪ0-VDD��
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
//IO��ʼ������
*****************************/
void Initial_IO(void)
{
      P0DIR |= 0xfe;     //P0����Ϊ���      
      P1DIR |= 0xff;     //P1_7����Ϊ���
} 

/****************************************************************
*�������� ����ʱ						*
*��ڲ��� ��������ʱ						*
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
������   
****************************************************************/ 
void main(void) 
{   
        uchar temp;
        Initial_IO();
        initial_lcd();
        HalAdcSetReference(HAL_ADC_REF_125V); /* Internal Reference (1.25V-CC2430)(1.15V-CC2530) */
        
        clear_screen();      //clear all dots
        LCD_write_english_string(1,1,"    Welcome to ES ");  //��ʾӢ���ַ���
        LCD_write_english_string(2,1," es-tech.taobao.com");
        LCD_write_english_string(5,1,"Sample Voltage at P00");
        
        LCD_write_english_string(4,1,"AD Value:      V");  //��ʾ�ַ���
        

        while(1) 
        {          
	       AD_data = HalAdcRead(HAL_ADC_CHANNEL_0,HAL_ADC_RESOLUTION_14); //P00
               num = (float)(AD_data)*1.15/8096.0;  //���ο���ѹΪ1.15V��14λ��ȷ��  
               LCD_disp_Float(4,62, num,2);     //��ʾ����
	       Delay(30000);
               temp++;                      //������ݴ���
               LCD_disp_char(7,62, temp);     //��ʾ����
               Red_LED=!Red_LED;
                      
        } 
}