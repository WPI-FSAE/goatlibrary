#include <Logger.h>
#include <TimeLib.h>
// Open sourced code found from
// https://www.arduinolibraries.info/libraries/sd
// SD-1.2.4.zip -> examples -> file read write
void Logger::setup_logging(std::string category, std::string header) {
  Serial.println("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }

  Serial.println("sd card initialized");

  char buf[40];
  snprintf(buf, 40, "%s_%d-%d-%d_%2d:%2d.log", category.c_str(), year(), month(), day(), hour(), minute());
  filename = std::string(buf);

  this->log("good morning! (i reset)");
  this->write("time\t" + header);
}

void Logger::write(std::string msg) {
  txtFile = SD.open(filename.c_str(), FILE_WRITE);
  if (!txtFile) {
    Serial.print("error opening ");
    Serial.println(filename.c_str());
    return;
  }
  txtFile.write(msg.c_str(), msg.length());
  txtFile.close();
}

void Logger::log(std::string msg) {
  char buf[500];
  snprintf(buf, 500, "[%d:%d:%d]\t", hour(), minute(), second());
  write(std::string(buf).append(msg).append("\n"));
}

void Logger::logf(std::string format, ...) {
  char buf[500];
  va_list args; // https://stackoverflow.com/a/20980016
  va_start(args, format);
  vsnprintf(buf, 500, format.c_str(), args);
  va_end(args);
  this->log(buf);
}