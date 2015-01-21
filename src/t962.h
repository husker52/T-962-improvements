#ifndef T962_H_
#define T962_H_

/* Hardware notes and pin mapping:
 *
 * LCD is KS0108 compatible, with two chip selects, active high
 * EEPROM is an AT24C02C with 2kbits capacity (256x8)
 * XTAL frequency is 11.0592MHz
 *
 * GPIO0 port
 * 0.0 ISP/Console UART TX output
 * 0.1 ISP/Console UART RX input
 * 0.2 EEPROM SCL line (SCL0) w/ 4k7 pullup
 * 0.3 EEPROM SDA line (SDA0) w/ 4k7 pullup
 * 0.4 F4 button (active low, with pullup)
 * 0.5 ?
 * 0.6 ?
 * 0.7 Used for 1-wire cold-junction DS18B20 temperature sensor retrofit
 * 0.8 Fan output (active low) PWM4
 * 0.9 Heater output (active low) PWM6
 * 0.10 ?
 * 0.11 LCD backlight control output (active high)
 * 0.12 LCD CS2 output (right side of display)
 * 0.13 LCD CS1 output (left side of display)
 * 0.14 Enter ISP mode if low during reset (4k7 pullup)
 * 0.15 F2 button (active low, with pullup)
 * 0.16 F3 button (active low, with pullup)
 * 0.17 ?
 * 0.18 LCD E(nable) output (data latched on falling edge)
 * 0.19 LCD RW output (0=write, 1=read)
 * 0.20 S button (active low, with pullup)
 * 0.21 Buzzer output (active high) PWM5
 * 0.22 LCD RS output (0=cmd, 1=data)
 * 0.23 F1 button (active low, with pullup) VBUS input as alt function on LPC214x
 * 0.24 (No pin)
 * 0.25 AD0.4 accessible on test point marked ADO - DAC output as alt function (now used for sysfan control)
 * 0.26 ? USB D+ on LPC214x-series of chips
 * 0.27 ? USB D- on LPC214x-series of chips
 * 0.28 Temperature sensor input 1 (AD0.1), this was the left-hand one in our oven
 * 0.29 Temperature sensor input 2 (AD0.2), this was the right-hand one in our oven
 * 0.30 ?
 * 0.31 Red LED on board (active low)
 *
 * GPIO1 port
 * 1.16-1.23 LCD D0-D7 I/O
 * 1.24 ?
 * 1.25 ?
 * 1.26 ?
 * 1.27 ?
 * 1.28 ?
 * 1.29 ?
 * 1.30 ?
 * 1.31 ?
 */

/* EEPROM contents:

First two bytes and last two bytes needs to be 0x56, 0x57, 0x58 and 0x59
respectively for original software to recognize the profile.
Profile then is stored as 48 setpoint temperatures in Celsius in big-endian 16-bit words,
spaced 10 seconds apart for a run-time of up to 470s (in original SW they're spaced
15 seconds apart due to the slowdown of the RTC clock though). Unused space from address
0x62 to 0x7d (28 bytes) in each profile.

Wave7
0x56 0x57 0x00 0x14 0x00 0x23 0x00 0x2c 0x00 0x39 0x00 0x42 0x00 0x49 0x00 0x52
0x00 0x5b 0x00 0x64 0x00 0x67 0x00 0x6a 0x00 0x73 0x00 0x78 0x00 0x7b 0x00 0x82
0x00 0x8d 0x00 0x96 0x00 0x8d 0x00 0x82 0x00 0x79 0x00 0x6a 0x00 0x63 0x00 0x50
0x00 0x49 0x00 0x3c 0x00 0x35 0x00 0x2c 0x00 0x21 0x00 0x14 0x00 0x14 0x00 0x14
0x00 0x14 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x41 0x00 0x00
0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x41 0x00 0x00 0x00 0x00 0x00 0x00
0x00 0x00 0x00 0x00 0x31 0x6a 0x00 0x00 0x3b 0x5d 0x00 0x00 0x00 0x11 0x00 0x00
0x07 0x6f 0x00 0x00 0x40 0x00 0x00 0x00 0x06 0x00 0x00 0x00 0x06 0x00 0x58 0x59

Wave8
0x56 0x57 0x00 0x14 0x00 0x23 0x00 0x32 0x00 0x41 0x00 0x50 0x00 0x5f 0x00 0x6e
0x00 0x7d 0x00 0x8c 0x00 0x9b 0x00 0x9b 0x00 0x9b 0x00 0xa5 0x00 0xa5 0x00 0xa5
0x00 0xa5 0x00 0xa5 0x00 0xa5 0x00 0xaa 0x00 0xb9 0x00 0xc8 0x00 0xd7 0x00 0xe6
0x00 0xf5 0x00 0xf8 0x00 0xf5 0x00 0xe6 0x00 0xd7 0x00 0xc8 0x00 0xb9 0x00 0xaa
0x00 0x9b 0x00 0x8c 0x00 0x7d 0x00 0x6e 0x00 0x5f 0x00 0x50 0x00 0x41 0x00 0x00
0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00
0x00 0x00 0x00 0x00 0x31 0x6a 0x00 0x00 0x3b 0x5d 0x00 0x00 0x00 0x11 0x00 0x00
0x07 0x6f 0x00 0x00 0x40 0x00 0x00 0x00 0x07 0x00 0x00 0x00 0x07 0x00 0x58 0x59

 */

#define PCLKFREQ (5 * 11059200)

#endif /* T962_H_ */
