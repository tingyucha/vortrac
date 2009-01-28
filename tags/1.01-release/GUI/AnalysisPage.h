/*
 * AnalysisPage.h
 * VORTRAC
 *
 * Created by Michael Bell on 7/21/05
 *  Copyright 2005 University Corporation for Atmospheric Research.
 *  All rights reserved.
 *
 *
 */

#ifndef ANALYSISPAGE_H
#define ANALYSISPAGE_H

#include <QWidget>
#include <QTextEdit>
#include <QFile>
#include "Config/Configuration.h"
#include "IO/Log.h"
#include "ConfigTree.h"
#include "Threads/PollThread.h"
#include "GraphFace.h"
#include "ConfigurationDialog.h"
#include "DiagnosticPanel.h"
#include "CappiDisplay.h"

//#include "TestGraph.h"

class AnalysisPage : public QWidget
{

  Q_OBJECT

 public:

  AnalysisPage(QWidget *parent = 0);
  ~AnalysisPage();

  void newFile();
  bool loadFile(const QString &fileName);
  bool save();
  bool saveAs();
  bool saveFile(const QString &fileName);
  QString getVortexLabel() { return vortexLabel; }
  QString currentFile() { return configFileName; }
  QDir getWorkingDirectory() { return workingDirectory; }
  void setVortexLabel();
  bool maybeSave();
  void saveDisplay();
  

  GraphFace *getGraph() {return graph;}
  Log* getStatusLog(){ return statusLog;} 
  ConfigurationDialog* getConfigDialog(){ return configDialog;}
  Configuration* getConfiguration() {return configData;}
  bool isRunning();

  public slots:
    void saveLog();
    void catchLog(const Message& message); 
    void catchVCP(const int vcp); 
    void updateCappi(const GriddedData* cappi);
    void updateCappiInfo(const float& x, const float& y, const float& sMin, 
			 const float& sMax, const float& vMax);
    void updateCappiDisplay(bool hasImage);

    // void changeStopLight(StopLightColor color, const QString message);
    // void changeStormSignal(StormSignalStatus status, const QString message);
	
 signals:
    void tabLabelChanged(QWidget* labelWidget, const QString& new_Label);
    void log(const Message& message);
    void saveGraphImage(const QString& name);
    void vortexListChanged(VortexList* list);
    void newVCP(const int vcp);
    void newCappi(const GriddedData* cappi);
    void newCappiInfo(const float& x, const float& y, const float& sMin, 
		      const float& sMax, const float& vMax);

    //void newStormSignalStatus(StormSignalStatus status, const QString message);
    //void newStopLightColor(StopLightColor color, const QString message);
	
 private slots:
    void updatePage();
    void runThread();
    void abortThread();
    void autoScroll();
    void prepareToClose();
    void pollVortexUpdate(VortexList* list);

 protected:
  void closeEvent(QCloseEvent *event);

 private:
  QString vortexLabel;
  QString configFileName;
  Configuration *configData;
  // ConfigTree *configTree;
  DiagnosticPanel *diagPanel;
  Log *statusLog;
  QTextEdit *statusText;
  int lastMax;
  PollThread *pollThread;
  bool isUntitled;
  GraphFace* graph;
  ConfigurationDialog *configDialog;
  QDir workingDirectory;
  QString imageFileName;
  QLCDNumber *currPressure;
  QLCDNumber *currRMW;
  QLCDNumber *currDeficit;
  QTabWidget* visuals;
  CappiDisplay* cappiDisplay;
  QLCDNumber *appMaxWind;
  QLCDNumber *recMaxWind;
  QLabel* deficitLabel;
  //  TestGraph *tester;

  bool analyticModel();

};

#endif