## LiquidCrystal for Atmel AVR(Atmega) Microcontroller (AVR-LiquidCrystal) ##

[LiquidCrystal](https://github.com/arduino/Arduino/tree/master/libraries/LiquidCrystal) 原先是 Arduino 中用於控制 LCM 的內建 Library，去年需要將其移植為 Atmel AVR(Atmega) 可使用的 Library。

## Environment ##

支援使用 AVR-GCC(gcc version 4.9.2) 以上(包含)版本。

## How to use ? ##

AVR-LiquidCrystal 主要為 LiquidCrystal.h/LiquidCrystal.c 兩個檔案，針對電路設計不同需要針對 LiquidCrystal.h/LiquidCrystal.c 進行簡單的修改。

### LiquidCrystal.h ###

\_rs\_pin\_pd / \_rw\_pin\_pd / \_enable\_pin\_pd 分別代表 rs/rw/enable PIN 在 PORTX 的腳位 (X 可能等於 A/B/C/D，依使用者電路而定義)，針對腳位的不同，修改後面的數字。

```

#define _rs_pin_px 1
#define _rw_pin_px 3
#define _enable_pin_px 5

```

而 \_rs\_pin / \_rw\_pin / \_enable\_pin 是為了實現對 rs/rw/enable PIN 做電位輸出而定義的，預設是假定 LCM rs/rw/enable PIN 接在 PORTD，如果是接在其它排，請將下面的 PORTD 替換成符合你電路設計的名稱。

```

#define _rs_pin(N) ((N) ? (PORTD |= BITHIGH(_rs_pin_px)) : (PORTD &= BITLOW(_rs_pin_px)))
#define _rw_pin(N) ((N) ? (PORTD |= BITHIGH(_rw_pin_px)) : (PORTD &= BITLOW(_rw_pin_px)))
#define _enable_pin(N) ((N) ? (PORTD |= BITHIGH(_enable_pin_px)) : (PORTD &= BITLOW(_enable_pin_px)))

```

### LiquidCrystal.c ###

_data_pin 是一個 function 用於對 data 腳位做輸出，AVR-LiquidCrystal 預設是將 data 腳接在 PORTB 0~7(分別對應 data 0~7)，若有更動，請對 \_data\_pin funciton 中的 PORTB 進行相應的修改。

```

((value) ? (PORTB |= BITHIGH(0)) : (PORTB &= BITLOW(0)));

```

其餘使用請參考 examples 底下的範例。

另外也可以參考 Arduino 的兩個 LiquidCrystal page，以及 Arduino LiquidCrystal source code：

[Arduino - LiquidCrystal(Reference)](http://www.arduino.cc/en/Reference/LiquidCrystal)
[Arduino - LiquidCrystal(Tutorial)](http://www.arduino.cc/en/Tutorial/LiquidCrystal)

## Tools(Windows only) ##

之前為了使用 LCM 的方面，用 C# 撰寫了兩個輔助的小工具，分別是 CalcCreateChar(計算自訂字型) / GetStringLength(計算字串長度)。

程式運行最低要求：.NET Framework 2.0

### Download ###

+ [CalcCreateChar](http://bit.ly/1GFB7f4)
+ [GetStringLength](http://bit.ly/1GQGFc1)

## License ##

(Arduino LiquidCrystal 使用的是 LGPL 授權，LGPL 授權規範衍生品一樣需要為 LPGL 授權，AVR-LiquidCrystal 作為其衍生品，故以 LPGL 授權發行)

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.