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
## Measurement on LED:
### Freq: 2.273 kHz -> 440 uS Period
### Analisis in Excel
### Resolution of 40 uS -> Measure with higher resolution
### Deriving switching code from it
### Codeing: Low (80 us) High (320 us) ->1 / Low (80 uS) High (160 uS) Low 160 (uS)  -> 0  
### (high start) 1011 0111 1011 1010 0101 1(high end)
### High/Low visible in High Part of Phase (Full/Half)
### Watch out as Low Part of High and next Low are connected
# Arduino setup to replay code
## Delay with delayMicroseconds()
### Accurancy of 3 uS, should be enought
### Measure real time with Oszi
### Manual delaying? -> Not portable!
### Measure time of direct toggeling
### Disable Interupts



# Test with self read-in
# Test with garage
# Test with garage failed
# Reread data from remote and analyse with sigrok
## low: 100, hihg 360, low 80, 180, 260, 360, 80, 360 , 100, 160, 280, 340 ....
## mearuement oszi: low 92, high 352, ,low 268/270, hihg half 174/176 -> use this values!!!