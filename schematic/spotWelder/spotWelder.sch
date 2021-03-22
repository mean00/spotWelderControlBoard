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
L MCU_ST_STM32F1:STM32F103CBTx U?
U 1 1 6052EF82
P 2500 3600
F 0 "U?" H 2450 2011 50  0000 C CNN
F 1 "STM32F103CBTx" H 2450 1920 50  0000 C CNN
F 2 "Package_QFP:LQFP-48_7x7mm_P0.5mm" H 1900 2200 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00161566.pdf" H 2500 3600 50  0001 C CNN
	1    2500 3600
	1    0    0    -1  
$EndComp
$Comp
L Device:Rotary_Encoder_Switch SW?
U 1 1 60532662
P 5300 4950
F 0 "SW?" H 5300 5317 50  0000 C CNN
F 1 "Rotary_Encoder_Switch" H 5300 5226 50  0000 C CNN
F 2 "" H 5150 5110 50  0001 C CNN
F 3 "~" H 5300 5210 50  0001 C CNN
	1    5300 4950
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic_MountingPin:Conn_01x05_MountingPin J?
U 1 1 60533CA5
P 2150 6350
F 0 "J?" H 2072 6767 50  0000 C CNN
F 1 "InterBoard" H 2072 6676 50  0000 C CNN
F 2 "" H 2150 6350 50  0001 C CNN
F 3 "~" H 2150 6350 50  0001 C CNN
	1    2150 6350
	-1   0    0    -1  
$EndComp
$Comp
L Converter_DCDC:ATA00A18S-L U?
U 1 1 60534A8D
P 4750 6350
F 0 "U?" H 4750 6817 50  0000 C CNN
F 1 "DC/DC converter" H 4750 6726 50  0000 C CNN
F 2 "Converter_DCDC:Converter_DCDC_Artesyn_ATA_SMD" H 4750 6000 50  0001 C CIN
F 3 "https://www.artesyn.com/power/assets/ata_series_ds_01apr2015_79c25814fd.pdf" H 4750 5900 50  0001 C CNN
	1    4750 6350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6053615D
P 2400 6800
F 0 "#PWR?" H 2400 6550 50  0001 C CNN
F 1 "GND" H 2405 6627 50  0000 C CNN
F 2 "" H 2400 6800 50  0001 C CNN
F 3 "" H 2400 6800 50  0001 C CNN
	1    2400 6800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60536815
P 4150 6650
F 0 "#PWR?" H 4150 6400 50  0001 C CNN
F 1 "GND" H 4155 6477 50  0000 C CNN
F 2 "" H 4150 6650 50  0001 C CNN
F 3 "" H 4150 6650 50  0001 C CNN
	1    4150 6650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60538853
P 2000 5100
F 0 "#PWR?" H 2000 4850 50  0001 C CNN
F 1 "GND" H 2005 4927 50  0000 C CNN
F 2 "" H 2000 5100 50  0001 C CNN
F 3 "" H 2000 5100 50  0001 C CNN
	1    2000 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 5100 2300 5100
Connection ~ 2300 5100
Wire Wire Line
	2300 5100 2400 5100
Connection ~ 2400 5100
Wire Wire Line
	2400 5100 2500 5100
Connection ~ 2500 5100
Wire Wire Line
	2500 5100 2600 5100
Wire Wire Line
	2350 6550 2400 6550
Wire Wire Line
	2400 6550 2400 6800
Wire Wire Line
	4250 6550 4150 6550
Wire Wire Line
	4150 6550 4150 6650
$Comp
L power:+3.3V #PWR?
U 1 1 6053BD4F
P 2050 1850
F 0 "#PWR?" H 2050 1700 50  0001 C CNN
F 1 "+3.3V" H 2065 2023 50  0000 C CNN
F 2 "" H 2050 1850 50  0001 C CNN
F 3 "" H 2050 1850 50  0001 C CNN
	1    2050 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 6150 5250 6150
Wire Wire Line
	2700 2100 2600 2100
Wire Wire Line
	2050 2100 2050 1850
Connection ~ 2300 2100
Wire Wire Line
	2300 2100 2050 2100
Connection ~ 2400 2100
Wire Wire Line
	2400 2100 2300 2100
Connection ~ 2500 2100
Wire Wire Line
	2500 2100 2400 2100
Connection ~ 2600 2100
Wire Wire Line
	2600 2100 2500 2100
$Comp
L Device:R R?
U 1 1 6053FC16
P 2800 6450
F 0 "R?" V 2950 6450 50  0000 C CNN
F 1 "470" V 2950 6600 50  0000 C CNN
F 2 "" V 2730 6450 50  0001 C CNN
F 3 "~" H 2800 6450 50  0001 C CNN
	1    2800 6450
	0    1    1    0   
$EndComp
Wire Wire Line
	2350 6450 2650 6450
Wire Wire Line
	3100 4000 3500 4000
Wire Wire Line
	3500 4000 3500 6450
