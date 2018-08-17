# Under the hood: Bare Metal Embedded Programming in C

[![CircleCI](https://circleci.com/gh/meriac/baremetal-c.svg?style=svg)](https://circleci.com/gh/meriac/baremetal-c)

## Introduction & Scope

A single plain C file is sufficient to express the complete functionality of an embedded system. The [Arm Cortex-M architecture](http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0553a/index.html) is designed with C-Code in mind, no assembly level system bring up code is required.

This wokshop will teach you how to program C code on top of a bare metal CPU without an operating system or support libraries like libc. It will give you insight on how linkers can be configured to run your program at the right location and placing data.

I will epxplain using the free arm-gcc toolchain and related tools - starting from the toolchain to analyze the program on assembly level. I will show how C-language maps to machine code depending on the chosen compiler optimization level and linker settings.

This workshop will further introduce you to low level features like stacks and interrupts, how they are used and how they map onto Arm assembly code. One of the purposes of this course is to lay out the programming methods for talking to hardware in a minimal configuration. My broader objective is teaching a better understanding of interaction with low level hardware and toolchains for embedded systems.

Last, but not least I will show debug techniques for low level OS-development and  security features of the used microcontroller platform.

In case you’re interested in reading material on the topic, I recommend reading [The Definitive Guide to ARM® Cortex®-M3 and Cortex®-M4 Processors](https://www.amazon.com/dp/0124080820), but it will be by no means required for participating in this course.

Basic knowledge of the C-programming language is required.

## Hardware Development Kit

Form my lession I am using the 
[nRF52 Development Kit](https://infocenter.nordicsemi.com/index.jsp?topic=%2Fcom.nordic.infocenter.nrf52%2Fdita%2Fnrf52%2Fdevelopment%2Fnrf52_dev_kit.html) for the 
[nRF52832 CPU](https://infocenter.nordicsemi.com/pdf/nRF52832_PB_v2.0.pdf) from Nordic Semiconductors which is [available everywhere](https://www.nordicsemi.com/eng/Buy-Online?search_token=nRF52-DK). The [nRF52832 datasheet](http://infocenter.nordicsemi.com/pdf/nRF52832_PS_v1.4.pdf) is publicly available and well written.

### Development Kit Features
- [nRF52832](https://infocenter.nordicsemi.com/pdf/nRF52832_PS_v1.4.pdf) system-on-a-chip solution
	- 32-bit ARM Cortex-M4F Processor
	- Integrated a 2.4GHz Bluetooth Low Energy (BLE) interface
	- Very power efficient, can run many years from coincell battery
	- Hardware floating point support
	- 512kB flash + 64kB RAM
	- AES hardware encryption builtin
	- Many integrated hardware peripherals: 3x SPI, 2x I²C, UART, 3x PWM, ADC, RTC, PDM
- Buttons and LEDs for user interaction
- Integrated [SEGGER J-Link debugger](https://www.segger.com/downloads/jlink/#J-LinkSoftwareAndDocumentationPack) with debug out functionality
	- Virtual COM port interface via UART
	- Drag-and-drop mass storage device (MSD) programming
- Supporting 13.56 MHz NFC-A RFID tag emuation mode
- I/O interface for Arduino form factor plug-in modules (2.54mm headers)

### Overview

Below you can see the development kit - the largest part of the devleopment kit is occupied by the debug interface. The actual system running the lession examples is just the one black chip within the red square.
The antenna for the Bluetooth Low Energy functionality is located underneath the printed URL below the NORDIC-logo at right side of the board. 

![nRF51 Development Kit](Documentation/Images/nRF52_DK.jpg)


