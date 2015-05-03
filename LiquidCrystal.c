#include "LiquidCrystal.h"

void LCMcommand(uint8_t value) {
  LCMsend(value, 0);
}

void LCMsend(uint8_t value, uint8_t mode) {
  _rs_pin(mode);
  _rw_pin(0);
  LCMwrite8bits(value);
}

void LCMwrite8bits(uint8_t value) {
  int i = 0;
  for (i = 0; i < 8; i++) {
  	_data_pin(i,(value >> i) & 0x01);
  }
  
  LCMpulseEnable();
}

void LCMsetCursor(uint8_t col, uint8_t row) {
  int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
  if ( row >= _numlines ) {
    row = _numlines - 1;    // we count rows starting w/0
  }
  LCMcommand(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

void LCMcreateChar(uint8_t location, uint8_t charmap[]) {
  location &= 0x7; // we only have 8 locations 0-7
  LCMcommand(LCD_SETCGRAMADDR | (location << 3));
  int i = 0;
  for (i = 0; i < 8; i++) {
    LCMwrite_three(charmap[i]);
  }
}

void LCMpulseEnable(void) {
  _enable_pin(0);
  _delay_us(1);
  _enable_pin(1);
  _delay_us(1);    // enable pulse must be >450ns
  _enable_pin(0);
  _delay_us(100);   // commands need > 37us to settle
}

void LCMdisplay() {
  _displaycontrol |= LCD_DISPLAYON;
  LCMcommand(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LCMnoDisplay() {
  _displaycontrol &= ~LCD_DISPLAYON;
  LCMcommand(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LCMclear()
{
  LCMcommand(LCD_CLEARDISPLAY);  // clear display, set cursor position to zero
  _delay_us(2000);  // this command takes a long time!
}

void LCMclearUpOrDown(int choice) {
  LCMsetCursor(0, choice);
  LCMprint("                                        ");
}

int LCMprint(const char str[])
{
  return LCMwrite(str);
}

int LCMucharPrint(uchar b, int base) {
  return LCMulongPrint((unsigned long) b, base);
}

int LCMulongPrint(unsigned long n, int base)
{
  if (base == 0) {
    return LCMwrite_three(n);
  }
  else  {
    return printNumber(n, base);
  }
}

int LCMlongPrint(long n, int base) {
  if (base == 0) {
    return LCMwrite_three(n);
  } else if (base == 10) {
    if (n < 0) {
      int t = LCMcharPrint('-');
      n = -n;
      return printNumber(n, 10) + t;
    }
    return printNumber(n, 10);
  } else {
    return printNumber(n, base);
  }
}

int LCMintPrint(int n, int base) {
  return LCMlongPrint((long) n, base);
}

int LCMdoublePrint(double number, int digits) {
  if (isnan(number))
  {
    LCMprint("isNaN");
    return 1;
  }
  if (isinf(number))
  {
    LCMprint("isinf");
    return 1;
  }
  if (number < 0.0)
  {
    LCMprint("-");
    number = -number;
  }
  double rounding = 0.5;
  int i = 0;
  for (i = 0; i < digits; i++)
  {
    rounding /= 10.0;
  }
  number += rounding;
  int H = (int)number;
  double remainder = (number - (double)H);
  LCMintPrint(H, 10);
  if (digits > 0)
  {
    LCMprint(".");
  }
  while (digits-- > 0)
  {
    remainder *= 10.0;
    int toInt = (int)remainder;
    remainder -= toInt;
    LCMintPrint(toInt, 10);
  }
  return 1;
}

int printNumber(unsigned long n, uint8_t base) {
  char buf[8 * sizeof(long) + 1];
  char *str = &buf[sizeof(buf) - 1];

  *str = '\0';

  if (base < 2) base = 10;

  do {
    unsigned long m = n;
    n /= base;
    char c = m - base * n;
    *--str = c < 10 ? c + '0' : c + 'A' - 10;
  } while(n);

  return LCMwrite(str);
}

int LCMcharPrint(char c) {
  return LCMwrite_three(c);
}

int LCMwrite(const char *str) {
      if (str == NULL) return 0;
      return LCMwrite_two((const uint8_t *)str, strlen(str));
}

int LCMwrite_two(const uint8_t *buffer, int size)
{
  int n = 0;
  while (size--) {
    n += LCMwrite_three(*buffer++);
  }
  return n;
}

int LCMwrite_three(uint8_t value) {
  LCMsend(value, HIGH);
  return 1;
}

void _data_pin(int pins, uint8_t value) {
	switch(pins) {	
		case 0:	
			((value) ? (PORTB |= BITHIGH(0)) : (PORTB &= BITLOW(0)));
			break;	
		case 1:	
			((value) ? (PORTB |= BITHIGH(1)) : (PORTB &= BITLOW(1)));	
			break;	
		case 2:	
			((value) ? (PORTB |= BITHIGH(2)) : (PORTB &= BITLOW(2)));
			break;	
		case 3:	
			((value) ? (PORTB |= BITHIGH(3)) : (PORTB &= BITLOW(3)));	
			break;	
		case 4:	
			((value) ? (PORTB |= BITHIGH(4)) : (PORTB &= BITLOW(4)));	
			break;	
		case 5:	
			((value) ? (PORTB |= BITHIGH(5)) : (PORTB &= BITLOW(5)));	
			break;	
		case 6:	
			((value) ? (PORTD |= BITHIGH(6)) : (PORTD &= BITLOW(6)));	
			break;	
		case 7:	
			((value) ? (PORTD |= BITHIGH(7)) : (PORTD &= BITLOW(7)));	
			break;	
	}
}

void LCMinit(void) {
	//init
	_displayfunction = LCD_BITMODE | LCD_LINEMODE | LCD_DOTSMODE;
	//begin
    
  _displayfunction |= LCD_2LINE;
  _delay_us(50000);

	_rs_pin(0);
	_rw_pin(0);
	_enable_pin(0);

	LCMcommand(LCD_FUNCTIONSET | _displayfunction);
	_delay_us(4500);
	LCMcommand(LCD_FUNCTIONSET | _displayfunction);
  _delay_us(150);
  LCMcommand(LCD_FUNCTIONSET | _displayfunction);
  LCMcommand(LCD_FUNCTIONSET | _displayfunction);
  _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
  LCMdisplay();
  LCMclear();
  _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
  LCMcommand(LCD_ENTRYMODESET | _displaymode);

  LCMbegin(16, 1);
  LCMbegin(16, 2);
}

void LCMbegin(uint8_t cols, uint8_t lines) {
  if (lines > 1) {
      _displayfunction |= LCD_2LINE;
  }
  _numlines = lines;

  _delay_us(50000);
  _rs_pin(0);
  _rw_pin(0);
  _enable_pin(0);

  LCMcommand(LCD_FUNCTIONSET | _displayfunction);
  _delay_us(4500);
  LCMcommand(LCD_FUNCTIONSET | _displayfunction);
  _delay_us(150);
  LCMcommand(LCD_FUNCTIONSET | _displayfunction);
  LCMcommand(LCD_FUNCTIONSET | _displayfunction);
  _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
  LCMdisplay();
  LCMclear();
  _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
  LCMcommand(LCD_ENTRYMODESET | _displaymode);
}

void LCMnoCursor() {
  _displaycontrol &= ~LCD_CURSORON;
  LCMcommand(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LCMcursor() {
  _displaycontrol |= LCD_CURSORON;
  LCMcommand(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LCMhome() {
  LCMcommand(LCD_RETURNHOME);  // set cursor position to zero
  _delay_ms(2000);  // this command takes a long time!
}

void LCMblink() {
  _displaycontrol |= LCD_BLINKON;
  LCMcommand(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LCMnoBlink() {
  _displaycontrol &= ~LCD_BLINKON;
  LCMcommand(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LCMscrollDisplayLeft() {
  LCMcommand(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void LCMscrollDisplayRight() {
  LCMcommand(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

void LCMleftToRight() {
  _displaymode |= LCD_ENTRYLEFT;
  LCMcommand(LCD_ENTRYMODESET | _displaymode);
}

void LCMrightToLeft() {
  _displaymode &= ~LCD_ENTRYLEFT;
  LCMcommand(LCD_ENTRYMODESET | _displaymode);
}

void LCMautoscroll() {
  _displaymode |= LCD_ENTRYSHIFTINCREMENT;
  LCMcommand(LCD_ENTRYMODESET | _displaymode);
}

void LCMnoAutoscroll() {
  _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
  LCMcommand(LCD_ENTRYMODESET | _displaymode);
}

void LCMcursorLeft() {
  LCMcommand(LCD_CURSORSHIFT | LCD_CURSORLIFT);
}

void LCMcursorRight() {
  LCMcommand(LCD_CURSORSHIFT | LCD_CURSORRIGHT);
}