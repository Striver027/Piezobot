#include "lcd_init.h"
#include "spi.h"




/******************************************************************************
      函数说明：LCD串行数据写入函数
      入口数据：dat  要写入的串行数据
      返回值：  无
******************************************************************************/
void LCD_Writ_Bus(uint8_t dat) 
{	
	LCD_CS_LOW();
	HAL_SPI_Transmit(&hspi3, &dat, 1, 0xffff);
	LCD_CS_HIGH();

}


/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA8(uint8_t dat)
{
//	LCD_DC_HIGH();//写数据
	LCD_Writ_Bus(dat);
//	LCD_CS_HIGH();
}


/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA16(uint16_t dat)
{
//	LCD_DC_HIGH();//写数据
	LCD_Writ_Bus(dat>>8);
	LCD_Writ_Bus(dat);
//	LCD_CS_HIGH();
}


/******************************************************************************
      函数说明：LCD写入命令
      入口数据：dat 写入的命令
      返回值：  无
******************************************************************************/
void LCD_WR_REG(uint8_t dat)
{
	LCD_DC_LOW();//写命令
	LCD_Writ_Bus(dat);
//	LCD_CS_HIGH();
	LCD_DC_HIGH();//写数据
}


/******************************************************************************
      函数说明：设置起始和结束地址
      入口数据：x1,x2 设置列的起始和结束地址
                y1,y2 设置行的起始和结束地址
      返回值：  无
******************************************************************************/
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	if(USE_HORIZONTAL==0)
	{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA16(x1);
		LCD_WR_DATA16(x2);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA16(y1+45);
		LCD_WR_DATA16(y2+45);
		LCD_WR_REG(0x2c);//储存器写
	}
	else if(USE_HORIZONTAL==1)
	{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA16(x1);
		LCD_WR_DATA16(x2);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA16(y1);
		LCD_WR_DATA16(y2);
		LCD_WR_REG(0x2c);//储存器写
	}
	else if(USE_HORIZONTAL==2)
	{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA16(x1+45);
		LCD_WR_DATA16(x2+45);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA16(y1);
		LCD_WR_DATA16(y2);
		LCD_WR_REG(0x2c);//储存器写
	}
	else
	{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA16(x1);
		LCD_WR_DATA16(x2);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA16(y1);
		LCD_WR_DATA16(y2);
		LCD_WR_REG(0x2c);//储存器写
	}
}
void LCD_Init(void)
{
	LCD_REST_HIGH();
	HAL_Delay(10);
	LCD_REST_LOW();//复位
	HAL_Delay(200);
	LCD_REST_HIGH();
	HAL_Delay(10);
	
//	LCD_BLK_Set();//打开背光
//  HAL_Delay(100);
	LCD_WR_REG(0x36);
	if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x00);
	else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC0);
	else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x60);
	else LCD_WR_DATA8(0xA0);


	LCD_WR_REG(0xFE);			
	LCD_WR_REG(0xEF);
		
	LCD_WR_REG(0xB0);			
	LCD_WR_DATA8(0xC0); 
		
	LCD_WR_REG(0xB2);		
	LCD_WR_DATA8(0x2f); 
			
	LCD_WR_REG(0xB3);		
	LCD_WR_DATA8(0x03);
		
	LCD_WR_REG(0xB7);		
	LCD_WR_DATA8(0x01);  

	LCD_WR_REG(0xB6);			
	LCD_WR_DATA8(0x19); 
		
	LCD_WR_REG(0xAC);
	LCD_WR_DATA8(0xDB);
		
	LCD_WR_REG(0xAB);
	LCD_WR_DATA8(0x0f);

	LCD_WR_REG(0x3A);		
	LCD_WR_DATA8(0x05); 
			
	LCD_WR_REG(0xB4);	
	LCD_WR_DATA8(0x04);

	LCD_WR_REG(0xA8);	
	LCD_WR_DATA8(0x08);

	LCD_WR_REG(0xb8);
	LCD_WR_DATA8(0x08);
		
	LCD_WR_REG(0xea);
	LCD_WR_DATA8(0x94); 

	LCD_WR_REG(0xe8);
	LCD_WR_DATA8(0x22); 

	LCD_WR_REG(0xe9);
	LCD_WR_DATA8(0x43); 

	LCD_WR_REG(0xc6);
	LCD_WR_DATA8(0x21); 

	LCD_WR_REG(0xc7);	
	LCD_WR_DATA8(0x12); 


	LCD_WR_REG(0xF0);	
	LCD_WR_DATA8(0x1D);
	LCD_WR_DATA8(0x45);
	LCD_WR_DATA8(0x0a);
	LCD_WR_DATA8(0x54);
	LCD_WR_DATA8(0xB4);
	LCD_WR_DATA8(0x2F);
	LCD_WR_DATA8(0x35);
	LCD_WR_DATA8(0x52);
	LCD_WR_DATA8(0x1E);
	LCD_WR_DATA8(0x0e);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x18);
	LCD_WR_DATA8(0x1A);
	LCD_WR_DATA8(0x1F);

	LCD_WR_REG(0xF1);
	LCD_WR_DATA8(0x16);
	LCD_WR_DATA8(0x38);
	LCD_WR_DATA8(0x1A);
	LCD_WR_DATA8(0x56);
	LCD_WR_DATA8(0x97);
	LCD_WR_DATA8(0x2D);
	LCD_WR_DATA8(0x2E);
	LCD_WR_DATA8(0x56);
	LCD_WR_DATA8(0x10);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x06);
	LCD_WR_DATA8(0x16);
	LCD_WR_DATA8(0x12);
	LCD_WR_DATA8(0x1E);

	LCD_WR_REG(0x11);
	HAL_Delay(120);
	LCD_WR_REG(0x29);
	HAL_Delay(120);
	

}