Wire Wire Line
	3500 6450 2950 6450
Wire Wire Line
	2350 6350 3350 6350
Wire Wire Line
	3350 6350 3350 3600
Wire Wire Line
	3350 3600 3100 3600
$Comp
L power:GND #PWR?
U 1 1 60555388
P 3650 3900
F 0 "#PWR?" H 3650 3650 50  0001 C CNN
F 1 "GND" H 3655 3727 50  0000 C CNN
F 2 "" H 3650 3900 50  0001 C CNN
F 3 "" H 3650 3900 50  0001 C CNN
	1    3650 3900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60556E22
P 4850 4950
F 0 "#PWR?" H 4850 4700 50  0001 C CNN
F 1 "GND" H 4855 4777 50  0000 C CNN
F 2 "" H 4850 4950 50  0001 C CNN
F 3 "" H 4850 4950 50  0001 C CNN
	1    4850 4950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6055764E
P 5800 5050
F 0 "#PWR?" H 5800 4800 50  0001 C CNN
F 1 "GND" H 5805 4877 50  0000 C CNN
F 2 "" H 5800 5050 50  0001 C CNN
F 3 "" H 5800 5050 50  0001 C CNN
	1    5800 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 5050 5600 5050
Wire Wire Line
	4850 4950 5000 4950
Wire Wire Line
	3100 4300 4750 4300
Wire Wire Line
	4750 4300 4750 4850
Wire Wire Line
	4750 4850 5000 4850
Wire Wire Line
	3100 4400 4300 4400
Wire Wire Line
	4300 4400 4300 5250
Wire Wire Line
	4300 5250 5000 5250
Wire Wire Line
	5000 5250 5000 5050
Wire Wire Line
	3100 4200 5850 4200
Wire Wire Line
	5850 4200 5850 4850
Wire Wire Line
	5850 4850 5600 4850
$Comp
L Device:D_Zener D?
U 1 1 605532B6
P 3650 3750
F 0 "D?" V 3604 3830 50  0000 L CNN
F 1 "3.3V" V 3695 3830 50  0000 L CNN
F 2 "" H 3650 3750 50  0001 C CNN
F 3 "~" H 3650 3750 50  0001 C CNN
	1    3650 3750
	0    1    1    0   
$EndComp
Connection ~ 3350 3600
Wire Wire Line
	3350 3600 3650 3600
Text Label 1900 6150 0    50   ~ 0
VBAT
Text Label 1800 6350 0    50   ~ 0
DETECT
Text Label 1750 6450 0    50   ~ 0
TRIGGER
Text Label 1750 6550 0    50   ~ 0
GROUND
$Comp
L pspice:DIODE D?
U 1 1 6059A68B
P 2650 6150
F 0 "D?" H 2650 6415 50  0000 C CNN
F 1 "DIODE schottky" H 2650 6324 50  0000 C CNN
F 2 "" H 2650 6150 50  0001 C CNN
F 3 "~" H 2650 6150 50  0001 C CNN
	1    2650 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 6150 2450 6150
Wire Wire Line
	2850 6150 4000 6150
$Comp
L Device:R R?
U 1 1 6059FD90
P 4150 3000
F 0 "R?" V 4300 3000 50  0000 C CNN
F 1 "4.7k" H 4000 3000 50  0000 C CNN
F 2 "" V 4080 3000 50  0001 C CNN
F 3 "~" H 4150 3000 50  0001 C CNN
	1    4150 3000
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 605A0FFE
P 4150 3400
F 0 "R?" V 4300 3400 50  0000 C CNN
F 1 "1k" H 4000 3400 50  0000 C CNN
F 2 "" V 4080 3400 50  0001 C CNN
F 3 "~" H 4150 3400 50  0001 C CNN
	1    4150 3400
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 605A1617
P 4150 3650
F 0 "#PWR?" H 4150 3400 50  0001 C CNN
F 1 "GND" H 4155 3477 50  0000 C CNN
F 2 "" H 4150 3650 50  0001 C CNN
F 3 "" H 4150 3650 50  0001 C CNN
	1    4150 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 3550 4150 3650
Wire Wire Line
	4150 3150 4150 3200
Wire Wire Line
	3100 3500 3800 3500
Wire Wire Line
	3800 3500 3800 3200
Wire Wire Line
	3800 3200 4150 3200
Connection ~ 4150 3200
Wire Wire Line
	4150 3200 4150 3250
Wire Wire Line
	4000 6150 4000 5550
Wire Wire Line
	4000 5550 6750 5550
Wire Wire Line
	6750 5550 6750 2750
Wire Wire Line
	6750 2750 4150 2750
Wire Wire Line
	4150 2750 4150 2850
Connection ~ 4000 6150
Wire Wire Line
	4000 6150 4250 6150
$Comp
L Device:Buzzer BZ?
U 1 1 60584C9C
P 900 5150
F 0 "BZ?" H 1052 5179 50  0000 L CNN
F 1 "Buzzer" H 1052 5088 50  0000 L CNN
F 2 "" V 875 5250 50  0001 C CNN
F 3 "~" V 875 5250 50  0001 C CNN
	1    900  5150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60585A6D
