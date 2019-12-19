EESchema Schematic File Version 4
LIBS:LightStar_RevA-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Microchip_ATtiny:ATtiny85-20SU U101
U 1 1 5DC21689
P 3100 2200
F 0 "U101" H 2571 2246 50  0000 R CNN
F 1 "ATtiny85-20SU" H 2571 2155 50  0000 R CNN
F 2 "Package_SO:SOIJ-8_5.3x5.3mm_P1.27mm" H 3100 2200 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet.pdf" H 3100 2200 50  0001 C CNN
	1    3100 2200
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT101
U 1 1 5DC21EFF
P 4900 2150
F 0 "BT101" H 5018 2246 50  0000 L CNN
F 1 "Battery_Cell" H 5018 2155 50  0000 L CNN
F 2 "Battery:BatteryHolder_Keystone_1060_1x2032" V 4900 2210 50  0001 C CNN
F 3 "~" V 4900 2210 50  0001 C CNN
	1    4900 2150
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J101
U 1 1 5DC224FB
P 3600 3600
F 0 "J101" H 3650 3917 50  0000 C CNN
F 1 "Conn_02x03_Odd_Even" H 3650 3826 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Vertical" H 3600 3600 50  0001 C CNN
F 3 "~" H 3600 3600 50  0001 C CNN
	1    3600 3600
	1    0    0    -1  
$EndComp
Text GLabel 3400 3500 0    50   Input ~ 0
MISO
Text GLabel 3400 3600 0    50   Input ~ 0
SCK
Text GLabel 3400 3700 0    50   Input ~ 0
RST
Text GLabel 3900 3500 2    50   Input ~ 0
VCC
Text GLabel 3900 3600 2    50   Input ~ 0
MOSI
Text GLabel 3900 3700 2    50   Input ~ 0
GND
Text GLabel 3700 2400 2    50   Input ~ 0
RST
Text GLabel 3100 2800 3    50   Input ~ 0
GND
Text GLabel 3100 1600 1    50   Input ~ 0
VCC
Text GLabel 4900 1950 1    50   Input ~ 0
VBAT
Text GLabel 4900 2250 3    50   Input ~ 0
GND
Text GLabel 3700 2100 2    50   Input ~ 0
SCK
Text GLabel 3700 1900 2    50   Input ~ 0
MOSI
Text GLabel 3700 2000 2    50   Input ~ 0
MISO
$Comp
L Device:C_Small C101
U 1 1 5DC236FD
P 4150 2900
F 0 "C101" H 4242 2946 50  0000 L CNN
F 1 "100nF" H 4242 2855 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4150 2900 50  0001 C CNN
F 3 "~" H 4150 2900 50  0001 C CNN
	1    4150 2900
	1    0    0    -1  
$EndComp
Text GLabel 4150 2800 1    50   Input ~ 0
VCC
Text GLabel 4150 3000 3    50   Input ~ 0
GND
$Comp
L Device:R R101
U 1 1 5DC24242
P 4650 2950
F 0 "R101" H 4720 2996 50  0000 L CNN
F 1 "47K" H 4720 2905 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4580 2950 50  0001 C CNN
F 3 "~" H 4650 2950 50  0001 C CNN
	1    4650 2950
	1    0    0    -1  
$EndComp
Text GLabel 4650 3100 3    50   Input ~ 0
RST
Text GLabel 4650 2800 1    50   Input ~ 0
VCC
Text GLabel 3700 2200 2    50   Input ~ 0
PB3
$Comp
L Switch:SW_SPDT SW101
U 1 1 5DC3EEA4
P 5200 3450
F 0 "SW101" H 5200 3735 50  0000 C CNN
F 1 "SW_SPDT" H 5200 3644 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPDT_PCM12" H 5200 3450 50  0001 C CNN
F 3 "~" H 5200 3450 50  0001 C CNN
	1    5200 3450
	1    0    0    -1  
