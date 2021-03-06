EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:mma7660
LIBS:led-cap-cache
EELAYER 24 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 1 1
Title "ECE 498 CAP LED"
Date "20 Feb 2015"
Rev "A"
Comp "UMaine"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ATTINY20-X IC1
U 1 1 54E7790E
P 3850 4050
F 0 "IC1" H 2900 4800 40  0000 C CNN
F 1 "ATTINY20-X" H 4650 3300 40  0000 C CNN
F 2 "tssop-14:TSSOP14" H 3850 4150 35  0000 C CIN
F 3 "" H 3850 4050 60  0000 C CNN
	1    3850 4050
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 54E77970
P 2550 3750
F 0 "C1" H 2550 3850 40  0000 L CNN
F 1 ".1u" H 2556 3665 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 2588 3600 30  0001 C CNN
F 3 "" H 2550 3750 60  0000 C CNN
	1    2550 3750
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 54E77984
P 8450 3900
F 0 "C2" H 8450 4000 40  0000 L CNN
F 1 "1u" H 8456 3815 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 8488 3750 30  0001 C CNN
F 3 "" H 8450 3900 60  0000 C CNN
	1    8450 3900
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 54E77999
P 5250 3050
F 0 "R1" V 5330 3050 40  0000 C CNN
F 1 "2k2" V 5257 3051 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 5180 3050 30  0001 C CNN
F 3 "" H 5250 3050 30  0000 C CNN
	1    5250 3050
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 54E779AD
P 5500 3050
F 0 "R2" V 5580 3050 40  0000 C CNN
F 1 "2k2" V 5507 3051 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 5430 3050 30  0001 C CNN
F 3 "" H 5500 3050 30  0000 C CNN
	1    5500 3050
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P1
U 1 1 54E779C1
P 3600 2900
F 0 "P1" V 3550 2900 40  0000 C CNN
F 1 "battery" V 3650 2900 40  0000 C CNN
F 2 "mods.pretty:AA Box" H 3600 2900 60  0001 C CNN
F 3 "" H 3600 2900 60  0000 C CNN
	1    3600 2900
	-1   0    0    -1  
$EndComp
$Comp
L CONN_3 K1
U 1 1 54E779F7
P 8050 3850
F 0 "K1" V 8000 3850 50  0000 C CNN
F 1 "CONN_3" V 8100 3850 40  0000 C CNN
F 2 "Connect:GS3" H 8050 3850 60  0001 C CNN
F 3 "" H 8050 3850 60  0000 C CNN
	1    8050 3850
	1    0    0    -1  
$EndComp
$Comp
L MMA7660 U1
U 1 1 54E77E58
P 6700 3350
F 0 "U1" H 6350 3000 60  0000 C CNN
F 1 "MMA7660" H 6500 3650 60  0000 C CNN
F 2 "mods:DFN-10" H 6750 3150 60  0001 C CNN
F 3 "" H 6750 3150 60  0000 C CNN
	1    6700 3350
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 54E77E6C
P 2650 4800
F 0 "#PWR01" H 2650 4800 30  0001 C CNN
F 1 "GND" H 2650 4730 30  0001 C CNN
F 2 "" H 2650 4800 60  0000 C CNN
F 3 "" H 2650 4800 60  0000 C CNN
	1    2650 4800
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR02
U 1 1 54E77E87
P 2550 3300
F 0 "#PWR02" H 2550 3400 30  0001 C CNN
F 1 "VCC" H 2550 3400 30  0000 C CNN
F 2 "" H 2550 3300 60  0000 C CNN
F 3 "" H 2550 3300 60  0000 C CNN
	1    2550 3300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 54E77E9E
P 2550 3950
F 0 "#PWR03" H 2550 3950 30  0001 C CNN
F 1 "GND" H 2550 3880 30  0001 C CNN
F 2 "" H 2550 3950 60  0000 C CNN
F 3 "" H 2550 3950 60  0000 C CNN
	1    2550 3950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 54E77EB1
