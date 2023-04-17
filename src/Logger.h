#pragma once
#include <SD.h>
#include <SPI.h>
#include <string>

class Logger {
private:
  bool failed = false;
  std::string filename = "null.log";
  File txtFile;

  void write(std::string msg);
public:
  void setup_logging(std::string category, std::string header);
  void log(std::string msg);
  void logf(std::string format, ...);
};