$EndComp
Text GLabel 5400 3550 2    50   Input ~ 0
VBAT
Text GLabel 5000 3450 0    50   Input ~ 0
VCC
$Comp
L Jumper:Jumper_2_Open JP101
U 1 1 5DC40BA1
P 5150 4000
F 0 "JP101" H 5150 4235 50  0000 C CNN
F 1 "Jumper_2_Open" H 5150 4144 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 5150 4000 50  0001 C CNN
F 3 "~" H 5150 4000 50  0001 C CNN
	1    5150 4000
	1    0    0    -1  
$EndComp
Text GLabel 4950 4000 0    50   Input ~ 0
VCC
Text GLabel 5350 4000 2    50   Input ~ 0
VBAT
$Comp
L Device:LED D101
U 1 1 5DCA0B06
P 6500 2250
F 0 "D101" V 6539 2133 50  0000 R CNN
F 1 "LED" V 6448 2133 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm" H 6500 2250 50  0001 C CNN
F 3 "~" H 6500 2250 50  0001 C CNN
	1    6500 2250
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D102
U 1 1 5DCA1260
P 6500 2750
F 0 "D102" V 6539 2633 50  0000 R CNN
F 1 "LED" V 6448 2633 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm" H 6500 2750 50  0001 C CNN
F 3 "~" H 6500 2750 50  0001 C CNN
	1    6500 2750
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D103
U 1 1 5DCA1628
P 7000 2250
F 0 "D103" V 6947 2328 50  0000 L CNN
F 1 "LED" V 7038 2328 50  0000 L CNN
F 2 "LED_THT:LED_D5.0mm" H 7000 2250 50  0001 C CNN
F 3 "~" H 7000 2250 50  0001 C CNN
	1    7000 2250
	0    1    1    0   
$EndComp
$Comp
L Device:LED D104
U 1 1 5DCA1A18
P 7000 2750
F 0 "D104" V 6947 2828 50  0000 L CNN
F 1 "LED" V 7038 2828 50  0000 L CNN
F 2 "LED_THT:LED_D5.0mm" H 7000 2750 50  0001 C CNN
F 3 "~" H 7000 2750 50  0001 C CNN
	1    7000 2750
	0    1    1    0   
$EndComp
$Comp
L Device:LED D105
U 1 1 5DCA1E37
P 7500 2500
F 0 "D105" V 7539 2383 50  0000 R CNN
F 1 "LED" V 7448 2383 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm" H 7500 2500 50  0001 C CNN
F 3 "~" H 7500 2500 50  0001 C CNN
	1    7500 2500
	0    -1   -1   0   
$EndComp
Text GLabel 6000 2000 0    50   Input ~ 0
MOSI
Text GLabel 6000 2500 0    50   Input ~ 0
MISO
Text GLabel 4250 2100 2    50   Input ~ 0
IR
Text GLabel 4200 2100 0    50   Input ~ 0
SCK
Text GLabel 6000 3000 0    50   Input ~ 0
PB3
Wire Wire Line
	4200 2100 4250 2100
$Comp
L MyParts:VS18388 U102
U 1 1 5DCA5186
P 5400 1275
F 0 "U102" H 5387 1568 60  0000 C CNN
F 1 "VS18388" H 5387 1462 60  0000 C CNN
F 2 "MyFootprints:VS1838B" H 5400 1275 60  0001 C CNN
F 3 "http://www.elecrow.com/download/Infrared%20receiver%20vs1838b.pdf" H 5387 1356 60  0000 C CNN
	1    5400 1275
	1    0    0    -1  
$EndComp
Text GLabel 4100 1350 0    50   Input ~ 0
VCC
Text GLabel 5000 1450 0    50   Input ~ 0
GND
Text GLabel 5900 1400 2    50   Input ~ 0
IR
Wire Wire Line
	5900 1400 5775 1400