P 4000 3100
F 0 "#PWR04" H 4000 3100 30  0001 C CNN
F 1 "GND" H 4000 3030 30  0001 C CNN
F 2 "" H 4000 3100 60  0000 C CNN
F 3 "" H 4000 3100 60  0000 C CNN
	1    4000 3100
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR05
U 1 1 54E77EBE
P 4000 2750
F 0 "#PWR05" H 4000 2850 30  0001 C CNN
F 1 "VCC" H 4000 2850 30  0000 C CNN
F 2 "" H 4000 2750 60  0000 C CNN
F 3 "" H 4000 2750 60  0000 C CNN
	1    4000 2750
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR06
U 1 1 54E77FB7
P 5700 4150
F 0 "#PWR06" H 5700 4250 30  0001 C CNN
F 1 "VCC" H 5700 4250 30  0000 C CNN
F 2 "" H 5700 4150 60  0000 C CNN
F 3 "" H 5700 4150 60  0000 C CNN
	1    5700 4150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 54E77FCD
P 5750 4950
F 0 "#PWR07" H 5750 4950 30  0001 C CNN
F 1 "GND" H 5750 4880 30  0001 C CNN
F 2 "" H 5750 4950 60  0000 C CNN
F 3 "" H 5750 4950 60  0000 C CNN
	1    5750 4950
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR08
U 1 1 54E78138
P 7700 3500
F 0 "#PWR08" H 7700 3600 30  0001 C CNN
F 1 "VCC" H 7700 3600 30  0000 C CNN
F 2 "" H 7700 3500 60  0000 C CNN
F 3 "" H 7700 3500 60  0000 C CNN
	1    7700 3500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 54E78143
P 7700 4600
F 0 "#PWR09" H 7700 4600 30  0001 C CNN
F 1 "GND" H 7700 4530 30  0001 C CNN
F 2 "" H 7700 4600 60  0000 C CNN
F 3 "" H 7700 4600 60  0000 C CNN
	1    7700 4600
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR010
U 1 1 54E78219
P 5250 2800
F 0 "#PWR010" H 5250 2900 30  0001 C CNN
F 1 "VCC" H 5250 2900 30  0000 C CNN
F 2 "" H 5250 2800 60  0000 C CNN
F 3 "" H 5250 2800 60  0000 C CNN
	1    5250 2800
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR011
U 1 1 54E78224
P 5500 2800
F 0 "#PWR011" H 5500 2900 30  0001 C CNN
F 1 "VCC" H 5500 2900 30  0000 C CNN
F 2 "" H 5500 2800 60  0000 C CNN
F 3 "" H 5500 2800 60  0000 C CNN
	1    5500 2800
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR012
U 1 1 54E7825F
P 5800 2800
F 0 "#PWR012" H 5800 2900 30  0001 C CNN
F 1 "VCC" H 5800 2900 30  0000 C CNN
F 2 "" H 5800 2800 60  0000 C CNN
F 3 "" H 5800 2800 60  0000 C CNN
	1    5800 2800
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR013
U 1 1 54E7826A
P 7600 2800
F 0 "#PWR013" H 7600 2900 30  0001 C CNN
F 1 "VCC" H 7600 2900 30  0000 C CNN
F 2 "" H 7600 2800 60  0000 C CNN
F 3 "" H 7600 2800 60  0000 C CNN
	1    7600 2800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 54E7830A
P 7550 3650
F 0 "#PWR014" H 7550 3650 30  0001 C CNN
F 1 "GND" H 7550 3580 30  0001 C CNN
F 2 "" H 7550 3650 60  0000 C CNN
F 3 "" H 7550 3650 60  0000 C CNN
	1    7550 3650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 54E78315
P 5850 3650
F 0 "#PWR015" H 5850 3650 30  0001 C CNN
F 1 "GND" H 5850 3580 30  0001 C CNN
F 2 "" H 5850 3650 60  0000 C CNN
F 3 "" H 5850 3650 60  0000 C CNN
	1    5850 3650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR016
U 1 1 54E78405
P 8450 4100
F 0 "#PWR016" H 8450 4100 30  0001 C CNN
F 1 "GND" H 8450 4030 30  0001 C CNN
F 2 "" H 8450 4100 60  0000 C CNN
F 3 "" H 8450 4100 60  0000 C CNN
	1    8450 4100
	1    0    0    -1  
$EndComp
$Comp
L BSS138 Q1
U 1 1 54E78EA8
P 7600 4300
F 0 "Q1" H 7600 4151 40  0000 R CNN
F 1 "IRLML2402PbF" H 8250 4350 40  0000 R CNN
F 2 "SMD_Packages:SOT-323" H 7470 4402 29  0000 C CNN
F 3 "" H 7600 4300 60  0000 C CNN
	1    7600 4300
	1    0    0    -1  
