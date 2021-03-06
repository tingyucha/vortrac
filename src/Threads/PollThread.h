/*
 *  PollThread.h
 *  VORTRAC
 *
 *  Created by Michael Bell on 7/25/05.
 *  Copyright 2005 University Corporation for Atmospheric Research. 
 *	All rights reserved.
 *
 */

#ifndef POLLTHREAD_H
#define POLLTHREAD_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QList>
#include "Radar/RadarFactory.h"
#include "AnalysisThread.h"
#include "Config/Configuration.h"
#include "DataObjects/VortexList.h"
#include "DataObjects/SimplexList.h"
#include "DataObjects/GriddedData.h"
#include "Pressure/PressureFactory.h"
#include "Pressure/PressureList.h"

#include <QTextStream>

class PollThread : public QThread
{
  Q_OBJECT

  public:
	PollThread(QObject *parent = 0);
	~PollThread();
	void setConfig(Configuration *configPtr);
	
  public slots:
        void catchLog(const Message& message);
        void analysisDoneProcessing();
	void remoteFileFetchDone();
	void catchVCP(const int vcp);
	void catchCappi(const GriddedData* cappi);
	void catchCappiInfo(const float& x, const float& y, const float& rmwEstimate, const float& sMin,const float& sMax,
			    const float& vMax, const float& userLat, const float& userLon, const float& lat, const float& lon);
	void abortThread();
	void setOnlyRunOnce(const bool newRunOnce = true);
	void setContinuePreviousRun(const bool &decision);
       
  signals:
	void log(const Message& message);
	void newVCP(const int);
	void vortexListUpdate(VortexList* list);
	void dropListChanged(VortexList* list);
	void newCappi(const GriddedData* cappi);
	void newCappiInfo(const float& x, const float& y, const float& rmwEstimate, const float& sMin,const float& sMax,
			const float& vMax, const float& userLat, const float& userLon, const float& lat, const float& lon);
	
  protected:
	void run();

  private:
	QMutex mutex;
	bool runOnce;
	bool processPressureData;
	QWaitCondition waitForAnalysis;
	QWaitCondition waitForData;
	bool abort;
	bool continuePreviousRun;
	RadarFactory *dataSource;
	PressureFactory *pressureSource;
	Configuration *configData;
	VortexList *vortexList;
	SimplexList *simplexList;
	PressureList *pressureList;
	PressureList *dropSondeList;
	AnalysisThread *analysisThread;
	Configuration *vortexConfig;
	Configuration *simplexConfig;
	Configuration *pressureConfig;
	Configuration *dropSondeConfig;
	SimplexThread *simplexThread;
	VortexThread *vortexThread;

	void checkIntensification();
	void checkListConsistency();
	
};

#endif
