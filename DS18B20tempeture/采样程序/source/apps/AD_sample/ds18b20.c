
#include "DS18B20.h"

unsigned char id[8];
unsigned char sensor_data_value[2];
unsigned char flag; 

void Delay_nus(unsigned int s) 
{
  while (s--)
  {
    asm("NOP");
    asm("NOP");
    asm("NOP");
  }
}

void init_1820(void) 
{
  SET_OUT; 
  SET_DQ;//���1
  CL_DQ; 
  Delay_nus(550);//����һ��ʱ�� 
  SET_DQ;//�ͷ� 
  SET_IN;//���� 
  Delay_nus(40); //�ͷ����ߺ�ȴ�15-60us
  while(IN_DQ)  {;}//�ȴ��ظ� 
  Delay_nus(240);//�ظ��ĵ͵�ƽ��60��240us  
  SET_OUT; 
  SET_DQ;//�ص���ʼDQ=1��
}

void write_1820(unsigned char x)  
{  
  unsigned char m;    
  SET_OUT;
  for(m=0;m<8;m++)  
  {  
     CL_DQ;
     if(x&(1<<m))    //д���ݣ��ӵ�λ��ʼ  
     SET_DQ; 
     else  
     CL_DQ;  
     Delay_nus(40);   //15~60us  
     SET_DQ;  
  }
  SET_DQ;  
} 


unsigned char read_1820(void)  
{   
  unsigned char temp,k,n;    
  temp=0;  
  for(n=0;n<8;n++)  
  {  
    CL_DQ;     
    SET_DQ; 
    SET_IN;  
    k=IN_DQ;    //������,�ӵ�λ��ʼ  
    if(k)  
    temp|=(1<<n);  
    else  
    temp&=~(1<<n);  
    Delay_nus(70); //60~120us      
    SET_OUT;
  
  }  
  return (temp);  
}  
//����ID
void get_id()
{     
  init_1820();        //resert
  write_1820(0x33); 
  
  for(unsigned char ii=0;ii<8;ii++)
  {
    id[ii]=read_1820();
  }
}

void Match_DS18B20(unsigned char *buffer)
{
 unsigned char i;
 write_1820(0x55);
 for(i=0;i<8;i++){
   write_1820(buffer[i]);
   }
 } 






