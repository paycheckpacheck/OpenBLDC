## Members
Pacheck Nicholas, Electrical Engineering Student (2025)
pacheck@vt.edu

Eddie Prichard (Computer Engineering Alum)

## Mentor
Pacheck Nicholas
Eddie Prichard

## Current Status
IN PROGRESS

## Project Overview

This project provides Open Source Hardware and Firmware for a 3-Phase Brushless DC Motor Driver. It aims to be an educational platform for some basic Power Electrionics problems.

To understand how a BLDC motor works, we must understand how a DC motor works. Well, its pretty simple, we apply a voltage and the motor spins. What if we want to have speed control? 
Well, we must decrease the average coil voltage. We can use a variable power supply to do this, or we can do this with a swith mode driver which will apply a PWM to the motor coil, allowing us to modify the duty cycle to compute the average voltage on the coil. 

An N-Channel Inverter is used to take that low power PWM generated from the discrete-controller/microcontroller and use it to switch on and off the Powersupply directly.


Below is an image of the N-Channel Inverter Developed after expirmental trials using a breadboard:
![image](https://github.com/user-attachments/assets/25ce9b4f-0bd3-4961-82af-debf6f43ea7e)
In additon to the cooresponding schematic:
![image](https://github.com/user-attachments/assets/bb9370cb-dcc5-447f-b111-a4fa37e59ae6)

This N-channel inverter essentially connects the Switch Node (Output) to power, or to ground. To Connect the Switch Node to Power, you must activate the High-Side Fet and deactivate the Low-side Fet; vice versa to connect to ground. 

But whats stopping us from just hooking up an inverter and directly driving the Gates of the Fets using something like an OpAmp? Gate Capacitance! In reality, there are two conditions required for a MOSFET to turn on ( Surpassing the Gate-Source voltage (VGS)) which is ussually found in the datasheet, AND filling up the gate capacitor. In order for a MOSFET to have fast switching, we must put consideration into the gate capacitance. In the datasheet, there is ussually like an effective gate charge, which is the total amount of charge needed to fill up the gate capacitor, this charge also needs to be dumped into the gate quicly, since there is a high frequrncy switching and not doing it fast enough or not filling it up entirely will cause the MOSFET to not fully turn on. 

Hence introducing the need for a bootstrap capacitor and bootstrap diode. These two components work as a team; the bootstrap diode allows the bootstrap capacitor to charge through the VCC, while also inuring the charge doesnt leak back in the way it came in. Now, during the lowside cycle, the bootstrap capacitor is charged up such that when the

The board has footprints for the 3-pin THT MOSFET package or the D-PACK6 Mosfet footprint.

A BLDC motor driver is just 3 of these. 
![image](https://github.com/user-attachments/assets/c6c0ecef-3594-4565-935a-c865fe14f61e)


The goal specifications for this motor driver should be to drive a 40V 10A load per phase. 

## Educational Value Added
This BLDC driver is made out of primitive components.
## Tasks

<!-- Your Text Here. You may work with your mentor on this later when they are assigned -->

## Design Decisions

<!-- Your Text Here. You may work with your mentor on this later when they are assigned -->

## Design Misc

<!-- Your Text Here. You may work with your mentor on this later when they are assigned -->

## Steps for Documenting Your Design Process

<!-- Your Text Here. You may work with your mentor on this later when they are assigned -->

## BOM + Component Cost

<!-- Your Text Here. You may work with your mentor on this later when they are assigned -->

## Timeline

<!-- Your Text Here. You may work with your mentor on this later when they are assigned -->

## Useful Links

<!-- Your Text Here. You may work with your mentor on this later when they are assigned -->

## Log

<!-- Your Text Here. You may work with your mentor on this later when they are assigned -->
