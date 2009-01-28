/*
 * DiagnosticPanel.h
 * VORTRAC
 *
 *  Created by Lisa Mauger on 04/09/06
 *  Copyright 2006 University Corporation for Atmospheric Research.
 *  All rights reserved.
 *
 *
 */

#ifndef DIAGNOSTICPANEL_H
#define DIAGNOSTICPANEL_H

#include <QTimer>
#include <QLCDNumber>
#include <QPushButton>
#include <QColor>
#include <QTextEdit>
#include <QLineEdit>

#include "Message.h"
#include "StopLight.h"
#include "StormSignal.h"
#include "CappiDisplay.h"
#include "DataObjects/GriddedData.h"

class DiagnosticPanel : public QWidget
{

Q_OBJECT

 public:
      DiagnosticPanel(QWidget *parent = 0);
      ~DiagnosticPanel();

 public slots:
      void catchLog(const Message& message);
      void pickColor();
      void testLight();
      void testStormSignal();
      void updateVCP(const int newVCP);
      void changeStopLight(StopLightColor newColor, const QString newMessage);
      void changeStormSignal(StormSignalStatus status, 
			     const QString newMessage);
      //	  void updateCappi(const GriddedData* newCappi);
      //	  void launchCappi();
	  
 private:
      QTimer *timer;
      QLCDNumber *clock;

      QLineEdit *vcp;
      QString* vcpString;

      StopLight *lights;
      QLineEdit *stopLightWarning;
      int dummy, stormDummy;
      QList<int> colorsReceived;
      QList<QString> colorMessagesReceived;

      StormSignal *stormSignal;
      QLineEdit *stormSignalWarning;

      //QPushButton *cappiLaunch;
      //CappiDisplay *cappiDisplay;
      //const GriddedData *cappi;
      //bool hasNewCappi;

 private slots:
      void updateClock();

 protected:

 signals:
      void log(const Message& message); 

};

#endif