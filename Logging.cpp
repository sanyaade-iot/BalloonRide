#include <Arduino.h>
#include <SdFat.h>      // FAT filesystem for SD cards: https://github.com/greiman?tab=repositories
#include <time.h>
#include "BalloonRide.h"

/*
 * Handle logging to the three SD card logs: runlog, telemetry, Iridium
 */

// File objects
static SdFatSdio sd;
static File RunLog, TelemetryLog/*, IridiumLog*/;
static bool sdfail = false;
bool SDFail() { return sdfail; }

void startLogs()
{
  consoleText("Checking SD...");
  displayText("Checking SD...");

  if (!sd.begin())
  {
    consoleText("SD Init failed.\r\n");
    displayText("fail.\r\n");
    // fatal(BALLOON_ERR_SD_INIT);
    sdfail = true;
    return;
  }
  
  char dirname[32];
#if false
  // First, find an unused directory name
  for (uint32_t i=0; ; ++i)
  {
    sprintf(dirname, "/%08lu", i);
    if (!sd.exists(dirname))
      break;
  }
#else
  time_t now = Teensy3Clock.get();
  struct tm *tnow = localtime(&now);
  sprintf(dirname, "%d-%02d-%02d-%02d-%02d-%02d", 1900 + tnow->tm_year, 1 + tnow->tm_mon, tnow->tm_mday, tnow->tm_hour, tnow->tm_min, tnow->tm_sec);
#endif

  if (!sd.mkdir(dirname) || !sd.chdir(dirname, true))
  {
    consoleText("Couldn't create directory.\r\n");
    displayText("fail2.\r\n");
    displayText(dirname);
    delay(2000);
    // fatal(BALLOON_ERR_SD_INIT);
    sdfail = true;
    return;
  }
  
  consoleText(F("Directory created: "));
  consoleText(dirname);
  consoleText("\r\n");

  if (!RunLog.open("run.log", O_CREAT | O_TRUNC | O_WRITE) ||
      !TelemetryLog.open("telemetry.log", O_CREAT | O_TRUNC | O_WRITE) /*||
      !IridiumLog.open("iridium.log", O_CREAT | O_TRUNC | O_WRITE)*/)
  {
    consoleText("Couldn't create log files.\r\n");
    displayText("fail3.\r\n");
    // fatal(BALLOON_ERR_LOG_FILE);
    sdfail = true;
    return;
  }

  consoleText("done.\r\n");
  displayText("OK.\r\n");
}

void processLogs()
{
  static unsigned long lastLogTime = 0UL;
  unsigned long now = millis() / 1000;

  // Do logging stuff once per second
  if (now != lastLogTime)
  {
    // First, create a new record for the telemetry log
    const GPSInfo &ginf = getGPSInfo();
    const BatteryInfo &binf = getBatteryInfo();
    const ThermalInfo &tinf = getThermalInfo();
    const IridiumInfo &iinf = getIridiumInfo();
    const BalloonInfo &balinf = getBalloonInfo();
    
    lastLogTime = now;
    char logBuffer[500] = "";
    snprintf(logBuffer, sizeof(logBuffer),
      "<LOG time=\"%lu\" batt=\"%.2f\" T-int=\"%.2f\" T-ext=\"%.2f\" G-fix=\"%s\" G-loc=\"%.6f,%.6f\" G-alt=\"%ld\" "
      "G-time=\"%04d-%02d-%02d %02d:%02d:%02d\" G-chk-fail=\"%lu\" I-xmit=\"%ld\" I-fail=\"%ld\" "
      "I-msg1=\"%s\" G-sats=\"%d\" G-age=\"%ld\" I-age=\"%ld\" I-msg2=\"%s\" G-speed=\"%.2f\" G-course=\"%03d\" "
      "B-ground=\"%ld\" B-maxalt=\"%ld\" B-state=\"%s\" B-descend=\"%s\" B-horiz=\"%.2f\" B-vert=\"%lu\" />\r\n",
      now,
      binf.batteryVoltage,
      tinf.temperature[0],
      tinf.temperature[1],
      ginf.fixAcquired ? "true" : "false",
      ginf.latitude,
      ginf.longitude,
      ginf.altitude,
      ginf.year,
      ginf.month,
      ginf.day,
      ginf.hour,
      ginf.minute,
      ginf.second,
      ginf.checksumFail,
      iinf.count,
      iinf.failcount,
      iinf.transmitBuffer1,
      ginf.satellites,
      ginf.age,
      now - iinf.xmitTime1 / 1000,
      iinf.transmitBuffer2,
      ginf.speed,
      (int)ginf.course,
      balinf.groundAltitude,
      balinf.maxAltitude,
      balinf.flightState == BalloonInfo::INFLIGHT ? "flight" : balinf.flightState == BalloonInfo::LANDED ? "landed" : "ground",
      balinf.isDescending ? "true" : "false",
      balinf.lateralTravel,
      balinf.verticalTravel);

    TelemetryLog.print(logBuffer);
    RunLog.print(logBuffer);
    if (getConsoleViewFlags() & (LOG_TELEMETRY | LOG_RUNLOG))
      consoleText(logBuffer);

    // Then flush all the logs in case the system halts for some reason
    RunLog.sync();
    TelemetryLog.sync();
    //IridiumLog.sync();
  }
}

// Print a message to program log and to console
static char buf[500];
void log(const char *fmt, ...)
{
  va_list argp;
  va_start(argp, fmt);
  vsnprintf(buf, sizeof buf, fmt, argp);
  va_end(argp);
 
  RunLog.print(buf);
  if (getConsoleViewFlags() & LOG_RUNLOG)
    consoleText(buf);
}

extern void log(FlashString fmt, ...)
{
  va_list argp;
  va_start(argp, fmt);
  vsnprintf_P(buf, sizeof buf, (PGM_P)fmt, argp);
  va_end(argp);
 
  RunLog.print(buf);
  if (getConsoleViewFlags() & LOG_RUNLOG)
    consoleText(buf);
}

void log(char c)
{
  RunLog.write(c);
  if (getConsoleViewFlags() & LOG_RUNLOG)
    consoleText(c);
}

void iridiumLog(char c)
{
  //IridiumLog.write(c);
  RunLog.write(c);
  if (getConsoleViewFlags() & LOG_IRIDIUM)
    consoleText(c);
}

void showLog(LOGTYPE whichLog)
{
  File log;
  const char *name = whichLog == LOG_TELEMETRY ? "telemetry.log" : /*whichLog == LOG_IRIDIUM ? "iridium.log" : */ "run.log";
  if (!log.open(name, O_READ))
  {
    consoleText(F("Error: Could not open "));
    consoleText(name);
    consoleText(F("\r\n"));
    return;
  }

  consoleText(F("*************************************\r\n"));
  consoleText(name);
  consoleText("\r\n");
  consoleText(F("*************************************\r\n"));
  while (log.available())
    consoleText((char)log.read());
  consoleText(F("*************************************\r\n"));

  log.close();
  
}