$Comp
L Device:LED D106
U 1 1 5DCA688D
P 8000 2500
F 0 "D106" V 7947 2578 50  0000 L CNN
F 1 "LED" V 8038 2578 50  0000 L CNN
F 2 "LED_THT:LED_D5.0mm" H 8000 2500 50  0001 C CNN
F 3 "~" H 8000 2500 50  0001 C CNN
	1    8000 2500
	0    1    1    0   
$EndComp
Wire Wire Line
	6000 2500 6500 2500
Wire Wire Line
	7000 2500 7000 2400
Wire Wire Line
	7000 2500 7000 2600
Connection ~ 7000 2500
Wire Wire Line
	6500 2400 6500 2500
Connection ~ 6500 2500
Wire Wire Line
	6500 2500 7000 2500
Wire Wire Line
	6500 2500 6500 2600
Wire Wire Line
	6000 2000 6500 2000
Wire Wire Line
	8000 2000 8000 2350
Wire Wire Line
	8000 2650 8000 3000
Wire Wire Line
	8000 3000 7500 3000
Wire Wire Line
	6500 2900 6500 3000
Connection ~ 6500 3000
Wire Wire Line
	6500 3000 6000 3000
Wire Wire Line
	7000 2900 7000 3000
Connection ~ 7000 3000
Wire Wire Line
	7000 3000 6500 3000
Wire Wire Line
	7000 2100 7000 2000
Connection ~ 7000 2000
Wire Wire Line
	7000 2000 7500 2000
Wire Wire Line
	6500 2100 6500 2000
Connection ~ 6500 2000
Wire Wire Line
	6500 2000 7000 2000
Wire Wire Line
	7500 2350 7500 2000
Connection ~ 7500 2000
Wire Wire Line
	7500 2000 8000 2000
Wire Wire Line
	7500 2650 7500 3000
Connection ~ 7500 3000
Wire Wire Line
	7500 3000 7000 3000
$Comp
L Device:C C102
U 1 1 5DCACBAD
P 3850 2900
F 0 "C102" H 3965 2946 50  0000 L CNN
F 1 "10uF" H 3965 2855 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3888 2750 50  0001 C CNN
F 3 "~" H 3850 2900 50  0001 C CNN
	1    3850 2900
	1    0    0    -1  
$EndComp
Text GLabel 3850 2750 1    50   Input ~ 0
VCC
Text GLabel 3850 3050 3    50   Input ~ 0
GND
$Comp
L Device:R R103
U 1 1 5DCAD102
P 6350 1450
F 0 "R103" H 6420 1496 50  0000 L CNN
F 1 "47K" H 6420 1405 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6280 1450 50  0001 C CNN
F 3 "~" H 6350 1450 50  0001 C CNN
	1    6350 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R102
U 1 1 5DCAD683
P 4250 1350
F 0 "R102" H 4320 1396 50  0000 L CNN
F 1 "100R" H 4320 1305 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4180 1350 50  0001 C CNN
F 3 "~" H 4250 1350 50  0001 C CNN
	1    4250 1350
	0    1    1    0   
$EndComp
Text GLabel 6350 1600 3    50   Input ~ 0
IR
Text GLabel 6350 1300 1    50   Input ~ 0
VCC
$Comp
L Device:C_Small C103
U 1 1 5DCAEA2E
P 4500 1650
F 0 "C103" H 4592 1696 50  0000 L CNN
F 1 "100nF" H 4592 1605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4500 1650 50  0001 C CNN
F 3 "~" H 4500 1650 50  0001 C CNN
	1    4500 1650
	1    0    0    -1  
$EndComp
Text GLabel 4500 1750 3    50   Input ~ 0
GND
Wire Wire Line
	4400 1350 4500 1350
Wire Wire Line
	4500 1550 4500 1350
Connection ~ 4500 1350
Wire Wire Line
	4500 1350 5000 1350
$EndSCHEMATC
