/*
 *  Message.h 
 *  VORTRAC
 *
 *  Created by Michael Bell on 7/14/05.
 *  Copyright 2005 University Corporation for Atmospheric Research.
 *  All rights reserved.
 *
 */

// Process error messages

#ifndef ERROR_H
#define ERROR_H

#include <QMessageBox>
#include <iostream>
#include <QString>

class Message
{

 public:


  enum StopLightColor{
    AllOff,
    BlinkRed,
    Red,
    BlinkYellow,
    Yellow,
    BlinkGreen,
    Green,
    AllOn
  };

  enum StormSignalStatus {
    rapidIncrease,
    rapidDecrease,
    ok
  };

  Message(const char *errormsg = 0, int newProgress = 0, 
	  const char *newLocation = 0, 
	  StopLightColor newColor = Green, const char *newStopLightMessage = 0,
	  StormSignalStatus newStatus = ok, 
	  const char *newStormSignalMessage = 0);

  Message(const QString errormsg = QString(), int newProgress = 0,
	  const QString newLocation = QString(), 
	  StopLightColor newColor = Green, 
	  const QString newStopLightMessage = QString(), 
	  StormSignalStatus newStatus = ok, 
	  const QString newStormSignalMessage = QString());

  ~Message();

  QString getLogMessage() { return logMessage; }
  void setLogMessage(const QString newLogMessage);
  void setLogMessage(const char *newLogMessage);

  int getProgress() { return progress; }
  void setProgress(int progressPercentage);

  QString getLocation() { return location; }
  void setLocation(const QString newLocation);
  void setLocation(const char *newLocation);

  StopLightColor getColor() { return color; }
  void setColor(StopLightColor newColor);

  QString getStopLightMessage() { return stopLightMessage; }
  void setStopLightMessage(const QString newStopLightMessage);
  void setStopLightMessage(const char *newStopLightMessage);

  StormSignalStatus getStatus() { return status; }
  void setStatus(StormSignalStatus newStatus);
  
  QString getStormSignalMessage() { return stormSignalMessage; }
  void setStormSignalMessage(const QString newMessage);
  void setStormSignalMessage(const char *newMessage);
  
  static void report(const char *errormsg);
  static void report(const QString errormsg);
  static void toScreen(const char *message);
  static void toScreen(const QString message);

 private:
  QString logMessage;
  int progress;
  QString location;
  StopLightColor color;
  QString stopLightMessage;
  StormSignalStatus status;
  QString stormSignalMessage;

};

#endif
