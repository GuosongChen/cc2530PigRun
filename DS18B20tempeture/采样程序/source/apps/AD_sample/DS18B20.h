#ifndef DS18B20_H
#define DS18B20_H

#include "ioCC2530.h"
//#include "hal.h"

#define CL_DQ  P0_1=0
#define SET_DQ P0_1=1 
#define SET_OUT P0DIR|=0x02
#define SET_IN  P0DIR&=~0x02
#define IN_DQ  P0_1

extern unsigned char id[8];
extern unsigned char sensor_data_value[2];
extern unsigned char flag;


//void Delay_1us(void); 
void Delay_nus(unsigned int n) ;
void write_1820(unsigned char x) ; 
unsigned char read_1820(void);  
void init_1820(void) ; 
unsigned int read_data(unsigned char *buffer);
void get_id(void);
void Match_DS18B20(unsigned char *buffer);
void ds18b20_main(void);
#endif

