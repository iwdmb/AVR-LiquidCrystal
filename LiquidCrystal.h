#ifndef LIQUIDCRYSTAL_H
#define LIQUIDCRYSTAL_H

#include <util/delay.h>
#include <string.h>
#include "usbdrv.h"

#define HIGH 1
#define LOW 0

#define BITHIGH(N) (1 << N)
#define BITLOW(N) ~(1 << N)

#define _rs_pin_px 1	// rs pin 在 PORTX 的腳位
#define _rw_pin_px 3	// rw pin 在 PORTX 的腳位
#define _enable_pin_px 5	// enable pin 在 PORTX 的腳位

#define _rs_pin(N) ((N) ? (PORTD |= BITHIGH(_rs_pin_px)) : (PORTD &= BITLOW(_rs_pin_px)))	// 對 rs pin 輸出 HIGH(高) / LOW(低) 電位
#define _rw_pin(N) ((N) ? (PORTD |= BITHIGH(_rw_pin_px)) : (PORTD &= BITLOW(_rw_pin_px)))	// 對 rw pin 輸出 HIGH(高) / LOW(低) 電位
#define _enable_pin(N) ((N) ? (PORTD |= BITHIGH(_enable_pin_px)) : (PORTD &= BITLOW(_enable_pin_px)))	// 對 enable pin 輸出 HIGH(高) / LOW(低) 電位

#define LCD_FUNCTIONSET 0x20
#define LCD_BITMODE 0x10	// 8 bit mode
#define LCD_LINEMODE 0x00	// 1 LINE
#define LCD_DOTSMODE 0x00	//	5 x 7 Dot

// 工具函數，一般不會調用到
void LCMpulseEnable(void);
void LCMinit(void);	// LCM 初始化
void LCMbegin(uint8_t , uint8_t);	// for LCMinit
int printNumber(unsigned long, uint8_t);	// for LCMulongPrint
int LCMwrite(const char *);		// 輸出字串
int LCMwrite_two(const uint8_t *, int);	// 將要 print 的字串分割為單一字元
void LCMcommand(uint8_t);
void LCMsend(uint8_t, uint8_t);
void LCMwrite8bits(uint8_t);
void _data_pin(int, uint8_t);	// 對 LCM data pin

// print
int LCMprint(const char[]);	// char[]
int LCMcharPrint(char);	// char
int LCMucharPrint(uchar, int);	// uchar
int LCMintPrint(int, int);	// int
int LCMlongPrint(long, int);	// long
int LCMulongPrint(unsigned long, int);	// unsigned long
int LCMdoublePrint(double number, int digits);	// double
int LCMwrite_three(uint8_t);	// 自訂字型輸出

void LCMdisplay();		// 螢幕顯示
void LCMnoDisplay();	// 螢幕不顯示 #
void LCMclear();	// 清除 LCM 畫面
void LCMclearUpOrDown(int choice);	// 清除 LCM 上排或下排
void LCMsetCursor(uint8_t, uint8_t);	// 游標移至指定位置(x, y)
void LCMcreateChar(uint8_t, uint8_t[]);	// 建立自訂字形 (設定自訂字形編號, 自訂字形參數)
void LCMcursor();	// 輸入下劃線 -> a_
void LCMnoCursor();	// 關閉輸入下劃線 -> a
void LCMhome();	// 返回第一格(0, 0)	#
void LCMblink();	// 開啟長方形光標
void LCMnoBlink();	// 關閉長方形光標
void LCMscrollDisplayLeft();	// 螢幕左移
void LCMscrollDisplayRight();	// 螢幕右移
void LCMleftToRight();	//	文字由左至右輸出
void LCMrightToLeft();	//	文字由右至左輸出
void LCMautoscroll();
void LCMnoAutoscroll();
void LCMcursorLeft();	// 游標向左移一格
void LCMcursorRight();	// 游標向右移一格

uint8_t _displaycontrol;
uint8_t _numlines;
uint8_t _displaymode;
uint8_t _displayfunction;

#define LCD_DISPLAYCONTROL 0x08
#define LCD_DISPLAYON 0x04
#define LCD_CURSOROFF 0x00
#define LCD_BLINKOFF 0x00
#define LCD_BLINKON 0x01	// 游標開啟閃耀
#define LCD_ENTRYMODESET 0x04
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTDECREMENT 0x00
#define LCD_CLEARDISPLAY 0x01
#define LCD_2LINE 0x08
#define LCD_SETDDRAMADDR 0x80
#define LCD_SETCGRAMADDR 0x40
#define LCD_CURSORON 0x02
#define LCD_RETURNHOME 0x02
#define LCD_CURSORSHIFT 0x10
#define LCD_DISPLAYMOVE 0x08
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00
#define LCD_CURSORLIFT 0x00
#define LCD_CURSORRIGHT 0x04
#define LCD_ENTRYSHIFTINCREMENT 0x01

#endif