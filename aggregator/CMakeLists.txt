# Path to your arduino-cmake directory
set(CMAKE_ARDUINO_PATH /Users/halfdan-rump/projects/learning/arduino-cmake-master)
#set(CMAKE_MODULE_PATH ${CMAKE_ARDUINO_PATH}/cmake/modules) # CMake module search path
set(CMAKE_MODULE_PATH ${CMAKE_ARDUINO_PATH}/cmake/Platform/Arduino.cmake) # CMake module search path
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_ARDUINO_PATH}/cmake/ArduinoToolchain.cmake) # Arduino Toolchain
set(CMAKE_EXTERNAL_LIBS_PATH /Applications/Arduino.app/Contents/Resources/Java/libraries)
#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries)
#add_subdirectory(blink_led)


# Set the minimum required version of cmake for your project
cmake_minimum_required(VERSION 2.8)

# Set a variable for commands below
set(PROJECT_NAME chibi_aggregator)


link_directories(/Users/halfdan-rump/Documents/Arduino/libraries/chibiArduino/)
# Define your project and language
project(${PROJECT_NAME} C CXX)


###################################################################
###   ADD ALL ARDUINO-CMAKE COMMANDS AFTER THIS
###################################################################

register_hardware_platform(/Applications/Arduino.app/Contents/Resources/Java/hardware/mighty-1284p-freaklabs)
print_board_list()


#find_package(Arduino 1.0 REQUIRED)

# Define your Arduino board (below is for Arduino Duemilanova)
set(${PROJECT_NAME}_BOARD freakduino-lr)


# Define the source code
set(${PROJECT_NAME}_SRCS aggregator.ino)

# Define the port for uploading code to the Arduino
set(${PROJECT_NAME}_PORT /dev/ttyUSB0)

# Command to generate code arduino firmware (.hex file)
generate_arduino_firmware(${PROJECT_NAME})
