# Path to script folder
set(SATOYAMA_LIBS ${CMAKE_CURRENT_SOURCE_DIR}/../satoyama-libs)

# Path to arduino-cmake
set(CMAKE_ARDUINO_PATH ${SATOYAMA_LIBS}/arduino-cmake)


#set(CMAKE_MODULE_PATH ${CMAKE_ARDUINO_PATH}/cmake/Platform/Arduino.cmake)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_ARDUINO_PATH}/cmake/ArduinoToolchain.cmake) # Arduino Toolchain


# Set the minimum required version of cmake for your project
cmake_minimum_required(VERSION 2.8)

# Set a variable for commands below
set(PROJECT_NAME chibi_aggregator)

link_directories(${SATOYAMA_LIBS}/chibiArduino-master/)
link_directories(${SATOYAMA_LIBS}/SatoyamaChibiLib/)

# Define your project and language
project(${PROJECT_NAME} C CXX)


###################################################################
###   ADD ALL ARDUINO-CMAKE COMMANDS AFTER THIS
###################################################################


set(${PROJECT_NAME}_BOARD freakduino-lr)
#register_hardware_platform(/Applications/Arduino.app/Contents/Resources/Java/hardware/mighty-1284p-freaklabs)
register_hardware_platform(${SATOYAMA_LIBS}/mighty-1284p-freaklabs)

#set(${PROJECT_NAME}_BOARD freakduino-lr)
#set(${PROJECT_NAME}_BOARD pro328)
#register_hardware_platform(/Applications/Arduino.app/Contents/Resources/Java/hardware/mighty-1284p-freaklabs)
#print_board_list()

# Define the source code
set(${PROJECT_NAME}_SRCS aggregator.cpp)

# Define the port for uploading code to the Arduino
IF(APPLE)
  set(${PROJECT_NAME}_PORT /dev/tty.usbserial-A90178AU)
ELSE()
  set(${PROJECT_NAME}_PORT /dev/tty.usbserial-A501KA6M)
ENDIF()

# Command to generate code arduino firmware (.hex file)
generate_arduino_firmware(${PROJECT_NAME})