$EndComp
Text Label 5600 3450 0    60   ~ 0
SDA
Text Label 5600 3550 0    60   ~ 0
SCL
Text Label 5100 3750 0    60   ~ 0
LED_DATA
Text Label 5100 3850 0    60   ~ 0
LED_CTRL
Text Label 6450 3750 0    60   ~ 0
Accel_INT
Text Label 7700 4100 0    60   ~ 0
LED_GND
Wire Wire Line
	2700 4650 2650 4650
Wire Wire Line
	2650 4650 2650 4800
Wire Wire Line
	2550 3450 2700 3450
Wire Wire Line
	2550 3300 2550 3550
Wire Wire Line
	3950 2800 4000 2800
Wire Wire Line
	4000 2800 4000 2750
Wire Wire Line
	3950 3000 4000 3000
Wire Wire Line
	4000 3000 4000 3100
Wire Wire Line
	5350 4350 6000 4350
Wire Wire Line
	5700 4450 6000 4450
Wire Wire Line
	5700 4450 5700 4150
Wire Wire Line
	5650 4550 6000 4550
Wire Wire Line
	5200 4750 6000 4750
Wire Wire Line
	5000 4650 5650 4650
Wire Wire Line
	5750 4850 6000 4850
Wire Wire Line
	5750 4850 5750 4950
Wire Wire Line
	5000 3450 5950 3450
Wire Wire Line
	5000 3550 5950 3550
Wire Wire Line
	7400 3550 7400 3750
Wire Wire Line
	7400 3750 5700 3750
Wire Wire Line
	5700 3750 5700 3650
Wire Wire Line
	5700 3650 5000 3650
Wire Wire Line
	5000 3750 5600 3750
Wire Wire Line
	5600 3750 5600 3850
Wire Wire Line
	5600 3850 7700 3850
Wire Wire Line
	7700 3950 7700 4100
Wire Wire Line
	5000 3850 5500 3850
Wire Wire Line
	5500 3850 5500 3950
Wire Wire Line
	5500 3950 7300 3950
Wire Wire Line
	7300 3950 7300 4350
Wire Wire Line
	7300 4350 7400 4350
Wire Wire Line
	7700 4600 7700 4500
Wire Wire Line
	7700 3500 7700 3750
Wire Wire Line
	5250 3300 5250 3450
Connection ~ 5250 3450
Wire Wire Line
	5500 3300 5500 3550
Connection ~ 5500 3550
Wire Wire Line
	7400 3350 7600 3350
Wire Wire Line
	5950 3250 5800 3250
Wire Wire Line
	5800 3250 5800 2800
Wire Wire Line
	5950 3350 5850 3350
Wire Wire Line
	5850 3350 5850 3650
Wire Wire Line
	7400 3450 7550 3450
Wire Wire Line
	7550 3150 7550 3650
Wire Wire Line
	7700 3600 8450 3600
Wire Wire Line
	8450 3600 8450 3700
Connection ~ 7700 3600
Wire Wire Line
	7600 3350 7600 2800
Connection ~ 2550 3450
Wire Wire Line
	7400 3150 7550 3150
Connection ~ 7550 3450
$Comp
L CONN_6 P2
U 1 1 54EFC480
P 6350 4600
F 0 "P2" V 6300 4600 60  0000 C CNN
F 1 "TPI pgrm" V 6400 4600 60  0000 C CNN
F 2 "" H 6350 4600 60  0000 C CNN
F 3 "" H 6350 4600 60  0000 C CNN
	1    6350 4600
	1    0    0    -1  
$EndComp
Text Label 5750 4850 0    60   ~ 0
GND
Text Label 5750 4750 0    60   ~ 0
CLK
Text Label 5750 4550 0    60   ~ 0
RST
Text Label 5750 4450 0    60   ~ 0
VCC
Text Label 5750 4350 0    60   ~ 0
DATA
Wire Wire Line
	5000 4350 5200 4350
Wire Wire Line
	5000 4450 5350 4450
Wire Wire Line
	5350 4450 5350 4350
Wire Wire Line
	5200 4350 5200 4750
Wire Wire Line
	5650 4650 5650 4550
$EndSCHEMATC
