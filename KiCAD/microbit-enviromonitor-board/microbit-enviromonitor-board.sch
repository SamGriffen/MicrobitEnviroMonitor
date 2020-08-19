EESchema Schematic File Version 4
EELAYER 30 0
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
L microcontroller:ESP32-DEVKIT E1
U 1 1 5F0D7604
P 2100 3650
F 0 "E1" H 2100 4665 50  0000 C CNN
F 1 "ESP32-DEVKIT" H 2100 4574 50  0000 C CNN
F 2 "microcontroller:ESP31-DEVKIT" H 2105 2775 50  0001 C CNN
F 3 "" H 2105 2775 50  0001 C CNN
	1    2100 3650
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J1
U 1 1 5F0D867F
P 1550 1650
F 0 "J1" H 1468 1325 50  0000 C CNN
F 1 "12V" H 1468 1416 50  0000 C CNN
F 2 "headers:screw_terminal" H 1550 1650 50  0001 C CNN
F 3 "~" H 1550 1650 50  0001 C CNN
	1    1550 1650
	-1   0    0    1   
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J4
U 1 1 5F0D955A
P 4850 1300
F 0 "J4" H 4930 1292 50  0000 L CNN
F 1 "PUMP" H 4930 1201 50  0000 L CNN
F 2 "headers:screw_terminal" H 4850 1300 50  0001 C CNN
F 3 "~" H 4850 1300 50  0001 C CNN
	1    4850 1300
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J3
U 1 1 5F0D9E40
P 3200 1550
F 0 "J3" H 3280 1542 50  0000 L CNN
F 1 "3V3" H 3280 1451 50  0000 L CNN
F 2 "headers:screw_terminal" H 3200 1550 50  0001 C CNN
F 3 "~" H 3200 1550 50  0001 C CNN
	1    3200 1550
	1    0    0    -1  
$EndComp
$Comp
L misc:REGULATOR U1
U 1 1 5F0DACB8
P 2400 1550
F 0 "U1" H 2400 1815 50  0000 C CNN
F 1 "REGULATOR" H 2400 1724 50  0000 C CNN
F 2 "misc:buck_converter" H 2400 1550 50  0001 C CNN
F 3 "" H 2400 1550 50  0001 C CNN
	1    2400 1550
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:TIP41C Q1
U 1 1 5F0DBB13
P 4400 1650
F 0 "Q1" H 4591 1696 50  0000 L CNN
F 1 "TIP41C" H 4591 1605 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Horizontal_TabDown" H 4650 1575 50  0001 L CIN
F 3 "https://www.centralsemi.com/get_document.php?cmp=1&mergetype=pd&mergepath=pd&pdf_id=tip41.PDF" H 4400 1650 50  0001 L CNN
	1    4400 1650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5F0DCBB7
P 4000 1650
F 0 "R1" V 3793 1650 50  0000 C CNN
F 1 "47R" V 3884 1650 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 3930 1650 50  0001 C CNN
F 3 "~" H 4000 1650 50  0001 C CNN
	1    4000 1650
	0    1    1    0   
$EndComp
Wire Wire Line
	1750 1550 2000 1550
$Comp
L power:GND #PWR0101
U 1 1 5F0DEC5C
P 1800 1900
F 0 "#PWR0101" H 1800 1650 50  0001 C CNN
F 1 "GND" H 1805 1727 50  0000 C CNN
F 2 "" H 1800 1900 50  0001 C CNN
F 3 "" H 1800 1900 50  0001 C CNN
	1    1800 1900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5F0DFA56
P 2850 1900
F 0 "#PWR0102" H 2850 1650 50  0001 C CNN
F 1 "GND" H 2855 1727 50  0000 C CNN
F 2 "" H 2850 1900 50  0001 C CNN
F 3 "" H 2850 1900 50  0001 C CNN
	1    2850 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 1700 2850 1700
Wire Wire Line
	2850 1700 2850 1900
Wire Wire Line
	1750 1650 1800 1650
Wire Wire Line
	1800 1650 1800 1900
Wire Notes Line
	1400 1000 1400 2200
Wire Notes Line
	3450 2200 3450 1000
Text Notes 2300 950  0    50   ~ 0
POWER REGULATION
$Comp
L power:+3V3 #PWR0103
U 1 1 5F0E311F
P 2850 1350
F 0 "#PWR0103" H 2850 1200 50  0001 C CNN
F 1 "+3V3" H 2865 1523 50  0000 C CNN
F 2 "" H 2850 1350 50  0001 C CNN
F 3 "" H 2850 1350 50  0001 C CNN
	1    2850 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 1550 2850 1550
Wire Wire Line
	2850 1550 2850 1350
