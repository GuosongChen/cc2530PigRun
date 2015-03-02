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
* ��    ��: InitLed()
* ��    ��: ����LED��Ӧ��IO��
* ��ڲ���: ��
* ���ڲ���: ��
****************************************************************************/
void InitLed(void)
{
  P1DIR |= 0x01;               //P1.0����Ϊ�����  
  P1DIR |= 0x02;               //P1.1����Ϊ����� 
  P1DIR |= 0x10;               //P1.4����Ϊ����� 
  Yellow_LED=0;
  Green_LED=0;
  Red_LED=0;
}

/****************************************************************************
* ��    ��: InitKey()
* ��    ��: ���ð�����Ӧ��IO��
* ��ڲ���: ��
* ���ڲ���: ��
****************************************************************************/
void InitKey(void)
{
    P0SEL &= ~0x10;     //����P0.4Ϊ��ͨIO��  
    P0DIR &= ~0x10;     //��������P0.4���ϣ���P0.4Ϊ����ģʽ 
    P0SEL &= ~0x20;     //����P0.5Ϊ��ͨIO��  
    P0DIR &= ~0x20;     //��������P0.5���ϣ���P0.5Ϊ����ģʽ 
}


void halBoardInit(void)
{
    halMcuInit();
    halIntOn();
    InitLed();
    InitKey();
}

