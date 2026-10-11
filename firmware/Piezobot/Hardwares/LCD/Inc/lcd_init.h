#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "lcd_init.h"
#include "stm32g4xx_hal.h"

#define USE_HORIZONTAL 0  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏

#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 128
#define LCD_H 115

#else
#define LCD_W 115
#define LCD_H 128
#endif





//-----------------LCD端口定义---------------- 

//#define LCD_SCLK_Clr() GPIO_ResetBits(GPIOG,GPIO_Pin_12)//SCL=SCLK
//#define LCD_SCLK_Set() GPIO_SetBits(GPIOG,GPIO_Pin_12)

//#define LCD_MOSI_Clr() GPIO_ResetBits(GPIOD,GPIO_Pin_5)//SDA=MOSI
//#define LCD_MOSI_Set() GPIO_SetBits(GPIOD,GPIO_Pin_5)

#define LCD_REST_LOW()   HAL_GPIO_WritePin(IPS_RESET_GPIO_Port, IPS_RESET_Pin, GPIO_PIN_RESET);
#define LCD_REST_HIGH()  HAL_GPIO_WritePin(IPS_RESET_GPIO_Port, IPS_RESET_Pin, GPIO_PIN_SET);

#define LCD_DC_LOW()     HAL_GPIO_WritePin(IPS_DC_GPIO_Port, IPS_DC_Pin, GPIO_PIN_RESET);
#define LCD_DC_HIGH()    HAL_GPIO_WritePin(IPS_DC_GPIO_Port, IPS_DC_Pin, GPIO_PIN_SET);

#define LCD_CS_LOW()     HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_RESET);
#define LCD_CS_HIGH()    HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_SET);

//#define LCD_WR_RS(n) (n?HAL_GPIO_WritePin(IPS_DC_GPIO_Port,IPS_DC_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(IPS_DC_GPIO_Port,IPS_DC_Pin,GPIO_PIN_RESET))





void LCD_GPIO_Init(void);//初始化GPIO
void LCD_Writ_Bus(uint8_t dat);//模拟SPI时序
void LCD_WR_DATA8(uint8_t dat);//写入一个字节
void LCD_WR_DATA16(uint16_t dat);//写入两个字节
void LCD_WR_REG(uint8_t dat);//写入一个指令
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);//设置坐标函数
void LCD_Init(void);//LCD初始化
#endif