P 800 5850
F 0 "#PWR?" H 800 5600 50  0001 C CNN
F 1 "GND" H 805 5677 50  0000 C CNN
F 2 "" H 800 5850 50  0001 C CNN
F 3 "" H 800 5850 50  0001 C CNN
	1    800  5850
	1    0    0    -1  
$EndComp
$Comp
L Display_Graphic:EA_DOGXL160-7 U?
U 1 1 6058DB7E
P 4000 1500
F 0 "U?" H 4644 1496 50  0000 L CNN
F 1 "SSD1306-I2C-OLED-128x64" H 4644 1405 50  0000 L CNN
F 2 "Display:EA_DOGXL160-7" H 4000 500 50  0001 C CNN
F 3 "http://www.lcd-module.com/eng/pdf/grafik/dogxl160-7e.pdf" H 1650 2650 50  0001 C CNN
	1    4000 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 3900 1800 3900
$Comp
L power:GND #PWR?
U 1 1 60593E03
P 3700 2400
F 0 "#PWR?" H 3700 2150 50  0001 C CNN
F 1 "GND" H 3705 2227 50  0000 C CNN
F 2 "" H 3700 2400 50  0001 C CNN
F 3 "" H 3700 2400 50  0001 C CNN
	1    3700 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 2300 3700 2400
$Comp
L power:+3.3V #PWR?
U 1 1 605967BF
P 3200 700
F 0 "#PWR?" H 3200 550 50  0001 C CNN
F 1 "+3.3V" H 3215 873 50  0000 C CNN
F 2 "" H 3200 700 50  0001 C CNN
F 3 "" H 3200 700 50  0001 C CNN
	1    3200 700 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 4200 1150 4200
$Comp
L Device:R R?
U 1 1 605B195B
P 800 4750
F 0 "R?" H 870 4796 50  0000 L CNN
F 1 "100" H 870 4705 50  0000 L CNN
F 2 "" V 730 4750 50  0001 C CNN
F 3 "~" H 800 4750 50  0001 C CNN
	1    800  4750
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 605BD90E
P 5350 5950
F 0 "#PWR?" H 5350 5800 50  0001 C CNN
F 1 "+5V" H 5365 6123 50  0000 C CNN
F 2 "" H 5350 5950 50  0001 C CNN
F 3 "" H 5350 5950 50  0001 C CNN
	1    5350 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 5950 5350 6150
Wire Wire Line
	3700 2300 3900 2300
Connection ~ 3900 2300
Wire Wire Line
	3900 2300 4000 2300
Wire Wire Line
	4000 800  4000 700 
Wire Wire Line
	4000 700  3200 700 
Wire Wire Line
	1500 3900 1500 1200
Wire Wire Line
	1500 1200 3400 1200
Wire Wire Line
	3400 1600 1350 1600
Wire Wire Line
	1350 1600 1350 4000
Wire Wire Line
	1350 4000 1800 4000
Wire Wire Line
	3400 1500 1250 1500
Wire Wire Line
	1250 1500 1250 4100
Wire Wire Line
	1250 4100 1800 4100
$Comp
L power:+5V #PWR?
U 1 1 605E35CF
P 800 4500
F 0 "#PWR?" H 800 4350 50  0001 C CNN
F 1 "+5V" H 815 4673 50  0000 C CNN
F 2 "" H 800 4500 50  0001 C CNN
F 3 "" H 800 4500 50  0001 C CNN
	1    800  4500
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:BSS214NW Q?
U 1 1 605F3E69
P 900 5550
F 0 "Q?" H 1105 5596 50  0000 L CNN
F 1 "Generic Logic N" H 250 5650 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-323_SC-70" H 1100 5475 50  0001 L CIN
F 3 "https://www.infineon.com/dgdl/Infineon-BSS214NW-DS-v02_02-en.pdf?fileId=db3a30431b3e89eb011b695aebc01bde" H 900 5550 50  0001 L CNN
	1    900  5550
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 605F82FD
P 1150 5700
F 0 "R?" H 1220 5746 50  0000 L CNN
F 1 "10k" H 1220 5655 50  0000 L CNN
F 2 "" V 1080 5700 50  0001 C CNN
F 3 "~" H 1150 5700 50  0001 C CNN
	1    1150 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	800  4600 800  4500
Wire Wire Line
	800  5050 800  4900
Wire Wire Line
	850  5350 800  5350
Wire Wire Line
	800  5350 800  5250
Connection ~ 800  5350
Wire Wire Line
	1100 5550 1150 5550
Wire Wire Line
	1150 5850 800  5850
Connection ~ 800  5850
Wire Wire Line
	1150 4200 1150 5550
Wire Wire Line
	800  5750 800  5850
Connection ~ 1150 5550
$EndSCHEMATC
