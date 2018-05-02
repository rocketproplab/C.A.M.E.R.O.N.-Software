# C.A.M.E.R.O.N. Software

This repository holds the software that will run on RPL's [C.A.M.E.R.O.N.](https://github.com/rocketproplab/C.A.M.E.R.O.N.), who controls everything on Launchy McLaunchface.

This software project is designed to be opened using [System Workbench](http://www.st.com/en/development-tools/sw4stm32.html).

## Features and Peripherals

C.A.M.E.R.O.N. is responsible for cotrolling the following peripherals:
* 4 K-Type thermocouples (SPI Interface)
* 5 Pressure Transducers (connected to an external 24-bit ADC w/ SPI Interface)
* 5 Solenoids (GPIO signals)
* Recovery board driver (separate PCB, connected via 8 GPIOs)

C.A.M.E.R.O.N. also connects to a Beaglebone Black via both SPI and I2C busses. The Beaglebone acts as the main Flight Computer and issues commands to C.A.M.E.R.O.N.

## Programming and Debugging

C.A.M.E.R.O.N. features a 2-wire SWD interface for programming/debugging, and also a UART breakout for serial communications to facilitate debugging further. The programming interface used is ST-Link V2.

Notice: There is no breakout for the NRST pin. If using System Workbench, the PROJECTNAME.cfg file must be edited (PROJECTNAME might be different from developer to developer). There is a line that starts with `reset_config`, find it and change it to read the following:
```reset_config none separate```
