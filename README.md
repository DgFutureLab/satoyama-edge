satoyama-edge
=============
The edge node consists of a chibi and a Raspberry Pi. The Chibi forwards everything it receives on the radio to the raspi via a serial port, and the raspi parses the input and uploads the data to satoyama-api. 

# Installation

## NOOBS installation

1. Format the SD Card using SDFormatter.
2. Download the latest NOOBS version. (You may find it here: http://www.raspberrypi.org/downloads/ )
3. Insert the SD Card in the Raspberry Pi
4. Connect HDMI cable, RJ45 network cable, keyboard and power supply cable to the raspberry pie
5. Follow the installation instructions for Raspbian (The Raspberry OS). This is the first screen that you will see:.
6. When the install process has completed, the Raspberry Pi configuration menu (raspi-config) will load. Here you are able to set the time and date for your region and enable a Raspberry Pi camera board, or even create users.  Use TAB to go until Finish and press ENTER.

## Setup raspi
7. The default login for Raspbian is username pi with the password raspberry.
8. ifconfig. To make sure you are connected to the internet. If you are not... fix it.. it's probably your company's firewall ;)
9. sudo apt-get update
10. sudo apt-get install python-setuptools
11. git clone https://github.com/DgFutureLab/satoyama-edge.git (If your NOOBs does not have git installed, install it before using apt-get)
12. cd satoyama-edge
13. git submodule update --init --recursive
14. sudo easy_install pip
15. sudo pip install -r requirements.txt

## Setup Chibi
Upload aggregator.ino to the chibi and connect the chibi to the raspberry pi with a USB cable.

## Setup build system with CMake
Before we wrote the sketches using the Arduino GUI, but now we use standard CMake to generate make files.

1. Install CMake (e.g. brew install cmake on OSX)
2. Change directory into satoyama-edge/aggegrator
3. mkdir build (all the build files will be stored in this directory)
4. Navigate to build directory: cd build 
5. compile source code and upload to the device: cmake .. -Wno-dev && make && make upload (make sure that the build directory is empty, as CMake will complain otherwise)
6. Use screen to monitor output from the serial device (e.g. tty.usbserial-A501K9HW): /dev/tty.usbserial-A501K9HW 57600,sc8

## Run edge router
The run_edge.py script launches two processes. One constantly listens to the serial port and parses the data from the Chibi connected to the raspi. The other process uploads the information to a webserver with regular intervals. 

12. cd satoayama-edge
13. python run_edge.py --help
13. python run_edge.py --host <your.host.name> --port
