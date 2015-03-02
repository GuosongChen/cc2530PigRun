/********************************************************************************/
//---------------------------AD 采样与无线通信程序----------------------------------//
/*                              Creat By ES                                    */
/*                      http://es-tech.taobao.com                        */
/*******************************************************************************

实验操作：

把本程序下载到模块中并运行，模块上电后每隔一段时间采样温度值
温度值储存在 pTxData 数组里，通过Zigbee协议发送 到地址为 
ADDR   0xBEEF 的模块中

DS18B20 的VCC引脚接CC2530的VCC，GND接CC2530的GND，数据引脚接CC2530的P01引脚

当接收模块接收到数据以后，把接收到的数据转化成温度值，并显示在液晶上
同时发送到计算机

***********************************************************************************/
// INCLUDES
//
#include <hal_assert.h>
#include <hal_board.h>
#include <hal_int.h>
#include "hal_mcu.h"
#include "hal_rf.h"
#include "hal.h"
#include "basic_rf.h"
#include "hal_lcd.h"
#include "DS18B20.h"


/***********************************************************************************
* CONSTANTS
*/
// Application parameters
#define RF_CHANNEL                25      // 2.4 GHz RF channel

// BasicRF address definitions
#define PAN_ID                0x2007
#define ADDR                  0xBEEE
#define ADDR_dest             0xBEEF
#define APP_PAYLOAD_LENGTH        3

#define DISABLE_ALL_INTERRUPTS() (IEN0 = IEN1 = IEN2 = 0x00)//三个



static uint8 pTxData[APP_PAYLOAD_LENGTH];
static basicRfCfg_t basicRfConfig;
uint8 temp=0;
uint8 data_count=0;
uint16 temp_ini=0;
float temperature;



unsigned char DS18B20_address[8]={40,252,5,130,4,0,0,131};

unsigned int  M_wendu=0;


/**************************
读取温度函数
**************************/ 
unsigned int read_data(unsigned char *buffer)
{
  unsigned char temh,teml; 
  unsigned int wendu;
//  unsigned char *temp;
  
//  temp=buffer;
  init_1820();  //复位18b20  
//  Match_DS18B20(temp) ; // 
  write_1820(0xcc); 
  write_1820(0x44);     //启动  
  Delay_nus(50000);
  init_1820();  
//  Match_DS18B20(temp) ; 
  write_1820(0xcc); 
  write_1820(0xbe);      
  teml=read_1820();  //读数据  
  temh=read_1820();
  wendu=temh*256+teml;
  return(wendu);   //返回温度数据
}


void main(void)
{
    // Config basicRF
    basicRfConfig.panId = PAN_ID;
    basicRfConfig.channel = RF_CHANNEL;
    basicRfConfig.ackRequest = TRUE;

    halBoardInit();  
    initial_lcd();
    clear_screen(); 
    
    LCD_write_english_string(1,1,"Welcome to XinTaoYuan ");
    LCD_write_english_string(2,1,"DS18B20 Sample");
    LCD_write_english_string(4,1,"Wendu:");


    // Initalise hal_rf
    if(halRfInit()==FAILED) {
      HAL_ASSERT(FALSE);
    }

    basicRfConfig.myAddr = ADDR; // Initialize BasicRF
    if(basicRfInit(&basicRfConfig)==FAILED) {
      HAL_ASSERT(FALSE);
    }   
        
    basicRfReceiveOn();  
    
    while(1){
      
            Red_LED=1;    //红色LED亮，开始采样
            
            M_wendu = read_data(DS18B20_address);   //采样温度  temperature= M_wendu*0.0625
            halMcuWaitMs(1); 
            temperature=M_wendu*0.0625;
            LCD_disp_Float(4,80, temperature,1);    
            pTxData[0]=(unsigned char)(M_wendu>>8);         //装载传感器温度数据到发送数据数据
            pTxData[1]=(unsigned char)(M_wendu&0x00ff);
            
            basicRfSendPacket(ADDR_dest, pTxData, APP_PAYLOAD_LENGTH);  // 发送数据 

            halIntOn(); // interrupt enable           
            Red_LED=0;   //红色LED灭，发送数据完毕
                       
            halMcuWaitMs(1000);
                        
 
    }
      

}

/******************************************************************************
* @fn  powermodes_ST_IRQ
*
* @brief
*     Interrupt handler for Sleep Timer.
*
* Parameters:
*
* @param  void
*
* @return void
*
******************************************************************************/
#pragma vector=ST_VECTOR
__interrupt void powermodes_ST_IRQ(void){
   INT_SETFLAG(INUM_ST, INT_CLR);
}





