#include "drv_lcd.h"
#include "delay.h"
#include "spi.h"
#include "tim.h"

//-----------------端口定义----------------
#define SCLK_PORT			GPIOB
#define SCLK_PIN			GPIO_PIN_3

#define SDA_PORT			GPIOB
#define SDA_PIN				GPIO_PIN_5

#define BLK_PORT			GPIOB
#define BLK_PIN				GPIO_PIN_0


#define LCD_SCLK_Clr()       HAL_GPIO_WritePin(SCLK_PORT,SCLK_PIN,GPIO_PIN_RESET)
#define LCD_SCLK_Set()       HAL_GPIO_WritePin(SCLK_PORT,SCLK_PIN,GPIO_PIN_SET)

#define LCD_MOSI_Clr()       HAL_GPIO_WritePin(SDA_PORT,SDA_PIN,GPIO_PIN_RESET)
#define LCD_MOSI_Set()       HAL_GPIO_WritePin(SDA_PORT,SDA_PIN,GPIO_PIN_SET)

#define LCD_CS_Clr()        HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,GPIO_PIN_RESET)
#define LCD_CS_Set()        HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,GPIO_PIN_SET)

#define LCD_DC_Clr()        HAL_GPIO_WritePin(LCD_DC_GPIO_Port,LCD_DC_Pin,GPIO_PIN_RESET)
#define LCD_DC_Set()        HAL_GPIO_WritePin(LCD_DC_GPIO_Port,LCD_DC_Pin,GPIO_PIN_SET)

#define LCD_BLK_OFF()       HAL_GPIO_WritePin(BLK_PORT,BLK_PIN,GPIO_PIN_RESET)
#define LCD_BLK_ON()        HAL_GPIO_WritePin(BLK_PORT,BLK_PIN,GPIO_PIN_SET)

#define LCD_RST_Clr()		HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,GPIO_PIN_RESET)
#define LCD_RST_Set()		HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,GPIO_PIN_SET)




/*************************************
 * @brief 写16位数据
 * @param  u16 data
 * @return void
 *************************************/
static void LCDSendData(u16 data)
{
	HAL_SPI_Transmit(&hspi1,(u8 *)&data,1,1);
}

/*************************************
 * @brief 发送命令
 * @param  u8 cmd
 * @return void
 *************************************/
static void LCDSendCmd(u8 cmd)
{
    LCD_DC_Clr();
    LCDSendData(cmd);
    LCD_DC_Set();
}

/*************************************
 * @brief  往指定寄存器地址写8位数据
 * @param  u8 addr,u8 data
 * @return void
 *************************************/
static void LCDWriteReg(u8 addr,u8 data)
{
    LCDSendCmd(addr);
    LCDSendData(data);
}



void LCD_Init(void)
{
    LCD_CS_Clr();		//chip select
	
	//复位
	LCD_RST_Clr();	
	delay_ms(100);
	LCD_RST_Set();
	delay_ms(100);
	
	LCDSendCmd(0x11); 
	delay_ms(120); 
	LCDSendCmd(0x36); 
	if(USE_HORIZONTAL==0)LCDSendData(0x00);
	else if(USE_HORIZONTAL==1)LCDSendData(0xC0);
	else if(USE_HORIZONTAL==2)LCDSendData(0x70);
	else LCDSendData(0xA0);

	LCDSendCmd(0x3A);
	LCDSendData(0x05);

	LCDSendCmd(0xB2);
	LCDSendData(0x0C);
	LCDSendData(0x0C);
	LCDSendData(0x00);
	LCDSendData(0x33);
	LCDSendData(0x33); 

	LCDSendCmd(0xB7); 
	LCDSendData(0x35);  

	LCDSendCmd(0xBB);
	LCDSendData(0x19);

	LCDSendCmd(0xC0);
	LCDSendData(0x2C);

	LCDSendCmd(0xC2);
	LCDSendData(0x01);

	LCDSendCmd(0xC3);
	LCDSendData(0x12);   

	LCDSendCmd(0xC4);
	LCDSendData(0x20);  

	LCDSendCmd(0xC6); 
	LCDSendData(0x0F);    

	LCDSendCmd(0xD0); 
	LCDSendData(0xA4);
	LCDSendData(0xA1);

	LCDSendCmd(0xE0);
	LCDSendData(0xD0);
	LCDSendData(0x04);
	LCDSendData(0x0D);
	LCDSendData(0x11);
	LCDSendData(0x13);
	LCDSendData(0x2B);
	LCDSendData(0x3F);
	LCDSendData(0x54);
	LCDSendData(0x4C);
	LCDSendData(0x18);
	LCDSendData(0x0D);
	LCDSendData(0x0B);
	LCDSendData(0x1F);
	LCDSendData(0x23);

	LCDSendCmd(0xE1);
	LCDSendData(0xD0);
	LCDSendData(0x04);
	LCDSendData(0x0C);
	LCDSendData(0x11);
	LCDSendData(0x13);
	LCDSendData(0x2C);
	LCDSendData(0x3F);
	LCDSendData(0x44);
	LCDSendData(0x51);
	LCDSendData(0x2F);
	LCDSendData(0x1F);
	LCDSendData(0x1F);
	LCDSendData(0x20);
	LCDSendData(0x23);

	LCDSendCmd(0x21); 

	LCDSendCmd(0x29); 

}

/*************************************
 * @brief 设置屏幕起始和结束地址
 * @param  LCDArea_t *area
 * @return void
 *************************************/
static void LCDSetCusor(LCDArea_t *area)
{
	//指定X方向操作区域
    LCDSendCmd(0x2a);
    LCDSendData(area->x1);
    LCDSendData(area->x2);

	//指定y方向操作区域
    LCDSendCmd(0x2b);
    LCDSendData(area->y1);
    LCDSendData(area->y2);

	//发送该命令，LCD开始等待接收显存数据
    LCDSendCmd(0x2c);
}


void LCDFillPureColor(LCDArea_t *area,u16 *color_p)
{
	if((area->x1 > LCD_W-1) || (area->x2 > LCD_W-1) || (area->y1 > LCD_H-1) || (area->y2 > LCD_H-1))
		return;
	LCDSetCusor(area);
	u32 size;
	size = (area->x2 - area->x1+1)*(area->y2 - area->y1+1);

	

}

