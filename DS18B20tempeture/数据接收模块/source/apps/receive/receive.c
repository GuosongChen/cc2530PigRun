/**********************************************************************************/
//---------------------------温度无线数据采样并发送至计算机显示------------------------------//
/*                                Creat By ES                                   */  
/*                        http://es-tech.taobao.com                       */  
/*******************************************************************************
此程序为接收模块程序

实验操作：

把本程序下载到其中一个模块中，模块上电设定本机地址为 RECEIVE_ADDR = 0xBEEF，当检测到
有其他模块向本地址发送数据，进入到数据接收函数，把数据保存在寄存器 Data_buffer 
中，LED闪烁一下。同时液晶显示接收到的数据值, 并发送至计算机。
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
#define SEND_ADDR             0xBEEE   //发送模块地址
#define RECEIVE_ADDR          0xBEEF   //接收模块地址
#define APP_PAYLOAD_LENGTH        3    //数据长度

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
*函数功能 ：延时						*
*入口参数 ：定性延时						*
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
    basicRfConfig.myAddr = RECEIVE_ADDR;   // 设定本机地址
    
    halBoardInit();   //初始化单片机
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
    basicRfReceiveOn();   //开接收
    
     while (1) {
         
        if (basicRfPacketIsReady()){   // receive data
          if(basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL)>0) { 
            temperture=(float)(pRxData[0]*256+pRxData[1])*0.0625;  //取出数据并计算温度  
                       
            Green_LED=!Green_LED;
            Data_receive=1;

            }
         }
          if(Data_receive){
            Data_receive=0;
            LCD_disp_Float(4,80, temperture,1);     //  显示传感器温度

            temp_data[0]= (unsigned char)(temperture)/10+'0';
            temp_data[1]= (unsigned char)(temperture)%10+'0';
            temp_data[3]= (unsigned char)(temperture*10)%10+'0';             
            
            UartTX_Send_String(" Wendu:",7);  
            UartTX_Send_String(temp_data,4);           //发送温度数据 
          }
   
    }
    
}

        
