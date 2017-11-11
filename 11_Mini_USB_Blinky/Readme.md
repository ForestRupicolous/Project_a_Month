Project a month:
11 Mini USB Blinky

Goal:
Minimal (cost/piece and effort) USB connected RGB-LED light to show information.

Idea from blink(1): https://blink1.thingm.com/
Also available as blinkstick: https://www.blinkstick.com/

Work-breakdown-structure:
Hardware:
* USB connected board
** Digispark: http://digistump.com/products/1
*** ATTiny85 - 5V - Direct USB connector
*** Cheap chinese knock-off: https://www.amazon.de/AZDelivery-Kickstarter-kompatibles-Entwiklung-Development/dp/B01N7SGC1I/ref=sr_1_2?ie=UTF8&qid=1510405170&sr=8-2&keywords=digispark&dpID=51RZMq0lm6L&preST=_SY300_QL70_&dpSrc=srch
* RGB LED
** WS2812 (or compatible)
*** Possiblity to increase led numbers later

Software:
* Firmware
** Reuse of blink(1) software possible?
*** https://github.com/todbot/blink1
*** Schematic shows PIC16F1466ML / Code PIC16F1455 :( -> port for attiny available?
** Reuse of blinkenstick firmware?
*** Also uses aTTiny85 :)
***
** Project with digispark:
*** https://www.hardill.me.uk/wordpress/2013/02/06/budget-blink1/
** Tutorial from digistump without USB connection:
*** http://digistump.com/wiki/digispark/tutorials/digiled

* PC control to interface
** Reuse of blink(1) sw if possible, use same interface

Chasing:
* 3D printed

Connection:
5V - GND - 
Questions: Does the 5V port have the USB power?

Getting started Digispark:
http://digistump.com/wiki/digispark/tutorials/connecting

First steps:
Install drivers
Install board in Arduino IDE
! Unplug Board !
Compile/Upload
Plug-In Board

Basic blinky works :)


