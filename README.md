satoyama-edge
=============
Satoyama edge router stack: Raspberry pie, noobs and python

## Installation

## NOOBS installation

1. Format the SD Card using SDFormatter.
2. Download the latest NOOBS version.
3. Insert the SD Card in the Raspberry Pi
4. Connect HDMI cable, RJ45 network cable, keyboard and power supply cable to the raspberry pie
5. Follow the installation instructions for Raspbian (The Raspberry OS). This is the first screen that you will see:.
6. When the install process has completed, the Raspberry Pi configuration menu (raspi-config) will load. Here you are able to set the time and date for your region and enable a Raspberry Pi camera board, or even create users.  Use TAB to go until Finish and press ENTER.
7. The default login for Raspbian is username pi with the password raspberry.
8. ifconfig. To make sure you are connected to the internet. If you are not... fix it.. it's probably your company's firewall ;)
9. git clone https://github.com/DgFutureLab/satoyama-edge.git (If your NOOBs does not have git installed, install it before using apt-get)
10. cd satoayama-edge
11. sudo apt-get update
12. sudo apt-get install python-setuptools
13. 

