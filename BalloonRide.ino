#include <Arduino.h>
#include <EEPROM.h>
#include <IridiumSBD.h> // Satellite comms: http://arduiniana.org
#include <TinyGPS++.h>  // NMEA parsing: http://arduiniana.org
#include <SdFat.h>      // FAT filesystem for SD cards: https://github.com/greiman/SdFat
#include <OneWire.h>    // for DS18B20 thermometer
#include <Wire.h>       // I2C bus management for OLED Display
#include <Adafruit_GFX.h> // Adafruit base graphics library
#include <Adafruit_SSD1306.h> // Adafruit SSD1306 library
#include <Snooze.h>
//#include <TimeLib.h>
//#include <time.h>
#include "BalloonRide.h"

// State variables
static bool IridiumReentrant = false;
static bool setupComplete = false;

void setup()
{
  // Set up the status LED
  startLED();
  
  // Start the console port
  startConsole();

  // Greeting
  log(PROGRAMNAME " " VERSION "\r\n");
  log(COPYRIGHT "\r\n");
  log("Onwards and Upwards and Around the World!\r\n");
  log("\r\n");
  showCommands();

  // Set up the OLED display
  startDisplay();

  // Open SD log files
  startLogs();

  // Start up the thermal probes
  startThermalProbes();

  // Set up the GPS port
  startGPS();

  // Set up the RockBLOCK's serial port...
  startIridium();

  // Battery
  startBatteryMonitor();

  // Andrew
  AndrewsStartup();
  
  // All done with initialization!
  setupComplete = true;
}

void loop()
{
  processGPS();
  processThermalData();
  processBatteryData();
  processLogs();
  if (!IridiumReentrant)
    processIridium();
  processLED();
  processDisplay();
  processConsole();
  RunScheduler();
}

// Recursively call loop during lengthy Iridium operations!
bool ISBDCallback()
{
  if (setupComplete)
  {
    IridiumReentrant = true;
    loop();
    IridiumReentrant = false;
  }
  
  return true;
}


