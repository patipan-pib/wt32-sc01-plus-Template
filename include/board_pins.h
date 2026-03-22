#pragma once

// Touch FT6336 / FT5x06
#define TP_SDA      6
#define TP_SCL      5
#define TP_INT      7
#define TP_RST      4
#define FT6336_ADDR 0x38

// LCD ST7796 Parallel 8-bit
#define LCD_WR   47
#define LCD_RD   -1
#define LCD_RS   0

#define LCD_D0   9
#define LCD_D1   46
#define LCD_D2   3
#define LCD_D3   8
#define LCD_D4   18
#define LCD_D5   17
#define LCD_D6   16
#define LCD_D7   15

#define LCD_CS   -1
#define LCD_RST  4
#define LCD_BUSY -1

#define LCD_BL   45
#define LCD_BL_CHANNEL 7

// ใช้งานจริงเป็นแนวนอน
#define LCD_WIDTH   480
#define LCD_HEIGHT  320