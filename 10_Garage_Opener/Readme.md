Garage opener:
Goal: Replacement for garage opener remote at home

Steps:
# Arduino IR Lib Haredware setup
## Tsop 31238 IR receiver
### GND, VS, OUT
### 38 kHZ 
## VS 1838b IR receiver
### 38 kHZ
# IRLib2: https://github.com/cyborg5/IRLib2
## Pin 2 has to be used!
# (/) Test hardware by reading in new remote

# Read in garage remote
## different results for each receiver

# Testing 2nd remote
## Installing Oszi :]
## Opening Remote
### Lm7805
### B9048 - MM5741ON ? [no information found] as main IC 
### Button enables voltage on regulator
### Velleman P6704 kit , [no information found]
### 4 IR Leds in Series
## Measurment on LED:
### Freq: 2.273 kHz
# Arduino setup to replay code
# Test with self read-in
# Test with garage