#ifndef _DRV_LCD_H__
#define _DRV_LCD_H__

#include "sys.h"

#define USE_HORIZONTAL 0  //?????????? 0?1??? 2?3???


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 240
#define LCD_H 280

#else
#define LCD_W 280
#define LCD_H 240
#endif

//????
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE           	 0x001F  
#define BRED             0XF81F
#define GRED 			       0XFFE0
#define GBLUE			       0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			     0XBC40 //??
#define BRRED 			     0XFC07 //???
#define GRAY  			     0X8430 //??
#define DARKBLUE      	 0X01CF	//???
#define LIGHTBLUE      	 0X7D7C	//???  
#define GRAYBLUE       	 0X5458 //???
#define LIGHTGREEN     	 0X841F //???
#define LGRAY 			     0XC618 //???(PANNEL),?????
#define LGRAYBLUE        0XA651 //????(?????)
#define LBBLUE           0X2B12 //????(???????)


typedef struct
{
    u16 x1; //??????
    u16 x2; //??????
    u16 y1; //??????
    u16 y2; //??????
} LCDArea_t;

typedef struct {
    u16 x;
    u16 y;   
}LCDPoint_t;















#endif

