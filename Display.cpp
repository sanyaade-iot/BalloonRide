#include <Arduino.h>
#include <Adafruit_GFX.h> // Adafruit base graphics library
#include <Adafruit_SSD1306.h> // Adafruit SSD1306 library
#include "BalloonRide.h"

/*
 * Handle the OLED display mounted outside the chassis
 */

static Adafruit_SSD1306 display;
static bool started = false;

#define ADAFRUIT128x96 false
#define TWOCOLOR128x64 true

#if ADAFRUIT128x96
#define I2C_ADDR 0x3D
#define ROWS 96
#define BIGTEXTSIZE 3
#endif

#if TWOCOLOR128x64
#define I2C_ADDR 0x3C
#define ROWS 64
#define BIGTEXTSIZE 1
#endif

//------------------------------------------------------------------------------
// File generated by LCD Assistant
// http://en.radzio.dxp.pl/bitmap_converter/
//------------------------------------------------------------------------------

static const unsigned char SundialLogo[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x07, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFC, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x01, 0x7F, 0xFE, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0x80, 0x00, 0x04, 0x00, 0x00, 0x00,
0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xFD, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x02, 0x00, 0x00, 0x00,
0x00, 0x00, 0x08, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x01, 0x00, 0x00, 0x00,
0x00, 0x00, 0x10, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x10, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x20, 0x00, 0x04, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x40, 0x00, 0x00,
0x00, 0x00, 0x40, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x20, 0x00, 0x00,
0x00, 0x00, 0x40, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x20, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x10, 0x00, 0x00,
0x00, 0x00, 0x80, 0x07, 0xC7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x10, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x10, 0x00, 0x00,
0x00, 0x01, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x08, 0x00, 0x00,
0x00, 0x01, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x08, 0x00, 0x00,
0x00, 0x01, 0x00, 0x7F, 0xC7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x08, 0x00, 0x00,
0x00, 0x01, 0x00, 0x1E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x08, 0x00, 0x00,
0x00, 0x01, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x08, 0x00, 0x00,
0x00, 0x01, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x08, 0x00, 0x00,
0x00, 0x01, 0x00, 0x3F, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00, 0x71, 0xF9, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x0E, 0x07, 0xE7, 0xFD, 0xFF, 0x7C, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x01, 0xFF, 0x80, 0x03, 0xFF, 0x18, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
0x00, 0x00, 0x40, 0x00, 0x00, 0x7E, 0x00, 0x07, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00,
0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00,
0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x40, 0x00, 0x00,
0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x01, 0x00, 0x00, 0x00,
0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x02, 0x00, 0x00, 0x00,
0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x04, 0x00, 0x00, 0x00,
0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x07, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFC, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void startDisplay()
{
  consoleText(F("Starting display..."));
  display.begin(SSD1306_SWITCHCAPVCC, I2C_ADDR);  // initialize with the I2C addr 0x3D (for the 128x64)
  started = true;
  display.clearDisplay();
#if ADAFRUIT128x96
  display.drawBitmap(0, 0, SundialLogo, 128, ROWS, WHITE);
  display.invertDisplay(true);
  display.display();
  delay(3000);
#endif
  
  // Clear the buffer.
  display.invertDisplay(false);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.display();
  display.setCursor(0, 0);
  display.println("BalloonRide 6.00");
  display.println("(C) 2015-7 ICBC");
  display.display();
  delay(2000); // allow display message to sink in
  display.clearDisplay();
  display.setCursor(0, 0);
  display.display();
  consoleText(F("done.\r\n"));
}

void processDisplay()
{
  static unsigned long lastDisplayTime = 0UL;
  unsigned long now = millis() / 1000;

  // Display only once per second
  if (now != lastDisplayTime)
  {
    lastDisplayTime = now;
    display.clearDisplay();

    // Mission time
    unsigned hour = (unsigned)(now / 3600);
    unsigned minute = (unsigned)((now - 3600UL * hour) / 60);
    unsigned second = (unsigned)(now % 60);
    display.setCursor(0, 0);
    display.print(hour < 10 ? "0" : "");
    display.print(hour);
    display.print(minute < 10 ? ":0" : ":");
    display.print(minute);
    display.print(second < 10 ? ":0" : ":");
    display.print(second);
    display.print(" ");

    // "Transmitting"
    display.println(getIridiumInfo().isTransmitting && now % 2 == 0 ? "Transmitting" : "");

    // Time since fix
    display.print("Fix: ");
    long age = getGPSInfo().age / 1000;
    if (!getGPSInfo().fixAcquired)
    {
      display.print("None. ");
    }
    else if (age > 15 && now % 2 == 1) // flash if no GPS in >15 seconds
    {
      display.print("      ");
    }
    else if (age < 10)
    {
      display.print("Ok.   ");
    }
    else
    {
      display.print(age);
      if (age < 1000) display.print(" ");
      if (age < 100) display.print(" ");
      if (age < 10) display.print(" ");
      display.print(" ");
    }

    // Time since last successful transmission
    display.print("X: ");
    age = (millis() - getIridiumInfo().xmitTime1) / 1000;
    
    if (getIridiumInfo().xmitTime1 == 0UL)
    {
      display.println("None.");
    }
    else if (age > 15 * 60 && now % 2 == 1) // flash if no Xmit in >15 minutes
    {
      display.println("     ");    
    }
    else
    {
      minute = (unsigned)((age % 3600) / 60);
      second = (unsigned)(age % 60);
      display.print(minute < 10 ? "0" : "");
      display.print(minute > 99 ? 99 : minute);
      display.print(":");
      display.print(second < 10 ? "0" : "");
      display.print(second);
      display.println();
    }

#if ADAFRUIT128x96
    display.println();
    display.setTextSize(BIGTEXTSIZE);
    switch((now / 5) % 2)
    {
      case 0:
        if (getGPSInfo().altitude < 10000)
          display.print(" ");
        if (getGPSInfo().altitude == 0) 
        {
          display.print("---");
        }
        else 
        {
          display.print(getGPSInfo().altitude);
          display.print("m");
        }
        break;
      case 1:
        if (getThermalInfo().temperature[1] >= 0)
          display.print(" ");
        display.print(getThermalInfo().temperature[1], 1);
        display.print("C");
        break;
    }
#else
    display.print(F("ALT: "));
    if (getGPSInfo().altitude < 10000)
      display.print(" ");
    if (getGPSInfo().altitude == 0) 
    {
      display.print("--- ");
    }
    else 
    {
      display.print(getGPSInfo().altitude);
      display.print("m ");
    }
    display.print("ET: ");
    if (getThermalInfo().temperature[1] >= 0)
      display.print(" ");
    if (getThermalInfo().temperature[1] == INVALID_TEMPERATURE)
      display.print(" --- ");
    else
    {
      display.print(getThermalInfo().temperature[1], 1);
      display.print("C");
    }
#endif

    // Voltage and message count
#if ADAFRUIT128x96
    display.setTextSize(1);
    display.setCursor(0, 64 - 7);
#else
    display.println();
#endif

    display.print(getBatteryInfo().batteryVoltage, 2);
    display.print("V XC:");
    display.print(getIridiumInfo().count);
    display.print(" IT:");
    display.print(getThermalInfo().temperature[0], 1);
    display.display();
  }
}

void displayText(const char *str)
{
  if (started)
  {
    display.print(str);
    display.display();
  }
}

void displayText(int n)
{
  if (started)
  {
    display.print(n);
    display.display();
  }
}

void displayText(FlashString fs)
{
  if (started)
  {
    display.print(fs);
    display.display();
  }
}
