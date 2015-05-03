// ----------------------------- Include Header Start -----------------------------

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>  /* for sei() */
#include <avr/pgmspace.h>   /* required by usbdrv.h */
#include <util/delay.h>     /* for _delay_ms() */
#include <string.h>
#include "usbdrv.h"

#include "LiquidCrystal.h"

// ----------------------------- Include Header  End -----------------------------

// ----------------------------- USB Interface Start -----------------------------

PROGMEM const char usbHidReportDescriptor[22] = {    /* USB report descriptor */
  0x06, 0x00, 0xff,              // USAGE_PAGE (Generic Desktop)
  0x09, 0x01,                    // USAGE (Vendor Usage 1)
  0xa1, 0x01,                    // COLLECTION (Application)
  0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
  0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
  0x75, 0x08,                    //   REPORT_SIZE (8)
  0x95, 0x80,                    //   REPORT_COUNT (128)
  0x09, 0x00,                    //   USAGE (Undefined)
  0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)
  0xc0                           // END_COLLECTION
};

// ----------------------------- USB Interface End -----------------------------

// ----------------------------- Custom Character End ----------------------------- 

// Tools Function

void resetDog(void) {
  wdt_reset();
  usbPoll();
}

void avrUsbInit(void) {
  wdt_enable(WDTO_2S);  // 啟用 wdt(看門狗)
  usbInit();  // USB 初始化
  usbDeviceDisconnect();
  uchar i = 0;
  while(--i) {
      wdt_reset();
      _delay_ms(1);
  }
  usbDeviceConnect();
  sei();  // Enable 中斷
}

void portInit(void) {
  DDRB = 0x3f;
  PORTB = 0x0;
  DDRC = 0x0F;
  PORTC = 0x0;
  DDRD = 0xeb;
  PORTD = 0x0;
}

// Tools Function

// ------------------------------------------------------------------------- */

usbMsgLen_t usbFunctionSetup(uchar data[8]);  // usbFunctionRead/Write Interface
uchar usbFunctionRead(uchar *data, uchar len);  // AVR->PC
uchar usbFunctionWrite(uchar *data, uchar len); // PC->AVR

// ----------------------------- Main Start -----------------------------

int main(void) {

	portInit(); // DDRB/PORT 初始化
	avrUsbInit(); // USB 初始化
	LCMinit();  // LCM 初始化

  LCMprint("Hello, world!");
  LCMsetCursor(0, 1);
  LCMprint("AVR-LC by Ming");
  
  // #task
  while(1) {
    resetDog(); // 重置看門狗/USB 輪詢事件
  }

  return 0;
}

// ----------------------------- Main End -----------------------------

usbMsgLen_t usbFunctionSetup(uchar data[8]) {

  return USB_NO_MSG;
}

// ----------------------------- AVR->PC Start -----------------------------

uchar usbFunctionRead(uchar *data, uchar len) {

  return len;
}

// ----------------------------- AVR->PC Start -----------------------------

// ----------------------------- PC->AVR Start -----------------------------

uchar usbFunctionWrite(uchar *data, uchar len) {
  
  return len;
}

// ----------------------------- PC->AVR End -----------------------------