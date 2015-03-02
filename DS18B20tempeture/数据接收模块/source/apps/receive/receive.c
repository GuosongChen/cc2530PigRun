/**********************************************************************************/
//---------------------------�¶��������ݲ������������������ʾ------------------------------//
/*                                Creat By ES                                   */  
/*                        http://es-tech.taobao.com                       */  
/*******************************************************************************
�˳���Ϊ����ģ�����

ʵ�������

�ѱ��������ص�����һ��ģ���У�ģ���ϵ��趨������ַΪ RECEIVE_ADDR = 0xBEEF������⵽
������ģ���򱾵�ַ�������ݣ����뵽���ݽ��պ����������ݱ����ڼĴ��� Data_buffer 
�У�LED��˸һ�¡�ͬʱҺ����ʾ���յ�������ֵ, ���������������
***********************************************************************************/
// INCLUDES
//
#include <hal_assert.h>
#include <hal_board.h>
#include <hal_int.h>
#include "hal_mcu.h"
#include "hal_rf.h"
#include "basic_rf.h"
#include "hal_lcd.h"


/***********************************************************************************
* CONSTANTS
*/
// Application parameters
#define RF_CHANNEL                25    // 2.4 GHz RF channel
#define PAN_ID                0x2007
#define SEND_ADDR             0xBEEE   //����ģ���ַ
#define RECEIVE_ADDR          0xBEEF   //����ģ���ַ
#define APP_PAYLOAD_LENGTH        3    //���ݳ���

/***********************************************************************************
* LOCAL VARIABLES
*/
static uint8 pRxData[APP_PAYLOAD_LENGTH];
static basicRfCfg_t basicRfConfig;

uint16 Data_count=0;
uint8 Data_receive=0;
float temperture; 
uint8 wendu;
uint8 shidu;
uint8 Receive_Data_buffer[APP_PAYLOAD_LENGTH];
char data_buffer1[3]; 
char data_buffer2[3]; 
float num=0;
uint16 Reveive_data=0;
char temp_data[4]={0,0,'.','6'};

/****************************************************************
*�������� ����ʱ						*
*��ڲ��� ��������ʱ						*
****************************************************************/
void Delay(uint16 n)
{
	uint16 i;
	for(i=0;i<n;i++);
}

void InitUART0(void)
{
	PERCFG = 0x00;				 
	P0SEL = 0x0c;				 
	
	P2DIR &= ~0XC0;                            
        U0CSR |= 0x80;   	                  
        U0GCR |= 11;				
        U0BAUD |= 216;		                  

	UTX0IF = 1;                             
        U0CSR |= 0X40;				 
        IEN0 |= 0x84;				 

}

void UartTX_Send_String(char *Data,int len)
{
  int j;
  for(j=0;j<len;j++)
  {
    U0DBUF = *Data++;
    while(UTX0IF == 0);
    UTX0IF = 0;
  }
//     U0DBUF = 0x0A;        // ??
//    while(UTX0IF == 0);
//      UTX0IF = 0;
}



void main(void)
{
  // Config basicRF
    basicRfConfig.panId = PAN_ID;
    basicRfConfig.channel = RF_CHANNEL;
    basicRfConfig.ackRequest = TRUE;
    basicRfConfig.myAddr = RECEIVE_ADDR;   // �趨������ַ
    
    halBoardInit();   //��ʼ����Ƭ��
    InitUART0(); 
    initial_lcd();
    clear_screen(); //clear all dots
    LCD_write_english_string(1,1,"Welcome to XinTaoYuan ");
    LCD_write_english_string(2,1,"     Receiver ");
    LCD_write_english_string(4,1,"Wendu:");
    
    if(halRfInit()==FAILED) {
      HAL_ASSERT(FALSE);
    }    
    if(basicRfInit(&basicRfConfig)==FAILED) {
      HAL_ASSERT(FALSE);
    }   
   UartTX_Send_String("Testing ",8);
    basicRfReceiveOn();   //������
    
     while (1) {
         
        if (basicRfPacketIsReady()){   // receive data
          if(basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL)>0) { 
            temperture=(float)(pRxData[0]*256+pRxData[1])*0.0625;  //ȡ�����ݲ������¶�  
                       
            Green_LED=!Green_LED;
            Data_receive=1;

            }
         }
          if(Data_receive){
            Data_receive=0;
            LCD_disp_Float(4,80, temperture,1);     //  ��ʾ�������¶�

            temp_data[0]= (unsigned char)(temperture)/10+'0';
            temp_data[1]= (unsigned char)(temperture)%10+'0';
            temp_data[3]= (unsigned char)(temperture*10)%10+'0';             
            
            UartTX_Send_String(" Wendu:",7);  
            UartTX_Send_String(temp_data,4);           //�����¶����� 
          }
   
    }
    
}

        
