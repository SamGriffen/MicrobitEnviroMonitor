# MicrobitEnviroMonitor
ESP based webserver for displaying data from weather:bit. This project will allow for the sparkfun weather:bit to send data to an ESP32, which will then display the data on a local webpage. The ESP32 must have a network to connect to, it does not create it's own local access point.
 
 ![web interface](/img/screenshot.png)
 
# MicroBit Code
MicroBit code can be downloaded here: https://makecode.microbit.org/_66RTrKJwsf48
The hex file can be found in the `microbit` folder of the repository.
 
 # Setup
 After cloning the repository, the project can be opened in PlatformIO. Web data is loaded into the SPIFFs storage on the ESP32, and the platformio config files are setup to allow for this. To install out of the box you must do the following:
 
 - Edit `ssid` and `password` at the top of the file to contain your WiFi network credentials.
 - Plug in ESP32.
 - From terminal, run `pio run --target uploadfs` in the root directory of the project. This will upload all web files to the ESP.
 - The project can then be uploaded as per usual.
 - Once running, the IP address of the ESP should be logged to the serial monitor (If DEBUG is defined). Navigate to this in a web browser, and the interface should appear.
 
 # Wiring Notes
 The following connections need to be made:
 weather:bit RX --> ESP32 GPIO17
 weather:bit TX --> ESP32 GPIO16
 weather:bit GND --> ESP32 GND
