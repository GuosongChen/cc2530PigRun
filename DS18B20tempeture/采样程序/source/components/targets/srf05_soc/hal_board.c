/***********************************************************************************
  Filename:     hal_board.c

  Description:  HAL board peripherals library for the
                SmartRF05EB + CC2430EM/CC2531EM/CC2510/CC1110 platforms

***********************************************************************************/

/***********************************************************************************
* INCLUDES
*/
#include "hal_types.h"
#include "hal_defs.h"
#include "hal_digio.h"
#include "hal_int.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "clock.h"

#define SPI_CLOCK_POL_LO       0x00
#define SPI_CLOCK_POL_HI       0x80
#define SPI_CLOCK_PHA_0        0x00
#define SPI_CLOCK_PHA_1        0x40
#define SPI_TRANSFER_MSB_FIRST 0x20
#define SPI_TRANSFER_MSB_LAST  0x00

/****************************************************************************
* 名    称: InitLed()
* 功    能: 设置LED相应的IO口
* 入口参数: 无
* 出口参数: 无
****************************************************************************/
void InitLed(void)
{
  P1DIR |= 0x01;               //P1.0定义为输出口  
  P1DIR |= 0x02;               //P1.1定义为输出口 
  P1DIR |= 0x10;               //P1.4定义为输出口 
  Yellow_LED=0;
  Green_LED=0;
  Red_LED=0;
}

/****************************************************************************
* 名    称: InitKey()
* 功    能: 设置按键相应的IO口
* 入口参数: 无
* 出口参数: 无
****************************************************************************/
void InitKey(void)
{
    P0SEL &= ~0x10;     //设置P0.4为普通IO口  
    P0DIR &= ~0x10;     //按键接在P0.4口上，设P0.4为输入模式 
    P0SEL &= ~0x20;     //设置P0.5为普通IO口  
    P0DIR &= ~0x20;     //按键接在P0.5口上，设P0.5为输入模式 
}


void halBoardInit(void)
{
    halMcuInit();
    halIntOn();
    InitLed();
    InitKey();
}

