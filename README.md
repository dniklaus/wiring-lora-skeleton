# wiring-skeleton
Wiring / Arduino based Skeleton Embedded Application, powered by [PlatformIO](http://platformio.org "Cross-platform build system")

The project has initially been created for and tested on an Arduino Mega 2560 controller module.

## Purpose
This project builds up an Arduino Framework based application skeleton and it comprises of several components helping with debugging and integrating embedded applications on [Arduino](http://arduino.cc) based contoller modules.

This skeleton application can help you to build up your own Arduino Framework based applications. 

This project integrates the following **components**:

* ***Timer***: configurable recurring or non-recurring timer to schedule events without having to use Arduino delay() function; helps to improve your application's architecture by encapsulating the timers into your components and thus make them active
* ***Ramutils***: helps to determine the free Ram that is currently available
* ***DbgTrace***: debug trace log environment with configurable log levels
* ***DbgCLI***: interactive console environment with command tree that can be built up decentralized (from any different location in your application code and within any component)
* ***App-Dbg***: boilerplate code setting up all the debug environment such as CLI and Tracing and free RAM info printer
The **command line interface** provides the following **functionality**:  

* set the trace level of the free heap monitoring printer

This skeleton application demonstrates how to integrate libraries provided by the PlatformIO ecosystem and also how to use your own libraries and can help you to build up your own Arduino Framework based applications with focus on IoT. 

The following components are in focus:

* [Timer](https://github.com/dniklaus/wiring-timer)
* [Debug-Cli](https://github.com/ERNICommunity/debug-cli)
* [Dbg-Trace](https://github.com/ERNICommunity/dbg-trace)

## Toolchain
[PlatformIO](http://platformio.org "Cross-platform build system") is the ideal foundation when developing IoT devices. It supports cross-platform development for many different controller boards widely used in the maker field and also for industrial applications.

### Installation
#### Python 2.7

**Windows**

* download Python 2.7.x from: https://www.python.org/downloads/
* install for all users
* select destinationdirectory (keep default): C:\Python27\
* add python.exe to path

**Linux**

Install Python 2.7 using your package manager.

#### PlatformIO
Install PlatformIO using the Python Package Manager
(see also http://docs.platformio.org/en/latest/installation.html#python-package-manager):

* in a cmd shell enter: `pip install -U platformio`
* upgrade pip, in the cmd shell enter: `python -m pip install --upgrade pip`
* upgrade PlatformIO, in the cmd shell enter: `pio upgrade`
 

## How to build for Eclipse CDT
  1. Create a directory where your Eclipse Workspace will be stored and where this project shall be cloned into. E.g. `C:\git\pio-prj`
  2. Clone the repository - [wiring-lora-skeleton](https://github.com/ERNICommunity/wiring-lora-skeleton) - into the folder you created before, `git clone git@github.com:ERNICommunity/wiring-lora-skeleton.git`
  3. Open a command shell in the just cloned project folder , i.e in `C:\git\pio-prj\wiring-lora-skeleton`
  4. Run the command `pio init --ide eclipse`, this prepares the project to be edited using Eclipse CDT
  5. Run the command `pio run`, this starts the project build 

Note: Print a list of all available boards with the command: `pio boards`

## Open project in Eclipse CDT
  1. Open Eclipse CDT, choose the folder you created before as workspace, i.e `C:\git\pio-prj`
  2. Import the project with File->Import->General->Existing Projects into Workspace, choose the `wiring-lora-skeleton` (i.e `C:\git\pio-prj\wiring-lora-skeleton`)

## Connect Terminal Emulation
In order to test and run the CLI commands, a terminal emulation program shall be used. The one giving you the best experience will be the [HTerm](http://www.der-hammer.info/terminal/). 

Load the _hterm-com10.cfg_ file to configure HTerm properly. Alter the COM10 accordingly to the one that has been selected on your computer.

## Debug Features
### Debug CLI Commands
#### Command Tree
     dbg                      Debug CLI root node
       assets                 Assets
         dvcser               Device Serial Number
           get                Get Device Serial Number
           set                Set Device Serial Number
         lorakeys             LoRa Keys
           get                Get LoRa Keys
       lora                   LoRaWan Driver
         cfg                  Configure the LoRaWan Driver
         sch [get|set <0|1>]  Get / set the LoRaWan Driver's single channel mode config status
       tr                     Debug Trace Port config access
         heap                 Particular Trace Port (heap: see below)
           out                Trace Output cfg access for current port
             get              Show the assigned Trace Output
             set <outName>    Set a particular Trace Output name
             list             Show all available Trace Output names (and the currently selected)
           lvl                Trace Level config access for the current trace port
             get              Show the current trace level
             set <level>      Set a particular trace level
             list             Show all available trace levels (and the currenntly selected)

#### Example commands
* `dbg tr heap lvl set debug`


### Trace Port

|Trace Port|default level|functionality|
|----------|-------------|:------------|
|heap|info|if set to debug level: automatically print free heap memory [bytes], every 10 seconds|
|assets|info||
|lora|debug||

## Library Usage
This chapter lists all the libraries this project is using.

### PlatformIO Libraries

|ID|Name|URL|Description|
|:---|:------------|:----------------|:-----------------------|
| 173|SerialCommand|https://github.com/kroimon/Arduino-SerialCommand|A Wiring/Arduino library to tokenize and parse commands received over a serial port.|
|1699|wiring-timer |https://github.com/dniklaus/wiring-timer|Universal recurring or non-recurring Timer. <br />Configurable timer to schedule events without having to use Arduino delay() function; helps to improve your application's architecture by encapsulating the timers into your components and thus make them active.|
|1716|debug-cli|https://github.com/ERNICommunity/debug-cli|Debug CLI for Embedded Applications - Command Line  Interface for debugging and testing based on object oriented tree structure.|
|1717|dbg-trace|https://github.com/ERNICommunity/dbg-trace|Debug Trace component for Embedded Applications - Debug and Trace Log message system based on trace ports with adjustable levels.|
|31|Adafruit Unified Sensor|https://github.com/adafruit/Adafruit_Sensor|Adafruit Unified Sensor Driver|
|19|DHT sensor library|https://github.com/adafruit/DHT-sensor-library|Adafruit DHT Humidity & Temperature Sensor Library|
|431|Nanopb|https://github.com/nanopb/nanopb|Nanopb - Protocol Buffers for Embedded Systems (Google)|



### Homebrew Libraries

|Name|URL|Description|
|:------|:---------------------|:-------------------------------|
|RamUtils|https://github.com/dniklaus/arduino-utils-mem|Arduino Memory Utilities - helps to determine the free Ram that is currently available|
|App-Debug  |https://github.com/dniklaus/wiring-app-debug.git|Wiring application debug setup component - boilerplate code setting up all the debug environment such as CLI and Tracing and free RAM info printer                                                                                         |
|Battery |https://github.com/dniklaus/Battery|LiPo Battery Voltage Surveillance component |
|Arduino-LMIC library |https://github.com/mymichu/Arduino_LMIC#EuropeConfiguration|IBM LMIC (LoraMAC-in-C) library for Arduino environment, allowing using the SX1272, SX1276 transceivers and compatible modules (such as some HopeRF RFM9x modules and the Murata LoRa modules). |