Text Label 1750 1550 0    50   ~ 0
+12V
Wire Wire Line
	4150 1650 4200 1650
$Comp
L power:+12V #PWR0104
U 1 1 5F0E6763
P 4500 1250
F 0 "#PWR0104" H 4500 1100 50  0001 C CNN
F 1 "+12V" H 4515 1423 50  0000 C CNN
F 2 "" H 4500 1250 50  0001 C CNN
F 3 "" H 4500 1250 50  0001 C CNN
	1    4500 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 1250 4500 1300
Wire Wire Line
	4500 1300 4650 1300
Wire Wire Line
	4650 1400 4500 1400
Wire Wire Line
	4500 1400 4500 1450
$Comp
L power:GND #PWR0105
U 1 1 5F0E7F72
P 4500 1950
F 0 "#PWR0105" H 4500 1700 50  0001 C CNN
F 1 "GND" H 4505 1777 50  0000 C CNN
F 2 "" H 4500 1950 50  0001 C CNN
F 3 "" H 4500 1950 50  0001 C CNN
	1    4500 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 1850 4500 1950
Text Label 3650 1650 0    50   ~ 0
PUMP
Wire Wire Line
	3650 1650 3850 1650
Wire Notes Line
	3550 1000 3550 2200
Wire Notes Line
	3550 2200 5250 2200
Wire Notes Line
	5250 2200 5250 1000
Wire Notes Line
	5250 1000 3550 1000
Text Notes 4650 950  0    50   ~ 0
PUMP CONTROL
Wire Notes Line
	1400 2200 3450 2200
Wire Notes Line
	1400 1000 3450 1000
Wire Wire Line
	3000 1550 2850 1550
Connection ~ 2850 1550
Wire Wire Line
	3000 1650 3000 1700
Wire Wire Line
	3000 1700 2850 1700
Connection ~ 2850 1700
$Comp
L power:+3V3 #PWR0106
U 1 1 5F0EF304
P 2850 4150
F 0 "#PWR0106" H 2850 4000 50  0001 C CNN
F 1 "+3V3" H 2865 4323 50  0000 C CNN
F 2 "" H 2850 4150 50  0001 C CNN
F 3 "" H 2850 4150 50  0001 C CNN
	1    2850 4150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 5F0F0F6B
P 2700 4450
F 0 "#PWR0107" H 2700 4200 50  0001 C CNN
F 1 "GND" H 2705 4277 50  0000 C CNN
F 2 "" H 2700 4450 50  0001 C CNN
F 3 "" H 2700 4450 50  0001 C CNN
	1    2700 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 4200 2700 4200
Wire Wire Line
	2700 4200 2700 4450
Wire Wire Line
	2600 4300 2850 4300
Wire Wire Line
	2850 4300 2850 4150
Wire Wire Line
	2600 2900 2700 2900
Text Label 2700 2900 0    50   ~ 0
PUMP
Wire Notes Line
	1400 2500 1400 4750
Wire Notes Line
	1400 4750 3450 4750
Wire Notes Line
	3450 4750 3450 2500
Wire Notes Line
	3450 2500 1400 2500
Text Notes 3200 2450 0    50   ~ 0
ESP32
$Comp
L Connector:Conn_01x04_Female J2
U 1 1 5F10408E
P 3150 3200
F 0 "J2" H 3178 3176 50  0000 L CNN
F 1 "SERIAL" H 3178 3085 50  0000 L CNN
F 2 "headers:4x1" H 3150 3200 50  0001 C CNN
F 3 "~" H 3150 3200 50  0001 C CNN
	1    3150 3200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5F10692A
P 2800 3500
F 0 "#PWR02" H 2800 3250 50  0001 C CNN
F 1 "GND" H 2805 3327 50  0000 C CNN
F 2 "" H 2800 3500 50  0001 C CNN
F 3 "" H 2800 3500 50  0001 C CNN
	1    2800 3500
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR01
U 1 1 5F107157
P 2800 3050
F 0 "#PWR01" H 2800 2900 50  0001 C CNN
F 1 "+3V3" H 2950 3150 50  0000 C CNN
F 2 "" H 2800 3050 50  0001 C CNN
F 3 "" H 2800 3050 50  0001 C CNN
	1    2800 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 3050 2800 3300
Wire Wire Line
	2800 3300 2950 3300
Wire Wire Line
	2800 3500 2800 3400
Wire Wire Line
	2800 3400 2950 3400
Wire Wire Line
	2950 3100 2650 3100
Wire Wire Line
	2650 3100 2650 3700
Wire Wire Line
	2650 3700 2600 3700
Wire Wire Line
	2950 3200 2700 3200
Wire Wire Line
	2700 3200 2700 3800
Wire Wire Line
	2700 3800 2600 3800
$EndSCHEMATC
